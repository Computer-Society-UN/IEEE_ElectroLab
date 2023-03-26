
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "ElectroLab/Public/Interfaces/LabIDamageable.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LabEngineerCharacter.generated.h"

// Forward Declarations
class USpringArmComponent;
class UCameraComponent;
enum ESafetyEquipmentType;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabEngineerCharacter : public ACharacter, public ILabIDamageable
{
	GENERATED_BODY()
	
	/* ------------------------------ CLASS COMPONENTS ------------------------------ */
	
private:
	
	UPROPERTY(VisibleDefaultsOnly, Transient, meta=(DisplayName="Camera"))
	TObjectPtr<UCameraComponent> CameraComponent = { nullptr };
	
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

#pragma region DebugVariables
	
	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Interaction Debug Type", ClampMin=0.0f, ClampMax=20.0f), Category="Engineer Character|Debug")
    TEnumAsByte<EDrawDebugTrace::Type> InteractionDebugType = EDrawDebugTrace::None;
        
    UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Debug Draw Time", ClampMin=0.0f, ClampMax=20.0f), Category="Engineer Character|Debug")
    float DebugDrawTime = 1.0f;

#pragma endregion DebugVariables

	UPROPERTY(Transient)
	TArray<TEnumAsByte<ESafetyEquipmentType>> EngineerSafetyEquipment = {};
	
	UPROPERTY(Transient)
	TObjectPtr<AActor> ActorToInteract = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="Max Interaction Distance", ClampMin=50, ClampMax=250), Category="Engineer Character|Interation")
	int32 MaxInteractionDistance = 100;
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="VFX Character Footsteps"), Category="Engineer Character|Events")
	void SFXCharacterFoosteps();
	
	UFUNCTION()
	void CharacterMovement(const float HorizontalMovementValue, const float VerticalMovementValue);

	UFUNCTION()
	void CharacterLook(const float YawRotationValue, const float PitchRotationValue);

	UFUNCTION()
	void CharacterStaticInteraction();

	UFUNCTION()
	void CharacterOnGoingDynamicInteraction(const float HoldTime);
	
	UFUNCTION()
	void CharacterCancelDynamicInteraction();
	
	UFUNCTION()
	void CharacterTriggerDynamicInteraction();
	
private:

	// Class Constructor
	ALabEngineerCharacter();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Damageable Interface Implementation
	virtual void TakeDamage() override;

	/* When the system requests the character's equipment, it sends it. */
	UFUNCTION()
	void CheckIfIShouldEndTheEquipmentIHaveOn();
	
	/**
	 * @brief When a new security item is picked up, it adds it to the list of items.
	 * @param NewEquipmentCollected New safety element collected.
	 */
	UFUNCTION()
	void PickUpNewSafetyEquipment(TEnumAsByte<ESafetyEquipmentType> NewEquipmentCollected);
	
};