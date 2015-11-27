// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.h"
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

	// Called when a child detaches from us.
	// It checks whether the component is a selected item and resets the pointer
	// if true.
	virtual void OnChildDetached(USceneComponent* ChildComponent) override;

	// Activates the action item
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ActivateActionItem();

	// Deactivates the action item
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DeactivateActionItem();

	// Returns our current action item
	UItemComponent* GetActionItem();

	// Sets our current action item. Only works if the item is attached to us.
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	void SetActionItem(UItemComponent* Item);

	// Returns our current passive item.
	UItemComponent* GetPassiveItem();

	// Sets our current passive item. Only works if the item is attached to us.
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	void SetPassiveItem(UItemComponent* Item);

protected:
	// Our current action item.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|Inventory")
	UItemComponent* ActionItem;

	// Our current passive item.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|Inventory")
	UItemComponent* PassiveItem;
	
};
