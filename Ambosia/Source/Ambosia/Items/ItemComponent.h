// (C) Flumminard 2015

#pragma once

#include "Components/SceneComponent.h"
#include "ItemComponent.generated.h"

// This is the item base class.
UCLASS( ClassGroup=(Items), meta=(BlueprintSpawnableComponent) )
class AMBOSIA_API UItemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

	FString GetName();

	FText GetDescription();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Description;
	
};
