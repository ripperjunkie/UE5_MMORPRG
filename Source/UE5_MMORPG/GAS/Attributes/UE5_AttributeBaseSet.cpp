// @Big Moxi Engineers.

#include "UE5_AttributeBaseSet.h"
#include "Net/UnrealNetwork.h"

void UUE5_AttributeBaseSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UUE5_AttributeBaseSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUE5_AttributeBaseSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UUE5_AttributeBaseSet::Rep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE5_AttributeBaseSet, Health, OldHealth);
}

void UUE5_AttributeBaseSet::Rep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUE5_AttributeBaseSet, MaxHealth, OldMaxHealth);
}