// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "WeaponComponent.generated.h"

/*
Base class for weapons.
*/
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API UWeaponComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	UWeaponComponent();

	/*
	Override from ItemComponent.
	Returns true if the time till cooled is equal/smaller than zero
	and if the player has enough mana to use us.
	*/
	virtual bool Action_Implementation() override;

	/*
	Multiplies the attack points by our attack factor and returns them.
	If we have a critical hit, it also multiplies the attack points by 2.
	*/
	virtual float ModifyAttackPoints_Implementation(float AttackPoints) override;

	/*
	Multiplies the magical attack points by our magical attack factor.
	*/
	virtual float ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints) override;

	/*
	Returns our mana costs
	*/
	float GetManaCost();

	/*
	Returns or attack factor.
	*/
	float GetAttackFactor();

	/*
	Returns our magical attack factor
	*/
	float GetMagicalAttackFactor();

	/*
	Returns our chance for a critical hit.
	*/
	float GetCriticalDamageChance();
	
protected:

	/*
	Our attack factor
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float AttackFactor;

	/*
	Our mana costs
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float ManaCost;

	/*
	Our magical attack factor
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float MagicalAttackFactor;

	/*
	Our chance for a critical hit.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float CriticalDamageChance;
};
