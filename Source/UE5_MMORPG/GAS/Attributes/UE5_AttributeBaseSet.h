// @Big Moxi Engineers.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "UE5_AttributeBaseSet.generated.h"

UCLASS()
class UE5_MMORPG_API UUE5_AttributeBaseSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category=Attributes)
	FGameplayAttributeData Health;

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UUE5_AttributeBaseSet, Health);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health)
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health)
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health)
};
