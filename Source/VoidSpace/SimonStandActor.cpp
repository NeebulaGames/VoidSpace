// All rights Neebula Games

#include "VoidSpace.h"
#include "SimonStandActor.h"
#include "SpaceStatics.h"


// Sets default values
ASimonStandActor::ASimonStandActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> simonStand(TEXT("StaticMesh'/Game/Meshes/Simon/Simon_Stand.Simon_Stand'"));
	SimonStandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SimonStand"));
	SimonStandMesh->SetupAttachment(RootComponent);
	SimonStandMesh->SetStaticMesh(simonStand.Object);
}

// Called when the game starts or when spawned
void ASimonStandActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimonStandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimonStandActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FActorSpawnParameters leftButtonParams;
	leftButtonParams.Name = TEXT("Left Button");
	ASimonButtonActor* leftButton = GetWorld()->SpawnActor<ASimonButtonActor>(FVector::ZeroVector, FRotator::ZeroRotator, leftButtonParams);
	leftButton->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	leftButton->SetActorRelativeLocation(FVector(-19.f, 45.f, 54.f));

	Buttons.Add(leftButton);

	FActorSpawnParameters centralButtonParams;
	centralButtonParams.Name = TEXT("Central Button");
	ASimonButtonActor* centralButton = GetWorld()->SpawnActor<ASimonButtonActor>(FVector::ZeroVector, FRotator::ZeroRotator, centralButtonParams);
	centralButton->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	centralButton->SetActorRelativeLocation(FVector(-0.684814f, 45.f, 54.f));

	Buttons.Add(centralButton);
}
