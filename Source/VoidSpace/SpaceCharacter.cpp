// Fill out your copyright notice in the Description page of Project Settings.

#include "VoidSpace.h"
#include "SpaceCharacter.h"
#include "InteractableComponent.h"
#include "PickableComponent.h"
#include "SpaceStatics.h"
#include "SpaceGameStateBase.h"


// Sets default values
ASpaceCharacter::ASpaceCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	physics_handle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("physicsHandle"));

}

// Called when the game starts or when spawned
void ASpaceCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (pickedObject != nullptr)
	{
		const FVector Start = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
		const FVector dir_camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector();
		const FVector End = Start + dir_camera * 75;

		APawn* pawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

		physics_handle->SetTargetLocationAndRotation(End, pawn->GetControlRotation());
	}

	SprintControl(DeltaTime);
}

void ASpaceCharacter::ReleaseObject()
{
	pickedObject = nullptr;

	physics_handle->ReleaseComponent();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Object Released"));
}

// Enables and disables player's gravity
void ASpaceCharacter::ToggleGravity()
{
	if (!bWearsSpaceSuit)
	{
		// TODO: Die here
	}
	else
	{
		bGravityEnabled = !bGravityEnabled;

		UCharacterMovementComponent* characterMovement = GetCharacterMovement();

		characterMovement->MovementMode = characterMovement->DefaultLandMovementMode = bGravityEnabled ? MOVE_Walking : MOVE_Flying;
	}
}

void ASpaceCharacter::ToggleSpaceSuit(bool activate)
{
	bWearsSpaceSuit = activate;
}

// Called to bind functionality to input
void ASpaceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Forward", this, &ASpaceCharacter::MoveForward);
	InputComponent->BindAxis("Horizontal", this, &ASpaceCharacter::MoveHorizontal);
	InputComponent->BindAxis("Turn", this, &ASpaceCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ASpaceCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ASpaceCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ASpaceCharacter::OnStopJump);
	InputComponent->BindAction("Use", IE_Pressed, this, &ASpaceCharacter::Use);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &ASpaceCharacter::OnStartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &ASpaceCharacter::OnStopSprint);
}

void ASpaceCharacter::MoveForward(float Val)
{
	if (ASpaceGameStateBase::Instance(GetWorld())->bMovementAllowed && (Controller != nullptr) && (Val != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (!GetCharacterMovement()->IsFlying() &&
			GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);

	}
}

void ASpaceCharacter::MoveHorizontal(float Val)
{
	if (ASpaceGameStateBase::Instance(GetWorld())->bMovementAllowed && (Controller != nullptr) && (Val != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Val);
	}
}

void ASpaceCharacter::OnStartJump()
{
	bPressedJump = ASpaceGameStateBase::Instance(GetWorld())->bMovementAllowed;
}

void ASpaceCharacter::OnStopJump()
{
	bPressedJump = false;
}

void ASpaceCharacter::KillPlayer(int mode) const
{
	// TODO: Run death animation and trigger event when finished
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Killed in mode %d"), mode));
}

void ASpaceCharacter::Use()
{
	if (ASpaceGameStateBase::Instance(GetWorld())->bInteractionAllowed)
	{
		const FVector Start = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
		const FVector dir_camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector();
		const FVector End = Start + dir_camera * 250;

		FHitResult hitData(ForceInit);

		// RELEASE OBJECT
		if (pickedObject != nullptr)
		{
			ReleaseObject();
		}
		else
		{
			if (USpaceStatics::Trace(GetWorld(), this, Start, End, hitData))
			{
				UInteractableComponent* interactable = hitData.Actor->FindComponentByClass<UInteractableComponent>();
				UPickableComponent* pickable = hitData.Actor->FindComponentByClass<UPickableComponent>();

				if (interactable != nullptr && interactable->IsActive())
					interactable->Trigger();

				else if (pickable != nullptr && pickedObject == nullptr)
				{
					DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f, 0, 2.f);
					physics_handle->GrabComponentAtLocationWithRotation(
						hitData.GetComponent(), 
						"None", 
						hitData.GetComponent()->GetComponentLocation(), 
						hitData.GetComponent()->GetComponentRotation());

					pickedObject = hitData.GetActor();
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Object pickedUp"));
				}
			}

		}
	}
}

void ASpaceCharacter::SprintControl(float DeltaTime)
{
	//TODO: Control by time not by ticks.
	if (bIsSprinting)
	{
		if (StaminaDuration > 0)
		{
			StaminaDuration -= StaminaConsumition;
		}
		else if (StaminaDuration <= 0)
		{
			OnStopSprint();
			StaminaDuration = 0;
			bIsRecovering = true;
		}
	}

	if (bIsRecovering)
	{
		StaminaDuration += StaminaRecovery;

		if (StaminaDuration >= MaxStamina)
		{
			StaminaDuration = MaxStamina;
			bIsRecovering = false;
		}
	}

	if ((!bIsSprinting && !bIsRecovering) && StaminaDuration<MaxStamina)
	{
		StaminaDuration += StaminaRecovery;

		if (StaminaDuration >= MaxStamina)
		{
			StaminaDuration = MaxStamina;
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Stamina: %f"), StaminaDuration));
}

void ASpaceCharacter::OnStartSprint()
{
	if(!bIsRecovering)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void ASpaceCharacter::OnStopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
