// All rights Neebula Games

#include "VoidSpace.h"
#include "WelderActor.h"
#include "EquipableComponent.h"


// Sets default values
AWelderActor::AWelderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> welder(TEXT("StaticMesh'/Game/Meshes/Welder/Welder.Welder'"));
	WelderMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = WelderMeshComponent;
	WelderMeshComponent->SetStaticMesh(welder.Object);

	EquipableComponent = CreateDefaultSubobject<UEquipableComponent>(TEXT("Equipable"));
	EquipableComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> beam(TEXT("ParticleSystem'/Game/Particles/P_electricity_arc.P_electricity_arc'"));
	BeamStreamComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BeamStream"));
	BeamStreamComponent->SetupAttachment(WelderMeshComponent, TEXT("WelderStream"));
	BeamStreamComponent->SetTemplate(beam.Object);
	BeamStreamComponent->bAutoActivate = true;
}

// Called when the game starts or when spawned
void AWelderActor::BeginPlay()
{
	Super::BeginPlay();

	EquipableComponent->OnEquipped.AddDynamic(this, &AWelderActor::Equipped);
	EquipableComponent->OnUnequipped.AddDynamic(this, &AWelderActor::Unequipped);
	EquipableComponent->OnUsed.AddDynamic(this, &AWelderActor::UseWelder);
}

// Called every frame
void AWelderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWelderActor::Equipped()
{
	WelderMeshComponent->SetSimulatePhysics(false);

	WelderMeshComponent->SetCollisionProfileName("NoCollision");
}

void AWelderActor::Unequipped()
{
	WelderMeshComponent->SetCollisionProfileName("BlockAll");

	WelderMeshComponent->SetSimulatePhysics(true);
}

void AWelderActor::UseWelder()
{

}

