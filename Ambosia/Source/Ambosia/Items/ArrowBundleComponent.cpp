// (C) Flumminard 2015

#include "Ambosia.h"
#include "ArrowBundleComponent.h"

UArrowBundleComponent::UArrowBundleComponent()
{
	Name = "Arrow bundle";
	Description = "A bundle of arrows to be used with a bow";
	bStackable = true;
	ArrowClass = nullptr;
}

UClass* UArrowBundleComponent::GetArrowClass()
{
	return this->ArrowClass;
}