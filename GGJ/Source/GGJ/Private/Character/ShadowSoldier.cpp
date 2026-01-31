// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShadowSoldier.h"

#include "AbilitySystemComponent.h"
#include "GAS/ShadowAbilitySystemComponent.h"
#include "GAS/ShadowAttributeSet.h"


// Sets default values
AShadowSoldier::AShadowSoldier()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UShadowAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UShadowAttributeSet>("AttributeSet");
	
}

void AShadowSoldier::Die()
{
}

void AShadowSoldier::SetHit(bool Hit)
{
	bHit = Hit;
}

bool AShadowSoldier::GetHit()
{
	return bHit;
}

UCapsuleComponent* AShadowSoldier::GetWeaponCapsule_Implementation()
{
	return Weapon->GetCollisionCapsule();
}

void AShadowSoldier::InitAbilityActorInfo()
{
	InitialAttribute();
}

void AShadowSoldier::BeginPlay()
{
	Super::BeginPlay();
	InitialWeapons();
}


void AShadowSoldier::InitialWeapons()
{
	Weapon = GetWorld()->SpawnActor<AShadowWeapon>(WeaponActorClass);
	AttachWeaponToHand();
}

void AShadowSoldier::AttachWeaponToHand()
{
	if (!GetMesh() || !Weapon)
	{
		return;
	}

	UStaticMeshComponent* WeaponMeshComp = Weapon->FindComponentByClass<UStaticMeshComponent>();
	if (!WeaponMeshComp)
	{
		return;
	}

	static const FName WeaponHandleSocketName(TEXT("Handle"));

	const FTransform CharacterHandSocketWorld = GetMesh()->GetSocketTransform(WeaponHandleSocketName, RTS_World);
	const FTransform WeaponHandleInWeaponMesh = WeaponMeshComp->GetSocketTransform(WeaponHandleSocketName, RTS_Component);

	// 目标：WeaponMesh 的 Handle Socket 世界变换 == 角色手部 Socket 世界变换
	// DesiredWeaponMeshWorld * WeaponHandleInWeaponMesh == CharacterHandSocketWorld
	// => DesiredWeaponMeshWorld = CharacterHandSocketWorld * Inverse(WeaponHandleInWeaponMesh)
	const FTransform DesiredWeaponMeshWorld = WeaponHandleInWeaponMesh.Inverse() * CharacterHandSocketWorld;

	// 将 DesiredWeaponMeshWorld 转为 Actor 世界变换（考虑 WeaponMesh 相对 Actor 的变换）
	const FTransform WeaponMeshRelToActor = WeaponMeshComp->GetRelativeTransform();
	const FTransform DesiredActorWorld = WeaponMeshRelToActor.Inverse() * DesiredWeaponMeshWorld;

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, WeaponHandleSocketName);
	Weapon->SetActorTransform(DesiredActorWorld);
}
