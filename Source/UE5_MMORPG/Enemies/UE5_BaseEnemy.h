// @Big Moxi Engineers.
// Author(s): Rafael Zagolin. Created on 11 December, 2024.
// Contributor(s):

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "UE5_BaseEnemy.generated.h"

class UUE5_AttributeBaseSet;
class UAbilitySystemComponent;

UCLASS()
class UE5_MMORPG_API AUE5_BaseEnemy : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AUE5_BaseEnemy();
	virtual void Tick(float DeltaTime) override;
	
#pragma region IAbilitySystemInterface Methods
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
#pragma endregion 


#pragma region GAS
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS")
	const UUE5_AttributeBaseSet* AttributeBaseSet;
	
#pragma endregion GAS
	
	
protected:
	virtual void BeginPlay() override;
};
