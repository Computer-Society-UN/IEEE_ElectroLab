
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/UMG/Menus/LabUWSettingsMenu.h"
// Unreal Engine Dependencies:
#include "CommonNumericTextBlock.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
// User Defined Dependencies:
#include "ElectroLab/Public/Core/SGSettings.h"
#include "ElectroLab/Public/UMG/Menus/LabUWMainMenu.h"
#include "ElectroLab/Public/UMG/Menus/LabCustomButton.h"
#include "ElectroLab/Public/UMG/Menus/LabUWPauseGame.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

#pragma region Initialization

void ULabUWSettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	SliderMusicVolume->OnMouseCaptureEnd.AddUniqueDynamic(this, &ULabUWSettingsMenu::SetMusicVolume);
	SliderMusicVolume->OnControllerCaptureEnd.AddUniqueDynamic(this, &ULabUWSettingsMenu::SetMusicVolume);
	SliderSfxVolume->OnMouseCaptureEnd.AddUniqueDynamic(this, &ULabUWSettingsMenu::SetSfxVolume);
	SliderSfxVolume->OnControllerCaptureEnd.AddUniqueDynamic(this, &ULabUWSettingsMenu::SetSfxVolume);
	ComboBoxResolutions->OnSelectionChanged.AddDynamic(this, &ULabUWSettingsMenu::SetScreenResolution);
	
	bIsInMenu = UGameplayStatics::GetCurrentLevelName(GetWorld(), true) == "Map_MainMenu";
	
	TArray<FIntPoint> ScreenResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(ScreenResolutions);

	for(const FIntPoint Resolution: ScreenResolutions)
	{
		const FText Width = UKismetTextLibrary::Conv_IntToText(Resolution.X,false,false,3,4);
		const FText Heigh = UKismetTextLibrary::Conv_IntToText(Resolution.Y,false,false,3,4);
		const FString ResolutionToAdd = FText::Format(FText::FromString("{0} x {1}"), Width, Heigh).ToString();
		ComboBoxResolutions->AddOption(ResolutionToAdd);
	}

	GameUserSettingsReference = UGameUserSettings::GetGameUserSettings();
	PostProcessQualityReference = GameUserSettingsReference->GetPostProcessingQuality();
	AntiAliasingQualityReference = GameUserSettingsReference->GetAntiAliasingQuality();
	TextureQualityReference = GameUserSettingsReference->GetTextureQuality();
	ShadowsQualityReference = GameUserSettingsReference->GetShadowQuality();
	
	switch(GameUserSettingsReference->GetFullscreenMode())
	{
	case EWindowMode::Fullscreen:
		WindowModeReference = 0;
		break;
		
	case EWindowMode::WindowedFullscreen:
		WindowModeReference = 1;
		break;
		
	case EWindowMode::Windowed:
		WindowModeReference = 2;
		break;
		
	default:break;
	}
	
	LoadSettings();
}

#pragma endregion Initialization

#pragma region Extra Functions

void ULabUWSettingsMenu::Back()
{
	if(!IsValid(WidgetPauseRef) || !IsValid(WidgetMainMenuRef)) return;

	APlayerController* PlayerReference = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	SaveSettings();
	this->DeactivateWidget();
	this->RemoveFromParent();

	if (bIsInMenu)
	{
		WidgetMainMenu = CreateWidget<ULabUWMainMenu>(PlayerReference, WidgetMainMenuRef);
        WidgetMainMenu->AddToViewport();
        WidgetMainMenu->ActivateWidget();
	}
	else
	{
		WidgetPauseMenu = CreateWidget<ULabUWPauseGame>(PlayerReference, WidgetPauseRef);
		WidgetPauseMenu->AddToViewport();
		WidgetPauseMenu->ActivateWidget();
	}
	
	PlayerReference->SetInputMode(FInputModeUIOnly().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock));
	PlayerReference->SetShowMouseCursor(true);
}


