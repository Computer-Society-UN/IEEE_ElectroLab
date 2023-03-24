
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#include "ElectroLab/Public/Maps/LabLBPMainMenu.h"
// Unreal Engine Dependencies:
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Sound/SoundMix.h"
// User Defined Dependencies:
#include "ElectroLab/Public/UMG/Menus/LabUWMainMenu.h"
#include "ElectroLab/Public/Core/SGSettings.h"

	/* ---------------------------- FUNCTION DEFINITIONS ---------------------------- */

ALabLBPMainMenu::ALabLBPMainMenu()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALabLBPMainMenu::BeginPlay()
{
	Super::BeginPlay();

	UGameUserSettings::GetGameUserSettings()->SetFrameRateLimit(30);
	
	if(IsValid(WidgetMainMenuRef) && IsValid(SMixMasterSoundRef) && IsValid(SClassSfxRef) && IsValid(SClassMusicRef))
	{
		APlayerController* CurrentPlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
		
		UGameplayStatics::SetBaseSoundMix(GetWorld(), SMixMasterSoundRef);
		
		WidgetMainMenu = CreateWidget<ULabUWMainMenu>(CurrentPlayerController, WidgetMainMenuRef);
		WidgetMainMenu->AddToViewport();
		WidgetMainMenu->ActivateWidget();
		
		CurrentPlayerController->SetInputMode(FInputModeUIOnly().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock));
		CurrentPlayerController->SetShowMouseCursor(true);
		
		if(UGameplayStatics::DoesSaveGameExist(TEXT("GameSettings"), 0))
		{
			const USGSettings* SGSettings = Cast<USGSettings>(UGameplayStatics::LoadGameFromSlot(TEXT("GameSettings"), 0));
			
			if(SGSettings != nullptr)
			{
				UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SMixMasterSoundRef, SClassMusicRef,
									Cast<USGSettings>(UGameplayStatics::LoadGameFromSlot(TEXT("GameSettings"),0))->MusicVolume,
								1,0,true);
					
				UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SMixMasterSoundRef, SClassSfxRef,
					Cast<USGSettings>(UGameplayStatics::LoadGameFromSlot(TEXT("GameSettings"),0))->SfxVolume,
					1,0,true);

				switch (Cast<USGSettings>(UGameplayStatics::LoadGameFromSlot(TEXT("GameSettings"),0))->GameLanguage)
				{
					case 0:
					UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("en"), false);
					break;

					case 1:
					UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("es"), false);
					break;
			
					default:
					UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("en"), false);
					break;
				}
			}
		}
		else
		{
			/** First Game Start:
			 *
			 * When it detects that the game is starting for the first time or the settings file has been lost, it obtains
			 * the resolutions supported by the monitor where the game is running and by default activates the Full Screen
			 * Mode at the maximum available resolution, then it runs a Benchmark to detect the optimal settings, applies
			 * these settings and saves them, it also generates a save file with the default values for sound and language.
			 * 
			 */
			
			UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
			TArray<FIntPoint> ScreenResolutions;
			UKismetSystemLibrary::GetSupportedFullscreenResolutions(ScreenResolutions);
			const FIntPoint MaxResolutionSupported = ScreenResolutions.Last();
			
			GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
			GameUserSettings->SetScreenResolution(MaxResolutionSupported);
			
			GameUserSettings->RunHardwareBenchmark(10, 0.75f, 0.75f);
			GameUserSettings->ApplyHardwareBenchmarkResults();
			GameUserSettings->SaveSettings();
			GameUserSettings->ApplySettings(false);
			
			USGSettings* SaveGameObject = Cast<USGSettings>(UGameplayStatics::CreateSaveGameObject(USGSettings::StaticClass()));
			
			SaveGameObject->SfxVolume = 1;
			SaveGameObject->MusicVolume = 1;
			SaveGameObject->GameLanguage = 0;
			UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("en"), false);
			
			UGameplayStatics::SaveGameToSlot(SaveGameObject, TEXT("GameSettings"), 0);
		}
	}
}