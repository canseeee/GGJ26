// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Input/ShadowInputConfig.h"
#include "UI/DamageText/DamageTextComponent.h"
#include "ShadowPlayerController.generated.h"

class UShadowAbilitySystemComponent;
class UInputMappingContext;
struct FGameplayTag;
class UInputAction;
class UOathInputConfig;
class UGameplayAbility;

/**
 * 
 */
UCLASS()
class GGJ_API AShadowPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AShadowPlayerController();

	UFUNCTION()
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void AddPressedTime();

	UFUNCTION(BlueprintCallable)
	void SetPressedTime(float val);

		
private:
	UShadowAbilitySystemComponent* GetASC();

	
	UPROPERTY()
	TObjectPtr<UShadowAbilitySystemComponent> ShadowAbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, Category="Shadow | Input")
	TObjectPtr<UInputMappingContext> InputContext;
	
	UPROPERTY(EditAnywhere, Category="Shadow | Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Shadow | Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	UPROPERTY(EditAnywhere, Category="Shadow | Input")
	float ShortPressedThreshold = 0.2f;
	
	UPROPERTY(EditAnywhere, Category="Shadow | Input")
	float PressedTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UShadowInputConfig> InputConfig;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& Value);
	void InputTagPressed(FGameplayTag InputTag);
	void InputTagReleased(FGameplayTag InputTag);
	void InputTagHeld(FGameplayTag InputTag);
};
