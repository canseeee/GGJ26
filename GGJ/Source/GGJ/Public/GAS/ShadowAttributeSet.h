// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ShadowAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class GGJ_API UShadowAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UShadowAttributeSet();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData HP;	
	ATTRIBUTE_ACCESSORS(UShadowAttributeSet, HP);
	
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData MaxHP;	
	ATTRIBUTE_ACCESSORS(UShadowAttributeSet, MaxHP);
	
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData MaxMP;	
	ATTRIBUTE_ACCESSORS(UShadowAttributeSet, MaxMP);
	
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData AD;	
	ATTRIBUTE_ACCESSORS(UShadowAttributeSet, AD);
	
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData MoveSpeed;	
	ATTRIBUTE_ACCESSORS(UShadowAttributeSet, MoveSpeed);
	
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData EnergyRed;	
	ATTRIBUTE_ACCESSORS(UShadowAttributeSet, EnergyRed);

	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData EnergyGreen;	
	ATTRIBUTE_ACCESSORS(UShadowAttributeSet, EnergyGreen);

	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData EnergyWhite;	
	ATTRIBUTE_ACCESSORS(UShadowAttributeSet, EnergyWhite);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
