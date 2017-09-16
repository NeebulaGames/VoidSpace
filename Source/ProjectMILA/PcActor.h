// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "PcActor.generated.h"

UCLASS()
class PROJECTMILA_API APcActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APcActor();

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	bool bEmergencyKeyboard = false;

	class ASpacestationManagementActor* StationManager;

	UPROPERTY(VisibleAnywhere, Category = Audio)
	USoundWave* InsertCDSound;
	
	UPROPERTY(VisibleAnywhere, Category = PcMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* PcMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = BoxTrigger, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	bool bPcIsActive = false;
	UMaterialInstanceDynamic* ScreenMaterial = nullptr;
	UMaterialInstanceDynamic* PCMaterial = nullptr;

	UFUNCTION()
	void OnActivePc();

	UFUNCTION()
	void OnDisablePc();
};
