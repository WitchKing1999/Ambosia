// (C) Flumminard 2015

#pragma once

#include "Components/ActorComponent.h"
#include "GameplayValuesComponent.generated.h"

// This component holds all gameplay values of a NPC or the Player.
// You just need to add this to your controller and it will be used!
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMBOSIA_API UGameplayValuesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameplayValuesComponent();

	// Returns our health points.
	float GetHealthPoints();

	// Sets our health points.
	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	void SetHealthPoints(float HealthPoints);

	// Divides 'Delta' by our effective defence factor and adds it to our health points.
	// If the new health points are greater than the effective health points limit,
	// the health points will be set to the limit. If lower or equal zero, the owner will be destroyed.
	UFUNCTION(BlueprintCallable, Category = "GameplayValues")
	void AffectHealthPoints(float Delta);

	// Returns our health points limit. This does not include the hp limit of our inventory.
	float GetHealthPointsLimit();

	// Returns our health points limit increased by the hp limit of our inventory.
	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	float GetEffectiveHealthPointsLimit();

	// Sets our health points limit. This does not affect our inventory.
	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	void SetHealthPointsLimit(float HealthPointsLimit);

	// Returns our attack points. This does not include the ap of our inventory.
	float GetAttackPoints();

	// Returns our attack points increased by the ap of our inventory.
	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	float GetEffectiveAttackPoints();

	// Sets our attack points. This does not affect our inventory.
	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	void SetAttackPoints(float AttackPoints);

	// Returns our defence factor. This does not include the df of our inventory.
	float GetDefenceFactor();

	// Returns our defence factor increased by the df of our inventory.
	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	float GetEffectiveDefenceFactor();

	// Sets our defence factor. This does not affect our inventory.
	UFUNCTION(BlueprintCallable, Category = "Variables|GameplayValues")
	void SetDefenceFactor(float DefenceFactor);

public:

	// If true, we will print some debug information on the screen.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	bool bPrintDebugStrings;

protected:

	// Our health points limit. If zero, we will die!
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameplayValues")
	float HealthPoints;

	// Our health points limit. Our health points can't be greater than this limit.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameplayValues")
	float HealthPointsLimit;

	// Our attack points. This will be used as delta when affecting one others health points.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameplayValues")
	float AttackPoints;

	// Our defence factor. When someone affects our health points, the delta will be divided by this.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameplayValues")
	float DefenceFactor;
	
};
