// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "AmbosiaDamageType.h"

UAmbosiaDamageType::UAmbosiaDamageType()
{
	bMagical = false;
}

bool UAmbosiaDamageType::IsMagical()
{
	return this->bMagical;
}