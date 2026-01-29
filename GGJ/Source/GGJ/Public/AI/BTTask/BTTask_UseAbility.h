// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagContainer.h"
#include "BTTask_UseAbility.generated.h"

class AShadowCharacterBase;
class UShadowGameplayAbility;

/**
 * 行为树任务：通过GameplayTag激活特定的Gameplay Ability并等待其完成
 */
UCLASS()
class GGJ_API UBTTask_UseAbility : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_UseAbility(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	/** 用于激活能力的Gameplay Tag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FGameplayTagContainer AbilityTags;

protected:
	// 当能力结束时调用此函数,用于完成任务
	UFUNCTION()
	void OnAbilityEnded();

private:
	// 当前行为树组件引用
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> CachedOwnerComp;

	// 当前激活的能力实例
	UPROPERTY()
	TObjectPtr<UShadowGameplayAbility> ActiveAbilityInstance;
};
