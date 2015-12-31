// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "Items/WeaponComponent.h"
#include "Items/ArmorComponent.h"
#include "Items/PotionComponent.h"
#include "Items/ArrowBundleComponent.h"
#include "InventoryComponent.generated.h"

/**
This component has some pointers to our selected items.
These items need to be attached to us.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UInventoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	virtual void OnChildDetached(USceneComponent* ChildComponent) override;

	/*
	Weapon
	*/

	UWeaponComponent* GetWeapon();

	/**
	Sets our weapon to the new weapon.
	Doesn't work if the new weapon ism't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetWeapon(UWeaponComponent* NewWeapon);

	/*
	Armor
	*/

	UArmorComponent* GetArmor();

	/**
	Sets our armor to the new armor.
	Doesn't work if the new armor isn't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetArmor(UArmorComponent* NewArmor);

	/*
	Potion
	*/

	UPotionComponent* GetPotion();

	/**
	Sets our potion to the new potion.
	Doesn't work if the new potion ism't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetPotion(UPotionComponent* NewPotion);

	/*
	Arrow Bundle
	*/

	UArrowBundleComponent* GetArrowBundle();

	/**
	Sets our arrow bundle to the new arrow bundle.
	Doesn't work if the new arrow bundle isn't attached to us.
	*/
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetArrowBundle(UArrowBundleComponent* NewArrowBundle);

protected:
	
	/*
	Our Properties
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UWeaponComponent* Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UArmorComponent* Armor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UPotionComponent* Potion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UArrowBundleComponent* ArrowBundle;

};