void ULabUWSettingsMenu::SaveSettings()
{
	GameUserSettingsReference->SaveSettings();
	SaveGameObject = Cast<USGSettings>(UGameplayStatics::CreateSaveGameObject(USGSettings::StaticClass()));
	
	SaveGameObject->SfxVolume = SliderSfxVolume->GetValue();
	SaveGameObject->MusicVolume = SliderMusicVolume->GetValue();;
	SaveGameObject->GameLanguage = CurrentLanguage;

	UGameplayStatics::SaveGameToSlot(SaveGameObject, TEXT("GameSettings"), 0);
}

void ULabUWSettingsMenu::LoadSettings()
{
	GameUserSettingsReference->ApplySettings(false);
	
	const FIntPoint ScreenResolution = GameUserSettingsReference->GetScreenResolution();
	const FText Width = UKismetTextLibrary::Conv_IntToText(ScreenResolution.X,false,false,3,4);
	const FText Heigh = UKismetTextLibrary::Conv_IntToText(ScreenResolution.Y,false,false,3,4);
	const FString SelectedResolution = FText::Format(FText::FromString("{0} x {1}"), Width, Heigh).ToString();
	ComboBoxResolutions->SetSelectedOption(SelectedResolution);
	
	UpdateSelectedButtonForWindowMode();
	UpdateSelectedButtonForPostProcessQuality();
	UpdateSelectedButtonForTextureQuality();
	UpdateSelectedButtonForAntiAliasingQuality();
	UpdateSelectedButtonForShadowsQuality();
	
	if(IsValid(SMixMasterSoundRef))
	{
		UGameplayStatics::SetBaseSoundMix(GetWorld(), SMixMasterSoundRef);
	}
	
	const USGSettings* SGSettings = Cast<USGSettings>(UGameplayStatics::LoadGameFromSlot(TEXT("GameSettings"), 0));
	
	if(SGSettings != nullptr)
	{
		CurrentLanguage = SGSettings->GameLanguage;
		UpdateSelectedButtonForGameLanguage();
		SliderMusicVolume->SetValue(SGSettings->MusicVolume);
		SliderSfxVolume->SetValue(SGSettings->SfxVolume);
		SetMusicVolume();
		SetSfxVolume();
	}
}

#pragma endregion Extra Functions

#pragma region Change Configuration

