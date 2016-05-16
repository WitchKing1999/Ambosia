// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "AmbosiaPlayerController.h"
#include "Saving/MetaSaveGame.h"
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
	if (this->GetWorld()->GetFirstPlayerController()->GetPawn() != OtherActor)
		return;
	UMetaSaveGame* MetaSave = Cast<UMetaSaveGame>(UGameplayStatics::LoadGameFromSlot("Meta", 0));
	if (!MetaSave)
		return;
	UAmbosiaSaveGame* SaveGame = Cast<UAmbosiaSaveGame>(UGameplayStatics::LoadGameFromSlot(MetaSave->GetCurrentUserName(),MetaSave->CurrentUserIndex));
	if (SaveGame)
	{
		SaveGame->LevelName = TargetWorldPath;
		SaveGame->Spawnpoint = TargetTransform;
		if (UGameplayStatics::SaveGameToSlot(SaveGame, MetaSave->GetCurrentUserName(), MetaSave->CurrentUserIndex))
		{
			UGameplayStatics::OpenLevel(this, LOADINGSCREEN_PATH, true);
		}
	}
}