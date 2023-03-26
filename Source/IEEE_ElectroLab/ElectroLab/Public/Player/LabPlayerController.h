
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "ElectroLab/Public/Input/LabInputDataBase.h"
#include "GameFramework/PlayerController.h"
#include "LabPlayerController.generated.h"

//Forward Declarations
class UCommonActivatableWidget;
class UInputMappingContext;
class ALabEngineerCharacter;
class ULabUWPauseGame;
class ULabHUDGameplay;
class ULabInputDataBase;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabPlayerController : public APlayerController
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

    UPROPERTY(Transient)
	TObjectPtr<UEnhancedPlayerInput> PlayerInputReference;
	
	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Input Mapping Context")
	TObjectPtr<UInputMappingContext> LabMappingContext = { nullptr };

	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Input Actions Data")
	TObjectPtr<ULabInputDataBase> InputDataAsset = { nullptr };

	UPROPERTY(Transient)
	TObjectPtr<ALabEngineerCharacter> EngineerCharacterRef = { nullptr };

	UPROPERTY(Transient)
	TObjectPtr<ULabHUDGameplay> WidgetHUDGameplay = { nullptr };
	
	UPROPERTY(Transient)
	TObjectPtr<ULabUWPauseGame> WidgetPause = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Widgets")
	TSubclassOf<ULabUWPauseGame> WidgetPauseRef = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Widgets")
	TSubclassOf<ULabHUDGameplay> WidgetHUDGameplayRef = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

private:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	/**
	 * @brief Processes the input and sends the motion parameters to the character.
	 * @param Value Input received from user controls (Mouse/Keyboard).
	 */
	UFUNCTION()
	void CharacterMovement(const FInputActionValue& Value);

	/**
	 * @brief Processes the input and sends the parameters of the camera movement to the character.
	 * @param Value Input received from user controls (Mouse/Keyboard).
	 */
	UFUNCTION()
	void CharacterLook(const FInputActionValue& Value);

	/**
	 * @brief Processes the Input and sends the command to initiate a static interaction to the character.
	 * @param Value Input received from user controls (Mouse/Keyboard).
	 */
	UFUNCTION()
	void CharacterStaticInteraction(const FInputActionValue& Value);
	
	/**
	 * @brief Processes the Input and sends the time the button has been pressed.
	 * @param Value Time the button has been held down.
	 */
	UFUNCTION()
	void CharacterOnGoingDynamicInteraction(const FInputActionValue& Value);
	
	/**
	 * @brief It is triggered when the player releases the button and the required time has not been completed.
	 * @param Value Input received from user controls (Mouse/Keyboard).
	 */
	UFUNCTION()
	void CharacterCancelDynamicInteraction(const FInputActionValue& Value);
	
	/**
	 * @brief Processes the Input and sends the command to initiate a dynamic interaction to the character.
	 * @param Value Input received from user controls (Mouse/Keyboard).
	 */
	UFUNCTION()
	void CharacterTriggerDynamicInteraction(const FInputActionValue& Value);

	/**
	 * @brief Processes the Input and sends the command to initiate a static interaction to the character.
	 */
	UFUNCTION()
	void PauseGame(const FInputActionValue& Value);
	
};