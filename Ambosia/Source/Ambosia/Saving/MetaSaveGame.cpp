// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "MetaSaveGame.h"

UMetaSaveGame::UMetaSaveGame()
{
	int32 CurrentUserIndex = 1;
}

FString UMetaSaveGame::GetCurrentUserName()
{
	return "Slot" + FString::FromInt(CurrentUserIndex);
}
