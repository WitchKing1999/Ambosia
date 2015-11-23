// (C) Flumminard 2015

#include "Ambosia.h"
#include "SwordBoxComponent.h"

USwordBoxComponent::USwordBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
	SwordSizeExtended = FVector(32, 32, 32);

	IsSwordExtended = true;
	RetractSword();

	this->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void USwordBoxComponent::TickComponent(float Delta, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(Delta, TickType, ThisTickFunction);
	TArray<AActor*> overlappingActors;
	this->GetOverlappingActors(overlappingActors);
	for (AActor* OtherActor : overlappingActors)
	{
		if ((OtherActor != nullptr) && (OtherActor != this->GetOwner()))
		{
			// get the gameplayValuesComponents of the other actor
			APawn* otherPawn = dynamic_cast<APawn*>(OtherActor);
			if (otherPawn == nullptr)
				return;
			AController* otherController = otherPawn->GetController();
			if (otherController == nullptr)
				return;
			TArray<UActorComponent*> otherComponents = otherController->GetComponents();
			UGameplayValuesComponent* otherGameplayValues = nullptr;
			for (UActorComponent* component : otherComponents)
			{
				UGameplayValuesComponent* componentCasted = dynamic_cast<UGameplayValuesComponent*>(component);
				if (componentCasted != nullptr)
				{
					otherGameplayValues = componentCasted;
				}
			}
			if (otherGameplayValues == nullptr)
				return;

			// get the gameplayValuesComponents of the own actor
			APawn* ownPawn = dynamic_cast<APawn*>(this->GetOwner());
			if (ownPawn == nullptr)
				return;
			AController* ownController = ownPawn->GetController();
			if (ownController == nullptr)
				return;
			TArray<UActorComponent*> ownComponents = ownController->GetComponents();
			if (ownComponents.Num() == 0)
				return;
			UGameplayValuesComponent* ownGameplayValues = nullptr;
			for (UActorComponent* component : ownComponents)
			{
				UGameplayValuesComponent* componentCasted = dynamic_cast<UGameplayValuesComponent*>(component);
				if (componentCasted != nullptr)
				{
					ownGameplayValues = componentCasted;
				}
			}
			if (ownGameplayValues == nullptr)
				return;

			// affecting health and retract sword
			otherGameplayValues->AffectHealthPoints(ownGameplayValues->GetEffectiveAttackPoints() * -1);
			this->RetractSword();
		}
	}
}

void USwordBoxComponent::ExtendSword()
{
	if (!IsSwordExtended)
	{
		this->SetBoxExtent(this->SwordSizeExtended);
		this->SetRelativeLocation(FVector(this->SwordSizeExtended.X*2, 0, 0));
		this->UpdateOverlaps();
		this->IsSwordExtended = true;
	}
}

void USwordBoxComponent::RetractSword()
{
	if (IsSwordExtended)
	{
		this->SetBoxExtent(FVector(1, 1, 1));
		this->SetRelativeLocation(FVector(0, 0, 0));
		this->UpdateOverlaps();
		this->IsSwordExtended = false;
	}
}

bool USwordBoxComponent::GetIsSwordExtended()
{
	return this->IsSwordExtended;
}
