
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "LabUWPopUp.h"
#include "LabUWLaboratoryNotify.generated.h"

// Forward declarations
class ULabCustomButton;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabUWLaboratoryNotify : public ULabUWPopUp
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */
	
private:
	
	/** UCommonButtonBase->OnButtonBaseClicked must be called from Blueprints. <BlueprintReadOnly Needed to reference in GetDesiredFocusTarget() BP Override> */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidget, DisplayName="Button Secondary Action", AllowPrivateAccess=true), Category="Laboratory Notify|Buttons")
	TObjectPtr<ULabCustomButton> ButtonSecondaryAction = { nullptr };
	
};