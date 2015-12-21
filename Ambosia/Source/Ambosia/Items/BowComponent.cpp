// (C) Flumminard 2015

#include "Ambosia.h"
#include "InventoryComponent.h"
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
	UInventoryComponent* Inventory = dynamic_cast<UInventoryComponent*>(this->GetAttachParent());
	if (Inventory == nullptr)
		return false;
	UArrowBundleComponent* ArrowBundle = Inventory->GetArrowBundle();
	if (ArrowBundle == nullptr)
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

	this->GetWorld()->SpawnActor(ProjectileClass, &SpawnTransform, SpawnParameters);

	ArrowBundle->AffectStackSize(-1);

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