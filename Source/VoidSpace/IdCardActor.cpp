// All rights Neebula Games

#include "VoidSpace.h"
#include "IdCardActor.h"
#include "PickableComponent.h"


// Sets default values
AIdCardActor::AIdCardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> idCard(TEXT("StaticMesh'/Game/Meshes/IdCard.IdCard'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IdCard"));
	StaticMeshComponent->SetStaticMesh(idCard.Object);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->bGenerateOverlapEvents = true;

	PickableComponent = CreateDefaultSubobject<UPickableComponent>(TEXT("Pickable"));
	PickableComponent->SetupAttachment(StaticMeshComponent);

}

