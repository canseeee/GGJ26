// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ExecCalc/ExecCalc_EnergyGlobeCalc.h"

#include "GAS/ShadowAbilitySystemComponent.h"
#include "GAS/ShadowAttributeSet.h"

struct FShadowEnergyStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(EnergyWhite)
	DECLARE_ATTRIBUTE_CAPTUREDEF(EnergyGreen)
	DECLARE_ATTRIBUTE_CAPTUREDEF(EnergyRed)
	FShadowEnergyStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UShadowAttributeSet, EnergyWhite, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UShadowAttributeSet, EnergyGreen, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UShadowAttributeSet, EnergyRed, Source, true);
	}
};

void UExecCalc_EnergyGlobeCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UShadowAbilitySystemComponent* ShadowSourceASC = Cast<UShadowAbilitySystemComponent>(SourceASC);
	if(ShadowSourceASC->EnergyGlobeArray.Num()>5)
	{
		if(ShadowSourceASC->EnergyGlobeArray[0] == EEnergyGlobeClass::Green)
		{
			const FGameplayModifierEvaluatedData EvaluatedData(
			UShadowAttributeSet::GetGreenEnergyCostAttribute(), 
			EGameplayModOp::Additive,
			1
		);
			OutExecutionOutput.AddOutputModifier(EvaluatedData);
			return;
		}
		if(ShadowSourceASC->EnergyGlobeArray[0] == EEnergyGlobeClass::White)
		{
			const FGameplayModifierEvaluatedData EvaluatedData(
			UShadowAttributeSet::GetWhiteEnergyCostAttribute(), 
			EGameplayModOp::Additive,
			1
		);
			OutExecutionOutput.AddOutputModifier(EvaluatedData);
			return;
		}
		if(ShadowSourceASC->EnergyGlobeArray[0] == EEnergyGlobeClass::Red)
		{
			const FGameplayModifierEvaluatedData EvaluatedData(
			UShadowAttributeSet::GetRedEnergyCostAttribute(), 
			EGameplayModOp::Additive,
			1
		);
			OutExecutionOutput.AddOutputModifier(EvaluatedData);
			return;
		}
	}
}
