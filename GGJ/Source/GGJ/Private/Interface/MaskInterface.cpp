// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/MaskInterface.h"


// Add default functionality here for any IMaskInterface functions that are not pure virtual.
TObjectPtr<UMaskDataAsset> IMaskInterface::GetCurrentMask()
{
	return nullptr;
}

TArray<TObjectPtr<UMaskDataAsset>> IMaskInterface::GetAllMasks()
{
	return TArray<TObjectPtr<UMaskDataAsset>>();
}
