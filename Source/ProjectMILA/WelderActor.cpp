// All rights Neebula Games

#include "ProjectMILA.h"
#include "WelderActor.h"
#include "EquipableComponent.h"
#include "SpaceStatics.h"
#include "SpaceCharacter.h"
#include "OrtoHoleActor.h"


// Sets default values
AWelderActor::AWelderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> welder(TEXT("StaticMesh'/Game/Meshes/Welder/Welder.Welder'"));
	WelderMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = WelderMeshComponent;
	WelderMeshComponent->SetStaticMesh(welder.Object);
	WelderMeshComponent->SetSimulatePhysics(true);

	EquipableComponent = CreateDefaultSubobject<UEquipableComponent>(TEXT("Equipable"));
	EquipableComponent->SetupAttachment(RootComponent);
	EquipableComponent->bAutoActivate = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> beam(TEXT("ParticleSystem'/Game/Particles/P_electricity_arc.P_electricity_arc'"));
	BeamStreamComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BeamStream"));
	BeamStreamComponent->SetupAttachment(WelderMeshComponent, TEXT("WelderStream"));
	BeamStreamComponent->SetTemplate(beam.Object);
	BeamStreamComponent->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundWave> welderSound(TEXT("SoundWave'/Game/Sounds/SFX/welder.welder'"));
	WelderSound = welderSound.Object;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AWelderActor::BeginPlay()
{
	Super::BeginPlay();

	EquipableComponent->OnEquipped.AddDynamic(this, &AWelderActor::Equipped);
	EquipableComponent->OnUnequipped.AddDynamic(this, &AWelderActor::Unequipped);
	EquipableComponent->OnFire.AddDynamic(this, &AWelderActor::UseWelder);
	EquipableComponent->OnEndFire.AddDynamic(this, &AWelderActor::EndUseWelder);

	AudioComponent->bIsUISound = true;
	AudioComponent->SetSound(WelderSound);

	AudioComponent->SetActive(false);
}

// Called every frame
void AWelderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ASpaceCharacter* character = static_cast<ASpaceCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		if (nullptr != Hole && Hole->bRepaired)
		{
			character->UnequipObject();

			WelderMeshComponent->SetEnableGravity(false);
			EquipableComponent->SetActive(false);
			EquipableComponent->bHighlight = false;

			SetActorLocation(GetActorLocation() + (character->GetActorForwardVector() * 90.0f));

			Hole->StopClose();
			Hole = nullptr;
		}
		else if (bUsingWelder)
		{
			const FVector Start = character->FirstPersonCameraComponent->GetComponentLocation();
			const FVector dir_camera = character->FirstPersonCameraComponent->GetForwardVector();
			const FVector End = Start + dir_camera * 200;

			FHitResult hitData(ForceInit);

			if (USpaceStatics::Trace(GetWorld(), character, Start, End, hitData))
			{
				AOrtoHoleActor* actor = Cast<AOrtoHoleActor>(hitData.GetActor());

				if (nullptr != actor)
				{
					if (Hole != actor)
					{
						if (nullptr != Hole)
						{
							Hole->StopClose();
						}

						Hole = actor;
						Hole->BeginClose();
					}
				}
				else if (nullptr != Hole)
				{
					Hole->StopClose();

					Hole = nullptr;
				}
			}
		}
		else if (nullptr != Hole)
		{
			Hole->StopClose();

			Hole = nullptr;
		}
	}
}

void AWelderActor::Equipped()
{
	WelderMeshComponent->SetSimulatePhysics(false);

	WelderMeshComponent->SetCollisionProfileName("NoCollision");
	WelderMeshComponent->SetCastShadow(false);
}

void AWelderActor::Unequipped()
{
	WelderMeshComponent->SetCollisionProfileName("BlockAll");

	WelderMeshComponent->SetSimulatePhysics(true);
	WelderMeshComponent->SetCastShadow(true);
}

void AWelderActor::UseWelder()
{
	BeamStreamComponent->ActivateSystem();

	AudioComponent->SetActive(true);
		
	bUsingWelder = true;
}

void AWelderActor::EndUseWelder()
{
	BeamStreamComponent->DeactivateSystem();

	AudioComponent->SetActive(false);

	bUsingWelder = false;
}

