// (C) Flumminard 2015

#include "Ambosia.h"
#include "Text.h"
#include "ItemComponent.h"


// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Name = "Item";
	Description = "Does nothing at all!";
	StackSize = 1;
	TimeTillCooled = 0;
	CooldownTime = 1;
}

void UItemComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (this->TimeTillCooled > 0)
	{
		this->TimeTillCooled -= DeltaTime;
		if (this->TimeTillCooled <= 0)
		{
			this->OnCooledDown();
		}
	}
}

bool UItemComponent::Action()
{
	return true;
}

FString UItemComponent::GetName()
{
	return this->Name;
}

FString UItemComponent::GetDescription()
{
	return this->Description;
}

float UItemComponent::GetStackSize()
{
	return this->StackSize;
}

void UItemComponent::SetStackSize(float NewStackSize)
{
	this->StackSize = NewStackSize;
	if (this->StackSize <= 0)
	{
		this->DestroyComponent();
	}
}

void UItemComponent::AffectStackSize(float Delta)
{
	this->SetStackSize(this->StackSize + Delta);
}

void UItemComponent::StartCooldown()
{
	this->TimeTillCooled = this->CooldownTime;
}

void UItemComponent::OnCooledDown()
{
	// do nothing!
}

float UItemComponent::GetTimeTillCooled()
{
	return this->TimeTillCooled;
}

float UItemComponent::GetCooldownTime()
{
	return this->CooldownTime;
}

float UItemComponent::ModifyHealthPoints(float HealthPoints)
{
	return HealthPoints;
}

float UItemComponent::ModifyHealthPointsLimit(float HealthPointsLimit)
{
	return HealthPointsLimit;
}

float UItemComponent::ModifyAttackPoints(float AttackPoints)
{
	return AttackPoints;
}

float UItemComponent::ModifyMagicalAttackPoints(float MagicalAttackPoints)
{
	return MagicalAttackPoints;
}

float UItemComponent::ModifyMana(float Mana)
{
	return Mana;
}

float UItemComponent::ModifyManaLimit(float ManaLimit)
{
	return ManaLimit;
}

float UItemComponent::ModifyManaRegeneration(float ManaRegeneration)
{
	return ManaRegeneration;
}