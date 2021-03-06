// All rights Neebula Games

#include "ProjectMILA.h"
#include "ObservatoryBlind.h"
#include "BlindAnimInstance.h"


// Sets default values
AObservatoryBlind::AObservatoryBlind()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;
	
	static ConstructorHelpers::FObjectFinder<UClass> blindBlueprint(TEXT("Class'/Game/Animations/Blinds/Small/SmallBlindBlueprint.SmallBlindBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Smallblinds(TEXT("SkeletalMesh'/Game/Meshes/Blinds/Small/ObservatoryBlindSmall.ObservatoryBlindSmall'"));
	BlindMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Blinds"));
	BlindMeshComponent->SetupAttachment(RootComponent);
	BlindMeshComponent->SetSkeletalMesh(Smallblinds.Object);
	BlindMeshComponent->SetAnimInstanceClass(blindBlueprint.Object);
}

// Called when the game starts or when spawned
void AObservatoryBlind::BeginPlay()
{
	Super::BeginPlay();	

	SimonStand->OnSimonCompleted.AddDynamic(this, &AObservatoryBlind::OnSimonCompleted);
}

void AObservatoryBlind::OnSimonCompleted()
{
	Cast<UBlindAnimInstance>(BlindMeshComponent->GetAnimInstance())->bIsOpening = true;
}
