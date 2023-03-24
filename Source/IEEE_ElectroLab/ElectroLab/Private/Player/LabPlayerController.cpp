
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Player/LabPlayerController.h"
// Unreal Engine Dependencies:
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
// User Defined Dependencies:
#include "ElectroLab/Public/Player/LabEngineerCharacter.h"
#include "ElectroLab/Public/UMG/HUD/LabHUDGameplay.h"
#include "ElectroLab/Public/UMG/Menus/LabUWPauseGame.h"

void ALabPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(LabMappingContext)
		{
			Subsystem->AddMappingContext(LabMappingContext, 0);
		}
	}

	EngineerCharacterRef = Cast<ALabEngineerCharacter>(K2_GetPawn());
	
	if (IsValid(WidgetHUDGameplayRef) && IsValid(EngineerCharacterRef))
	{
		WidgetHUDGameplay = CreateWidget<ULabHUDGameplay>(this, WidgetHUDGameplayRef);
		WidgetHUDGameplay->AddToViewport();

		SetInputMode(FInputModeGameOnly());
		SetShowMouseCursor(false);
	}
}

void ALabPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ActionCharacterMovement, ETriggerEvent::Triggered, this, &ALabPlayerController::CharacterMovement);
		EnhancedInputComponent->BindAction(ActionCharacterLook, ETriggerEvent::Triggered, this, &ALabPlayerController::CharacterLook);
		EnhancedInputComponent->BindAction(ActionCharacterStaticInteraction, ETriggerEvent::Started, this, &ALabPlayerController::CharacterStaticInteraction);
		EnhancedInputComponent->BindAction(ActionCharacterDynamicInteraction, ETriggerEvent::Triggered, this, &ALabPlayerController::CharacterDynamicInteraction);
		EnhancedInputComponent->BindAction(ActionPause, ETriggerEvent::Started, this, &ALabPlayerController::PauseGame);
	}
}

void ALabPlayerController::CharacterMovement(const FInputActionValue& Value)
{
	if (IsValid(EngineerCharacterRef))
	{
		const FVector2d InputAmount = Value.Get<FVector2d>();
		EngineerCharacterRef->CharacterMovement(InputAmount.X, InputAmount.Y);
	}
}

void ALabPlayerController::CharacterLook(const FInputActionValue& Value)
{
	if (IsValid(EngineerCharacterRef))
	{
		const FVector2d InputAmount = Value.Get<FVector2d>();
		EngineerCharacterRef->CharacterLook(InputAmount.X, InputAmount.Y);
	}
}

void ALabPlayerController::CharacterStaticInteraction(const FInputActionValue& Value)
{
	if (const bool InputAmount = Value.Get<bool>(); IsValid(EngineerCharacterRef) && InputAmount)
	{
		EngineerCharacterRef->CharacterStaticInteraction();
	}
}

void ALabPlayerController::CharacterDynamicInteraction(const FInputActionValue& Value)
{
	if (const bool InputAmount = Value.Get<bool>(); IsValid(EngineerCharacterRef) && InputAmount)
	{
		EngineerCharacterRef->CharacterDynamicInteraction();
	}
}

void ALabPlayerController::PauseGame(const FInputActionValue& Value)
{
	if (const bool InputAmount = Value.Get<bool>())
    {
		UGameplayStatics::SetGamePaused(GetWorld(), InputAmount);
		
		if (IsValid(WidgetPauseRef))
		{
			WidgetPause = CreateWidget<ULabUWPauseGame>(this, WidgetPauseRef);
			WidgetPause->AddToViewport();
			WidgetPause->ActivateWidget();

			SetInputMode(FInputModeUIOnly().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock));
			SetShowMouseCursor(true);
		}
    }
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), InputAmount);

		if (IsValid(WidgetPause))
		{
			WidgetPause->RemoveFromParent();
			WidgetPause = nullptr;

			SetInputMode(FInputModeGameOnly());
			SetShowMouseCursor(false);
		}
	}
}