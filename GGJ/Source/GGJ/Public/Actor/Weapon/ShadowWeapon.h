// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "ShadowWeapon.generated.h"

UCLASS()
class GGJ_API AShadowWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShadowWeapon();

	TObjectPtr<UCapsuleComponent> GetCollisionCapsule();
private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> CollisionCapsule;
};
