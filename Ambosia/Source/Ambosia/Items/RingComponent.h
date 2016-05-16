// (C) Flumminard 2015-2016

#pragma once

#include "Items/ItemComponent.h"
#include "RingComponent.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API URingComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:

	URingComponent();

	/*
	Adds our health points limit to the given health points limit and returns it.
	*/
	virtual float ModifyInfightHealthPointsLimit_Implementation(float HealthPointsLimit) override;

	/*
	Adds our health points limit to the given health points limit and returns it.
	*/
	virtual float ModifyDisplayHealthPointsLimit_Implementation(float HealthPointsLimit) override;

	/*
	Adds our mana limit to the given mana limit and returns it.
	*/
	virtual float ModifyInfightManaLimit_Implementation(float ManaLimit) override;

	/*
	Adds our mana limit to the given mana limit and returns it.
	*/
	virtual float ModifyDisplayManaLimit_Implementation(float ManaLimit) override;

	/*
	Adds our attack points limit to the given attack points and returns it.
	*/
	virtual float ModifyInfightAttackPoints_Implementation(float AttackPoints) override;

	/*
	Adds our attack points limit to the given attack points and returns it.
	*/
	virtual float ModifyDisplayAttackPoints_Implementation(float AttackPoints) override;

	/*
	Adds our magical attack points to the given magical attack points and returns it.
	*/
	virtual float ModifyInfightMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;

	/*
	Adds our magical attack points to the given magical attack points and returns it.
	*/
	virtual float ModifyDisplayMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;

	/*
	Adds our mana regeneration to the given mana regeneration and returns it.
	*/
	virtual float ModifyInfightManaRegeneration_Implementation(float ManaRegeneration) override;

	/*
	Adds our mana regeneration to the given mana regeneration and returns it.
	*/
	virtual float ModifyDisplayManaRegeneration_Implementation(float ManaRegeneration) override;

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring")
	float HealthPointsLimit;

	/*
	Our mana limit
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring")
	float ManaLimit;

	/*
	Our attack points
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring")
	float AttackPoints;

	/*
	Our magical attack points
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring")
	float MagicalAttackPoints;

	/*
	Our mana regeneration
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring")
	float ManaRegenerationPerSec;

};
