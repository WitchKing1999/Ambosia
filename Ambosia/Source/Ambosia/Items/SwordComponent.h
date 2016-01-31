// (C) Flumminard 2015-2016

#pragma once

#include "Items/WeaponComponent.h"
#include "SwordComponent.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API USwordComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:

	USwordComponent();

	virtual bool Action_Implementation() override;

	float GetHitRange();
	void SetHitRange(float NewRange);

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	float HitRange;
	
};
