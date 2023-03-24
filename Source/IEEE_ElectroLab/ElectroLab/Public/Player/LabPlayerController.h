
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LabPlayerController.generated.h"

//Forward Declarations
class UCommonActivatableWidget;
class UInputMappingContext;
class UInputAction;
class ALabEngineerCharacter;
class ULabUWPauseGame;
class ULabHUDGameplay;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ALabPlayerController : public APlayerController
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

#pragma region EnhancedInput
    
	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Input Actions")
	TObjectPtr<UInputMappingContext> LabMappingContext = { nullptr };

	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Input Actions")
	TObjectPtr<UInputAction> ActionCharacterMovement = { nullptr };

	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Input Actions")
	TObjectPtr<UInputAction> ActionCharacterLook = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Input Actions")
	TObjectPtr<UInputAction> ActionCharacterStaticInteraction = { nullptr };

	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Input Actions")
	TObjectPtr<UInputAction> ActionCharacterDynamicInteraction = { nullptr };

	UPROPERTY(EditDefaultsOnly, Transient, Category="Player Controller|Input Actions")
	TObjectPtr<UInputAction> ActionPause = { nullptr };

#pragma endregion EnhancedInput

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
	 * @param Value Input received from user controls (Mouse/Keyboard - Gamepads).
	 */
	UFUNCTION()
	void CharacterMovement(const FInputActionValue& Value);

	/**
	 * @brief Processes the input and sends the parameters of the camera movement to the character.
	 * @param Value Input received from user controls (Mouse/Keyboard - Gamepads).
	 */
	UFUNCTION()
	void CharacterLook(const FInputActionValue& Value);

	/**
	 * @brief Processes the Input and sends the command to initiate a static interaction to the character.
	 * @param Value Input received from user controls (Mouse/Keyboard - Gamepads).
	 */
	UFUNCTION()
	void CharacterStaticInteraction(const FInputActionValue& Value);

	/**
	 * @brief Processes the Input and sends the command to initiate a dynamic interaction to the character.
	 * @param Value Input received from user controls (Mouse/Keyboard - Gamepads).
	 */
	UFUNCTION()
	void CharacterDynamicInteraction(const FInputActionValue& Value);

	/**
	 * @brief Processes the Input and sends the command to initiate a static interaction to the character.
	 */
	UFUNCTION()
	void PauseGame(const FInputActionValue& Value);
	
};