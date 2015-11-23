// (C) Flumminard 2015

#include "Ambosia.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ItemComponent.h"


// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	HealthPointsLimit = 200;
	AttackPoints = 100;
	DefenceFactor = 1;
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

float UItemComponent::GetHealthPointsLimit()
{
	return this->HealthPointsLimit;
}

float UItemComponent::GetAttackPoints()
{
	return this->AttackPoints;
}

float UItemComponent::GetDefenceFactor()
{
	return this->DefenceFactor;
}
