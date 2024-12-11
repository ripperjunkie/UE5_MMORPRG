// @Big Moxi Engineers.


#include "CustomPlayerController.h"

#include "AbilitySystemComponent.h"
#include "UE5_MMORPG/Components/CustomInputComponent.h"
#include "UE5_MMORPG/Heroes/UE5_BaseHero.h"

void ACustomPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if(TObjectPtr<AUE5_BaseHero> Hero = GetPawn<AUE5_BaseHero>())
	{
		if( TObjectPtr<UCustomInputComponent> CustomInputComponent =  Hero->GetInputComponent<UCustomInputComponent>())
		{
			CustomInputComponent ->ProcessAbilityInput(DeltaTime, bGamePaused);
		}
	}
	
	Super::PostProcessInput(DeltaTime, bGamePaused);
}