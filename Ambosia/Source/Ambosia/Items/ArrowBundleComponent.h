// (C) Flumminard 2015

#pragma once

#include "Items/ItemComponent.h"
#include "ArrowBundleComponent.generated.h"

/*
Base class for arrow bundles.
*/
UCLASS()
class AMBOSIA_API UArrowBundleComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	UArrowBundleComponent();

	UClass* GetArrowClass();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arrow Bundle")
	UClass* ArrowClass;
	
};
