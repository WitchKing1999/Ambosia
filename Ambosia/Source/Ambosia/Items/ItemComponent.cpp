// (C) Flumminard 2015

#include "Ambosia.h"
#include "ItemComponent.h"


// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

FString UItemComponent::GetName()
{
	return this->Name;
}

FText UItemComponent::GetDescription()
{
	return this->Description;
}