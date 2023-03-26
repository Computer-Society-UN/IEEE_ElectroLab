
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "LabUWComputerCheckStatus.generated.h"

// Forward Declarations
class UCommonTextBlock;
class UCommonTextStyle;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWComputerCheckStatus : public UCommonUserWidget
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

	UPROPERTY(EditDefaultsOnly, Transient, BlueprintReadWrite, meta=(BindWidget, DisplayName="Check Status Text", AllowPrivateAccess=true), Category = "Widget|Properties")
	TObjectPtr<UCommonTextBlock> SystemCheckStatus = { nullptr };

	UPROPERTY(EditDefaultsOnly, Transient, BlueprintReadOnly, meta=(BindWidget, DisplayName="Restore Text", AllowPrivateAccess=true), Category = "Widget|Properties")
	TObjectPtr<UCommonTextBlock> RestoreText = { nullptr };

	/** Custom ButtonStyle class reference, which will be used to change the style of the buttons when they are not selected. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, meta=(AllowPrivateAccess=true), Category="Settings Menu|Text Styles")
	TSubclassOf<UCommonTextStyle> TextStyleStatusOk = { nullptr };
	
	/** Custom ButtonStyle class reference, which will be used to change the style of the buttons when they are not selected. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, meta=(AllowPrivateAccess=true), Category="Settings Menu|Text Styles")
	TSubclassOf<UCommonTextStyle> TextStyleStatusFail = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta=(DisplayName="Check Result"), Category="Widget|Events")
	void SystemCheckResult(const bool bCheckResult);

private:
	
	/** Widget Constructor */
	virtual void NativeConstruct() override;
	
};