// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "ArmorComponent.generated.h"

/*
This item saves the player or NPC from receiving the complete damage
by multpiling it with a certain factor.
*/
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API UArmorComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	UArmorComponent();

	float GetDefenceFactor();
	
	/*
	Multiplies the attack points with the defence factor and returns them.
	*/
	virtual float ModifyInfightAttackPoints_Implementation(float AttackPoints) override;

	/*
	Multiplies the attack points with the defence factor and returns them.
	*/
	virtual float ModifyDisplayAttackPoints_Implementation(float AttackPoints) override;

	float GetMagicalDefenceFactor();

	/*
	Multiplies the magical attack points with the magical defence factor and returns them.
	*/
	virtual float ModifyInfightMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;

	/*
	Multiplies the magical attack points with the magical defence factor and returns them.
	*/
	virtual float ModifyDisplayMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	float DefenceFactor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	float MagicalDefenceFactor;
};
