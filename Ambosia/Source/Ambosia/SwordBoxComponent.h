// (C) Flumminard 2015

#pragma once

#include "Components/BoxComponent.h"
#include "GameplayValuesComponent.h"
#include "SwordBoxComponent.generated.h"

/**
 * This collision box provides to states: extended an retracted.
 * If extended, it will have the size defined in SwordSizeExtended
 * and will be set in front of the parent component. 
 * If retracted, it will almost disapear.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API USwordBoxComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	USwordBoxComponent();

	// Expands the box and places it in front of the parent component.
	UFUNCTION(BlueprintCallable, Category = "SwordBox")
	void ExtendSword();

	// Defaltes the box and places it in the parent component.
	UFUNCTION(BlueprintCallable, Category = "SwordBox")
	void RetractSword();

	// Gets whether the sword is extended or not.
	bool GetIsSwordExtended();
	
	// The size the sword will have when extended.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwordBox")
	FVector SwordSizeExtended;

protected:
	// Tells whether the sword is extended or not.
	UPROPERTY(BlueprintReadOnly, Category = "SwordBox")
	bool IsSwordExtended;
	
};
