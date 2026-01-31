// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ShadowCharacterBase.h"
#include "Interface/CombatInterface.h"
#include "ShadowBoss.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API AShadowBoss : public AShadowCharacterBase, public ICombatInterface
{
	GENERATED_BODY()

public: 
	AShadowBoss();

	virtual void Die_Implementation() override;
};
