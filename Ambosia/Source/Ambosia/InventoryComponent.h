// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "Items/WeaponComponent.h"
#include "Items/ArmorComponent.h"
#include "InventoryComponent.generated.h"

// This component manages all items that are attached to it.
// It provides an action item and an passive item.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UInventoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	virtual void OnChildDetached(USceneComponent* ChildComponent) override;

	UWeaponComponent* GetWeapon();

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetWeapon(UWeaponComponent* NewWeapon);

	UArmorComponent* GetArmor();

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	bool SetArmor(UArmorComponent* NewArmor);

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UWeaponComponent* Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UArmorComponent* Armor;
};
