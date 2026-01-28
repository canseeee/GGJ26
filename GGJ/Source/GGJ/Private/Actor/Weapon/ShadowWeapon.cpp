// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/ShadowWeapon.h"


// Sets default values
AShadowWeapon::AShadowWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

TObjectPtr<UCapsuleComponent> AShadowWeapon::GetCollisionCapsule()
{
	return CollisionCapsule;
}

