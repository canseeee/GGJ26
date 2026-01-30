// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowCharacterBase.h"
#include "Actor/Weapon/ShadowWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interface/CombatInterface.h"
#include "Interface/MaskInterface.h"
#include "ShadowCharacter.generated.h"

struct FGameplayAbilitySpecHandle;
class UMaskDataAsset;

UCLASS()
class GGJ_API AShadowCharacter : public AShadowCharacterBase, public IMaskInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShadowCharacter();
	virtual TObjectPtr<UMaskDataAsset> GetCurrentMask() override;
	virtual TArray<TObjectPtr<UMaskDataAsset>> GetAllMasks() override;
	UFUNCTION(BlueprintCallable)
	void ChangeMask(int32 NewMask);

	// Combat Interface Start
	
	virtual UCapsuleComponent* GetWeaponCapsule_Implementation() override;

	// Combat Interface End
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitialWeapons();
public:
	void InitAbilityActorInfo();
	/** 摄像机弹簧臂组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** 跟随摄像机 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Shadow | Data")
	TArray<TSubclassOf<AShadowWeapon>> WeaponClasses;
	
	virtual void PossessedBy(AController* NewController) override;

	FName WeaponHandSocketName;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Shadow | Data")
	TArray<TObjectPtr<UMaskDataAsset>> Masks;

	UPROPERTY()
	TArray<TObjectPtr<AShadowWeapon>> Weapons;
	
	UPROPERTY()
	int32 MaskIndex = 0;

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> WeaponAbilityHandles;

	void AttachWeaponToHand();
};