void ULabUWSettingsMenu::AutoDetectSettings()
{
	if(!IsValid(ButtonStyleUnselectedSetting) || !IsValid(ButtonStyleUnselectedSetting)) return;

	switch (PostProcessQualityReference)
	{
	case 0:
		ButtonPostProcessLow->SetStyle(ButtonStyleUnselectedSetting);
		ButtonPostProcessLow->SetIsLocked(false);
		break;
		
	case 1:
		ButtonPostProcessMedium->SetStyle(ButtonStyleUnselectedSetting);
		ButtonPostProcessMedium->SetIsLocked(false);
		break;

	case 2:
		ButtonPostProcessHigh->SetStyle(ButtonStyleUnselectedSetting);
		ButtonPostProcessHigh->SetIsLocked(false);
		break;

	case 3:
		ButtonPostProcessEpic->SetStyle(ButtonStyleUnselectedSetting);
		ButtonPostProcessEpic->SetIsLocked(false);
		break;
		
	default:break;
	}
	
	switch (TextureQualityReference)
	{
	case 0:
		ButtonTextureLow->SetStyle(ButtonStyleUnselectedSetting);
		ButtonTextureLow->SetIsLocked(false);
		break;

	case 1:
		ButtonTextureMedium->SetStyle(ButtonStyleUnselectedSetting);
		ButtonTextureMedium->SetIsLocked(false);
		break;

	case 2:
		ButtonTextureHigh->SetStyle(ButtonStyleUnselectedSetting);
		ButtonTextureHigh->SetIsLocked(false);
		break;

	case 3:
		ButtonTextureEpic->SetStyle(ButtonStyleUnselectedSetting);
		ButtonTextureEpic->SetIsLocked(false);
		break;
		
	default:break;
	}
	
	switch (AntiAliasingQualityReference)
	{
	case 0:
		ButtonAntiAliasingLow->SetStyle(ButtonStyleUnselectedSetting);
		ButtonAntiAliasingLow->SetIsLocked(false);
		break;

	case 1:
		ButtonAntiAliasingMedium->SetStyle(ButtonStyleUnselectedSetting);
		ButtonAntiAliasingMedium->SetIsLocked(false);
		break;

	case 2:
		ButtonAntiAliasingHigh->SetStyle(ButtonStyleUnselectedSetting);
		ButtonAntiAliasingHigh->SetIsLocked(false);
		break;

	case 3:
		ButtonAntiAliasingEpic->SetStyle(ButtonStyleUnselectedSetting);
		ButtonAntiAliasingEpic->SetIsLocked(false);
		break;
		
	default:break;
	}
	
	switch (ShadowsQualityReference)
		{
		case 0:
			ButtonShadowsLow->SetStyle(ButtonStyleUnselectedSetting);
			ButtonShadowsLow->SetIsLocked(false);
			break;

		case 1:
			ButtonShadowsMedium->SetStyle(ButtonStyleUnselectedSetting);
			ButtonShadowsMedium->SetIsLocked(false);
			break;

		case 2:
			ButtonShadowsHigh->SetStyle(ButtonStyleUnselectedSetting);
			ButtonShadowsHigh->SetIsLocked(false);
			break;

		case 3:
			ButtonShadowsEpic->SetStyle(ButtonStyleUnselectedSetting);
			ButtonShadowsEpic->SetIsLocked(false);
			break;
		
		default:;
		}
	
	GameUserSettingsReference->RunHardwareBenchmark(10, 0.75f, 0.75f);
	GameUserSettingsReference->ApplyHardwareBenchmarkResults();
	
	PostProcessQualityReference = GameUserSettingsReference->GetPostProcessingQuality();
	AntiAliasingQualityReference = GameUserSettingsReference->GetAntiAliasingQuality();
	TextureQualityReference = GameUserSettingsReference->GetTextureQuality();
	ShadowsQualityReference = GameUserSettingsReference->GetShadowQuality();
	
	SaveSettings();
	LoadSettings();
}


void ULabUWSettingsMenu::SetScreenResolution(const FString Item, [[maybe_unused]] ESelectInfo::Type Type)
{
	FString WidthScreen;
	FString HeightScreen;
	FString* LeftString = &WidthScreen;
	FString* RightString = &HeightScreen;
	
	if(Item.Split(TEXT(" x "), LeftString, RightString,ESearchCase::IgnoreCase, ESearchDir::FromStart))
	{
		FIntPoint ScreenResolution;
		
		ScreenResolution.X = UKismetStringLibrary::Conv_StringToInt(WidthScreen);
		ScreenResolution.Y = UKismetStringLibrary::Conv_StringToInt(HeightScreen);

		GameUserSettingsReference->SetScreenResolution(ScreenResolution);
		GameUserSettingsReference->ApplySettings(false);
	}
}

void ULabUWSettingsMenu::SetGameLanguage(const int32 LanguageValue)
{	
	switch (CurrentLanguage)
	{
	case 0:
		ButtonEnglish->SetStyle(ButtonStyleUnselectedSetting);
		ButtonEnglish->SetIsLocked(false);
		break;

	case 1:
		ButtonSpanish->SetStyle(ButtonStyleUnselectedSetting);
		ButtonSpanish->SetIsLocked(false);
		break;
		
	default:break;
	}

	switch (LanguageValue)
	{
	case 0:
		UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("en"), false);
		break;

	case 1:
		UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("es"), false);
		break;
		
	default:break;
	}
	
	CurrentLanguage = LanguageValue;
	UpdateSelectedButtonForGameLanguage();
}

void ULabUWSettingsMenu::SetMusicVolume()
{
	if(!IsValid(SMixMasterSoundRef) || !IsValid(SClassMusicRef)) return;
	SaveSettings();
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SMixMasterSoundRef, SClassMusicRef,
		Cast<USGSettings>(UGameplayStatics::LoadGameFromSlot(TEXT("GameSettings"),0))->MusicVolume,
		1,0,true);
	
	SliderMusicValueText->SetCurrentValue(SliderMusicVolume->GetValue() * 100);
}

