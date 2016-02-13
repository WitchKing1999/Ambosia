// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "DamageTypes/AmbosiaDamageType.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameplaySystemComponent.h"


// Sets default values for this component's properties
UGameplaySystemComponent::UGameplaySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TimeToNextRegen = 1;
	HealthPoints = 200;
	HealthPointsLimit = 200;
	AttackPoints = 100;
	Mana = 0;
	ManaLimit = 0;
	MagicalAttackPoints = 0;
	ManaRegenerationPerSec = 0;
	Weapon = nullptr;
	Armor = nullptr;
	Potion = nullptr;
	ArrowBundle = nullptr;
	FirstRing = nullptr;
	SecondRing = nullptr;
	Amulet = nullptr;
}

UItemComponent* UGameplaySystemComponent::CreateAndAddItem(UClass* ItemClass)
{
	UClass * baseClass = FindObject<UClass>(ANY_PACKAGE, TEXT("ActorComponent"));
	if (ItemClass->IsChildOf(baseClass))
	{
		UItemComponent* NewItem = NewObject<UItemComponent>(this, ItemClass);
		if (!NewItem)
		{
			return NULL;
		}
		//~~~~~~~~~~~~~
		NewItem->RegisterComponent();        //You must ConstructObject with a valid Outer that has world, see above    
		NewItem->AttachTo(this);
		return NewItem;
	}
	else
		return NULL;
}

float UGameplaySystemComponent::TakeDamage(float DamageAmount, UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser)
{
	UAmbosiaDamageType* AmbosiaDamageType = dynamic_cast<UAmbosiaDamageType*>(DamageType);

	if (AmbosiaDamageType != nullptr)
	{
		if (AmbosiaDamageType->IsMagical())
		{
			if (this->GetArmor() != nullptr)
				DamageAmount = this->GetArmor()->ModifyMagicalAttackPoints(DamageAmount);
		}
		else
		{
			if (this->GetArmor() != nullptr)
				DamageAmount = this->GetArmor()->ModifyAttackPoints(DamageAmount);
		}
	}

	this->AffectHealthPoints(DamageAmount * -1);

	return DamageAmount;
}

void UGameplaySystemComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->TimeToNextRegen -= DeltaTime;
	if (this->TimeToNextRegen <= 0)
	{
		this->SetMana(this->GetMana() + GetManaRegenerationPerSec());
		this->TimeToNextRegen = 1;
	}
}

void UGameplaySystemComponent::OnChildDetached(USceneComponent* ChildComponent)

{
	if (ChildComponent == this->GetWeapon())
	{
		this->Weapon = nullptr;
	}
	else if (ChildComponent == this->GetArmor())
	{
		this->Armor = nullptr;
	}
	else if (ChildComponent == this->GetPotion())
	{
		this->Potion = nullptr;
	}
	else if (ChildComponent == this->GetArrowBundle())
	{
		this->ArrowBundle = nullptr;
	}
	else if (ChildComponent == this->GetFirstRing())
	{
		this->FirstRing = nullptr;
	}
	else if (ChildComponent == this->GetSecondRing())
	{
		this->SecondRing = nullptr;
	}
	else if (ChildComponent == this->GetAmulet())
	{
		this->Amulet = nullptr;
	}
}

float UGameplaySystemComponent::GetHealthPoints()
{
	return this->HealthPoints;
}

void UGameplaySystemComponent::SetHealthPoints(float NewHealthPoints)
{
	if (NewHealthPoints > this->HealthPointsLimit)
	{
		this->HealthPoints = this->HealthPointsLimit;
	}
	else if (NewHealthPoints <= 0)
	{
		AController* OwnerAsController = dynamic_cast<AController*>(this->GetOwner());
		if (OwnerAsController != nullptr)
		{
			APawn* Pawn = OwnerAsController->GetPawn();
			Pawn->Destroy();
		}
		else
		{
			this->GetOwner()->Destroy();
		}
	}
	else
	{
		this->HealthPoints = NewHealthPoints;
	}
	FString DebugString = FString::FromInt((int) this->HealthPoints) + " / " + FString::FromInt((int) this->HealthPointsLimit);
	UKismetSystemLibrary::PrintString(this, DebugString);
}

void UGameplaySystemComponent::AffectHealthPoints(float Delta)
{
	UKismetSystemLibrary::PrintString(this, FString::FromInt((int) Delta) + " !");
	this->SetHealthPoints(this->GetHealthPoints() + Delta);
}

