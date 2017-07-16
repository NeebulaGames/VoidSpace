// All rights Neebula Games

#include "ProjectMILA.h"
#include "MeteoritesActor.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"


// Sets default values
AMeteoritesActor::AMeteoritesActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> particles(TEXT("ParticleSystem'/Game/Particles/P_Ribbon_Meteorites.P_Ribbon_Meteorites'"));
	ParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Meteorites"));
	ParticlesComponent->SetTemplate(particles.Object);

	RootComponent = ParticlesComponent;

}

// Called when the game starts or when spawned
void AMeteoritesActor::BeginPlay()
{
	Super::BeginPlay();
	
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventFinished.AddDynamic(this, &AMeteoritesActor::StopEmission);
}

void AMeteoritesActor::StopEmission()
{
	if (ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->GetCurrentEvent()->Name.Equals(FString("The Meteor")))
		ParticlesComponent->bSuppressSpawning = true;
}



