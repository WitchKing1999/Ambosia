// (C) Flumminard 2015

#include "Ambosia.h"
#include "GameplaySystemComponent.h"
#include "Pawns/Projectile.h"
#include "WeaponComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Name = FText::FromString("Weapon");
	Description = FText::FromString("Hurts everything!");
	ItemType = EItemType::VE_Weapon;
	AttackFactor = 1.0;
	ManaCost = 0;
	MagicalAttackFactor = 1.0;
	CriticalDamageChance = 0;
	ArrowBundleCosts = 0;
}

AActor* UWeaponComponent::PlotHitLine(float LineLength, AController* Instigator, TSubclassOf<UDamageType> DamageType, UGameplaySystemComponent* GameplaySystem)
{
	if (this->GetOwner() == nullptr)
		return nullptr;
	AController* OwnerAsController = dynamic_cast<AController*>(this->GetOwner());
	if (OwnerAsController == nullptr)
		return nullptr;
	if (OwnerAsController->GetPawn() == nullptr)
		return nullptr;

	FVector TraceStart = OwnerAsController->GetPawn()->GetActorLocation();
	FVector TraceEnd = OwnerAsController->GetPawn()->GetActorLocation();
	{
		FRotator Rotation = OwnerAsController->GetControlRotation();
		TraceEnd += Rotation.RotateVector(FVector(LineLength, 0, 0));
	}

	// Setup the trace query  
	FCollisionQueryParams TraceParams = FCollisionQueryParams(false);
	TraceParams.AddIgnoredActor(OwnerAsController->GetPawn());
	TraceParams.bTraceAsyncScene = true;
	FCollisionResponseParams CollisionParams = FCollisionResponseParams();

	FHitResult HitResult;
	if (this->GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_GameTraceChannel1, TraceParams, CollisionParams))
	{
		if (GameplaySystem == nullptr)
			return nullptr;
		APawn* TargetAsPawn = dynamic_cast<APawn*>(HitResult.Actor.Get());
		if (TargetAsPawn)
		{
			TargetAsPawn->GetController()->TakeDamage(GameplaySystem->GetAttackPoints(), FDamageEvent(DamageType), Instigator, Instigator->GetPawn());
		}
		return HitResult.GetActor();
	}
	else
	{
		return nullptr;
	}
}

AActor* UWeaponComponent::SpawnProjectile(UClass* ProjectileClass, FVector RelativeSpawnLocation, AActor* LaunchingActor, UGameplaySystemComponent* GameplaySystem)
{
	FTransform SpawnTransform;
	{
		FRotator SpawnRotation = LaunchingActor->GetActorRotation();
		FVector SpawnLocation = LaunchingActor->GetActorLocation();
		SpawnLocation += SpawnRotation.RotateVector(RelativeSpawnLocation);
		SpawnTransform = FTransform(SpawnRotation, SpawnLocation);
	}

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.Owner = this->GetOwner();

	AActor* SpawnedActor = this->GetWorld()->SpawnActor(ProjectileClass, &SpawnTransform, SpawnParameters);
	AProjectile* Projectile = dynamic_cast<AProjectile*>(SpawnedActor);

	if (Projectile != nullptr)
	{
		Projectile->SetAttackPoints(GameplaySystem->GetAttackPoints());
	}

	return SpawnedActor;
}

bool UWeaponComponent::AreManaCostsSatisfied(UGameplaySystemComponent* GameplaySystem)
{
	if (GameplaySystem == nullptr)
		return false;
	if (GameplaySystem->GetMana() < this->GetManaCost())
		return false;
	return true;
}

bool UWeaponComponent::ApplyManaCosts(UGameplaySystemComponent* GameplaySystem)
{
	if (this->AreManaCostsSatisfied(GameplaySystem))
	{
		GameplaySystem->AffectMana(this->GetManaCost() * -1);
		return true;
	}
	else
		return false;
}

bool UWeaponComponent::AreArrowBundleCostsSatisfied(UGameplaySystemComponent* GameplaySystem)
{
	UArrowBundleComponent* ArrowBundle = GameplaySystem->GetArrowBundle();
	if (ArrowBundle == nullptr)
		return false;
	if (this->GetAcceptedArrowBundles().Find(ArrowBundle->GetClass()) == INDEX_NONE)
		return false;
	if (ArrowBundle->GetStackSize() < this->GetArrowBundleCosts())
		return false;
	return true;
}

bool UWeaponComponent::ApplyArrowBundleCosts(UGameplaySystemComponent* GameplaySystem)
{
	if (this->AreArrowBundleCostsSatisfied(GameplaySystem))
	{
		GameplaySystem->GetArrowBundle()->AffectStackSize(this->GetArrowBundleCosts() * -1);
		return true;
	}
	else
	{
		return false;
	}
}

float UWeaponComponent::ModifyAttackPoints_Implementation(float AttackPoints)
{
	float CriticalFactor = 1;
	float RandomNumber = FMath::FRandRange(0.0f, 1.0f);
	if (RandomNumber <= this->GetCriticalDamageChance())
	{
		CriticalFactor = 2;
	}

	return AttackPoints * this->AttackFactor * CriticalFactor;
}

float UWeaponComponent::ModifyMagicalAttackPoints_Implementation(float MagicalAttackPoints)
{
	return MagicalAttackPoints * this->MagicalAttackFactor;
}

float UWeaponComponent::GetAttackFactor()
{
	return this->AttackFactor;
}

float UWeaponComponent::GetManaCost()
{
	return this->ManaCost;
}

float UWeaponComponent::GetMagicalAttackFactor()
{
	return this->MagicalAttackFactor;
}

float UWeaponComponent::GetCriticalDamageChance()
{
	return this->CriticalDamageChance;
}

int32 UWeaponComponent::GetArrowBundleCosts()
{
	return this->ArrowBundleCosts;
}

TArray<UClass*> UWeaponComponent::GetAcceptedArrowBundles()
{
	return this->AcceptedArrowBundles;
}