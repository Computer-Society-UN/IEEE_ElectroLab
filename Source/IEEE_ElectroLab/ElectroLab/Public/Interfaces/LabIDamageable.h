
// Copyright (c) 2023 Computer Society UN - https://github.com/orgs/Computer-Society-UN

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LabIDamageable.generated.h"

UINTERFACE()
class ULabIDamageable : public UInterface
{
	GENERATED_BODY()
};

class IEEE_ELECTROLAB_API ILabIDamageable
{
	GENERATED_BODY()

public:

	virtual void TakeDamage() = 0;
	
};