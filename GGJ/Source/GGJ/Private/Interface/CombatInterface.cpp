// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/CombatInterface.h"


bool ICombatInterface::GetHit()
{
	return false;
}

void ICombatInterface::SetHit(bool Hit)
{
}

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
void ICombatInterface::EquipWeapon(int32 WeaponSlot)
{
}

void ICombatInterface::UnEquipWeapon()
{
}

FVector ICombatInterface::GetHandSocketLocation()
{
	return FVector();
}

