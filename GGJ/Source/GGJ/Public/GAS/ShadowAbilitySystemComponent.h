// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ShadowAbilitySystemComponent.generated.h"



UENUM(BlueprintType)
enum class EEnergyGlobeClass : uint8
{
	Green,
	Red,
	White
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnergyChanged, const TArray<EEnergyGlobeClass>&, EnergyGlobeArray);

UCLASS()
class GGJ_API UShadowAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<EEnergyGlobeClass> EnergyGlobeArray;

	UPROPERTY(BlueprintAssignable, Category = "Shadow")
	FEnergyChanged EnergyChanged;

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
	UFUNCTION()
	void OnEnergyChanged();
	
};
