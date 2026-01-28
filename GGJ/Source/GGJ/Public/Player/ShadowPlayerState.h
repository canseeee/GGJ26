// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShadowPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;


/**
 * 
 */
UCLASS()
class GGJ_API AShadowPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AShadowPlayerState();
	
	UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
