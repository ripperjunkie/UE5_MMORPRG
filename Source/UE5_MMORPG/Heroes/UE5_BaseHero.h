// @Big Moxi Engineers.
// Author(s): Rafael Zagolin. Created on 09 December, 2024.
// Contributor(s):


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UE5_MMORPG/Interfaces/UE5_HeroInterface.h"

#include "UE5_BaseHero.generated.h"

class UUE5_AttributeBaseSet;
class UAbilitySystemComponent;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionInstance;

UCLASS()
class UE5_MMORPG_API AUE5_BaseHero : public ACharacter, public IUE5_HeroInterface, public IAbilitySystemInterface
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUE5_BaseHero();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region IUE5_HeroInterface Methods
	
	virtual void SwitchMappingContext(TSoftObjectPtr<UInputMappingContext> InputMappingContext) override;
	
#pragma endregion 

#pragma region IAbilitySystemInterface Methods
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
#pragma endregion 

	// Input Actions
	void Input_Movement(const FInputActionInstance &Instance);
	void Input_CameraControlMouse(const FInputActionInstance& Instance);
	void Input_Shoot(const FInputActionInstance& Instance);
	void Input_Jump(const FInputActionInstance& Instance);
	void Input_Evade(const FInputActionInstance& Instance);
	void Input_Aim(const FInputActionInstance& Instance);

	/************************** CHARACTER CONTROLS ******************************/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Action|Hero")
	UInputAction* Movement_IA;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Action|Hero")
	UInputAction* Jump_IA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Action|Hero")
	UInputAction* Shoot_IA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Action|Hero")
	UInputAction* Aim_IA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Action|Hero")
	UInputAction* Evade_IA;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input Action|Hero")
	UInputAction* MouseCameraControl_IA;

	/************************** ******************************/

	/********************** Input Mapping Context  ******************************/	
	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> HeroMappingContext;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	TObjectPtr<UCameraComponent> CameraComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	TObjectPtr<USpringArmComponent> SpringComp;

	/************************** ******************************/


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	FVector2D MouseSensitivity;

#pragma region GAS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS")
	const UUE5_AttributeBaseSet* AttributeBaseSet;
#pragma endregion GAS

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	
};
