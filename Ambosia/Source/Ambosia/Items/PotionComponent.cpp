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
		TInlineComponentArray<UGameplayValuesComponent*> GVComponents;
		this->GetOwner()->GetComponents(GVComponents);
		UGameplayValuesComponent* GVComponent = GVComponents[0];
		if (GVComponent == nullptr)
			return false;

		if (GVComponent->GetHealthPoints() < GVComponent->GetHealthPointsLimit())
		{
			float NewHP = this->ModifyHealthPoints(GVComponent->GetHealthPoints());
			GVComponent->SetHealthPoints(NewHP);

			float NewMana = this->ModifyMana(GVComponent->GetMana());
			GVComponent->SetMana(NewMana);

			this->AffectStackSize(-1);
			this->StartCooldown();

			return true;
		}

		return false;
	}
	else
	{
		return false;
	}
}

float UPotionComponent::ModifyHealthPoints(float HealthPoints)
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


