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

