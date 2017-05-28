// Fill out your copyright notice in the Description page of Project Settings.

#include "VoidSpace.h"
#include "SpaceCharacter.h"
#include "InteractableComponent.h"
#include "PickableComponent.h"
#include "SpaceStatics.h"
#include "SpaceGameStateBase.h"
#include "EquipableComponent.h"


// Sets default values
ASpaceCharacter::ASpaceCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


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
}

// Enables and disables player's gravity
void ASpaceCharacter::ToggleGravity()
{
	if (!bWearsSpaceSuit)
	{
		ASpaceGameStateBase* state = Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
		if (state)
			state->Die(0);
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
	InputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceCharacter::OnFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ASpaceCharacter::OnEndFire);
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
}

void ASpaceCharacter::Use()
{
	if (ASpaceGameStateBase::Instance(GetWorld())->bInteractionAllowed)
	{
		const FVector Start = FirstPersonCameraComponent->GetComponentLocation();
		const FVector dir_camera = FirstPersonCameraComponent->GetForwardVector();
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
				UEquipableComponent* equipable = hitData.Actor->FindComponentByClass<UEquipableComponent>();
				UInteractableComponent* interactable = hitData.Actor->FindComponentByClass<UInteractableComponent>();
				UPickableComponent* pickable = hitData.Actor->FindComponentByClass<UPickableComponent>();

				if (equipable != nullptr && equipable->IsActive())
				{
					equipable->Equipped();
					EquippedObject = equipable;
					
					equipable->GetOwner()->AttachToComponent(FirstPersonCameraComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
					equipable->GetOwner()->SetActorRelativeLocation(FVector(20.f, 8.f, -10.f));
				}
				if (interactable != nullptr && interactable->IsActive())
				{
					interactable->Trigger();
				}

				else if (pickable != nullptr && pickedObject == nullptr)
				{
					//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f, 0, 2.f);
					physics_handle->GrabComponentAtLocationWithRotation(
						hitData.GetComponent(), 
						"None", 
						hitData.GetComponent()->GetComponentLocation(), 
						hitData.GetComponent()->GetComponentRotation());

					pickedObject = hitData.GetActor();
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

void ASpaceCharacter::OnFire()
{
	if (EquippedObject)
	{
		EquippedObject->Fire();
	}
}

void ASpaceCharacter::OnEndFire()
{
	if (EquippedObject)
	{
		EquippedObject->EndFire();
	}
}
