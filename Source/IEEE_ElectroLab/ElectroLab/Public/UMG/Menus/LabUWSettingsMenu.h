
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "ElectroLab/Public/UMG/Menus/LabUWSubMenu.h"
#include "LabUWSettingsMenu.generated.h"

// Forward Declarations
class USlider;
class UComboBoxString;
class UCommonNumericTextBlock;
class UCommonButtonStyle;
class ULabCustomButton;
class USGSettings;
class ULabUWPauseGame;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWSettingsMenu : public ULabUWSubMenu
{
	GENERATED_BODY()
	
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */
	
private:

	/** It will store a reference of the processing quality set, to edit the style and behavior of the buttons. */
	UPROPERTY()
	int32 PostProcessQualityReference = 0;

	/** It will store a reference of the texture quality set, to edit the style and behavior of the buttons. */
	UPROPERTY()
	int32 TextureQualityReference = 0;
	
	/** It will store a reference of the AntiAliasing quality set, to edit the style and behavior of the buttons. */
	UPROPERTY()
	int32 AntiAliasingQualityReference = 0;
	
	/** It will store a reference of the shadows quality set, to edit the style and behavior of the buttons. */
	UPROPERTY()
	int32 ShadowsQualityReference = 0;
	
	/** It will store a reference of the win dow mode set, to edit the style and behavior of the buttons. */
	UPROPERTY()
	int32 WindowModeReference = 0;

	/** It will store a reference of the current language set, to edit the style and behavior of the buttons. */
	UPROPERTY()
	int32 CurrentLanguage = 0;
	
	/**
	  * It is used to know if we are or not in the main menu when the widget is created, so we know whether to return
	  * to the start menu or return to the pause menu when we leave it.
	  */
	bool bIsInMenu = true;
	
	/** It will be used to store a reference to the user settings when creating this widget. */
	UPROPERTY(Transient)
	TObjectPtr<UGameUserSettings> GameUserSettingsReference = { nullptr };

#pragma region Buttons
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonFullScreen = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonWindowedFullScreen = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonWindowed = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonPostProcessLow = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonPostProcessMedium = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonPostProcessHigh = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonPostProcessEpic = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonTextureLow = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonTextureMedium = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonTextureHigh = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonTextureEpic = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonAntiAliasingLow = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonAntiAliasingMedium = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonAntiAliasingHigh = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonAntiAliasingEpic = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonShadowsLow = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonShadowsMedium = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonShadowsHigh = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonShadowsEpic = { nullptr };

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonAutoDetect = { nullptr };

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonEnglish = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<ULabCustomButton> ButtonSpanish = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<USlider> SliderMusicVolume = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<USlider> SliderSfxVolume = { nullptr };
	
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UCommonNumericTextBlock> SliderMusicValueText = { nullptr };
	
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UCommonNumericTextBlock> SliderSfxValueText = { nullptr };
	
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<UComboBoxString> ComboBoxResolutions = { nullptr };

#pragma endregion Buttons
	
	UPROPERTY(Transient)
	TObjectPtr<ULabUWPauseGame> WidgetPauseMenu = { nullptr };

	/** Reference to the Global SoundMix created for the project. */
	UPROPERTY(EditAnywhere, Transient, Category="Settings Menu|Sound Types")
	TObjectPtr<USoundMix> SMixMasterSoundRef = { nullptr };

	/** Reference to the SoundClass used for game music. */
	UPROPERTY(EditAnywhere, Transient, Category="Settings Menu|Sound Types")
	TObjectPtr<USoundClass> SClassMusicRef = { nullptr };

	/** Reference to the SoundClass used for game sfx. */
	UPROPERTY(EditAnywhere, Transient, Category="Settings Menu|Sound Types")
	TObjectPtr<USoundClass> SClassSfxRef = { nullptr };
	
	/** To Store the reference to the save object where the configurations set by the player will be stored. */
	UPROPERTY(Transient)
	TObjectPtr<USGSettings> SaveGameObject = { nullptr };

	/** Custom ButtonStyle class reference, which will be used to change the style of the buttons when they are not selected. */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Settings Menu|Button Styles")
	TSubclassOf<UCommonButtonStyle> ButtonStyleUnselectedSetting = { nullptr };
	
	/** Custom ButtonStyle class reference, which will be used to change the style of the buttons when they are selected. */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Settings Menu|Button Styles")
	TSubclassOf<UCommonButtonStyle> ButtonStyleSelectedSetting = { nullptr };
	
	/** Pause Widget Class reference, to be used to create a new widget */
	UPROPERTY(EditDefaultsOnly, Transient, Category="Settings Menu|Widgets")
	TSubclassOf<UCommonActivatableWidget> WidgetPauseRef = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------ */

private:

	/** Widget Constructor. */
	virtual void NativeConstruct() override;

	/** If we are not in the main menu it is destroyed and generates a pause menu. */
	virtual void Back() override;
	
