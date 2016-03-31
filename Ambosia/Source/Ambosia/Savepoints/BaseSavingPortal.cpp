// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BaseSavingPortal.h"

ABaseSavingPortal::ABaseSavingPortal()
{
	
}

void ABaseSavingPortal::BeginPlay()
{
}

void ABaseSavingPortal::OnOverlapBegin(class AActor* OtherActor)
{
	Super::OnOverlapBegin(OtherActor);
	UGameplayStatics::OpenLevel(this, LOADINGSCREEN_PATH, true);
}

bool ABaseSavingPortal::SavePosition(UAmbosiaSaveGame* SaveGame)
{
	SaveGame->Spawnpoint = TargetTransform;
	SaveGame->LevelName = TargetWorldName;
	return true;
}