// All rights Neebula Games

#include "VoidSpace.h"
#include "ExitVault.h"
#include "InteractableComponent.h"
#include "ExitVaultDoorAnimInstance.h"
#include "SpaceGameStateBase.h"


// Sets default values
AExitVault::AExitVault()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	static ConstructorHelpers::FObjectFinder<UClass> exitVaultDoorBlueprint(TEXT("Class'/Game/Animations/ExitVaultDoor/ExitVaultDoorBlueprint.ExitVaultDoorBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> innerDoor(TEXT("SkeletalMesh'/Game/Meshes/ExitVaultDoor/ExitVaultDoor.ExitVaultDoor'"));
	ExitInnerDoorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DoorInner"));
	ExitInnerDoorMeshComponent->SetupAttachment(RootComponent);
	ExitInnerDoorMeshComponent->SetSkeletalMesh(innerDoor.Object);
	ExitInnerDoorMeshComponent->SetAnimInstanceClass(exitVaultDoorBlueprint.Object);
	ExitInnerDoorMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> externalDoor(TEXT("SkeletalMesh'/Game/Meshes/ExitVaultDoor/ExitVaultDoor.ExitVaultDoor'"));
	ExitExternalDoorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DoorExternal"));
	ExitExternalDoorMeshComponent->SetupAttachment(RootComponent);
	ExitExternalDoorMeshComponent->SetSkeletalMesh(externalDoor.Object);
	ExitExternalDoorMeshComponent->SetAnimInstanceClass(exitVaultDoorBlueprint.Object);
	ExitExternalDoorMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->bRequireUseButton = false;

	// Recalculate Box extension
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(130.f, 200.f, 120.f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Particles/P_Smoke.P_Smoke'"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeParticle"));
	ParticleSystem->SetTemplate(PS.Object);

	static ConstructorHelpers::FObjectFinder<USoundWave> zipperSound(TEXT("SoundWave'/Game/Sounds/ChamberDecompressing.ChamberDecompressing'"));
	Smoke = zipperSound.Object;
}


void AExitVault::OpenInnerDoor() const
{
	Cast<UExitVaultDoorAnimInstance>(ExitInnerDoorMeshComponent->GetAnimInstance())->bIsOpening = true;
}

void AExitVault::OpenExternalDoor() const
{
	Cast<UExitVaultDoorAnimInstance>(ExitExternalDoorMeshComponent->GetAnimInstance())->bIsOpening = true;
}

void AExitVault::CloseInnerDoor() const
{
	Cast<UExitVaultDoorAnimInstance>(ExitInnerDoorMeshComponent->GetAnimInstance())->bIsClosing = true;
}

void AExitVault::CloseExternalDoor() const
{
	Cast<UExitVaultDoorAnimInstance>(ExitExternalDoorMeshComponent->GetAnimInstance())->bIsClosing = true;
}

void AExitVault::doDepressurising() const
{
	FTimerHandle DoorHandler;
	FTimerHandle GravityHandler;

	//do particle and sounds effects
	ParticleSystem->Activate();
	UGameplayStatics::PlaySound2D(GetWorld(), Smoke);

	if (!isOutside)
		GetWorldTimerManager().SetTimer(DoorHandler, this, &AExitVault::OpenExternalDoor, 5.f, false);
	else
		GetWorldTimerManager().SetTimer(DoorHandler, this, &AExitVault::OpenInnerDoor, 5.f, false);

	GetWorldTimerManager().SetTimer(GravityHandler, this, &AExitVault::ToogleGravity, 4.5f, false);
}

void AExitVault::ToogleGravity() const
{
	ASpaceGameStateBase* state = Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	if (state)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Toggling gravity"));
		state->TogglePlayerGravity();
	}
}

// Called when the game starts or when spawned
void AExitVault::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableComponent->OnTriggerEnter.AddDynamic(this, &AExitVault::OnVaultEnter);
	InteractableComponent->OnTriggerExit.AddDynamic(this, &AExitVault::OnVaultExit);

	OpenInnerDoor();
}

// Called every frame
void AExitVault::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExitVault::OnVaultEnter()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entering ExitVault"));
	FTimerHandle UnusedHandle;

	if (!isOutside)
		CloseInnerDoor();
	else
		CloseExternalDoor();
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AExitVault::doDepressurising, 1.8f, false);
}

void AExitVault::OnVaultExit()
{
	isOutside = !isOutside;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Exiting ExitVault"));
}