float UGameplaySystemComponent::GetHealthPointsLimit()
{
	return this->HealthPointsLimit;
}

float UGameplaySystemComponent::GetEffectiveHealthPointsLimit()
{
	float ProperHealthPointsLimit = this->HealthPointsLimit;
	if (this->FirstRing != nullptr)
	{
		ProperHealthPointsLimit = this->FirstRing->ModifyHealthPointsLimit(ProperHealthPointsLimit);
	}
	if (this->SecondRing != nullptr)
	{
		ProperHealthPointsLimit = this->SecondRing->ModifyHealthPointsLimit(ProperHealthPointsLimit);
	}
	if (this->Amulet != nullptr)
	{
		ProperHealthPointsLimit = this->Amulet->ModifyHealthPointsLimit(ProperHealthPointsLimit);
	}
	return ProperHealthPointsLimit;
}

void UGameplaySystemComponent::SetHealthPointsLimit(float NewHealthPointsLimit)
{
	this->HealthPointsLimit = NewHealthPointsLimit;
	if (this->HealthPoints > this->HealthPointsLimit)
		this->HealthPoints = this->HealthPointsLimit;
}

void UGameplaySystemComponent::AffectHealthPointsLimit(float Delta)
{
	this->SetHealthPointsLimit(this->GetHealthPointsLimit() + Delta);
}

float UGameplaySystemComponent::GetRawAttackPoints()
{
	return this->AttackPoints;
}

float UGameplaySystemComponent::GetAttackPoints()
{
	float ProperAttackPoints = this->AttackPoints;
	if (this->FirstRing != nullptr)
	{
		ProperAttackPoints = this->FirstRing->ModifyAttackPoints(ProperAttackPoints);
	}
	if (this->SecondRing != nullptr)
	{
		ProperAttackPoints = this->SecondRing->ModifyAttackPoints(ProperAttackPoints);
	}
	if (this->Amulet != nullptr)
	{
		ProperAttackPoints = this->Amulet->ModifyAttackPoints(ProperAttackPoints);
	}
	if (this->Weapon != nullptr)
	{
		ProperAttackPoints = this->Weapon->ModifyAttackPoints(ProperAttackPoints);
	}
	return ProperAttackPoints;
}

void UGameplaySystemComponent::SetAttackPoints(float NewAttackPoints)
{
	this->AttackPoints = NewAttackPoints;
}

void UGameplaySystemComponent::AffectAttackPoints(float Delta)
{
	this->SetAttackPoints(this->AttackPoints + Delta);
}

float UGameplaySystemComponent::GetRawMagicalAttackPoints()
{
	return this->MagicalAttackPoints;
}

