// All rights Neebula Games

#include "VoidSpace.h"
#include "ObservatoryBlind.h"
#include "BlindAnimInstance.h"


// Sets default values
AObservatoryBlind::AObservatoryBlind()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	static ConstructorHelpers::FObjectFinder<UClass> blindBlueprint(TEXT("Class'/Game/Animations/BlindBlueprint.BlindBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> blinds(TEXT("SkeletalMesh'/Game/Meshes/Blinds/Blinds_Animated.Blinds_Animated'"));
	BlindMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Blinds"));
	BlindMeshComponent->SetupAttachment(RootComponent);
	BlindMeshComponent->SetSkeletalMesh(blinds.Object);
	BlindMeshComponent->SetAnimInstanceClass(blindBlueprint.Object);

}

// Called when the game starts or when spawned
void AObservatoryBlind::BeginPlay()
{
	Super::BeginPlay();
	
	Cast<UBlindAnimInstance>(BlindMeshComponent->GetAnimInstance())->SetSimonStandToInstance(SimonStandActor);
}
