// @Big Moxi Engineers.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

class UCustomInputComponent;
/**
 * 
 */
UCLASS()
class UE5_MMORPG_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	
};
