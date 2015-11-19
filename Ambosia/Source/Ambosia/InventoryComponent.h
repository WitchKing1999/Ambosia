// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UInventoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void OnChildDetached(USceneComponent* ChildComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	UItemComponent* GetActionItem();
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	void SetActionItem(UItemComponent* Item);

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	UItemComponent* GetPassiveItem();
	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	void SetPassiveItem(UItemComponent* Item);


protected:
	UItemComponent* ActionItem;
	UItemComponent* PassiveItem;
	
};
