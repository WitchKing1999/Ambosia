// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "AmbosiaPlayerController.h"
#include "BaseSavepoint.h"


// Sets default values
ABaseSavepoint::ABaseSavepoint()
{
	OnActorBeginOverlap.AddDynamic(this, &ABaseSavepoint::OnOverlapBegin);
}

void ABaseSavepoint::OnOverlapBegin(class AActor* OtherActor)
{
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn)
		return;
	AAmbosiaPlayerController* OtherPC = Cast<AAmbosiaPlayerController>(OtherPawn->GetController());
	if (!OtherPC)
		return;
	if (!OtherPC->GetSaveGameLoaded())
		return;
	OtherPC->SaveSaveGame();
}