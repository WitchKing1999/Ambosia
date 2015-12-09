// (C) Flumminard 2015

#include "Ambosia.h"
#include "SwordBoxComponent.h"
#include "SwordItemComponent.h"

USwordItemComponent::USwordItemComponent()
{
	// ...
}

void USwordItemComponent::Activate(bool bReset)
{
	Super::Activate();
	AController* controller = dynamic_cast<AController*>(this->GetOwner());
	if (controller == nullptr)
		return;
	APawn* pawn = controller->GetPawn();
	if (pawn == nullptr)
		return;
	TArray<UActorComponent*> pawnComponents = pawn->GetComponents();
	USwordBoxComponent* swordBox = nullptr;
	for (UActorComponent* component : pawnComponents)
	{
		USwordBoxComponent* componentAsSwordBox = dynamic_cast<USwordBoxComponent*>(component);
		if (componentAsSwordBox != nullptr)
		{
			swordBox = componentAsSwordBox;
		}
	}
	if (swordBox == nullptr)
		return;
	swordBox->ExtendSword();
}

void USwordItemComponent::Deactivate()
{
	Super::Activate();
	AController* controller = dynamic_cast<AController*>(this->GetOwner());
	if (controller == nullptr)
		return;
	APawn* pawn = controller->GetPawn();
	if (pawn == nullptr)
		return;
	TArray<UActorComponent*> pawnComponents = pawn->GetComponents();
	USwordBoxComponent* swordBox = nullptr;
	for (UActorComponent* component : pawnComponents)
	{
		USwordBoxComponent* componentAsSwordBox = dynamic_cast<USwordBoxComponent*>(component);
		if (componentAsSwordBox != nullptr)
		{
			swordBox = componentAsSwordBox;
		}
	}
	if (swordBox == nullptr)
		return;
	swordBox->RetractSword();
}