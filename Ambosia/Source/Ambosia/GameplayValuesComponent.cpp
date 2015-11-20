// (C) Flumminard 2015

#include "Ambosia.h"
#include "GameplayValuesComponent.h"


// Sets default values for this component's properties
UGameplayValuesComponent::UGameplayValuesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	Inventory = nullptr;

	HealthPoints = 200;
	HealthPointsLimit = 200;
	AttackPoints = 100;
	DefenceFactor = 1;
}


// Called when the game starts
void UGameplayValuesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGameplayValuesComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UGameplayValuesComponent::AffectHealthPoints(float Delta)
{
	this->HealthPoints += Delta / this->GetEffectiveDefenceFactor();
	if (this->HealthPoints > this->GetEffectiveHealthPointsLimit())
	{
		this->HealthPoints = this->GetEffectiveHealthPointsLimit();
	}
	else if (this->HealthPoints <= 0)
	{
		this->GetOwner()->Destroy();
	}
}

float UGameplayValuesComponent::GetHealthPoints()
{
	return this->HealthPoints;
}

void UGameplayValuesComponent::SetHealthPoints(float HealthPoints)
{
	this->HealthPoints = HealthPoints;
	if (this->HealthPoints <= 0)
	{
		this->GetOwner()->Destroy();
	}
}

float UGameplayValuesComponent::GetHealthPointsLimit()
{
	return this->HealthPointsLimit;
}

float UGameplayValuesComponent::GetEffectiveHealthPointsLimit()
{
	if (this->Inventory != nullptr)
	{
		return this->GetHealthPointsLimit() + this->GetInventory()->GetPassiveItem()->GetHealthPointsLimit();
	}
	else
	{
		return this->GetHealthPointsLimit();
	}
}

void UGameplayValuesComponent::SetHealthPointsLimit(float HealthPointsLimit)
{
	if (HealthPointsLimit > 0)
	{
		this->HealthPointsLimit = HealthPointsLimit;
		if (this->HealthPoints > HealthPointsLimit)
		{
			this->SetHealthPoints(HealthPointsLimit);
		}
	}
}

float UGameplayValuesComponent::GetAttackPoints()
{
	return this->AttackPoints;
}

float UGameplayValuesComponent::GetEffectiveAttackPoints()
{
	if (this->Inventory != nullptr)
	{
		return this->GetAttackPoints() + this->GetInventory()->GetActionItem()->GetAttackPoints();
	}
	else
	{
		return this->GetAttackPoints();
	}
}

void UGameplayValuesComponent::SetAttackPoints(float AttackPoints)
{
	this->AttackPoints = AttackPoints;
}

float UGameplayValuesComponent::GetDefenceFactor()
{
	return this->DefenceFactor;
}

float UGameplayValuesComponent::GetEffectiveDefenceFactor()
{
	if (this->Inventory != nullptr)
	{
		return this->GetDefenceFactor() + this->GetInventory()->GetPassiveItem()->GetDefenceFactor();
	}
	else
	{
		return this->GetDefenceFactor();
	}
}

void UGameplayValuesComponent::SetDefenceFactor(float DefenceFactor)
{
	this->DefenceFactor = DefenceFactor;
}

UInventoryComponent* UGameplayValuesComponent::GetInventory()
{
	return this->Inventory;
}

void UGameplayValuesComponent::SetInventory(UInventoryComponent* Inventory)
{
	this->Inventory = Inventory;
}