void ULabUWSettingsMenu::SetSfxVolume()
{
	if(!IsValid(SMixMasterSoundRef) || !IsValid(SClassSfxRef)) return;
	SaveSettings();
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SMixMasterSoundRef, SClassSfxRef,
		Cast<USGSettings>(UGameplayStatics::LoadGameFromSlot(TEXT("GameSettings"),0))->SfxVolume,
		1,0,true);
	
	SliderSfxValueText->SetCurrentValue(SliderSfxVolume->GetValue() * 100);
}

void ULabUWSettingsMenu::SetWindowMode(const EWindowMode::Type WindowModeType)
{
	if(!IsValid(ButtonStyleUnselectedSetting)) return;
	
	switch (WindowModeReference)
	{
	case 0:
		ButtonFullScreen->SetStyle(ButtonStyleUnselectedSetting);
		ButtonFullScreen->SetIsLocked(false);
		break;

	case 1:
		ButtonWindowedFullScreen->SetStyle(ButtonStyleUnselectedSetting);
		ButtonWindowedFullScreen->SetIsLocked(false);
		break;
		
	case 2:
		ButtonWindowed->SetStyle(ButtonStyleUnselectedSetting);
		ButtonWindowed->SetIsLocked(false);
		break;
		
	default:break;
	}
	
	switch(WindowModeType)
	{
		case EWindowMode::Fullscreen:
            WindowModeReference = 0;
		    break;
		
		case EWindowMode::WindowedFullscreen:
			WindowModeReference = 1;
			break;
		
        case EWindowMode::Windowed:
        	WindowModeReference = 2;
            break;
		
	default:break;
	}
	
	GameUserSettingsReference->SetFullscreenMode(WindowModeType);
	GameUserSettingsReference->ApplySettings(false);
	UpdateSelectedButtonForWindowMode();
}

void ULabUWSettingsMenu::SetPostProcessQuality(const int32 PostProcessValue)
{
	if(!IsValid(ButtonStyleUnselectedSetting)) return;
	
	switch (PostProcessQualityReference)
	{
	case 0:
		ButtonPostProcessLow->SetStyle(ButtonStyleUnselectedSetting);
		ButtonPostProcessLow->SetIsLocked(false);
		break;
		
	case 1:
		ButtonPostProcessMedium->SetStyle(ButtonStyleUnselectedSetting);
		ButtonPostProcessMedium->SetIsLocked(false);
		break;

	case 2:
		ButtonPostProcessHigh->SetStyle(ButtonStyleUnselectedSetting);
		ButtonPostProcessHigh->SetIsLocked(false);
		break;

	case 3:
		ButtonPostProcessEpic->SetStyle(ButtonStyleUnselectedSetting);
		ButtonPostProcessEpic->SetIsLocked(false);
		break;
		
	default:break;
	}
	
	PostProcessQualityReference = PostProcessValue;
	GameUserSettingsReference->SetPostProcessingQuality(PostProcessValue);
	GameUserSettingsReference->ApplySettings(false);
	UpdateSelectedButtonForPostProcessQuality();
}

void ULabUWSettingsMenu::SetTextureQuality(const int32 TextureValue)
{
	if(!IsValid(ButtonStyleUnselectedSetting)) return;
	
	switch (TextureQualityReference)
	{
	case 0:
		ButtonTextureLow->SetStyle(ButtonStyleUnselectedSetting);
		ButtonTextureLow->SetIsLocked(false);
		break;

	case 1:
		ButtonTextureMedium->SetStyle(ButtonStyleUnselectedSetting);
		ButtonTextureMedium->SetIsLocked(false);
		break;

	case 2:
		ButtonTextureHigh->SetStyle(ButtonStyleUnselectedSetting);
		ButtonTextureHigh->SetIsLocked(false);
		break;

	case 3:
		ButtonTextureEpic->SetStyle(ButtonStyleUnselectedSetting);
		ButtonTextureEpic->SetIsLocked(false);
		break;
		
	default:break;
	}
	
	TextureQualityReference = TextureValue;
	GameUserSettingsReference->SetTextureQuality(TextureValue);
	GameUserSettingsReference->ApplySettings(false);
	UpdateSelectedButtonForTextureQuality();
}

