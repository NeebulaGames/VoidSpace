// All rights Neebula Games

#include "VoidSpace.h"
#include "SimonStandActor.h"
#include "SpaceStatics.h"
#include "SpaceCharacter.h"
#include "PickableComponent.h"
#include "InteractableComponent.h"


const FLinearColor ASimonStandActor::Colors[3] = { FLinearColor::Red, FLinearColor::Green, FLinearColor::Blue };

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

void ASimonStandActor::RestoreButtons()
{
	for (int i = 0; i < 3; ++i)
	{
		Buttons[i]->SetColor(Colors[i], 0.f);
	}

	ShutAllButtons();
}

// Called every frame
void ASimonStandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bActivateSimon)
	{
		for (int i = 0; i < 3 ; ++i)
		{
			FLinearColor color = Colors[i];
			ASimonButtonActor* button = Buttons[i];
			button->ButtonNumber = i;
			button->SetColor(color, 0.f);
			button->OnButtonClicked.AddUObject(this, &ASimonStandActor::ButtonPressed);
		}

		GenerateSequence(3);
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASimonStandActor::ContinueSequence, 2.f);

		bActivateSimon = false;
	}
}

void ASimonStandActor::ContinueSequence()
{
	int lightenButton = Sequence[CurrentSequencePosition++];
	for (int i = 0; i < 3; ++i)
	{
		ASimonButtonActor* button = Buttons[i];
		i == lightenButton ? button->TurnOn() : button->TurnOff();
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASimonStandActor::ShutAllButtons, 2.f);
}

void ASimonStandActor::ShutAllButtons()
{
	bool sequenceCompleted = CurrentSequencePosition >= Sequence.Num();
	for (int i = 0; i < 3; ++i)
	{
		ASimonButtonActor* button = Buttons[i];
		//button->SetColor(FLinearColor::Black, 0.f);
		button->TurnOff();
		button->InteractableComponent->SetActive(sequenceCompleted);
	}

	if (sequenceCompleted)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASimonStandActor::ContinueSequence, 60.f);
		CurrentSequencePosition = 0;
	}
	else
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASimonStandActor::ContinueSequence, 1.f);
	}
}

void ASimonStandActor::GenerateSequence(int elements)
{
	CurrentButtonSequence = 0;
	CurrentSequencePosition = 0;
	Sequence.Empty(elements);
	while (elements--)
	{
		Sequence.Add(FMath::Rand() % 3);
	}
}

void ASimonStandActor::SequenceSuccess()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);

	bool sequencesCompleted = ++SequencesSuccess > 2;
	if (sequencesCompleted)
	{
		OnSimonCompleted.Broadcast();
	}
	else
	{
		GenerateSequence(CurrentButtonSequence + 1);
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASimonStandActor::RestoreButtons, 1.f);
	}

	for (int i = 0; i < 3; ++i)
	{
		ASimonButtonActor* button = Buttons[i];
		button->SetColor(FLinearColor::Green, sequencesCompleted ? 1.f : 0.f);
		button->InteractableComponent->SetActive(false);
		button->TurnOn();
	}
}

void ASimonStandActor::SequenceWrong()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);

	for (int i = 0; i < 3; ++i)
	{
		ASimonButtonActor* button = Buttons[i];
		button->SetColor(FLinearColor::Red, 0.f);
		button->TurnOn();
		button->InteractableComponent->SetActive(false);
	}

	CurrentButtonSequence = 0;
	CurrentSequencePosition = 0;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASimonStandActor::RestoreButtons, 1.f);
}

void ASimonStandActor::ButtonPressed(int button)
{
	UE_LOG(LogTemp, Warning, TEXT("Button %d pressed"), button);
	if (Sequence[CurrentButtonSequence] == button)
	{
		if (++CurrentButtonSequence == Sequence.Num())
		{
			SequenceSuccess();
		}
	}
	else
	{
		SequenceWrong();
	}
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

		bActivateSimon = true;

		Buttons.Add(button);
	}
}
