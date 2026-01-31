// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/ShadowMeleeAttackAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UShadowMeleeAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UShadowMeleeAttackAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

UCapsuleComponent* UShadowMeleeAttackAbility::GetCapsuleComponent()
{
	if(ICombatInterface* CI = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		return CI->GetWeaponCapsule();
	}
	return nullptr;
}

void UShadowMeleeAttackAbility::CauseDamage(AActor* TargetActor)
{
	if (!TargetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("UShadowMeleeAttackAbility::CauseDamage: TargetActor is null"));
		return;
	}

	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
	if (!SourceASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("UShadowMeleeAttackAbility::CauseDamage: Source AbilitySystemComponent is null"));
		return;
	}

	if (!DamageEffectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UShadowMeleeAttackAbility::CauseDamage: DamageEffectClass is not set"));
		return;
	}

	FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
	ContextHandle.AddSourceObject(SourceASC);
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.f, ContextHandle);

	if (!SpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UShadowMeleeAttackAbility::CauseDamage: Failed to create GameplayEffectSpec"));
		return;
	}

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("UShadowMeleeAttackAbility::CauseDamage: Target Actor has no AbilitySystemComponent"));
		return;
	}

	UAbilitySystemBlueprintLibrary::AssignSetByCallerMagnitude(SpecHandle, "DamageValue", DamageValue);
	UAbilitySystemBlueprintLibrary::AssignSetByCallerMagnitude(SpecHandle, "ArmorPiercing", ArmorPiercing);

	SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
}
