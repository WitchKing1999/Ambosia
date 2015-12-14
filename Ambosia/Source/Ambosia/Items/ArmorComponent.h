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
	
	virtual float ModifyAttackPoints_Implementation(float AttackPoints) override;

	float GetMagicalDefenceFactor();

	virtual float ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float DefenceFactor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float MagicalDefenceFactor;
};
