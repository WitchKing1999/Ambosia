// (C) Flumminard 2015

#include "Ambosia.h"
#include "ItemComponent.h"


// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Name = "Item";
	Description = "Does nothing at all!";
	StackSize = 1;
	TimeTillCooled = 0;
	CooldownTime = 0;
	bStackable = false;
	DropChance = 0;
	static ConstructorHelpers::FObjectFinder<UTexture> IconAsset(TEXT("/Game/Icons/Grey_Circle"));
	if (IconAsset.Succeeded())
	{
		Icon = IconAsset.Object;
	}
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

bool UItemComponent::Action_Implementation()
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

UTexture* UItemComponent::GetIcon()
{
	return this->Icon;
}

int32 UItemComponent::GetStackSize()
{
	return this->StackSize;
}

void UItemComponent::SetStackSize(int32 NewStackSize)
{
	this->StackSize = NewStackSize;
	if (this->StackSize <= 0)
	{
		this->DestroyComponent();
	}
}

void UItemComponent::AffectStackSize(int32 Delta)
{
	this->SetStackSize(this->StackSize + Delta);
}

void UItemComponent::AddItemToStack(UItemComponent* Item)
{
	if ((this->GetClass() == Item->GetClass()) && (Item != this) && this->IsStackable() && (! Item->IsBeingDestroyed()))
	{
		this->AffectStackSize(Item->GetStackSize());
		Item->DestroyComponent();
	}
}

bool UItemComponent::StartCooldown()
{
	if (this->TimeTillCooled <= 0)
	{
		this->TimeTillCooled = this->CooldownTime;
		return true;
	}
	else
		return false;
}

void UItemComponent::OnCooledDown_Implementation()
{
	return; // do nothing!
}

float UItemComponent::GetTimeTillCooled()
{
	return this->TimeTillCooled;
}

float UItemComponent::GetCooldownTime()
{
	return this->CooldownTime;
}

bool UItemComponent::IsStackable()
{
	return this->bStackable;
}

float UItemComponent::GetDropChance()
{
	return this->DropChance;
}

float UItemComponent::ModifyHealthPoints_Implementation(float HealthPoints)
{
	return HealthPoints;
}

float UItemComponent::ModifyHealthPointsLimit_Implementation(float HealthPointsLimit)
{
	return HealthPointsLimit;
}

float UItemComponent::ModifyAttackPoints_Implementation(float AttackPoints)
{
	return AttackPoints;
}

float UItemComponent::ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints)
{
	return MagicalAttackPoints;
}

float UItemComponent::ModifyMana_Implementation(float Mana)
{
	return Mana;
}

float UItemComponent::ModifyManaLimit_Implementation(float ManaLimit)
{
	return ManaLimit;
}

float UItemComponent::ModifyManaRegeneration_Implementation(float ManaRegeneration)
{
	return ManaRegeneration;
}