// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/DamageType.h"
#include "AmbosiaDamageType.generated.h"

/**
 * 
 */
UCLASS()
class AMBOSIA_API UAmbosiaDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:

	UAmbosiaDamageType();

	bool IsMagical();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Type")
	bool bMagical;
	
};
