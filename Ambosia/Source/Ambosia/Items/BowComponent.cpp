// (C) Flumminard 2015

#include "Ambosia.h"
#include "GameplaySystemComponent.h"
#include "Pawns/Projectile.h"
#include "Items/ArrowBundleComponent.h"
#include "BowComponent.h"

UBowComponent::UBowComponent()
{
	Name = "Bow";
	Description = "Shoots projectiles";
	SpawnOffset = FVector(64, 0, 0);
}

bool UBowComponent::Action_Implementation()
{
	if (!Super::Action_Implementation())
		return false;

	AController* OwnerAsController = dynamic_cast<AController*>(this->GetOwner());
	if (OwnerAsController == nullptr)
		return false;
	APawn* ControlledPawn = OwnerAsController->GetPawn();
	if (ControlledPawn == nullptr)
		return false;
	UGameplaySystemComponent* GameplaySystem = dynamic_cast<UGameplaySystemComponent*>(this->GetAttachParent());
	if (GameplaySystem == nullptr)
		return false;
	UArrowBundleComponent* ArrowBundle = GameplaySystem->GetArrowBundle();
	if (ArrowBundle == nullptr)
		return false;
	if (this->GetAcceptedArrows().Find(ArrowBundle->GetClass()) == INDEX_NONE)
		return false;
	UClass* ProjectileClass = ArrowBundle->GetArrowClass();
	if (ProjectileClass == nullptr)
		return false;

	FTransform SpawnTransform;
	{
		FRotator SpawnRotation = OwnerAsController->GetControlRotation();
		FVector SpawnLocation = ControlledPawn->GetActorLocation();
		SpawnLocation += SpawnRotation.RotateVector(this->GetSpawnOffset());
		SpawnTransform = FTransform(SpawnRotation, SpawnLocation);
	}

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.Owner = this->GetOwner();

	AProjectile* Projectile = dynamic_cast<AProjectile*>(this->GetWorld()->SpawnActor(ProjectileClass, &SpawnTransform, SpawnParameters));

	ArrowBundle->AffectStackSize(-1);

	if (Projectile != nullptr)
	{
		Projectile->SetAttackPoints(GameplaySystem->GetAttackPoints());
	}

	return true;
}

void UBowComponent::SetSpawnOffset(FVector NewSpawnOffset)
{
	this->SpawnOffset = NewSpawnOffset;
}

FVector UBowComponent::GetSpawnOffset()
{
	return this->SpawnOffset;
}

TArray<UClass*> UBowComponent::GetAcceptedArrows()
{
	return this->AcceptedArrows;
}