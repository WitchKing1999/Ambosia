// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "AmuletComponent.h"

UAmuletComponent::UAmuletComponent()
{
	HealthPointsLimit = 0;
	ManaLimit = 0;
	AttackPoints = 0;
	MagicalAttackPoints = 0;
	ManaRegenerationPerSec = 0;
}

float UAmuletComponent::ModifyHealthPointsLimit_Implementation(float HealthPointsLimit)
{
	return HealthPointsLimit + this->GetHealthPointsLimit();
}

float UAmuletComponent::ModifyManaLimit_Implementation(float ManaLimit)
{
	return ManaLimit + this->GetManaLimit();
}

float UAmuletComponent::ModifyAttackPoints_Implementation(float AttackPoints)
{
	return AttackPoints + this->GetAttackPoints();
}

float UAmuletComponent::ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints)
{
	return MagicalAttackPoints + this->GetMagicalAttackPoints();
}

float UAmuletComponent::ModifyManaRegeneration_Implementation(float ManaRegeneration)
{
	return ManaRegeneration + this->GetManaRegeneration();
}

float UAmuletComponent::GetHealthPointsLimit()
{
	return this->HealthPointsLimit;
}

float UAmuletComponent::GetManaLimit()
{
	return this->ManaLimit;
}

float UAmuletComponent::GetAttackPoints()
{
	return this->AttackPoints;
}

float UAmuletComponent::GetMagicalAttackPoints()
{
	return this->MagicalAttackPoints;
}

float UAmuletComponent::GetManaRegeneration()
{
	return this->ManaRegenerationPerSec;
}