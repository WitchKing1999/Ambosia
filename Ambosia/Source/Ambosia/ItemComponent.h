// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.generated.h"

// This is the item base class.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UItemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

	// Gets the health points limit.
	float GetHealthPointsLimit();

	// Gets the attack points.
	float GetAttackPoints();

	// Gets the defence factor.
	float GetDefenceFactor();

protected:

	// The health points limit
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HealthPointsLimit;

	// The attack points
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackPoints;

	// The defence factor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefenceFactor;
	
};
