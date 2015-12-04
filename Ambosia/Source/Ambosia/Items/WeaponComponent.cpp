// (C) Flumminard 2015

#include "Ambosia.h"
#include "WeaponComponent.h"

UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	AttackFactor = 1.0;
	ManaCost = 0;
	MagicalAttackFactor = 1.0;
}

void UWeaponComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (this->TimeTillCooled > 0)
	{
		this->TimeTillCooled -= DeltaTime;
		if (this->TimeTillCooled <= 0)
		{
			this->OnCooledDown();
		}
	}
}

void UWeaponComponent::Attack()
{
	this->TimeTillCooled = this->CooldownTime;
}

void UWeaponComponent::OnCooledDown()
{

}

float UWeaponComponent::GetTimeTillCooled()
{
	return this->TimeTillCooled;
}

float UWeaponComponent::GetCooldownTime()
{
	return this->CooldownTime;
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