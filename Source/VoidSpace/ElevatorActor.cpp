// All rights Neebula Games

#include "VoidSpace.h"
#include "ElevatorActor.h"
#include "InteractableComponent.h"
#include "ElevatorAnimInstance.h"
#include "SpaceGameStateBase.h"
#include "SpaceCharacter.h"


// Sets default values
AElevatorActor::AElevatorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UClass> elevatorBlueprint(TEXT("Class'/Game/Animations/Elevator/ElevatorAnim.ElevatorAnim_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> elevatorMesh(TEXT("SkeletalMesh'/Game/Meshes/Elevator/Elevator.Elevator'"));
	ElevatorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Elevator Mesh"));
	RootComponent = ElevatorMesh;
	ElevatorMesh->SetSkeletalMesh(elevatorMesh.Object);
	ElevatorMesh->SetAnimInstanceClass(elevatorBlueprint.Object);
	ElevatorMesh->SetCollisionProfileName(FName("BlockAll"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->bRequireUseButton = false;
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(10.f, 10.f, 120.f));
}

// Called when the game starts or when spawned
void AElevatorActor::BeginPlay()
{
	Super::BeginPlay();
	InteractableComponent->OnTriggerEnter.AddDynamic(this, &AElevatorActor::OnElevatorEnter);
	AnimInstance = Cast<UElevatorAnimInstance>(ElevatorMesh->GetAnimInstance());
}

void AElevatorActor::Tick(float DeltaTime)
{
	if (bWasClosing && AnimInstance->bIsClosing == false)
	{
		bWasClosing = false;

		float delay = 1.0f;
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.f, 1.f, delay, FLinearColor::Black, false, true);

		ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
		state->bMovementAllowed = false;
		state->bInteractionAllowed = false;

		static FTimerHandle unusedHandle;
		GetWorldTimerManager().SetTimer(unusedHandle, this, &AElevatorActor::OnFadeOutFinish, delay);
	}
}

void AElevatorActor::OnElevatorEnter()
{
	AnimInstance->bIsClosing = true;
	bWasClosing = true;
	InteractableComponent->OnTriggerEnter.RemoveDynamic(this, &AElevatorActor::OnElevatorEnter);
}

void AElevatorActor::OnFadeOutFinish()
{
	if (TeleportPosition != nullptr)
	{
		ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		
		AActor* parent = character->GetParentActor();
		FRotator characterRotation = GetActorRotation() - TeleportPosition->GetActorRotation() + character->GetActorRotation();
		character->TeleportTo(TeleportPosition->GetActorLocation(), TeleportPosition->GetActorRotation(), false, true);
		character->SetActorRotation(characterRotation);
		RootComponent->SetWorldLocationAndRotation(TeleportPosition->GetActorLocation(), TeleportPosition->GetActorRotation());
	}

	float delay = 1.0f;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.f, 0.f, delay, FLinearColor::Black, false, true);

	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
	state->bMovementAllowed = true;
	state->bInteractionAllowed = true;

	AnimInstance->bIsOpening = true;
}
