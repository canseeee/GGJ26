// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask/BTTask_UseAbility.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/ShadowCharacterBase.h"
#include "GAS/Abilities/ShadowGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UBTTask_UseAbility::UBTTask_UseAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Use Ability");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_UseAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 保存引用以便在委托回调中使用
	CachedOwnerComp = &OwnerComp;
	ActiveAbilityInstance = nullptr;

	// 获取AI控制器
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	// 获取被控制的Pawn
	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	// 转换为ShadowCharacterBase
	AShadowCharacterBase* CharacterBase = Cast<AShadowCharacterBase>(ControlledPawn);
	if (!CharacterBase)
	{
		return EBTNodeResult::Failed;
	}

	// 获取AbilitySystemComponent
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(CharacterBase);
	if (!ASC)
	{
		return EBTNodeResult::Failed;
	}

	// 检查AbilityTags是否有效
	if (AbilityTags.IsEmpty())
	{
		return EBTNodeResult::Failed;
	}

	// 查找匹配的能力并激活
	FScopedAbilityListLock ActiveScopeLock(*ASC);
	FGameplayAbilitySpecHandle ActivatedHandle;
	
	for (FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		// 检查能力的AssetTags或DynamicAbilityTags是否包含需要的标签
		bool bHasMatchingTag = false;
		for (const FGameplayTag& RequiredTag : AbilityTags)
		{
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(RequiredTag) || 
				(AbilitySpec.Ability && AbilitySpec.Ability->AbilityTags.HasTagExact(RequiredTag)))
			{
				bHasMatchingTag = true;
				break;
			}
		}

		if (bHasMatchingTag && AbilitySpec.Handle.IsValid())
		{
			// 尝试激活能力
			if (ASC->TryActivateAbility(AbilitySpec.Handle))
			{
				ActivatedHandle = AbilitySpec.Handle;
				break;
			}
		}
	}

	if (!ActivatedHandle.IsValid())
	{
		// 没有找到或激活失败
		return EBTNodeResult::Failed;
	}

	// 获取激活的能力实例
	// 首先尝试从激活的Spec中获取实例
	FGameplayAbilitySpec* ActivatedSpec = ASC->FindAbilitySpecFromHandle(ActivatedHandle);
	if (!ActivatedSpec || !ActivatedSpec->IsActive())
	{
		return EBTNodeResult::Failed;
	}

	// 获取能力实例（可能是CDO或实例）
	UGameplayAbility* ActivatedAbility = ActivatedSpec->GetPrimaryInstance();
	if (!ActivatedAbility)
	{
		// 如果没有实例，使用CDO（Class Default Object）
		ActivatedAbility = ActivatedSpec->Ability;
	}

	ActiveAbilityInstance = Cast<UShadowGameplayAbility>(ActivatedAbility);
	if (!ActiveAbilityInstance)
	{
		return EBTNodeResult::Failed;
	}

	// 绑定到能力结束委托（就像蓝图中那样）
	ActiveAbilityInstance->OnAbilityEnded.AddDynamic(this, &UBTTask_UseAbility::OnAbilityEnded);

	// 任务正在执行中，等待能力完成
	return EBTNodeResult::InProgress;
}

void UBTTask_UseAbility::OnAbilityEnded()
{
	if (!CachedOwnerComp)
	{
		return;
	}

	// 解绑委托
	if (ActiveAbilityInstance)
	{
		ActiveAbilityInstance->OnAbilityEnded.RemoveDynamic(this, &UBTTask_UseAbility::OnAbilityEnded);
		ActiveAbilityInstance = nullptr;
	}

	// 完成任务，标记为成功
	FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
}

void UBTTask_UseAbility::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	// 清理委托绑定
	if (ActiveAbilityInstance)
	{
		ActiveAbilityInstance->OnAbilityEnded.RemoveDynamic(this, &UBTTask_UseAbility::OnAbilityEnded);
		ActiveAbilityInstance = nullptr;
	}

	CachedOwnerComp = nullptr;

	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
