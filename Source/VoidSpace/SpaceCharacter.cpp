// Fill out your copyright notice in the Description page of Project Settings.

#include "VoidSpace.h"
#include "SpaceCharacter.h"
#include "InteractableComponent.h"
#include "PickableComponent.h"
#include "SpaceStatics.h"
#include "SpaceGameStateBase.h"
#include "EquipableComponent.h"
#include "SpaceSuitActor.h"
#include "SpacestationManagementActor.h"
#include "GameEventManager.h"


// Sets default values
ASpaceCharacter::ASpaceCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	ConstructorHelpers::FObjectFinder<UParticleSystem> SmokeJetpack(TEXT("ParticleSystem'/Game/Particles/P_JetpackSmoke.P_JetpackSmoke'"));

	LeftJetpackSmokeComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("JetpackSmoke1"));
	LeftJetpackSmokeComponent->SetupAttachment(GetCapsuleComponent());
	LeftJetpackSmokeComponent->Template = SmokeJetpack.Object;
	LeftJetpackSmokeComponent->RelativeLocation = FVector(0.f, -50.f, 0.f);
	LeftJetpackSmokeComponent->Deactivate();

	RightJetpackSmokeComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("JetpackSmoke2"));
	RightJetpackSmokeComponent->SetupAttachment(GetCapsuleComponent());
	RightJetpackSmokeComponent->Template = SmokeJetpack.Object;
	RightJetpackSmokeComponent->RelativeLocation = FVector(0.f, 50.f, 0.f);
	RightJetpackSmokeComponent->Deactivate();

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
		const FVector End = Start + dir_camera * 150;

		APawn* pawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

		physics_handle->SetTargetLocationAndRotation(End, pawn->GetControlRotation());
	}
	else
	{
		FHitResult hitData;

		if (CastRay(hitData))
		{
			UHighlightComponent* highlight = hitData.Actor->FindComponentByClass<UHighlightComponent>();

			if (LookedObject && LookedObject != highlight)
				LookedObject->OnStopLooking();

			LookedObject = highlight;

			if (highlight)
				highlight->OnBeginLooking();
		}
		else if (LookedObject)
		{
			LookedObject->OnStopLooking();
			LookedObject = nullptr;
		}
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
	ASpaceGameStateBase* state = Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	if (!EquippedSuit)
	{
		if (state)
			state->Die(0);
	}
	else
	{
		bGravityEnabled = !bGravityEnabled;

		state->SpacestationManager->bReduceLifeTime = !bGravityEnabled;
		state->SpacestationManager->LifeTime = state->GameEventManager->GetTime();

		UCharacterMovementComponent* characterMovement = GetCharacterMovement();

		characterMovement->MovementMode = characterMovement->DefaultLandMovementMode = bGravityEnabled ? MOVE_Walking : MOVE_Flying;

		if (bGravityEnabled)
			EquippedSuit->StopConsumingOxygen();
		else
			EquippedSuit->StartConsumingOxygen();
	}
}

void ASpaceCharacter::ToggleSpaceSuit(ASpaceSuitActor* spaceSuit)
{
	EquippedSuit = spaceSuit;
	
	bool set = spaceSuit != nullptr;
	FirstPersonCameraComponent->PostProcessSettings.BloomDirtMaskIntensity = set ? 8.f : 0.f;
	FirstPersonCameraComponent->PostProcessSettings.bOverride_BloomDirtMaskIntensity = set;
}

bool ASpaceCharacter::WearsSpaceSuit() const
{
	return EquippedSuit != nullptr;
}

ASpaceSuitActor* ASpaceCharacter::GetEquippedSuit() const
{
	return EquippedSuit;
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
	if (ASpaceGameStateBase::Instance(GetWorld())->bMovementAllowed && Controller != nullptr)
	{
		if(Val != 0.0f)
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

			float yaw = static_cast<float>(FMath::RadiansToDegrees(acos(-Val)));
			if (yaw > -90.f && yaw < 90.f && WearsSpaceSuit() && !bGravityEnabled)
			{
				LeftJetpackSmokeComponent->Activate();
				RightJetpackSmokeComponent->Activate();
				LeftJetpackSmokeComponent->RelativeRotation  = RightJetpackSmokeComponent->RelativeRotation = FRotator(0.f, yaw, 0.f);
			}
			else
			{
				LeftJetpackSmokeComponent->Deactivate();
				RightJetpackSmokeComponent->Deactivate();
			}
			ForwardAxisVal = Val;
		}
		else
		{
			LeftJetpackSmokeComponent->Deactivate();
			RightJetpackSmokeComponent->Deactivate();
		}
	}
}

void ASpaceCharacter::MoveHorizontal(float Val)
{
	if (ASpaceGameStateBase::Instance(GetWorld())->bMovementAllowed && Controller != nullptr && Val != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Val);

		float angleYAxisInRadians = static_cast<float>(fmod(0.5 * PI - atan2(-ForwardAxisVal, -Val), 2.0 * PI));
		float angleYAxis = FMath::RadiansToDegrees(angleYAxisInRadians);
		if (angleYAxis > -90.f && angleYAxis < 90.f && WearsSpaceSuit() && !bGravityEnabled)
		{
			LeftJetpackSmokeComponent->Activate();
			RightJetpackSmokeComponent->Activate();
			LeftJetpackSmokeComponent->RelativeRotation = RightJetpackSmokeComponent->RelativeRotation = FRotator(0.f, angleYAxis, 0.f);
		}
		else
		{
			LeftJetpackSmokeComponent->Deactivate();
			RightJetpackSmokeComponent->Deactivate();
		}
		ForwardAxisVal = 0.f;
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
		// RELEASE OBJECT
		if (pickedObject != nullptr)
		{
			ReleaseObject();
		}
		else
		{
			if (LookedObject)
			{
				LookedObject->OnStopLooking();

				AActor* lookedActor = LookedObject->GetOwner();
				UEquipableComponent* equipable = lookedActor->FindComponentByClass<UEquipableComponent>();
				UInteractableComponent* interactable = lookedActor->FindComponentByClass<UInteractableComponent>();
				UPickableComponent* pickable = lookedActor->FindComponentByClass<UPickableComponent>();

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
					UPrimitiveComponent* component = pickable->GetOwner()->FindComponentByClass<UPrimitiveComponent>();
					//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f, 0, 2.f);
					physics_handle->GrabComponentAtLocationWithRotation(
						component, 
						"None", 
						component->GetComponentLocation(), 
						component->GetComponentRotation());

					pickedObject = LookedObject->GetOwner();
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

bool ASpaceCharacter::CastRay(FHitResult& result)
{
	const FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	const FVector dir_camera = FirstPersonCameraComponent->GetForwardVector();
	const FVector End = Start + dir_camera * 250;

	result.Init();

	return USpaceStatics::Trace(GetWorld(), this, Start, End, result);
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