void ULabUWSettingsMenu::SetAntiAliasingQuality(const int32 AntiAliasingValue)
{
	if(!IsValid(ButtonStyleUnselectedSetting)) return;
	
	switch (AntiAliasingQualityReference)
	{
	case 0:
		ButtonAntiAliasingLow->SetStyle(ButtonStyleUnselectedSetting);
		ButtonAntiAliasingLow->SetIsLocked(false);
		break;

	case 1:
		ButtonAntiAliasingMedium->SetStyle(ButtonStyleUnselectedSetting);
		ButtonAntiAliasingMedium->SetIsLocked(false);
		break;

	case 2:
		ButtonAntiAliasingHigh->SetStyle(ButtonStyleUnselectedSetting);
		ButtonAntiAliasingHigh->SetIsLocked(false);
		break;

	case 3:
		ButtonAntiAliasingEpic->SetStyle(ButtonStyleUnselectedSetting);
		ButtonAntiAliasingEpic->SetIsLocked(false);
		break;
		
	default:break;
	}
	
	AntiAliasingQualityReference = AntiAliasingValue;
	GameUserSettingsReference->SetAntiAliasingQuality(AntiAliasingValue);
	GameUserSettingsReference->ApplySettings(false);
	UpdateSelectedButtonForAntiAliasingQuality();
}

void ULabUWSettingsMenu::SetShadowsQuality(const int32 ShadowsValue)
{
	if(!IsValid(ButtonStyleUnselectedSetting)) return;
	
	switch (ShadowsQualityReference)
		{
		case 0:
			ButtonShadowsLow->SetStyle(ButtonStyleUnselectedSetting);
			ButtonShadowsLow->SetIsLocked(false);
			break;

		case 1:
			ButtonShadowsMedium->SetStyle(ButtonStyleUnselectedSetting);
			ButtonShadowsMedium->SetIsLocked(false);
			break;

		case 2:
			ButtonShadowsHigh->SetStyle(ButtonStyleUnselectedSetting);
			ButtonShadowsHigh->SetIsLocked(false);
			break;

		case 3:
			ButtonShadowsEpic->SetStyle(ButtonStyleUnselectedSetting);
			ButtonShadowsEpic->SetIsLocked(false);
			break;
		
		default:;
		}
	
	ShadowsQualityReference = ShadowsValue;
	GameUserSettingsReference->SetShadowQuality(ShadowsValue);
	GameUserSettingsReference->ApplySettings(false);
	UpdateSelectedButtonForShadowsQuality();
}

#pragma endregion Change Configuration

#pragma region Buttons Visual Updates

void ULabUWSettingsMenu::UpdateSelectedButtonForGameLanguage() const
{
	if(!IsValid(ButtonStyleSelectedSetting)) return;
	
	switch (CurrentLanguage)
	{
		case 0:
			ButtonEnglish->SetStyle(ButtonStyleSelectedSetting);
			ButtonEnglish->SetIsLocked(true);
			break;

		case 1:
			ButtonSpanish->SetStyle(ButtonStyleSelectedSetting);
			ButtonSpanish->SetIsLocked(true);
			break;
		
		default:break;
	}
}

void ULabUWSettingsMenu::UpdateSelectedButtonForWindowMode() const
{
	if(!IsValid(ButtonStyleSelectedSetting)) return;
	
	switch (WindowModeReference)
	{
	case 0:
		ButtonFullScreen->SetStyle(ButtonStyleSelectedSetting);
		ButtonFullScreen->SetIsLocked(true);
		break;

	case 1:
		ButtonWindowedFullScreen->SetStyle(ButtonStyleSelectedSetting);
		ButtonWindowedFullScreen->SetIsLocked(true);
		break;
		
	case 2:
		ButtonWindowed->SetStyle(ButtonStyleSelectedSetting);
		ButtonWindowed->SetIsLocked(true);
		break;
		
	default:break;
	}
}

