// (C) Flumminard 2015

#pragma once

#include "Items/WeaponComponent.h"
#include "BowComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent), Blueprintable)
class AMBOSIA_API UBowComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	
	UBowComponent();

	virtual bool Action_Implementation() override;

	void SetSpawnOffset(FVector NewSpawnOffset);

	FVector GetSpawnOffset();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FVector SpawnOffset;

};
