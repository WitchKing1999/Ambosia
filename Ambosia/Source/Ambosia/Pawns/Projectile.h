// (C) Flumminard 2015

#pragma once

#include "GameFramework/Pawn.h"
#include "Projectile.generated.h"

UCLASS()
class AMBOSIA_API AProjectile : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AProjectile();

	float GetAttackPoints();

	void SetAttackPoints(float NewAttackPoints);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackPoints;
	
};