void ULabUWSettingsMenu::UpdateSelectedButtonForPostProcessQuality() const
{
	if(!IsValid(ButtonStyleSelectedSetting)) return;
	
	switch (PostProcessQualityReference)
	{
	case 0:
		ButtonPostProcessLow->SetStyle(ButtonStyleSelectedSetting);
		ButtonPostProcessLow->SetIsLocked(true);
		break;
		
	case 1:
		ButtonPostProcessMedium->SetStyle(ButtonStyleSelectedSetting);
		ButtonPostProcessMedium->SetIsLocked(true);
		break;

	case 2:
		ButtonPostProcessHigh->SetStyle(ButtonStyleSelectedSetting);
		ButtonPostProcessHigh->SetIsLocked(true);
		break;

	case 3:
		ButtonPostProcessEpic->SetStyle(ButtonStyleSelectedSetting);
		ButtonPostProcessEpic->SetIsLocked(true);
		break;
		
	default:break;
	}
}

void ULabUWSettingsMenu::UpdateSelectedButtonForTextureQuality() const
{
	if(!IsValid(ButtonStyleSelectedSetting)) return;
	
	switch (TextureQualityReference)
	{
	case 0:
		ButtonTextureLow->SetStyle(ButtonStyleSelectedSetting);
		ButtonTextureLow->SetIsLocked(true);
		break;

	case 1:
		ButtonTextureMedium->SetStyle(ButtonStyleSelectedSetting);
		ButtonTextureMedium->SetIsLocked(true);
		break;

	case 2:
		ButtonTextureHigh->SetStyle(ButtonStyleSelectedSetting);
		ButtonTextureHigh->SetIsLocked(true);
		break;

	case 3:
		ButtonTextureEpic->SetStyle(ButtonStyleSelectedSetting);
		ButtonTextureEpic->SetIsLocked(true);
		break;
		
	default:break;
	}
}

void ULabUWSettingsMenu::UpdateSelectedButtonForAntiAliasingQuality() const
{
	if(!IsValid(ButtonStyleSelectedSetting)) return;
	
	switch (AntiAliasingQualityReference)
	{
	case 0:
		ButtonAntiAliasingLow->SetStyle(ButtonStyleSelectedSetting);
		ButtonAntiAliasingLow->SetIsLocked(true);
		break;

	case 1:
		ButtonAntiAliasingMedium->SetStyle(ButtonStyleSelectedSetting);
		ButtonAntiAliasingMedium->SetIsLocked(true);
		break;

	case 2:
		ButtonAntiAliasingHigh->SetStyle(ButtonStyleSelectedSetting);
		ButtonAntiAliasingHigh->SetIsLocked(true);
		break;

	case 3:
		ButtonAntiAliasingEpic->SetStyle(ButtonStyleSelectedSetting);
		ButtonAntiAliasingEpic->SetIsLocked(true);
		break;
		
	default:break;
	}
}

void ULabUWSettingsMenu::UpdateSelectedButtonForShadowsQuality() const
{
	if(!IsValid(ButtonStyleSelectedSetting)) return;
	
	switch (ShadowsQualityReference)
	{
	case 0:
		ButtonShadowsLow->SetStyle(ButtonStyleSelectedSetting);
		ButtonShadowsLow->SetIsLocked(true);
		break;

	case 1:
		ButtonShadowsMedium->SetStyle(ButtonStyleSelectedSetting);
		ButtonShadowsMedium->SetIsLocked(true);
		break;

	case 2:
		ButtonShadowsHigh->SetStyle(ButtonStyleSelectedSetting);
		ButtonShadowsHigh->SetIsLocked(true);
		break;

	case 3:
		ButtonShadowsEpic->SetStyle(ButtonStyleSelectedSetting);
		ButtonShadowsEpic->SetIsLocked(true);
		break;
		
	default:break;
	}
}

#pragma endregion Buttons Visual Updates