float UGameplaySystemComponent::GetMagicalAttackPoints()
{
	float ProperMagicalAttackPoints = this->MagicalAttackPoints;
	if (this->FirstRing != nullptr)
	{
		ProperMagicalAttackPoints = this->FirstRing->ModifyMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->SecondRing != nullptr)
	{
		ProperMagicalAttackPoints = this->SecondRing->ModifyMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->Amulet != nullptr)
	{
		ProperMagicalAttackPoints = this->Amulet->ModifyMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->Weapon != nullptr)
	{
		ProperMagicalAttackPoints = this->Weapon->ModifyMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	return ProperMagicalAttackPoints;
}

void UGameplaySystemComponent::SetMagicalAttackPoints(float NewMagicalAttackPoints)
{
	this->MagicalAttackPoints = NewMagicalAttackPoints;
}

void UGameplaySystemComponent::AffectMagicalAttackPoints(float Delta)
{
	this->SetMagicalAttackPoints(this->MagicalAttackPoints + Delta);
}

float UGameplaySystemComponent::GetMana()
{
	return this->Mana;
}

void UGameplaySystemComponent::SetMana(float NewMana)
{
	if (NewMana <= this->ManaLimit)
		this->Mana = NewMana;
	else
		this->Mana = this->ManaLimit;
}

void UGameplaySystemComponent::AffectMana(float Delta)
{
	this->SetMana(this->GetMana() + Delta);
}

float UGameplaySystemComponent::GetRawManaLimit()
{
	return this->ManaLimit;
}

float UGameplaySystemComponent::GetManaLimit()
{
	float ProperManaLimit = this->ManaLimit;
	if (this->FirstRing != nullptr)
	{
		ProperManaLimit = this->FirstRing->ModifyManaLimit(ProperManaLimit);
	}
	if (this->SecondRing != nullptr)
	{
		ProperManaLimit = this->SecondRing->ModifyManaLimit(ProperManaLimit);
	}
	if (this->Amulet != nullptr)
	{
		ProperManaLimit = this->Amulet->ModifyManaLimit(ProperManaLimit);
	}
	return ProperManaLimit;
}

void UGameplaySystemComponent::SetManaLimit(float NewManaLimit)
{
	this->ManaLimit = NewManaLimit;
}

void UGameplaySystemComponent::AffectManaLimit(float Delta)
{
	this->SetManaLimit(this->ManaLimit + Delta);
}

float UGameplaySystemComponent::GetRawManaRegenerationPerSec()
{
	return this->ManaRegenerationPerSec;
}

float UGameplaySystemComponent::GetManaRegenerationPerSec()
{
	float ProperManaRegeneration = this->ManaRegenerationPerSec;
	if (this->FirstRing != nullptr)
	{
		ProperManaRegeneration = this->FirstRing->ModifyManaRegeneration(ProperManaRegeneration);
	}
	if (this->SecondRing != nullptr)
	{
		ProperManaRegeneration = this->SecondRing->ModifyManaRegeneration(ProperManaRegeneration);
	}
	if (this->Amulet != nullptr)
	{
		ProperManaRegeneration = this->Amulet->ModifyManaRegeneration(ProperManaRegeneration);
	}
	return ProperManaRegeneration;
}

void UGameplaySystemComponent::SetManaRegenerationPerSec(float NewManaReg)
{
	this->ManaRegenerationPerSec = NewManaReg;
}

void UGameplaySystemComponent::AffectManaRegeneration(float Delta)
{
	this->SetManaRegenerationPerSec(this->ManaRegenerationPerSec + Delta);
}

UWeaponComponent* UGameplaySystemComponent::GetWeapon()
{
	return this->Weapon;
}

bool UGameplaySystemComponent::SetWeapon(UWeaponComponent* NewWeapon)
{
	if ((NewWeapon->GetAttachParent() == this) | (NewWeapon == nullptr))
	{
		this->Weapon = NewWeapon;
		return true;
	}
	else
	{
		return false;
	}
}

UArmorComponent* UGameplaySystemComponent::GetArmor()
{
	return this->Armor;
}

bool UGameplaySystemComponent::SetArmor(UArmorComponent* NewArmor)
{
	if ((NewArmor->GetAttachParent() == this) | (NewArmor == nullptr))
	{
		this->Armor = NewArmor;
		return true;
	}
	else
	{
		return false;
	}
}

UPotionComponent* UGameplaySystemComponent::GetPotion()
{
	return this->Potion;
}

bool UGameplaySystemComponent::SetPotion(UPotionComponent* NewPotion)
{
	if ((NewPotion->GetAttachParent() == this) | (NewPotion == nullptr))
	{
		this->Potion = NewPotion;
		return true;
	}
	else
	{
		return false;
	}
}

UArrowBundleComponent* UGameplaySystemComponent::GetArrowBundle()
{
	return this->ArrowBundle;
}

bool UGameplaySystemComponent::SetArrowBundle(UArrowBundleComponent* NewArrowBundle)
{
	if ((NewArrowBundle->GetAttachParent() == this) | (NewArrowBundle == nullptr))
	{
		this->ArrowBundle = NewArrowBundle;
		return true;
	}
	else
	{
		return false;
	}
}

URingComponent* UGameplaySystemComponent::GetFirstRing()
{
	return this->FirstRing;
}

bool UGameplaySystemComponent::SetFirstRing(URingComponent* NewRing)
{
	if ((NewRing->GetAttachParent() == this) | (NewRing == nullptr))
	{
		this->FirstRing = NewRing;
		return true;
	}
	else
	{
		return false;
	}
}

URingComponent* UGameplaySystemComponent::GetSecondRing()
{
	return this->SecondRing;
}

bool UGameplaySystemComponent::SetSecondRing(URingComponent* NewRing)
{
	if ((NewRing->GetAttachParent() == this) | (NewRing == nullptr))
	{
		this->SecondRing = NewRing;
		return true;
	}
	else
	{
		return false;
	}
}

UAmuletComponent* UGameplaySystemComponent::GetAmulet()
{
	return this->Amulet;
}

bool UGameplaySystemComponent::SetAmulet(UAmuletComponent* NewAmulet)
{
	if ((NewAmulet->GetAttachParent() == this) | (NewAmulet == nullptr))
	{
		this->Amulet = NewAmulet;
		return true;
	}
	else
	{
		return false;
	}
}