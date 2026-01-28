// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/SummonSoldierAbility.h"

#include "Character/ShadowSoldier.h"
#include "Character/SummonBox.h"
#include "Interface/MaskInterface.h"
#include "UniversalObjectLocators/UniversalObjectLocatorUtils.h"

void USummonSoldierAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	if(IMaskInterface* MaskInterface = Cast<IMaskInterface>(GetAvatarActorFromActorInfo()))
	{
		const int32 SummonSoldierNum = MaskInterface->GetCurrentMask()->SummonNum;
		const TSubclassOf<AActor> SummonSoldierClass = MaskInterface->GetCurrentMask()->SummonSoldier;
		for(int32 SummonIndex = 0; SummonIndex < SummonSoldierNum; SummonIndex++)
		{
			if(GetAvatarActorFromActorInfo()->FindComponentByClass<USummonBox>())
			{
				const FString NameString = FString::Printf(TEXT("%s_%d"), *SummonSoldierClass->GetName(),SummonIndex);
				AActor* SummonSoldier = UE::UniversalObjectLocator::SpawnActorForLocator(GetWorld(), SummonSoldierClass, FName(*NameString));
				Soldiers.Add(*NameString, SummonSoldier);
				const FVector SummonLocation = GetAvatarActorFromActorInfo()->FindComponentByClass<USummonBox>()->GetRandomPointInBox();
				SummonSoldier->SetActorLocation(SummonLocation);
			}
		}
	}
}

void USummonSoldierAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	for(auto& Soldier : Soldiers)
	{
		Cast<AShadowSoldier>(Soldier.Value)->Die();
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
