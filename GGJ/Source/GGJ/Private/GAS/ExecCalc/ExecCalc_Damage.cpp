// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/ShadowAbilitySystemComponent.h"
#include "GAS/ShadowAttributeSet.h"

struct FShadowDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defence)
	FShadowDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UShadowAttributeSet, Strength, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UShadowAttributeSet, Defence, Source, true);
	}
};

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* SourceActor = SourceASC->GetOwner();
	AActor* TargetActor = TargetASC->GetOwner();

	if(TargetASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Status.Parry")))
	{
		FGameplayEventData ParrySuccessEventData;
		ParrySuccessEventData.EventTag = FGameplayTag::RequestGameplayTag("Battle.ParrySuccess");
		// 弹反成功标签发给目标
		ParrySuccessEventData.Instigator = SourceActor;
		ParrySuccessEventData.Target = TargetActor;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			TargetActor,
			ParrySuccessEventData.EventTag,
			ParrySuccessEventData
		);

		// 被弹反标签发给自己
		FGameplayEventData BlockedEventData;
		BlockedEventData.EventTag = FGameplayTag::RequestGameplayTag("Battle.ByBlocked");
		BlockedEventData.Instigator = SourceActor;
		BlockedEventData.Target = SourceActor;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			SourceActor,
			BlockedEventData.EventTag,
			BlockedEventData
		);
		
		const FGameplayModifierEvaluatedData EvaluatedData(
		UShadowAttributeSet::GetIncomingDamageAttribute(), 
		EGameplayModOp::Additive,
		0
		);
		OutExecutionOutput.AddOutputModifier(EvaluatedData);
		return;
	}
	if(TargetASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Status.Dodge")))
	{
		const FGameplayModifierEvaluatedData EvaluatedData(
		UShadowAttributeSet::GetIncomingDamageAttribute(), 
		EGameplayModOp::Additive,
		0
		);
		OutExecutionOutput.AddOutputModifier(EvaluatedData);
		return;
	}
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	float BaseDamage = Spec.GetSetByCallerMagnitude(FName("DamageValue"));

	//TODO::防御力减伤、穿甲计算
	
	const FGameplayModifierEvaluatedData EvaluatedData(
		UShadowAttributeSet::GetIncomingDamageAttribute(), 
		EGameplayModOp::Additive,
		BaseDamage
		);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
