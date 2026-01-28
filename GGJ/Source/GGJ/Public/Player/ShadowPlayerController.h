// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "ShadowPlayerController.generated.h"

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& Value);
	void InputTagPressed(FGameplayTag InputTag);
	void InputTagReleased(FGameplayTag InputTag);
	void InputTagHeld(FGameplayTag InputTag);
};
