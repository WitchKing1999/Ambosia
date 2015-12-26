// (C) Flumminard 2015

#include "Ambosia.h"
#include "InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	Weapon = nullptr;
	Armor = nullptr;
}

void UInventoryComponent::OnChildDetached(USceneComponent* ChildComponent)
{
	if (ChildComponent == this->GetWeapon())
	{
		this->Weapon = nullptr;
	}
	else if (ChildComponent == this->GetArmor())
	{
		this->Armor = nullptr;
	}
	else if (ChildComponent == this->GetPotion())
	{
		this->Potion = nullptr;
	}
	else if (ChildComponent == this->GetArrowBundle())
	{
		this->ArrowBundle = nullptr;
	}
}

UWeaponComponent* UInventoryComponent::GetWeapon()
{
	return this->Weapon;
}

bool UInventoryComponent::SetWeapon(UWeaponComponent* NewWeapon)
{
	if (NewWeapon->GetAttachParent() == this)
	{
		this->Weapon = NewWeapon;
		return true;
	}
	else
	{
		return false;
	}
}

UArmorComponent* UInventoryComponent::GetArmor()
{
	return this->Armor;
}

bool UInventoryComponent::SetArmor(UArmorComponent* NewArmor)
{
	if (NewArmor->GetAttachParent() == this)
	{
		this->Armor = NewArmor;
		return true;
	}
	else
	{
		return false;
	}
}

UPotionComponent* UInventoryComponent::GetPotion()
{
	return this->Potion;
}

bool UInventoryComponent::SetPotion(UPotionComponent* NewPotion)
{
	if (NewPotion->GetAttachParent() == this)
	{
		this->Potion = NewPotion;
		return true;
	}
	else
	{
		return false;
	}
}

UArrowBundleComponent* UInventoryComponent::GetArrowBundle()
{
	return this->ArrowBundle;
}

bool UInventoryComponent::SetArrowBundle(UArrowBundleComponent* NewArrowBundle)
{
	if (NewArrowBundle->GetAttachParent() == this)
	{
		this->ArrowBundle = NewArrowBundle;
		return true;
	}
	else
	{
		return false;
	}
}