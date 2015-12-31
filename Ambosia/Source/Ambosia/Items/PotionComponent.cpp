// (C) Flumminard 2015

#include "Ambosia.h"
#include "PotionComponent.h"

UPotionComponent::UPotionComponent()
{
	Name = "Potion";
	Description = "Gives you health points or mana!";
	HealthPoints = 0;
	Mana = 0;
	bStackable = true;
}

bool UPotionComponent::Action_Implementation()
{
	bool successfull = false;

	if (!Super::Action_Implementation())
		return false;

	if (this->GetTimeTillCooled() > 0)
		return false;

	TInlineComponentArray<UGameplayValuesComponent*> GVComponents;
	this->GetOwner()->GetComponents(GVComponents);
	UGameplayValuesComponent* GVComponent = GVComponents[0];
	if (GVComponent == nullptr)
		return false;

		
	if (GVComponent->GetHealthPoints() < GVComponent->GetHealthPointsLimit())
	{
		float NewHP = this->ModifyHealthPoints(GVComponent->GetHealthPoints());
		GVComponent->SetHealthPoints(NewHP);

		successfull = true;
	}

	if (GVComponent->GetMana() < GVComponent->GetManaLimit())
	{
		float NewMana = this->ModifyMana(GVComponent->GetMana());
		GVComponent->SetMana(NewMana);
	
		successfull = true;
	}
	
	if (successfull)
	{
		this->AffectStackSize(-1);
		this->StartCooldown();
		return true;
	}
	return false;
}

float UPotionComponent::ModifyHealthPoints_Implementation(float HealthPoints)
{
	return HealthPoints + this->GetHealthPoints();
}

float UPotionComponent::ModifyMana_Implementation(float Mana)
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


