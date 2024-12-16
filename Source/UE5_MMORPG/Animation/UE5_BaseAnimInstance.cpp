// @Big Moxi Engineers.
// Author(s): Rafael Zagolin. Created on 11 December, 2024.

#include "UE5_BaseAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

void UUE5_BaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Update stuff here
	const APawn* pawn = TryGetPawnOwner();
	
	if(pawn)
	{
		VerticalSpeed = pawn->GetVelocity().Z;
		GroundSpeed = FVector(pawn->GetVelocity().X, pawn->GetVelocity().Y, 0.F).Length();
		
		const UCharacterMovementComponent* cmc = Cast<UCharacterMovementComponent>(pawn->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
		if(cmc)
		{
			bIsInAir = cmc->IsFalling();
		}
		
	}	
}
