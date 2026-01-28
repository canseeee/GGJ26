// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShadowPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/ShadowAbilitySystemComponent.h"
#include "GAS/ShadowAttributeSet.h"

AShadowPlayerState::AShadowPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UShadowAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UShadowAttributeSet>(TEXT("AttributeSet"));

	//todo::5.4没这个函数
	// SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AShadowPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
