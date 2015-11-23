// (C) Flumminard 2015

#include "Ambosia.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameplayValuesComponent.h"


// Sets default values for this component's properties
UGameplayValuesComponent::UGameplayValuesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

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
	UKismetSystemLibrary::PrintString(this, "Affect!");
	this->HealthPoints += Delta / this->GetEffectiveDefenceFactor();
	if (this->HealthPoints > this->GetEffectiveHealthPointsLimit())
	{
		UKismetSystemLibrary::PrintString(this, "Limit reached!");
		this->HealthPoints = this->GetEffectiveHealthPointsLimit();
	}
	else if (this->HealthPoints <= 0)
	{
		UKismetSystemLibrary::PrintString(this, "Die!");
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
	TArray<UActorComponent*> otherComponents = this->GetOwner()->GetComponents();
	UInventoryComponent* inventory = nullptr;
	for (UActorComponent* component : otherComponents)
	{
		UInventoryComponent* componentCasted = dynamic_cast<UInventoryComponent*>(component);
		if (componentCasted != nullptr)
		{
			inventory = componentCasted;
		}
	}
	if (inventory == nullptr)
		return this->GetHealthPointsLimit();
	UItemComponent* PassiveItem = inventory->GetPassiveItem();

	if (PassiveItem != nullptr)
	{
		return (this->GetHealthPointsLimit() + inventory->GetPassiveItem()->GetHealthPointsLimit());
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
	TArray<UActorComponent*> otherComponents = this->GetOwner()->GetComponents();
	UInventoryComponent* inventory = nullptr;
	for (UActorComponent* component : otherComponents)
	{
		UInventoryComponent* componentCasted = dynamic_cast<UInventoryComponent*>(component);
		if (componentCasted != nullptr)
		{
			inventory = componentCasted;
		}
	}
	if (inventory == nullptr)
		return this->GetAttackPoints();
	UItemComponent* PassiveItem = inventory->GetPassiveItem();

	if (PassiveItem != nullptr)
	{
		return (this->GetAttackPoints() + inventory->GetActionItem()->GetAttackPoints());
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
	TArray<UActorComponent*> otherComponents = this->GetOwner()->GetComponents();
	UInventoryComponent* inventory = nullptr;
	for (UActorComponent* component : otherComponents)
	{
		UInventoryComponent* componentCasted = dynamic_cast<UInventoryComponent*>(component);
		if (componentCasted != nullptr)
		{
			inventory = componentCasted;
		}
	}
	if (inventory == nullptr)
		return this->GetDefenceFactor();
	UItemComponent* PassiveItem = inventory->GetPassiveItem();

	if (PassiveItem != nullptr)
		return (this->GetDefenceFactor() + inventory->GetPassiveItem()->GetDefenceFactor());
	else
		return this->GetDefenceFactor();
}

void UGameplayValuesComponent::SetDefenceFactor(float DefenceFactor)
{
	this->DefenceFactor = DefenceFactor;
}
