// (C) Flumminard 2015

#include "Ambosia.h"
#include "PotionComponent.h"

UPotionComponent::UPotionComponent()
{
	Name = "Potion";
	Description = "Gives you health points or mana!";
	HealthPoints = 0;
	Mana = 0;
}

bool UPotionComponent::Action_Implementation()
{
	if (!Super::Action_Implementation())
		return false;
	if (this->GetTimeTillCooled() <= 0)
	{
		UGameplayValuesComponent* GVComponent = dynamic_cast<UGameplayValuesComponent*>(this->GetOwner()->GetComponentByClass(TSubclassOf<UGameplayValuesComponent>()));
		if (GVComponent == nullptr)
			return false;

		float NewHP = this->ModifyHealthPoints(GVComponent->GetHealthPoints());
		GVComponent->SetHealthPoints(NewHP);

		float NewMana = this->ModifyMana(GVComponent->GetMana());
		GVComponent->SetMana(NewMana);

		this->AffectStackSize(-1);
		this->StartCooldown();

		return true;
	}
	else
	{
		return false;
	}
}

float UPotionComponent::ModifyHealthPoints(float HealthPoint)
{
	return HealthPoints + this->GetHealthPoints();
}

float UPotionComponent::ModifyMana(float Mana)
{
	return Mana + this->GetMana();
}


float UPotionComponent::GetHealthPoints()
{
	return this->HealthPoints;
}

float UPotionComponent::GetMana()
{
	return this->Mana;
}


