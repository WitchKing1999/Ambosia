// (C) Flumminard 2015

#include "Ambosia.h"
#include "GameplayValuesComponent.h"
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
	if (this->GetTimeTillCooled() > 0)
		return false;
	this->StartCooldown();

	UGameplayValuesComponent* GameplayValues = nullptr;
	for (UActorComponent* Component : this->GetOwner()->GetComponents())
	{
		UGameplayValuesComponent* ComponentAsGameplayValues = dynamic_cast<UGameplayValuesComponent*>(Component);
		if (ComponentAsGameplayValues != nullptr)
			GameplayValues = ComponentAsGameplayValues;
	}
	if (GameplayValues == nullptr)
		return false;
	if (GameplayValues->GetMana() < this->GetManaCost())
		return false;
	GameplayValues->AffectMana(this->GetManaCost() * -1);

	return true;
}

float UWeaponComponent::GetAttackFactor()
{
	return this->AttackFactor;
}

float UWeaponComponent::ModifyAttackPoints_Implementation(float AttackPoints)
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

float UWeaponComponent::ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints)
{
	return MagicalAttackPoints * this->MagicalAttackFactor;
}