// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UCapsuleComponent;
// This class does not need to be modified.
UINTERFACE()
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GGJ_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool GetHit();
	virtual void SetHit(bool Hit);
	virtual TObjectPtr<UCapsuleComponent> GetWeaponCapsule();
	virtual void EquipWeapon(int32 WeaponSlot);
	virtual void UnEquipWeapon();
	virtual FVector GetHandSocketLocation();
	virtual void Die();
};
