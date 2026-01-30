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
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.AddSourceObject(GetAbilitySystemComponentFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(DamageEffectClass, 1.f, ContextHandle);

	UAbilitySystemBlueprintLibrary::AssignSetByCallerMagnitude(SpecHandle, "DamageValue", DamageValue);
	UAbilitySystemBlueprintLibrary::AssignSetByCallerMagnitude(SpecHandle, "ArmorPiercing", ArmorPiercing);

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}
