// @Big Moxi Engineers.
// Author(s): Rafael Zagolin. Created on 11 December, 2024.
// Contributor(s):


#include "UE5_BaseEnemy.h"


// Sets default values
AUE5_BaseEnemy::AUE5_BaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUE5_BaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUE5_BaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* AUE5_BaseEnemy::GetAbilitySystemComponent() const
{
	// TODO:
	return nullptr;
}


