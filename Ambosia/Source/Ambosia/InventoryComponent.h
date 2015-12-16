// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "Items/WeaponComponent.h"
#include "Items/ArmorComponent.h"
#include "Items/PotionComponent.h"
#include "Items/ArrowBundleComponent.h"
#include "InventoryComponent.generated.h"

/*
This component manages all items that are attached to it.
Currently it holds a weapon-, an armor- and a potion item pointer.
All these items need to be attached to us.
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

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetWeapon(UWeaponComponent* NewWeapon);

	/*
	Armor
	*/

	UArmorComponent* GetArmor();

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetArmor(UArmorComponent* NewArmor);

	/*
	Potion
	*/

	UPotionComponent* GetPotion();

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetPotion(UPotionComponent* NewPotion);

	/*
	Arrow Bundle
	*/

	UArrowBundleComponent* GetArrowBundle();

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetArrowBundle(UArrowBundleComponent* NewArrowBundle);

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UWeaponComponent* Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UArmorComponent* Armor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UPotionComponent* Potion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UArrowBundleComponent* ArrowBundle;

};
