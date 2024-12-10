// @Big Moxi Engineers.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "UE5_AttributeBaseSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

UCLASS()
class UE5_MMORPG_API UUE5_AttributeBaseSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category=Attributes, ReplicatedUsing=Rep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UUE5_AttributeBaseSet, Health);

	UPROPERTY(BlueprintReadOnly, Category=Attributes, ReplicatedUsing=Rep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UUE5_AttributeBaseSet, MaxHealth);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void Rep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void Rep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
};
