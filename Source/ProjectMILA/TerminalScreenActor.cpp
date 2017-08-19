// All rights Neebula Games

#include "ProjectMILA.h"
#include "TerminalScreenActor.h"


// Sets default values
ATerminalScreenActor::ATerminalScreenActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> plane(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	ConstructorHelpers::FObjectFinder<UMaterial> screenMaterial(TEXT("Material'/Game/Materials/Props/TerminalScreen.TerminalScreen'"));
	ConstructorHelpers::FObjectFinder<UMaterial> fontMaterial(TEXT("Material'/Game/Fonts/M_Roboto.M_Roboto'"));

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility(EComponentMobility::Movable);

	DisplayComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Display"));
	DisplayComponent->SetStaticMesh(plane.Object);
	DisplayComponent->SetMaterial(0, screenMaterial.Object);
	DisplayComponent->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	DisplayComponent->SetRelativeScale3D(FVector(1.f, 0.5f, 1.f));
	DisplayComponent->SetupAttachment(RootComponent);

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	TextComponent->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	TextComponent->SetWorldSize(7.f);
	TextComponent->SetVerticalAlignment(EVRTA_TextTop);
	TextComponent->SetRelativeLocation(FVector(-47.f, 0.f, 24.f));
	TextComponent->SetTextMaterial(fontMaterial.Object);
	TextComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATerminalScreenActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerminalScreenActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString displayText = Text;
	
	if (NextBlinkTime <= 0.f)
	{
		NextBlinkTime = BlinkRatio;
		DisplaySlash = !DisplaySlash;
	}
	NextBlinkTime -= DeltaTime;

	if (DisplaySlash)
		displayText.Append("_");

	BreakText(displayText);
	TextComponent->SetText(FText::FromString(displayText));
}

bool ATerminalScreenActor::ShouldTickIfViewportsOnly() const
{
	return true;
}

void ATerminalScreenActor::BreakText(FString& text)
{
	if (text.Len() > MaxLineWidth)
	{
		int lines = text.Len() / MaxLineWidth;

		for (int i = 1; i <= lines; ++i)
		{
			int space = 0;

			for (int j = MaxLineWidth * i; j > MaxLineWidth * (i - 1) && j < text.Len() && space == 0; --j)
			{
				if (text[j] == ' ')
					space = j;
			}

			if (space != 0)
			{
				text[space] = '\n';
				lines = i + (text.Len() - MaxLineWidth * i) / MaxLineWidth;

			}
			else
				text.InsertAt(MaxLineWidth * i, '\n');
		}
	}
}

