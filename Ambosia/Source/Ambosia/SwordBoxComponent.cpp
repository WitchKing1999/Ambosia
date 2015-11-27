// (C) Flumminard 2015

#include "Ambosia.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SwordBoxComponent.h"

USwordBoxComponent::USwordBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
	SwordSizeExtended = FVector(32, 32, 32);

	IsSwordExtended = true;
	RetractSword();

	bGenerateOverlapEvents = true;
}

void USwordBoxComponent::TickComponent(float Delta, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(Delta, TickType, ThisTickFunction);
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