	/**
	 * @brief Function that establishes the quality of Post Processing.
	 * @param PostProcessValue Value between 0 - 3 that sets the quality of the PostProcess.
	 */
	UFUNCTION(BlueprintCallable, meta=(ToolTip ="PostProcessValue -> 0 = Low / 1 = Medium / 2 = High / 3 = Epic",DisplayName="Change PostProcess Quality"), Category="Settigns|Functions")
	void SetPostProcessQuality(int32 PostProcessValue);
	
	/**
	 * @brief Function that sets the AntiAliasing quality.
	 * @param AntiAliasingValue Value between 0 - 3 that sets the quality of the AntiAliasing.
	 */
	UFUNCTION(BlueprintCallable, meta=(ToolTip ="AntiAliasingValue -> 0 = Low / 1 = Medium / 2 = High / 3 = Epic",DisplayName="Change AntiAliasing Quality"), Category="Settigns|Functions")
	void SetAntiAliasingQuality(int32 AntiAliasingValue);

	/**
	 * @brief Function that sets the quality of the textures.
	 * @param TextureValue Value between 0 - 3 that sets the quality of the Textures.
	 */
	UFUNCTION(BlueprintCallable, meta=(ToolTip ="TextureValue -> 0 = Low / 1 = Medium / 2 = High / 3 = Epic",DisplayName="Change Texture Quality"), Category="Settigns|Functions")
	void SetTextureQuality(int32 TextureValue);
	
	/**
	 * @brief Function that sets the quality of the shadows.
	 * @param ShadowsValue Value between 0 - 3 that sets the quality of the Shadows.
	 */
	UFUNCTION(BlueprintCallable, meta=(ToolTip ="ShadowsValue -> 0 = Low / 1 = Medium / 2 = High / 3 = Epic",DisplayName="Change Shadows Quality"), Category="Settigns|Functions")
	void SetShadowsQuality(int32 ShadowsValue);
	
	/**
	 * @brief Function that sets the language of the game.
	 * @param LanguageValue Value between 0 - 1 that sets the game language.
	 */
	UFUNCTION(BlueprintCallable, meta=(ToolTip ="ShadowsValue -> 0 = English / 1 = Spanish",DisplayName="Change Game Language"), Category="Settigns|Functions")
	void SetGameLanguage(const int32 LanguageValue);
	
	/**
	 * @brief Function that sets the window mode of the application.
	 * @param WindowModeType Type EWindowMode, which will be set as window mode.
	 */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Set Screen Mode"), Category="Settigns|Functions")
	void SetWindowMode(EWindowMode::Type WindowModeType);
	
	/**
	  * This function performs a Benchmark to automatically set the graphic configuration, update it in the user
	  * options and save it.
	  */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="AutoDetect Best Settings"), Category="Settigns|Functions")
	void AutoDetectSettings();
	
	/**
		 * @brief Function that sets the screen resolution.
		 * @param Item This parameter corresponds to the desired resolution, it must be passed in the following format:
		 * {Width} x {Height}, e.g.: 1920 x 1080.
		 * @param Type [ Not Used ] This parameter initiates the type of selection, whether it was by click, gamepad button,
		 * etc...
		 */
	UFUNCTION()
	void SetScreenResolution(FString Item, ESelectInfo::Type Type);
	
	/** Function that creates a save object to store the settings set by the player and saves the settings in the GameUserSettings. */
	UFUNCTION()
	void SaveSettings();

	/** Function that updates the settings menu according to the settings set by the user. */
	UFUNCTION()
	void LoadSettings();

	/** Sets the volume of the music after the user finishes interacting with it. */
	UFUNCTION()
	void SetMusicVolume();

	/** Sets the volume of the sfx after the user finishes interacting with it. */
	UFUNCTION()
	void SetSfxVolume();

	/** This function updates the selected button for window mode and locks it to change its style and behavior. */
	UFUNCTION()
	void UpdateSelectedButtonForWindowMode() const;
	
	/** This function updates the selected button for PostProcess Quality and locks it to change its style and behavior. */
	UFUNCTION()
	void UpdateSelectedButtonForPostProcessQuality() const;

	/** This function updates the selected button for AntiAliasing Quality and locks it to change its style and behavior. */
	UFUNCTION()
	void UpdateSelectedButtonForAntiAliasingQuality() const;

	/** This function updates the selected button for Texture Quality and locks it to change its style and behavior. */
	UFUNCTION()
	void UpdateSelectedButtonForTextureQuality() const;

	/** This function updates the selected button for Shadows Quality and locks it to change its style and behavior. */
	UFUNCTION()
	void UpdateSelectedButtonForShadowsQuality() const;

	/** This function updates the selected button for Game Language and locks it to change its style and behavior. */
	UFUNCTION()
	void UpdateSelectedButtonForGameLanguage() const;
	
};