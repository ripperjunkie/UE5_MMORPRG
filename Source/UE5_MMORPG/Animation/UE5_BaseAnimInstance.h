// @Big Moxi Engineers.
// Author(s): Rafael Zagolin. Created on 11 December, 2024.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UE5_BaseAnimInstance.generated.h"



UCLASS()
class UE5_MMORPG_API UUE5_BaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly)
	float VerticalSpeed;

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsInAir : 1;
};
