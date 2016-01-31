// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "GameplaySystemComponent.h"
#include "DamageTypes/SwordDamageType.h"
#include "SwordComponent.h"

USwordComponent::USwordComponent()
{
	this->HitRange = 128;
}

bool USwordComponent::Action_Implementation()
{
	if (!Super::Action_Implementation())
		return false;
	if (this->GetOwner() == nullptr)
		return false;
	AController* OwnerAsController = dynamic_cast<AController*>(this->GetOwner());
	if (OwnerAsController == nullptr)
		return false;
	if (OwnerAsController->GetPawn() == nullptr)
		return false;

	FVector TraceStart = OwnerAsController->GetPawn()->GetActorLocation();
	FVector TraceEnd = OwnerAsController->GetPawn()->GetActorLocation();
	{
		FRotator Rotation = OwnerAsController->GetControlRotation();
		TraceEnd += Rotation.RotateVector(FVector(this->HitRange, 0, 0));
	}

	// Setup the trace query  
	FCollisionQueryParams TraceParams = FCollisionQueryParams(false);
	TraceParams.AddIgnoredActor(OwnerAsController->GetPawn());
	TraceParams.bTraceAsyncScene = true;
	FCollisionResponseParams CollisionParams = FCollisionResponseParams();

	FHitResult HitResult;
	if (this->GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_GameTraceChannel1, TraceParams, CollisionParams))
	{
		UGameplaySystemComponent* GameplaySystem = dynamic_cast<UGameplaySystemComponent*>(this->GetAttachParent());
		if (GameplaySystem == nullptr)
			return false;
		HitResult.Actor->TakeDamage(GameplaySystem->GetAttackPoints(),FDamageEvent(TSubclassOf<USwordDamageType>()),OwnerAsController,OwnerAsController->GetPawn());
	}
	return true;
}

float USwordComponent::GetHitRange()
{
	return this->HitRange;
}

void USwordComponent::SetHitRange(float NewRange)
{
	this->HitRange = NewRange;
}