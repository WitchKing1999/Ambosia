// (C) Flumminard 2015

#include "Ambosia.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackPoints = 0;
}

float AProjectile::GetAttackPoints()
{
	return this->AttackPoints;
}

void AProjectile::SetAttackPoints(float NewAttackPoints)
{
	this->AttackPoints = NewAttackPoints;
}