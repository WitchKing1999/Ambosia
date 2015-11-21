// (C) Flumminard 2015

#pragma once

#include "ItemComponent.h"
#include "SwordItemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API USwordItemComponent : public UItemComponent
{
	GENERATED_BODY()
	
public:
	USwordItemComponent();

	virtual void Activate(bool bReset) override;

	virtual void Deactivate() override;
	
	
};
