// All rights Neebula Games

#include "VoidSpace.h"
#include "SpaceSuitActor.h"
#include "InteractableComponent.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"
#include "SpaceCharacter.h"


// Sets default values
ASpaceSuitActor::ASpaceSuitActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = root;

	InteractableComponent = ObjectInitializer.CreateDefaultSubobject<UInteractableComponent>(this, TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> spaceSuit(TEXT("StaticMesh'/Game/Meshes/SpaceSuit.SpaceSuit'"));
	SpaceSuitComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SpaceSuit"));
	SpaceSuitComponent->SetupAttachment(RootComponent);
	SpaceSuitComponent->SetStaticMesh(spaceSuit.Object);

	ConstructorHelpers::FObjectFinder<UParticleSystem> SmokeJetpack(TEXT("ParticleSystem'/Game/Particles/P_JetpackSmoke.P_JetpackSmoke'"));

	jetpackSmoke1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("JetpackSmoke1"));
	jetpackSmoke1->SetupAttachment(RootComponent);
	jetpackSmoke1->Template = SmokeJetpack.Object;
	jetpackSmoke1->RelativeLocation = FVector(0.f, -50.f, 0.f);
	jetpackSmoke1->Deactivate();

	jetpackSmoke2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("JetpackSmoke2"));
	jetpackSmoke2->SetupAttachment(RootComponent);
	jetpackSmoke2->Template = SmokeJetpack.Object;
	jetpackSmoke2->RelativeLocation = FVector(0.f, 50.f, 0.f);
	jetpackSmoke2->Deactivate();

	static ConstructorHelpers::FObjectFinder<USoundWave> zipperSound(TEXT("SoundWave'/Game/Sounds/zipper.zipper'"));
	Zipper = zipperSound.Object;

	OxygenDelta = 100.f / OxygenTime;
}

void ASpaceSuitActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bCountingDown)
	{
		TimeRemaining -= DeltaSeconds;

		if (TimeRemaining <= 0.f && GameEventManager->GetCurrentEvent()->DeathReason != 2)
			ASpaceGameStateBase::Instance(GetWorld())->Die(GameEventManager->GetCurrentEvent()->DeathReason);
	}
}

void ASpaceSuitActor::StartConsumingOxygen()
{
	if (!bConsumingOxygen)
	{
		bCountingDown = GameEventManager->IsCounting();
		TimeRemaining = GameEventManager->GetTime();

		GameEventManager->OnEventStarted.AddDynamic(this, &ASpaceSuitActor::OnEventStarted);
		GameEventManager->OnEventFinished.AddDynamic(this, &ASpaceSuitActor::OnEventFinished);

		GameEventManager->SetTime(OxygenTime, true);

		SetupInput();
	}

	bConsumingOxygen = true;
}

void ASpaceSuitActor::StopConsumingOxygen()
{
	OxygenTime = GameEventManager->GetTime();
	GameEventManager->SetTime(TimeRemaining, bCountingDown);

	GameEventManager->OnEventStarted.RemoveDynamic(this, &ASpaceSuitActor::OnEventStarted);
	GameEventManager->OnEventFinished.RemoveDynamic(this, &ASpaceSuitActor::OnEventFinished);

	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	bConsumingOxygen = false;
}

float ASpaceSuitActor::GetRemainingOxygen() const
{
	if (bActive && bConsumingOxygen)
		return GameEventManager->GetTime();
	return OxygenTime;
}

bool ASpaceSuitActor::IsConsumingOxygen() const
{
	return bConsumingOxygen;
}

// Called when the game starts or when spawned
void ASpaceSuitActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnTriggerAction.AddDynamic(this, &ASpaceSuitActor::OnSuitTrigger);

	GameEventManager = ASpaceGameStateBase::Instance(GetWorld())->GameEventManager;
}

void ASpaceSuitActor::MoveForward(float Val)
{
	if (ASpaceGameStateBase::Instance(GetWorld())->bMovementAllowed)
	{
		if(Val != 0.0f)
		{
			float yaw = static_cast<float>(FMath::RadiansToDegrees(acos(-Val)));
			if (yaw > -90.f && yaw < 90.f)
			{
				jetpackSmoke1->Activate();
				jetpackSmoke2->Activate();
				jetpackSmoke1->RelativeRotation = jetpackSmoke2->RelativeRotation = FRotator(0.f, yaw, 0.f);
			}
			else
			{
				jetpackSmoke1->Deactivate();
				jetpackSmoke2->Deactivate();
			}
			forwardAxisVal = Val;
		}
		else
		{
			jetpackSmoke1->Deactivate();
			jetpackSmoke2->Deactivate();
		}
	}
}

void ASpaceSuitActor::MoveHorizontal(float Val)
{
	if (ASpaceGameStateBase::Instance(GetWorld())->bMovementAllowed && Val != 0.0f)
	{
		float angleYAxisInRadians = static_cast<float>(fmod(0.5 * PI - atan2(-forwardAxisVal, -Val), 2.0 * PI));
		float angleYAxis = FMath::RadiansToDegrees(angleYAxisInRadians);
		if (angleYAxis > -90.f && angleYAxis < 90.f)
		{
			jetpackSmoke1->Activate();
			jetpackSmoke2->Activate();
			jetpackSmoke1->RelativeRotation = jetpackSmoke2->RelativeRotation = FRotator(0.f, angleYAxis, 0.f);
		}
		else
		{
			jetpackSmoke1->Deactivate();
			jetpackSmoke2->Deactivate();
		}
		forwardAxisVal = 0.f;
	}
}

void ASpaceSuitActor::OnSuitTrigger()
{
	float delay = 1.0f;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.f, 1.f, delay, FLinearColor::Black, false, true);

	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
	state->bMovementAllowed = false;
	state->bInteractionAllowed = false;

	static FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &ASpaceSuitActor::OnFadeOutFinish, delay);
}

void ASpaceSuitActor::OnFadeOutFinish()
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	bActive = !bActive;

	if (character)
	{
		character->ToggleSpaceSuit(bActive ? this : nullptr);
	}

	UGameplayStatics::PlaySound2D(GetWorld(), Zipper);

	SpaceSuitComponent->ToggleVisibility();
	SpaceSuitComponent->ToggleActive();

	static FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &ASpaceSuitActor::OnSoundFinished, Zipper->Duration);
}

void ASpaceSuitActor::OnSoundFinished()
{
	float delay = 1.0f;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.f, 0.f, delay, FLinearColor::Black);

	static FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &ASpaceSuitActor::OnFadeInFinished, delay);
}

void ASpaceSuitActor::OnFadeInFinished()
{
	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
	state->bMovementAllowed = true;
	state->bInteractionAllowed = true;
}

void ASpaceSuitActor::OnEventStarted()
{
	bCountingDown = GameEventManager->IsCounting();
	TimeRemaining = GameEventManager->GetTime();

	GameEventManager->SetTime(OxygenTime, true);
}

void ASpaceSuitActor::OnEventFinished()
{
	OxygenTime = GameEventManager->GetTime();
}

void ASpaceSuitActor::SetupInput()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(InputComponent);

	InputComponent->BindAxis("Forward", this, &ASpaceSuitActor::MoveForward).bConsumeInput = false;
	InputComponent->BindAxis("Horizontal", this, &ASpaceSuitActor::MoveHorizontal).bConsumeInput = false;
}
