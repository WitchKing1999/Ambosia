// (C) Flumminard 2015

#include "Ambosia.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	ActionItem = nullptr;
}

void UInventoryComponent::OnChildDetached(USceneComponent* ChildComponent)
{
	Super::OnChildDetached(ChildComponent);

	UItemComponent* ChildAsItem = dynamic_cast<UItemComponent*>(ChildComponent);
	if (ChildAsItem == this->ActionItem)
	{
		this->ActionItem = nullptr;
	}
	else if (ChildAsItem == this->PassiveItem)
	{
		this->PassiveItem = nullptr;
	}
}

void UInventoryComponent::ActivateActionItem()
{
	if (this->ActionItem != nullptr)
		this->ActionItem->Activate();
}

void UInventoryComponent::DeactivateActionItem()
{
	if (this->ActionItem != nullptr)
		this->ActionItem->Deactivate();
}

UItemComponent* UInventoryComponent::GetActionItem()
{
	return this->ActionItem;
}

void UInventoryComponent::SetActionItem(UItemComponent* Item)
{
	if (Item->AttachParent == this)
	{
		this->ActionItem = Item;
	}
}

UItemComponent* UInventoryComponent::GetPassiveItem()
{
	return this->PassiveItem;
}

void UInventoryComponent::SetPassiveItem(UItemComponent* Item)
{
	if (Item->AttachParent == this)
	{
		this->PassiveItem = Item;
	}
}

