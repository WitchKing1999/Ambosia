// (C) Flumminard 2015

#include "Ambosia.h"
#include "SwordBoxComponent.h"

USwordBoxComponent::USwordBoxComponent()
{
	SwordSizeExtended = FVector(32, 32, 16);

	IsSwordExtended = true;
	RetractSword();

	this->OnComponentBeginOverlap.AddDynamic(this, &USwordBoxComponent::OnOverlapBegin);
}

void USwordBoxComponent::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this->GetOwner()) && (OtherComp != nullptr))
	{
		UGameplayValuesComponent* otherGameplayValues = dynamic_cast<UGameplayValuesComponent*>(OtherActor->GetComponentByClass(TSubclassOf<UGameplayValuesComponent>()));
		otherGameplayValues->AffectHealthPoints(this->OwnGameplayValues->GetEffectiveAttackPoints());
		this->RetractSword();
	}
}

void USwordBoxComponent::ExtendSword()
{
	if (!IsSwordExtended)
	{
		this->SetBoxExtent(this->SwordSizeExtended);
		this->SetRelativeLocation(FVector(this->SwordSizeExtended.X, 0, 0));
		this->IsSwordExtended = true;
	}
}

void USwordBoxComponent::RetractSword()
{
	if (IsSwordExtended)
	{
		FVector Nullvector = FVector(0, 0, 0);
		this->SetBoxExtent(Nullvector);
		this->SetRelativeLocation(Nullvector);
		this->IsSwordExtended = false;
	}
}

bool USwordBoxComponent::GetIsSwordExtended()
{
	return this->IsSwordExtended;
}

UGameplayValuesComponent* USwordBoxComponent::GetGameplayValues()
{
	return this->OwnGameplayValues;
}

void USwordBoxComponent::SetGameplayValues(UGameplayValuesComponent* newGameplayValues)
{
	this->OwnGameplayValues = newGameplayValues;
}
