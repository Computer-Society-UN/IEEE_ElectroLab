
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LabIInteractable.generated.h"

UINTERFACE()
class ULabIInteractable : public UInterface
{
	GENERATED_BODY()
};

class IEEE_ELECTROLAB_API ILabIInteractable
{
	GENERATED_BODY()

public:

	// Interaction that takes place when a button is pressed.
	virtual void StaticInteraction() = 0;

	// Interaction that takes place while a button is hold down.
	virtual void DynamicInteraction() = 0;

	// Interaction that is executed to highlight an element on the screen.
	virtual void VfxInteraction() = 0;

	// Interaction that is executed to stop highlighting an element on the screen.
	virtual void VfxDisinteraction() = 0;
	
};