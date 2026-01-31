// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShadowBoss.h"
#include "GAS/ShadowAbilitySystemComponent.h"
#include "GAS/ShadowAttributeSet.h"

AShadowBoss::AShadowBoss()
{
	PrimaryActorTick.bCanEverTick = true;
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
    AbilitySystemComponent = CreateDefaultSubobject<UShadowAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
    AttributeSet = CreateDefaultSubobject<UShadowAttributeSet>("AttributeSet");
}

void AShadowBoss::Die_Implementation()
{
	OnDie();
}

void AShadowBoss::OnDie_Implementation()
{
}
