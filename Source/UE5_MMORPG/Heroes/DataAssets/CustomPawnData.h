// @Big Moxi Engineers.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CustomPawnData.generated.h"

class UInputConfig;
class UAbilitySet;
/**
 * UCustomPawnData
 *
 *	Non-mutable data asset that contains properties used to define a pawn.
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "Custom Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class UE5_MMORPG_API UCustomPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UCustomPawnData(const FObjectInitializer& ObjectInitializer);
	
	// Class to instantiate for this pawn (should usually derive from ALyraPawn or ALyraCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Pawn")
	TSubclassOf<APawn> PawnClass;

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Abilities")
	TArray<TObjectPtr<UAbilitySet>> AbilitySets;

	// What mapping of ability tags to use for actions taking by this pawn (Not Implemented yet)
	

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Input")
	TObjectPtr<UInputConfig> InputConfig;

	// Default camera mode used by player controlled pawns. (Not Implemented yet)

};

