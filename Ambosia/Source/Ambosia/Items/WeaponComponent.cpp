// (C) Flumminard 2015

#include "Ambosia.h"
#include "WeaponComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Name = "Weapon";
	Description = "Hurts everything!";
	AttackFactor = 1.0;
	ManaCost = 0;
	MagicalAttackFactor = 1.0;
}

bool UWeaponComponent::Action_Implementation()
{
	if (!Super::Action_Implementation())
		return false;
	if (this->GetTimeTillCooled())
	{
		this->StartCooldown();
		return true;
	}
	else
	{
		return false;
	}
}

float UWeaponComponent::GetAttackFactor()
{
	return this->AttackFactor;
}

float UWeaponComponent::ModifyAttackPoints(float AttackPoints)
{
	return AttackPoints * this->AttackFactor;
}

float UWeaponComponent::GetManaCost()
{
	return this->ManaCost;
}

float UWeaponComponent::GetMagicalAttackFactor()
{
	return this->MagicalAttackFactor;
}

float UWeaponComponent::ModifyMagicalAttackPoints(float MagicalAttackPoints)
{
	return MagicalAttackPoints * this->MagicalAttackFactor;
}