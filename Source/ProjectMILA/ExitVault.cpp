// All rights Neebula Games

#include "ProjectMILA.h"
#include "ExitVault.h"
#include "InteractableComponent.h"
#include "ExitVaultDoorAnimInstance.h"
#include "ExitVaultLever.h"
#include "SpaceGameStateBase.h"


// Sets default values
AExitVault::AExitVault()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	FTimerHandle WaitToChangeDoorHandler;

	ParticleSystem->Activate();
	UGameplayStatics::PlaySound2D(GetWorld(), Smoke);

	if (!bExternalDoorOpen)
		GetWorldTimerManager().SetTimer(DoorHandler, this, &AExitVault::OpenExternalDoor, 5.f, false);
	else
		GetWorldTimerManager().SetTimer(DoorHandler, this, &AExitVault::OpenInnerDoor, 5.f, false);

	GetWorldTimerManager().SetTimer(GravityHandler, this, &AExitVault::ToogleGravity, 4.5f, false);

	GetWorldTimerManager().SetTimer(WaitToChangeDoorHandler, this, &AExitVault::ChangeDoor, 7.0f, false);
}

void AExitVault::ToogleGravity() const 
{
	ASpaceGameStateBase* State = Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	if (State)
	{
		State->TogglePlayerGravity();
	}
}

void AExitVault::ChangeDoor()
{
	bExternalDoorOpen = !bExternalDoorOpen;
	Lever->bCanBTriggered = true;
	Lever->InteractableComponent->bHighlight = true;
}

// Called when the game starts or when spawned
void AExitVault::BeginPlay()
{
	Super::BeginPlay();
		
	Lever->InteractableComponent->OnTriggerAction.AddDynamic(this, &AExitVault::OnLeverUse);
	
	OpenInnerDoor();
}

void AExitVault::OnLeverUse()
{
	if (!Lever->IsTriggering() && Lever->bCanBTriggered)
	{
		Lever->SetbIsNotTriggered(false);
		Lever->SetbIsTriggering(true);

		Lever->bCanBTriggered = false;
		Lever->InteractableComponent->bHighlight = false;

		FTimerHandle UnusedHandle;

		if (!bExternalDoorOpen)
			CloseInnerDoor();
		else
			CloseExternalDoor();
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AExitVault::doDepressurising, 1.8f, false);
	}
}
