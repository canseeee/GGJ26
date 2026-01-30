// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ShadowAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"

void UShadowAbilitySystemLibrary::AddGameplayTagToASC(UAbilitySystemComponent* ASC, const FGameplayTag GameplayTag)
{
	ASC->AddLooseGameplayTag(GameplayTag);
}

void UShadowAbilitySystemLibrary::RemoveGameplayTagFromASC(UAbilitySystemComponent* ASC, const FGameplayTag GameplayTag)
{
	ASC->RemoveLooseGameplayTag(GameplayTag);
}


void UShadowAbilitySystemLibrary::RemoveAllLooseGameplayTagFromASC(UAbilitySystemComponent* ASC, const FGameplayTag GameplayTag)
{
	ASC->SetLooseGameplayTagCount(GameplayTag,0);
}
