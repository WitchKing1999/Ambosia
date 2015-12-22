// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "WeaponComponent.generated.h"

/*
 This Item hurts everything!
*/
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API UWeaponComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	UWeaponComponent();

	virtual bool Action_Implementation() override;

	float GetAttackFactor();

	virtual float ModifyAttackPoints_Implementation(float AttackPoints) override;

	float GetManaCost();

	float GetMagicalAttackFactor();

	virtual float ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float AttackFactor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float ManaCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float MagicalAttackFactor;
};
