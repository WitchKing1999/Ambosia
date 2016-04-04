// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "Saving/AmbosiaSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "BaseSavingPortal.h"

ABaseSavingPortal::ABaseSavingPortal()
{
	TargetWorldPath = FName();
	TargetTransform = FTransform();
}

void ABaseSavingPortal::OnOverlapBegin(class AActor* OtherActor)
{
	Super::OnOverlapBegin(OtherActor);
	UAmbosiaSaveGame* SaveGame = Cast<UAmbosiaSaveGame>(UGameplayStatics::LoadGameFromSlot("Ambosia", 0));
	if (SaveGame)
	{
		SaveGame->LevelName = TargetWorldPath;
		SaveGame->Spawnpoint = TargetTransform;
		if (UGameplayStatics::SaveGameToSlot(SaveGame, "Ambosia", 0))
		{
			UGameplayStatics::OpenLevel(this, LOADINGSCREEN_PATH, true);
		}
	}
}