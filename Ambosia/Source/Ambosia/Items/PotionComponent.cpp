// (C) Flumminard 2015

#include "Ambosia.h"
#include "PotionComponent.h"

UPotionComponent::UPotionComponent()
{
	HealthPoints = 0;
	Mana = 0;
}

void UPotionComponent::AffectGameplayValues(UGameplayValuesComponent* GVComponent)
{
	if (this->GetTimeTillCooled() <= 0)
	{
		GVComponent->AffectHealthPoints(this->GetHealthPoints());
		GVComponent->AffectMana(this->GetMana());

		this->AffectStackSize(-1);
		this->StartCooldown();
	}
}

float UPotionComponent::GetHealthPoints()
{
	return this->HealthPoints;
}

float UPotionComponent::GetMana()
{
	return this->Mana;
}


