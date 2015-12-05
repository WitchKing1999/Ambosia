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

void UWeaponComponent::Attack()
{
	this->StartCooldown();
}

float UWeaponComponent::GetAttackFactor()
{
	return this->AttackFactor;
}

float UWeaponComponent::AffectAttackPoints(float RawAttackPoints)
{
	return RawAttackPoints * this->AttackFactor;
}

float UWeaponComponent::GetManaCost()
{
	return this->ManaCost;
}

float UWeaponComponent::GetMagicalAttackFactor()
{
	return this->MagicalAttackFactor;
}

float UWeaponComponent::AffectMagicalAttackPoints(float RawMagicalAttackPoints)
{
	return RawMagicalAttackPoints * this->MagicalAttackFactor;
}