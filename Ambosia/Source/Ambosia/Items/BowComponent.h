// (C) Flumminard 2015

#pragma once

#include "Items/WeaponComponent.h"
#include "BowComponent.generated.h"

/*
The Bow is a Weapon that spawns projectiles when its action-Function is called.
*/
UCLASS(ClassGroup = (Items), meta = (BlueprintSpawnableComponent), Blueprintable)
class AMBOSIA_API UBowComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	
	UBowComponent();

	/*
	Spawns a projectile and returns true, if it was successfull and false, if not.
	To be successfull, it requires that there is enough mana, that the weapon is cooled down
	and that the inventory has some arrows which are accepted by the weapon.
	Also, it will reduce the stack of the arrow bundle by 1.
	*/
	virtual bool Action_Implementation() override;

	/*
	Returns the spawn offset
	*/
	FVector GetSpawnOffset();

	/*
	Sets the spawn offset to the new spawn offset
	*/
	void SetSpawnOffset(FVector NewSpawnOffset);

	/*
	Returns an array of all accepted arrow bundle classes
	*/
	TArray<UClass*> GetAcceptedArrows();

protected:

	/*
	The offset to spawn the projectile at.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bow")
	FVector SpawnOffset;

	/*
	All accepted arrow bundle classes
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Bow")
	TArray<UClass*> AcceptedArrows;

};
