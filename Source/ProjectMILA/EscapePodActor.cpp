// All rights Neebula Games

#include "ProjectMILA.h"
#include "EscapePodActor.h"
#include "EscapePodAnimInstance.h"
#include "SpaceGameStateBase.h"
#include "SpaceCharacter.h"
#include "LevelSequence.h"
#include "MovieSceneSequencePlayer.h"
#include "LevelSequencePlayer.h"


// Sets default values
AEscapePodActor::AEscapePodActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> escapePod(TEXT("SkeletalMesh'/Game/Meshes/Props/EscapePod/EscapePod.EscapePod'"));
	EscapePodMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Escape Pod"));
	RootComponent = EscapePodMeshComponent;
	EscapePodMeshComponent->SetSkeletalMesh(escapePod.Object);
	EscapePodMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	static ConstructorHelpers::FObjectFinder<UClass> escapePodBlueprint(TEXT("Class'/Game/Animations/EscapePod/EscapePodBlueprint.EscapePodBlueprint_C'"));
	EscapePodMeshComponent->SetAnimInstanceClass(escapePodBlueprint.Object);

	BoxComponentToOpenPod = CreateDefaultSubobject<UBoxComponent>("TriggerBoxToOpenPod");
	BoxComponentToOpenPod->SetupAttachment(RootComponent);
	BoxComponentToOpenPod->InitBoxExtent(FVector(200.f, 250.f, 200.f));
	BoxComponentToOpenPod->SetRelativeLocation(FVector(0.f, 230.f, 150.f));
	BoxComponentToOpenPod->bSelectable = false;

	BoxComponentToClosePod = CreateDefaultSubobject<UBoxComponent>("TriggerBoxToClosePod");
	BoxComponentToClosePod->SetupAttachment(RootComponent);
	BoxComponentToClosePod->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	BoxComponentToClosePod->SetRelativeLocation(FVector(0.f, 145.f, 170.f));
	BoxComponentToClosePod->bSelectable = false;

	ConstructorHelpers::FObjectFinder<ULevelSequence> EndSequence1(TEXT("LevelSequence'/Game/Sequences/EscapeSequence.EscapeSequence'"));
	EndSequenceP1 = EndSequence1.Object;
}

// Called when the game starts or when spawned
void AEscapePodActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponentToOpenPod->OnComponentBeginOverlap.AddDynamic(this, &AEscapePodActor::OnControlRoomEnter);
	BoxComponentToClosePod->OnComponentBeginOverlap.AddDynamic(this, &AEscapePodActor::OnEscapePodEnter);

	EscapePodAnimInstance = Cast<UEscapePodAnimInstance>(EscapePodMeshComponent->GetAnimInstance());
}


void AEscapePodActor::Tick(float DeltaTime)
{
	if (bWasClosing && EscapePodAnimInstance->bIsClosing == false)
	{
		bWasClosing = false;

		float delay = 1.0f;
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.f, 1.f, delay, FLinearColor::Black, false, true);

		ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
		state->DisablePlayerInput();
		state->bInteractionAllowed = false;

		static FTimerHandle unusedHandle;
		GetWorldTimerManager().SetTimer(unusedHandle, this, &AEscapePodActor::OnFadeOutFinish, delay);
	}

	if (bClose && EscapePodAnimInstance->bIsOpened)
	{
		EscapePodAnimInstance->bIsClosing = true;
		bClose = false;
	}
}

void AEscapePodActor::ClosePod()
{
	EscapePodAnimInstance->bIsClosing = true;
}

void AEscapePodActor::OnControlRoomEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherActor->IsA(ASpaceCharacter::StaticClass()))
	{
		EscapePodAnimInstance->bIsOpening = true;
		BoxComponentToOpenPod->OnComponentBeginOverlap.RemoveDynamic(this, &AEscapePodActor::OnControlRoomEnter);
	}
}

void AEscapePodActor::OnEscapePodEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherActor->IsA(ASpaceCharacter::StaticClass()))
	{
		EscapePodAnimInstance->bIsClosing = true;
		bWasClosing = true;
		BoxComponentToClosePod->OnComponentBeginOverlap.RemoveDynamic(this, &AEscapePodActor::OnEscapePodEnter);
	}*/

	ASpaceGameStateBase::Instance(GetWorld())->bEnableHUD = false;
	ASpaceGameStateBase::Instance(GetWorld())->DisablePlayerInput();

	FMovieSceneSequencePlaybackSettings settings;
	ULevelSequencePlayer* player = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), EndSequenceP1, settings);
	player->Play();
}

void AEscapePodActor::OnFadeOutFinish()
{
	if (TeleportPosition != nullptr)
	{
		ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		AActor* parent = character->GetParentActor();
		FRotator characterRotation = GetActorRotation() - TeleportPosition->GetActorRotation() + character->GetActorRotation();
		FVector characterPosition = TeleportPosition->GetActorLocation() + FVector(0.f, 0.f, 150.f);
		character->TeleportTo(characterPosition, TeleportPosition->GetActorRotation(), false, true);
		character->SetActorRotation(characterRotation);
		RootComponent->SetWorldLocationAndRotation(TeleportPosition->GetActorLocation(), TeleportPosition->GetActorRotation());
	}

	float delay = 1.0f;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.f, 0.f, delay, FLinearColor::Black, false, true);

	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
	state->EnablePlayerInput();
	state->bInteractionAllowed = true;

	EscapePodAnimInstance->bIsOpening = true;
}


