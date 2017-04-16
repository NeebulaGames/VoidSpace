// All rights Neebula Games

#include "VoidSpace.h"
#include "SimonStandActor.h"
#include "SpaceStatics.h"
#include "SpaceCharacter.h"
#include "PickableComponent.h"


// Sets default values
ASimonStandActor::ASimonStandActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> simonStand(TEXT("StaticMesh'/Game/Meshes/Simon/Simon_Stand.Simon_Stand'"));
	SimonStandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SimonStand"));
	SimonStandMesh->SetStaticMesh(simonStand.Object);

	RootComponent = SimonStandMesh;
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

void ASimonStandActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(ASimonButtonActor::StaticClass()) && !OtherActor->IsAttachedTo(this))
	{
		UE_LOG(LogTemp, Log, TEXT("Simon button added"));
		
		ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (character)
		{
			UPrimitiveComponent* component = character->physics_handle->GetGrabbedComponent();

			if (component && component->GetOwner() == OtherActor)
				character->physics_handle->ReleaseComponent(); // TODO: Add release function in character
		}

		ASimonButtonActor* button = Cast<ASimonButtonActor>(OtherActor);
		button->SimonButtonMesh->SetSimulatePhysics(false);
		button->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		UActorComponent* pickable = button->GetComponentByClass(UPickableComponent::StaticClass());
		if (pickable)
			pickable->DestroyComponent(true);
		button->SetActorRelativeLocation(FVector(17.5f, 45.f, 54.f));
		button->SetActorRelativeRotation(FRotator::ZeroRotator);

		SimonStandMesh->bGenerateOverlapEvents = false;
	}
}
