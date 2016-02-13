// (C) Flumminard 2015-2016

#pragma once

#include "Items/ItemComponent.h"
#include "AmuletComponent.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API UAmuletComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:

	UAmuletComponent();

	/*
	Adds our health points limit to the given health points limit and returns it.
	*/
	virtual float ModifyHealthPointsLimit_Implementation(float HealthPointsLimit) override;

	/*
	Adds our mana limit to the given mana limit and returns it.
	*/
	virtual float ModifyManaLimit_Implementation(float ManaLimit) override;

	/*
	Adds our attack points limit to the given attack points and returns it.
	*/
	virtual float ModifyAttackPoints_Implementation(float AttackPoints) override;

	/*
	Adds our magical attack points to the given magical attack points and returns it.
	*/
	virtual float ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;

	/*
	Adds our mana regeneration to the given mana regeneration and returns it.
	*/
	virtual float ModifyManaRegeneration_Implementation(float ManaRegeneration) override;

	/*
	Returns our health points limit
	*/
	float GetHealthPointsLimit();

	/*
	Returns our mana limit
	*/
	float GetManaLimit();

	/*
	Returns our attack points
	*/
	float GetAttackPoints();

	/*
	Returns our magical attack points
	*/
	float GetMagicalAttackPoints();

	/*
	Returns our mana regeneration
	*/
	float GetManaRegeneration();

protected:

	/*
	Our health points limit
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Amulet")
		float HealthPointsLimit;

	/*
	Our mana limit
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Amulet")
		float ManaLimit;

	/*
	Our attack points
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Amulet")
		float AttackPoints;

	/*
	Our magical attack points
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Amulet")
		float MagicalAttackPoints;

	/*
	Our mana regeneration
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Amulet")
		float ManaRegenerationPerSec;
	
	
};
