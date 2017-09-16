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
	EndSequence = EndSequence1.Object;
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
	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());

	if (bClose && EscapePodAnimInstance->bIsOpened)
	{
		EscapePodAnimInstance->bIsClosing = true;
		bClose = false;
	}

	if (PlayerCamera)
	{
		Movement += DeltaTime;
		PlayerCamera->SetWorldLocation(FMath::Lerp<FVector>(CameraOriginalPosition, FVector(0.f, 137.576401f, 211.f), FVector(Movement)));

		if (Movement >= 1.f)
		{
			PlayerCamera = nullptr;
			
			FMovieSceneSequencePlaybackSettings settings;
			ALevelSequenceActor* playerActor;
			ULevelSequencePlayer* player = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), EndSequence, settings, playerActor);
			player->SetPlaybackPosition(0.f);
			player->Play();

			FTimerHandle unused;
			FTimerDelegate callback;
			callback.BindLambda([this, state]() -> void {state->EndGame(); });
			GetWorldTimerManager().SetTimer(unused, callback, player->GetLength(), false);
		}
	}
}

void AEscapePodActor::OnControlRoomEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherActor->IsA(ASpaceCharacter::StaticClass()))
	{
		EscapePodAnimInstance->bIsOpening = true;
		BoxComponentToOpenPod->OnComponentBeginOverlap.RemoveDynamic(this, &AEscapePodActor::OnControlRoomEnter);

		bClose = false;
	}
}

void AEscapePodActor::OnEscapePodEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	PlayerCamera = character->FirstPersonCameraComponent;
	CameraOriginalPosition = PlayerCamera->GetComponentLocation();
	CameraOriginalRotation = PlayerCamera->GetComponentRotation();
	PlayerCamera->bUsePawnControlRotation = false;

	ASpaceGameStateBase* gameState = ASpaceGameStateBase::Instance(GetWorld());

	gameState->bEnableHUD = false;
	gameState->DisablePlayerInput();
}
