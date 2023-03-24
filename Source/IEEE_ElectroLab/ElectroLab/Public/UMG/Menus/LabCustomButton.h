
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "LabCustomButton.generated.h"

// Forward declarations
class UCommonTextBlock;

UCLASS(HideCategories = (Rendering, Replication, Input, Actor, Collision, LOD, Cooking, HLOD))
class IEEE_ELECTROLAB_API ULabCustomButton : public UCommonButtonBase
{
	GENERATED_BODY()

	/* ------------------------------ CLASS PROPERTIES ------------------------------ */
	
private:
	
	/** Text that will be editable in the instances of this button to customize it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess=true), Category="Custom Button Text")
	FText ButtonText = FText::FromString("Default");
	
	/** Required text to be displayed on the button. */
	UPROPERTY(BlueprintReadWrite, Transient, meta=(BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonTextBlock> DisplayButtonText = { nullptr };

	/* ------------------------------ CLASS FUNCTIONS ------------------------------- */
	
private:
	
	/**
	  * -> It is recommended to use the Pre-Construct in the blueprint of the button that is
	  * created from this class to preview correctly the changes in the EDITOR, it is not necessary to do it in
	  * the constructor of the blueprint since the implementation of the constructor of this class already
	  * takes care of it.
	  */
	virtual void NativeConstruct() override;
	
};