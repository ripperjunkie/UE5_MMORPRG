// @Big Moxi Engineers.
// Author(s): Rafael Zagolin. Created on 09 December, 2024.
// Contributor(s):

#include "UE5_BaseHero.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"

#include "AbilitySystemComponent.h"
#include "UE5_MMORPG/Components/CustomInputComponent.h"
#include "UE5_MMORPG/GAS/CustomAbilitySystemComponent.h"
#include "UE5_MMORPG/GAS/Attributes/UE5_AttributeBaseSet.h"



#define ADD_COMPONENT(Property, Comp, Name) Property = CreateDefaultSubobject<Comp>(TEXT(Name));

// Helper to simplify input bindings.
#define BIND_ACTION(ACTION, EVENT, FUNCTION) Input->BindAction(ACTION, EVENT, this, &ThisClass::FUNCTION)

// Sets default values
AUE5_BaseHero::AUE5_BaseHero()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ADD_COMPONENT(CameraComp, UCameraComponent, "Camera Component");
	ADD_COMPONENT(SpringComp, USpringArmComponent, "Spring Arm Component");
	ADD_COMPONENT(AbilitySystemComponent, UCustomAbilitySystemComponent, "Ability System Component");
	ADD_COMPONENT(AttributeBaseSet, UUE5_AttributeBaseSet, "Attribute Set");
	ADD_COMPONENT(CustomInputComponent, UCustomInputComponent, "Input Component");
	
	if(SpringComp)
	{
		SpringComp->SetupAttachment(GetRootComponent());
	}

	if(SpringComp)
	{
		CameraComp->SetupAttachment(SpringComp);
	}

	MouseSensitivity = FVector2D(45.F,60.f);

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

// Called when the game starts or when spawned
void AUE5_BaseHero::BeginPlay()
{
	Super::BeginPlay();

	this->SwitchMappingContext(HeroMappingContext);

	// GAS
	if(IsValid(AbilitySystemComponent))
	{
		AttributeBaseSet = AbilitySystemComponent->GetSet<UUE5_AttributeBaseSet>();
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	CustomInputComponent->SetupComponent();
}

// Called every frame
void AUE5_BaseHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUE5_BaseHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	check(PlayerInputComponent);
	// if (UEnhancedInputComponent *Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	// {
	// 	// Hero Input Actions
	// 	BIND_ACTION(Movement_IA, ETriggerEvent::Triggered, Input_Movement);
	// 	BIND_ACTION(Shoot_IA, ETriggerEvent::Triggered, Input_Shoot);
	// 	BIND_ACTION(Jump_IA, ETriggerEvent::Triggered, Input_Jump);
	// 	BIND_ACTION(Evade_IA, ETriggerEvent::Triggered, Input_Evade);
	// 	BIND_ACTION(Aim_IA, ETriggerEvent::Triggered, Input_Aim);
	// 	BIND_ACTION(MouseCameraControl_IA, ETriggerEvent::Triggered, Input_CameraControlMouse);
	// }
}

void AUE5_BaseHero::SwitchMappingContext(TSoftObjectPtr<UInputMappingContext> InputMappingContext)
{
	// Adding map context
	if (APlayerController *PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem *InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (!InputMappingContext.IsNull())
			{
				InputSystem->ClearAllMappings();
				InputSystem->AddMappingContext(InputMappingContext.LoadSynchronous(), 0);
			}
		}
	}
}

UAbilitySystemComponent* AUE5_BaseHero::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AUE5_BaseHero::Input_Shoot(const FInputActionInstance& Instance)
{
	// TODO: Implement as an ability (GAS).
}

void AUE5_BaseHero::Input_Jump(const FInputActionInstance& Instance)
{
	// TODO: Implement as an ability (GAS).
}

void AUE5_BaseHero::Input_Evade(const FInputActionInstance& Instance)
{
	// TODO: Implement as an ability (GAS).
}

void AUE5_BaseHero::Input_Aim(const FInputActionInstance& Instance)
{
	// TODO: Implement as an ability (GAS).
}

