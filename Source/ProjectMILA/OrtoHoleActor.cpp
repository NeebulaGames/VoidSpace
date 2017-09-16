// All rights Neebula Games

#include "ProjectMILA.h"
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

	static ConstructorHelpers::FObjectFinder<UParticleSystem> oxygenLeak(TEXT("ParticleSystem'/Game/Particles/P_Distortion.P_Distortion'"));
	OxygenLeak = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DepressuringSystem"));
	OxygenLeak->SetTemplate(oxygenLeak.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> spark(TEXT("ParticleSystem'/Game/Particles/P_spark_burst.P_spark_burst'"));
	Sparks1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Sparks1"));
	Sparks1->SetTemplate(spark.Object);

	Sparks2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Sparks2"));
	Sparks2->SetTemplate(spark.Object);

	Sparks3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Sparks3"));
	Sparks3->SetTemplate(spark.Object);

	Sparks4 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Sparks4"));
	Sparks4->SetTemplate(spark.Object);
}

// Called when the game starts or when spawned
void AOrtoHoleActor::BeginPlay()
{
	Super::BeginPlay();

	HoleMaterial = HoleMeshComponent->CreateAndSetMaterialInstanceDynamic(0);

	OxygenLeak->SetActive(true);
	Sparks1->SetActive(true);
	Sparks2->SetActive(true);
	Sparks3->SetActive(true);
	Sparks4->SetActive(true);
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

			OxygenLeak->SetActive(false);
			Sparks1->SetActive(false);
			Sparks2->SetActive(false);
			Sparks3->SetActive(false);
			Sparks4->SetActive(false);

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

