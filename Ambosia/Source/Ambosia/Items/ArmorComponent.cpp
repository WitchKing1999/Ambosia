// (C) Flumminard 2015

#include "Ambosia.h"
#include "ArmorComponent.h"

UArmorComponent::UArmorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	Name = FText::FromString("Armor");
	Description = FText::FromString("Saves you from receiving the complete damage!");
	ItemType = EItemType::VE_Armor;

	DefenceFactor = 1.0;
	MagicalDefenceFactor = 1.0;
}

float UArmorComponent::GetDefenceFactor()
{
	return this->DefenceFactor;
}

float UArmorComponent::ModifyAttackPoints_Implementation(float AttackPoints)
{
	if (AttackPoints < 0)
	{
		return AttackPoints * this->DefenceFactor;
	}
	else
		return AttackPoints;
}

float UArmorComponent::GetMagicalDefenceFactor()
{
	return this->MagicalDefenceFactor;
}

float UArmorComponent::ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints)
{
	if (MagicalAttackPoints < 0)
	{
		return MagicalAttackPoints / this->GetMagicalDefenceFactor();
	}
	else
		return MagicalAttackPoints;
}