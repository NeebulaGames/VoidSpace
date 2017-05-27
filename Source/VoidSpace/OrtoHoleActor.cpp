// All rights Neebula Games

#include "VoidSpace.h"
#include "OrtoHoleActor.h"


// Sets default values
AOrtoHoleActor::AOrtoHoleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UClass> holeBlueprint(TEXT("Class'/Game/Animations/OrtoHole/OrtoHoleAnim.OrtoHoleAnim_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> holeMesh(TEXT("SkeletalMesh'/Game/Meshes/OrtoHole/OrtoHole.OrtoHole'"));

	HoleMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OrtoHole Mesh"));
	RootComponent = HoleMeshComponent;
	HoleMeshComponent->SetSkeletalMesh(holeMesh.Object);
	HoleMeshComponent->SetAnimInstanceClass(holeBlueprint.Object);
	HoleMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	HoleMeshComponent->GlobalAnimRateScale = 0.f;
}

// Called when the game starts or when spawned
void AOrtoHoleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOrtoHoleActor::BeginClose()
{
	HoleMeshComponent->GlobalAnimRateScale = 1.f;
}

void AOrtoHoleActor::StopClose() 
{
	HoleMeshComponent->GlobalAnimRateScale = 0.f;
}

