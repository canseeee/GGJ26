// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SummonBox.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ_API USummonBox : public UBoxComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float IgnoreAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MinGap;
	
	UFUNCTION(BlueprintCallable, Category="Summon")
	FVector GetRandomPointInBox() const;
};
