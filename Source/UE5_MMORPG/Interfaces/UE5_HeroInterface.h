// @Big Moxi Engineers.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UE5_HeroInterface.generated.h"

class UInputMappingContext;

// This class does not need to be modified.
UINTERFACE()
class UUE5_HeroInterface : public UInterface
{
	GENERATED_BODY()
};


class UE5_MMORPG_API IUE5_HeroInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SwitchMappingContext(TSoftObjectPtr<UInputMappingContext> InputMappingContext) = 0;
};
