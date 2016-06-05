// (C) Flumminard 2015-2016

#include "Ambosia.h"
#include "DamageTypes/AmbosiaDamageType.h"
#include "GameplaySystemComponent.h"


// Sets default values for this component's properties
UGameplaySystemComponent::UGameplaySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OnChildAttachedDispatcher = FChildAttachedDelegate();
	OnChildDetachedDispatcher = FChildDetachedDelegate();
	OnDamageTook = FDamageTookDelegate();

	TimeToNextRegen = 1;
	bLoadGameOverScreenOnDying = false;
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
		NewItem->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		return NewItem;
	}
	else
		return NULL;
}

float UGameplaySystemComponent::TakeDamage(float DamageAmount, UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser)
{
	UAmbosiaDamageType* AmbosiaDamageType = dynamic_cast<UAmbosiaDamageType*>(DamageType);

	float RawDamageAmount = DamageAmount;

	if (AmbosiaDamageType != nullptr)
	{
		if (AmbosiaDamageType->IsMagical())
		{
			if (this->GetArmor() != nullptr)
				DamageAmount = this->GetArmor()->ModifyInfightMagicalAttackPoints(DamageAmount);
		}
		else
		{
			if (this->GetArmor() != nullptr)
				DamageAmount = this->GetArmor()->ModifyInfightAttackPoints(DamageAmount);
		}
	}

	this->OnDamageTook.Broadcast(RawDamageAmount, DamageAmount, DamageType, DamageCauser);
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

void UGameplaySystemComponent::OnChildAttached(USceneComponent* ChildComponent)
{
	Super::OnChildAttached(ChildComponent);
	this->OnChildAttachedDispatcher.Broadcast(ChildComponent);
}

void UGameplaySystemComponent::OnChildDetached(USceneComponent* ChildComponent)
{
	Super::OnChildDetached(ChildComponent);
	this->OnChildDetachedDispatcher.Broadcast(ChildComponent);
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

void UGameplaySystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TArray<USceneComponent*> Items;
	this->GetChildrenComponents(true, Items);
	for (USceneComponent* Item : Items)
	{
		Item->DestroyComponent();
	}
}

float UGameplaySystemComponent::GetHealthPoints()
{
	return this->HealthPoints;
}

void UGameplaySystemComponent::SetHealthPoints(float NewHealthPoints)
{
	if (NewHealthPoints > this->GetInfightHealthPointsLimit())
	{
		this->HealthPoints = this->GetInfightHealthPointsLimit();
	}
	else if (NewHealthPoints <= 0)
	{
		AController* OwnerAsController = dynamic_cast<AController*>(this->GetOwner());
		if (bLoadGameOverScreenOnDying)
		{
			UGameplayStatics::OpenLevel(this, "/Game/Menues/GameOverScreen", true);
		}
		else
		{
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
	}
	else
	{
		this->HealthPoints = NewHealthPoints;
	}
}

void UGameplaySystemComponent::AffectHealthPoints(float Delta)
{
	this->SetHealthPoints(this->GetHealthPoints() + Delta);
}

float UGameplaySystemComponent::GetHealthPointsLimit()
{
	return this->HealthPointsLimit;
}

float UGameplaySystemComponent::GetInfightHealthPointsLimit()
{
	float ProperHealthPointsLimit = this->HealthPointsLimit;
	if (this->FirstRing != nullptr)
	{
		ProperHealthPointsLimit = this->FirstRing->ModifyInfightHealthPointsLimit(ProperHealthPointsLimit);
	}
	if (this->SecondRing != nullptr)
	{
		ProperHealthPointsLimit = this->SecondRing->ModifyInfightHealthPointsLimit(ProperHealthPointsLimit);
	}
	if (this->Amulet != nullptr)
	{
		ProperHealthPointsLimit = this->Amulet->ModifyInfightHealthPointsLimit(ProperHealthPointsLimit);
	}
	return ProperHealthPointsLimit;
}

float UGameplaySystemComponent::GetDisplayHealthPointsLimit()
{
	float ProperHealthPointsLimit = this->HealthPointsLimit;
	if (this->FirstRing != nullptr)
	{
		ProperHealthPointsLimit = this->FirstRing->ModifyDisplayHealthPointsLimit(ProperHealthPointsLimit);
	}
	if (this->SecondRing != nullptr)
	{
		ProperHealthPointsLimit = this->SecondRing->ModifyDisplayHealthPointsLimit(ProperHealthPointsLimit);
	}
	if (this->Amulet != nullptr)
	{
		ProperHealthPointsLimit = this->Amulet->ModifyDisplayHealthPointsLimit(ProperHealthPointsLimit);
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

float UGameplaySystemComponent::GetAttackPoints()
{
	return this->AttackPoints;
}

float UGameplaySystemComponent::GetInfightAttackPoints()
{
	float ProperAttackPoints = this->AttackPoints;
	if (this->FirstRing != nullptr)
	{
		ProperAttackPoints = this->FirstRing->ModifyInfightAttackPoints(ProperAttackPoints);
	}
	if (this->SecondRing != nullptr)
	{
		ProperAttackPoints = this->SecondRing->ModifyInfightAttackPoints(ProperAttackPoints);
	}
	if (this->Amulet != nullptr)
	{
		ProperAttackPoints = this->Amulet->ModifyInfightAttackPoints(ProperAttackPoints);
	}
	if (this->Weapon != nullptr)
	{
		ProperAttackPoints = this->Weapon->ModifyInfightAttackPoints(ProperAttackPoints);
	}
	return ProperAttackPoints;
}

float UGameplaySystemComponent::GetDisplayAttackPoints()
{
	float ProperAttackPoints = this->AttackPoints;
	if (this->FirstRing != nullptr)
	{
		ProperAttackPoints = this->FirstRing->ModifyDisplayAttackPoints(ProperAttackPoints);
	}
	if (this->SecondRing != nullptr)
	{
		ProperAttackPoints = this->SecondRing->ModifyDisplayAttackPoints(ProperAttackPoints);
	}
	if (this->Amulet != nullptr)
	{
		ProperAttackPoints = this->Amulet->ModifyDisplayAttackPoints(ProperAttackPoints);
	}
	if (this->Weapon != nullptr)
	{
		ProperAttackPoints = this->Weapon->ModifyDisplayAttackPoints(ProperAttackPoints);
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

float UGameplaySystemComponent::GetMagicalAttackPoints()
{
	return this->MagicalAttackPoints;
}

float UGameplaySystemComponent::GetInfightMagicalAttackPoints()
{
	float ProperMagicalAttackPoints = this->MagicalAttackPoints;
	if (this->FirstRing != nullptr)
	{
		ProperMagicalAttackPoints = this->FirstRing->ModifyInfightMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->SecondRing != nullptr)
	{
		ProperMagicalAttackPoints = this->SecondRing->ModifyInfightMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->Amulet != nullptr)
	{
		ProperMagicalAttackPoints = this->Amulet->ModifyInfightMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->Weapon != nullptr)
	{
		ProperMagicalAttackPoints = this->Weapon->ModifyInfightMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	return ProperMagicalAttackPoints;
}

float UGameplaySystemComponent::GetDisplayMagicalAttackPoints()
{
	float ProperMagicalAttackPoints = this->MagicalAttackPoints;
	if (this->FirstRing != nullptr)
	{
		ProperMagicalAttackPoints = this->FirstRing->ModifyDisplayMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->SecondRing != nullptr)
	{
		ProperMagicalAttackPoints = this->SecondRing->ModifyDisplayMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->Amulet != nullptr)
	{
		ProperMagicalAttackPoints = this->Amulet->ModifyDisplayMagicalAttackPoints(ProperMagicalAttackPoints);
	}
	if (this->Weapon != nullptr)
	{
		ProperMagicalAttackPoints = this->Weapon->ModifyDisplayMagicalAttackPoints(ProperMagicalAttackPoints);
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
	if (NewMana <= this->GetManaLimit())
		this->Mana = NewMana;
	else
		this->Mana = this->GetManaLimit();
}

void UGameplaySystemComponent::AffectMana(float Delta)
{
	this->SetMana(this->GetMana() + Delta);
}

float UGameplaySystemComponent::GetManaLimit()
{
	return this->ManaLimit;
}

float UGameplaySystemComponent::GetInfightManaLimit()
{
	float ProperManaLimit = this->ManaLimit;
	if (this->FirstRing != nullptr)
	{
		ProperManaLimit = this->FirstRing->ModifyInfightManaLimit(ProperManaLimit);
	}
	if (this->SecondRing != nullptr)
	{
		ProperManaLimit = this->SecondRing->ModifyInfightManaLimit(ProperManaLimit);
	}
	if (this->Amulet != nullptr)
	{
		ProperManaLimit = this->Amulet->ModifyInfightManaLimit(ProperManaLimit);
	}
	return ProperManaLimit;
}

float UGameplaySystemComponent::GetDisplayManaLimit()
{
	float ProperManaLimit = this->ManaLimit;
	if (this->FirstRing != nullptr)
	{
		ProperManaLimit = this->FirstRing->ModifyDisplayManaLimit(ProperManaLimit);
	}
	if (this->SecondRing != nullptr)
	{
		ProperManaLimit = this->SecondRing->ModifyDisplayManaLimit(ProperManaLimit);
	}
	if (this->Amulet != nullptr)
	{
		ProperManaLimit = this->Amulet->ModifyDisplayManaLimit(ProperManaLimit);
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

float UGameplaySystemComponent::GetManaRegenerationPerSec()
{
	return this->ManaRegenerationPerSec;
}

float UGameplaySystemComponent::GetInfightManaRegenerationPerSec()
{
	float ProperManaRegeneration = this->ManaRegenerationPerSec;
	if (this->FirstRing != nullptr)
	{
		ProperManaRegeneration = this->FirstRing->ModifyInfightManaRegeneration(ProperManaRegeneration);
	}
	if (this->SecondRing != nullptr)
	{
		ProperManaRegeneration = this->SecondRing->ModifyInfightManaRegeneration(ProperManaRegeneration);
	}
	if (this->Amulet != nullptr)
	{
		ProperManaRegeneration = this->Amulet->ModifyInfightManaRegeneration(ProperManaRegeneration);
	}
	return ProperManaRegeneration;
}

float UGameplaySystemComponent::GetDisplayManaRegenerationPerSec()
{
	float ProperManaRegeneration = this->ManaRegenerationPerSec;
	if (this->FirstRing != nullptr)
	{
		ProperManaRegeneration = this->FirstRing->ModifyDisplayManaRegeneration(ProperManaRegeneration);
	}
	if (this->SecondRing != nullptr)
	{
		ProperManaRegeneration = this->SecondRing->ModifyDisplayManaRegeneration(ProperManaRegeneration);
	}
	if (this->Amulet != nullptr)
	{
		ProperManaRegeneration = this->Amulet->ModifyDisplayManaRegeneration(ProperManaRegeneration);
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
	if (NewWeapon == nullptr)
	{
		this->Weapon = nullptr;
		return true;
	}
	else if (NewWeapon->GetAttachParent() == this)
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
	if (NewArmor == nullptr)
	{
		this->Armor = nullptr;
		return true;
	}
	else if (NewArmor->GetAttachParent() == this)
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
	if (NewPotion == nullptr)
	{
		this->Potion = nullptr;
		return true;
	}
	else if (NewPotion->GetAttachParent() == this)
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
	if (NewArrowBundle == nullptr)
	{
		this->ArrowBundle = nullptr;
		return true;
	}
	else if (NewArrowBundle->GetAttachParent() == this)
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
	if (NewRing == nullptr)
	{
		this->FirstRing = nullptr;
		this->AffectHealthPoints(0);	// Updates our health points and mana,
		this->AffectMana(0);			// in case the new limit is higher than the actual value
		return true;
	}
	else if (NewRing->GetAttachParent() == this)
	{
		this->FirstRing = NewRing;
		if (this->FirstRing == this->SecondRing)
		{
			this->SecondRing = nullptr;
		}
		this->AffectHealthPoints(0);	// Updates our health points and mana,
		this->AffectMana(0);			// in case the new limit is higher than the actual value
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
	if (NewRing == nullptr)
	{
		this->SecondRing = nullptr;
		this->AffectHealthPoints(0);	// Updates our health points and mana,
		this->AffectMana(0);			// in case the new limit is higher than the actual value
		return true;
	}
	else if (NewRing->GetAttachParent() == this)
	{
		this->SecondRing = NewRing;
		if (this->FirstRing == this->SecondRing)
		{
			this->FirstRing = nullptr;
		}
		this->AffectHealthPoints(0);	// Updates our health points and mana,
		this->AffectMana(0);			// in case the new limit is higher than the actual value
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
	if (NewAmulet == nullptr)
	{
		this->Amulet = nullptr;
		this->AffectHealthPoints(0);	// Updates our health points and mana,
		this->AffectMana(0);			// in case the new limit is higher than the actual value
		return true;
	}
	else if (NewAmulet->GetAttachParent() == this)
	{
		this->Amulet = NewAmulet;
		this->AffectHealthPoints(0);	// Updates our health points and mana,
		this->AffectMana(0);			// in case the new limit is higher than the actual value
		return true;
	}
	else
	{
		return false;
	}
}