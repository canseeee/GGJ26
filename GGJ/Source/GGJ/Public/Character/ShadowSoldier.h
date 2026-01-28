// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowCharacterBase.h"
#include "ShadowSoldier.generated.h"

UCLASS()
class GGJ_API AShadowSoldier : public AShadowCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShadowSoldier();
	void Die();
protected:
	void InitAbilityActorInfo();
};
