// (C) Flumminard 2015-2016

#pragma once

#include "GameFramework/DamageType.h"
#include "AmbosiaDamageType.generated.h"

/*
The damage type base class of Ambosia.
*/
UCLASS()
class AMBOSIA_API UAmbosiaDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:

	UAmbosiaDamageType();

	bool IsMagical();

protected:

	/*
	If true, the damaged gameplay system will use the magical defence factor
	instead of the standart defence factor.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Type")
	bool bMagical;
	
};
