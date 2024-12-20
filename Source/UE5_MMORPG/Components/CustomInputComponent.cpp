// @Big Moxi Engineers.


#include "CustomInputComponent.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UE5_MMORPG/GAS/CustomGameplayAbility.h"
#include "UE5_MMORPG/GAS/DataAssets/AbilitySet.h"
#include "UE5_MMORPG/Heroes/UE5_BaseHero.h"
#include "UE5_MMORPG/Heroes/DataAssets/CustomPawnData.h"
#include "UserSettings/EnhancedInputUserSettings.h"

class UInputConfig;



// Sets default values for this component's properties
UCustomInputComponent::UCustomInputComponent(const FObjectInitializer& ObjectInitializer)
{
	bWantsInitializeComponent=true;
}

void UCustomInputComponent::AddInputMappings(const UInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to add something from your input config if required
}

void UCustomInputComponent::RemoveInputMappings(const UInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to remove input mappings that you may have added above
}

void UCustomInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}



void  UCustomInputComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
		{
			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void  UCustomInputComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec :AbilitySystemComponent->GetActivatableAbilities())
		{
			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}


void UCustomInputComponent::SetupComponent()
{
	TObjectPtr<AUE5_BaseHero> Owner = Cast<AUE5_BaseHero>(GetOwner());
	check(Owner);
	Owner->InputComponent = this;

	
	const APlayerController* PC = Owner->GetController<APlayerController>();
	check(PC);
	
	AbilitySystemComponent = Owner->GetAbilitySystemComponent();
	check(AbilitySystemComponent);

	
	const ULocalPlayer* LP = PC ->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	
	if (Owner)
	{
		if(TObjectPtr<UCustomPawnData> PawnData = Owner->GetPawnData<UCustomPawnData>())
		{
			if(TObjectPtr<UInputConfig> InputConfig = PawnData->InputConfig)
			{
				UEnhancedInputUserSettings* Settings = Subsystem->GetUserSettings();
				FModifyContextOptions Options = {};
				Options.bIgnoreAllPressedKeysUntilRelease = false;
				for (UInputMappingContext* IMC : InputConfig->DefaultInputMappings)
				{
					if (Settings)
					{
						Settings->RegisterInputMappingContext(IMC);
					}

					Subsystem->AddMappingContext(IMC, 1, Options);
				}
				// Add the key mappings that may have been set by the player
				AddInputMappings(InputConfig, Subsystem);

				
				// This is where we actually bind and input action to a gameplay tag, which means that Gameplay Ability Blueprints will
				// be triggered directly by these input actions Triggered events. 
				TArray<uint32> BindHandles;

				BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

				BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag("InputTag.Movement.Move"), ETriggerEvent::Triggered, this, &ThisClass::Input_Movement, /*bLogIfNotFound=*/ false);
				BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag("InputTag.Mouse.CameraMovement"), ETriggerEvent::Triggered, this, &ThisClass::Input_CameraControlMouse, /*bLogIfNotFound=*/ false);
				
				
			}


			// We grant the default abilities here
			TArray<TObjectPtr<UAbilitySet>> AbilitiesToGrant = PawnData->AbilitySets;
			for (TObjectPtr<UAbilitySet> AbilitySet : AbilitiesToGrant)
				{
					AbilitySet->GiveToAbilitySystem(AbilitySystemComponent);
				}
			
		}
	}
}

void UCustomInputComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();
	
	//
	// Process all abilities that activate when the input is held.
	//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability && !AbilitySpec->IsActive())
			{
				const UCustomGameplayAbility* AbilityCDO = CastChecked<UCustomGameplayAbility>(AbilitySpec->Ability);
				if(AbilityCDO->GetActivationPolicy() == EAbilityActivationPolicy::WhileInputActive)
				{
					AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
				
			}
		}
	}

	//
	// Process all abilities that had their input pressed this frame.
	//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;

				if (AbilitySpec->IsActive())
				{
					// Ability is active so pass along the input event.
					AbilitySystemComponent->AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					const UCustomGameplayAbility* AbilityCDO = CastChecked<UCustomGameplayAbility>(AbilitySpec->Ability);

					if (AbilityCDO->GetActivationPolicy() == EAbilityActivationPolicy::OnInputTriggered)
					{
						AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					}
				}
			}
		}
	}

	//
	// Try to activate all the abilities that are from presses and holds.
	// We do it all at once so that held inputs don't activate the ability
	// and then also send a input event to the ability because of the press.
	//
	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		AbilitySystemComponent->TryActivateAbility(AbilitySpecHandle);
	}

	//
	// Process all abilities that had their input released this frame.
	//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;

				if (AbilitySpec->IsActive())
				{
					// Ability is active so pass along the input event.
					AbilitySystemComponent->AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}

	//
	// Clear the cached ability handles.
	//
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UCustomInputComponent::Input_Movement(const FInputActionInstance& Instance)
{
	if (APawn* Owner = GetOwner<APawn>())
	{
		if(AController* Controller =  Owner->GetController())
		{
			
			FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();
			const FRotator Rotation = FRotator(0.F, Controller->GetControlRotation().Yaw, 0.F);
			const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Type::X);
			Owner->AddMovementInput(ForwardDirection, AxisValue.X);

			const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Type::Y);
			Owner->AddMovementInput(RightDirection, AxisValue.Y);
		}

	}

}

void UCustomInputComponent::Input_CameraControlMouse(const FInputActionInstance& Instance)
{
	if (APawn* Owner = GetOwner<APawn>())
	{
			FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();

			Owner->AddControllerPitchInput(AxisValue.Y);
			Owner->AddControllerYawInput(AxisValue.X);
		
	}
}

