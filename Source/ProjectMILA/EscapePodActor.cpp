// All rights Neebula Games

#include "ProjectMILA.h"
#include "EscapePodActor.h"
#include "InteractableComponent.h"
#include "EscapePodAnimInstance.h"
#include "SpaceGameStateBase.h"
#include "SpaceCharacter.h"


// Sets default values
AEscapePodActor::AEscapePodActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> escapePod(TEXT("SkeletalMesh'/Game/Meshes/EscapePod/EscapePod.EscapePod'"));
	EscapePodMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Escape Pod"));
	RootComponent = EscapePodMeshComponent;
	EscapePodMeshComponent->SetSkeletalMesh(escapePod.Object);
	EscapePodMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	static ConstructorHelpers::FObjectFinder<UClass> escapePodBlueprint(TEXT("Class'/Game/Animations/EscapePod/EscapePodBlueprint.EscapePodBlueprint_C'"));
	EscapePodMeshComponent->SetAnimInstanceClass(escapePodBlueprint.Object);

	InteractableOpenComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableToOpen"));
	InteractableOpenComponent->SetupAttachment(RootComponent);
	InteractableOpenComponent->bRequireUseButton = false;
	InteractableOpenComponent->bHighlight = false;
	InteractableOpenComponent->BoxComponent->SetBoxExtent(FVector(200.f, 250.f, 200.f));
	InteractableOpenComponent->BoxComponent->SetRelativeLocation(FVector(0.f, 230.f, 150.f));

	InteractableCloseComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableToClose"));
	InteractableCloseComponent->SetupAttachment(RootComponent);
	InteractableCloseComponent->bRequireUseButton = false;
	InteractableCloseComponent->bHighlight = false;
	InteractableCloseComponent->BoxComponent->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	InteractableCloseComponent->BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 170.f));

}

// Called when the game starts or when spawned
void AEscapePodActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableOpenComponent->OnTriggerEnter.AddDynamic(this, &AEscapePodActor::OnControlRoomEnter);
	//InteractableCloseComponent->OnTriggerEnter.AddDynamic(this, &AEscapePodActor::OnEscapePodEnter);

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
}


void AEscapePodActor::OnControlRoomEnter()
{
	EscapePodAnimInstance->bIsOpening = true;
	InteractableOpenComponent->OnTriggerEnter.RemoveDynamic(this, &AEscapePodActor::OnControlRoomEnter);
}

void AEscapePodActor::OnEscapePodEnter()
{
	EscapePodAnimInstance->bIsClosing = true;
	bWasClosing = true;
	//InteractableCloseComponent->OnTriggerEnter.RemoveDynamic(this, &AEscapePodActor::OnEscapePodEnter);
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


