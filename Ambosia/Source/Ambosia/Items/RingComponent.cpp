// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "RingComponent.h"

URingComponent::URingComponent()
{
	ItemType = EItemType::VE_Ring;
	HealthPointsLimit = 0;
	ManaLimit = 0;
	AttackPoints = 0;
	MagicalAttackPoints = 0;
	ManaRegenerationPerSec = 0;
}

float URingComponent::ModifyHealthPointsLimit_Implementation(float HealthPointsLimit)
{
	return HealthPointsLimit + this->GetHealthPointsLimit();
}

float URingComponent::ModifyManaLimit_Implementation(float ManaLimit)
{
	return ManaLimit + this->GetManaLimit();
}

float URingComponent::ModifyAttackPoints_Implementation(float AttackPoints)
{
	return AttackPoints + this->GetAttackPoints();
}

float URingComponent::ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints)
{
	return MagicalAttackPoints + this->GetMagicalAttackPoints();
}

float URingComponent::ModifyManaRegeneration_Implementation(float ManaRegeneration)
{
	return ManaRegeneration + this->GetManaRegeneration();
}

float URingComponent::GetHealthPointsLimit()
{
	return this->HealthPointsLimit;
}

float URingComponent::GetManaLimit()
{
	return this->ManaLimit;
}

float URingComponent::GetAttackPoints()
{
	return this->AttackPoints;
}

float URingComponent::GetMagicalAttackPoints()
{
	return this->MagicalAttackPoints;
}

float URingComponent::GetManaRegeneration()
{
	return this->ManaRegenerationPerSec;
}