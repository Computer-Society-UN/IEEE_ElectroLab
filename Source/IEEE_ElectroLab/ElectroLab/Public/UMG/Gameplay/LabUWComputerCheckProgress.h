
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "LabUWComputerCheckProgress.generated.h"

// Forward Declarations
class UCommonTextBlock;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWComputerCheckProgress : public UCommonUserWidget
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

	UPROPERTY(EditDefaultsOnly, Transient, BlueprintReadWrite, meta=(BindWidget, DisplayName="Progres Status Text", AllowPrivateAccess=true), Category = "Widget|Properties")
	TObjectPtr<UCommonTextBlock> SystemCheckProgressText = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta=(DisplayName="Check Progress"), Category="Widget|Events")
	void SystemCheckProgress(const float ValidationProgress);

private:
	
	/** Widget Constructor */
	virtual void NativeConstruct() override;
	
};