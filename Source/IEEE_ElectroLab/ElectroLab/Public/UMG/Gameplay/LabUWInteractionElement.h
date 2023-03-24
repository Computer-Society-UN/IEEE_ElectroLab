
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "LabUWInteractionElement.generated.h"

// Forward Declarations
class UCommonTextBlock;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWInteractionElement : public UCommonUserWidget
{
	GENERATED_BODY()
	/* ------------------------------ CLASS PROPERTIES ------------------------------ */

private:

	UPROPERTY(EditDefaultsOnly, Transient, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> InteractionText = { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Transient, BlueprintReadWrite, meta=(DisplayName="Component Name",AllowPrivateAccess = "true", BindWidget), Category = "Widget|Properties")
	TObjectPtr<UCommonTextBlock> ComponentName = { nullptr };
	
	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta=(DisplayName="Set Component Name"), Category="Interaction Element|Events")
	void SetComponentName(const FText& NewComponentName);
	
private:
	
	/** Widget Constructor */
	virtual void NativeConstruct() override;
	
};