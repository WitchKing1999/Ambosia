// (C) Flumminard 2015

#include "Ambosia.h"
#include "GameplaySystemComponent.h"
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

	UGameplaySystemComponent* GSComponent = dynamic_cast<UGameplaySystemComponent*>(this->GetAttachParent());
	if (GSComponent == nullptr)
		return false;

		
	if (GSComponent->GetHealthPoints() < GSComponent->GetHealthPointsLimit())
	{
		float NewHP = this->ModifyHealthPoints(GSComponent->GetHealthPoints());
		GSComponent->SetHealthPoints(NewHP);

		successfull = true;
	}

	if (GSComponent->GetMana() < GSComponent->GetManaLimit())
	{
		float NewMana = this->ModifyMana(GSComponent->GetMana());
		GSComponent->SetMana(NewMana);
	
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


