// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MaskDataAsset.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UENUM(BlueprintType)
enum class EMaskType : uint8
{
	Ninja,
	Razors,
	Bat,
	Sumo
};
/**
 * 
 */
UCLASS()
class GGJ_API UMaskDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	EMaskType MaskType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	TSubclassOf<UStaticMeshComponent> MaskMash;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	float MaxEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	float CurEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	TSubclassOf<UGameplayEffect> EquipCostEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	TSubclassOf<UGameplayAbility> MaskActiveAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	TSubclassOf<UGameplayAbility> MaskPassiveAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	TSubclassOf<AActor> SummonSoldier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mask")
	int32 SummonNum;
};
