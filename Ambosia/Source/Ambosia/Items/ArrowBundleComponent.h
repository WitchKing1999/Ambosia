// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "ArrowBundleComponent.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API UArrowBundleComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	UArrowBundleComponent();

	UClass* GetArrowClass();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UClass* ArrowClass;
	
};
