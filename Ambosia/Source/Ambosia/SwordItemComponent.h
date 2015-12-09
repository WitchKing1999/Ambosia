// (C) Flumminard 2015

#pragma once

#include "ItemComponent.h"
#include "SwordItemComponent.generated.h"

/**
 * This item is intended to be used as an active item.
 * When activated, it extends the sword of the pawn.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AMBOSIA_API USwordItemComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	USwordItemComponent();

	// Tries to extend the sword.
	virtual void Activate(bool bReset) override;

	// Tries to retract the sword.
	virtual void Deactivate() override;
	
	
};
