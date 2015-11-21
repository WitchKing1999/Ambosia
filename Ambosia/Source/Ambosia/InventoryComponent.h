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

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ActivateActionItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DeactivateActionItem();

	UItemComponent* GetActionItem();

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	void SetActionItem(UItemComponent* Item);

	UItemComponent* GetPassiveItem();

	UFUNCTION(BlueprintCallable, Category = "Variables|Inventory")
	void SetPassiveItem(UItemComponent* Item);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|Inventory")
	UItemComponent* ActionItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|Inventory")
	UItemComponent* PassiveItem;
	
};
