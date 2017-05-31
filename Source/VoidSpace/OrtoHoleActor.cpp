// All rights Neebula Games

#include "VoidSpace.h"
#include "OrtoHoleActor.h"


// Sets default values
AOrtoHoleActor::AOrtoHoleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> holeMesh(TEXT("StaticMesh'/Game/Meshes/Props/OrtoHole/OrtoHole.OrtoHole'"));

	HoleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrtoHole Mesh"));
	RootComponent = HoleMeshComponent;
	HoleMeshComponent->SetStaticMesh(holeMesh.Object);
	HoleMeshComponent->SetCollisionProfileName(FName("BlockAll"));
}

// Called when the game starts or when spawned
void AOrtoHoleActor::BeginPlay()
{
	Super::BeginPlay();

	HoleMaterial = HoleMeshComponent->CreateAndSetMaterialInstanceDynamic(1);
}

void AOrtoHoleActor::Tick(float DeltaSeconds)
{
	if (!bRepaired && bRepairing)
	{
		Opacity -= DeltaSeconds;

		Opacity = FMath::Clamp(Opacity, 0.f, 1.f);
		GEngine->AddOnScreenDebugMessage(10, 1.f, FColor::Red, FString::Printf(TEXT("Opacity %f"), Opacity));

		HoleMaterial->SetScalarParameterValue("Opacity", Opacity);

		if (Opacity <= 0.f)
		{
			bRepairing = false;
			bRepaired = true;

			OnHoleClosed.Broadcast();
		}
	}
}

void AOrtoHoleActor::BeginClose()
{
	if (!bRepaired)
	{
		bRepairing = true;
	}
}

void AOrtoHoleActor::StopClose() 
{
	bRepairing = false;
}

