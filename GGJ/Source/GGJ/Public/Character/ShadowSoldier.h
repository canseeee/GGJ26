// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowCharacterBase.h"
#include "Actor/Weapon/ShadowWeapon.h"
#include "Interface/CombatInterface.h"
#include "ShadowSoldier.generated.h"

UCLASS()
class GGJ_API AShadowSoldier : public AShadowCharacterBase, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShadowSoldier();
	void Die();

	// Combat Interface Start
	
	virtual void SetHit(bool Hit) override;
	virtual bool GetHit() override;
	virtual UCapsuleComponent* GetWeaponCapsule_Implementation() override;

	// Combat Interface End

	/** WeaponActor类 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<AShadowWeapon> WeaponActorClass;

protected:
	void InitAbilityActorInfo();protected:
	virtual void BeginPlay() override;
	void InitialWeapons();
	void AttachWeaponToHand();

private:
	bool bHit;

	UPROPERTY()
	TObjectPtr<AShadowWeapon> Weapon;
};
