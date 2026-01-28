// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mask/MaskDataAsset.h"
#include "UObject/Interface.h"
#include "MaskInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMaskInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GGJ_API IMaskInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TObjectPtr<UMaskDataAsset> GetCurrentMask();

	virtual TArray<TObjectPtr<UMaskDataAsset>> GetAllMasks();
};
