// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ShadowAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Interface/CombatInterface.h"


void UShadowAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UShadowAttributeSet::UShadowAttributeSet()
{
}

void UShadowAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
}

void UShadowAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;

	if (Attribute == GetHPAttribute())
	{
		HandleHPChanged(Props);
	}
	else if (Attribute == GetEnergyGreenAttribute())
	{
		HandleEnergyChanged(Props, 1);
	}
	else if (Attribute == GetEnergyRedAttribute())
	{
		HandleEnergyChanged(Props, 2);
	}
	else if (Attribute == GetEnergyWhiteAttribute())
	{
		HandleEnergyChanged(Props, 3);
	}
}

void UShadowAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		if (!IsValid(Props.SourceAvatarActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("SetEffectProperties: SourceAvatarActor became invalid after Get()"));
			return;
		}
		
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		if (!IsValid(Props.TargetAvatarActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("SetEffectProperties: TargetAvatarActor became invalid after Get()"));
			return;
		}
		
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
		
		if (!IsValid(Props.TargetASC))
		{
			UE_LOG(LogTemp, Warning, TEXT("SetEffectProperties: Failed to get TargetASC"));
		}
	}
}

void UShadowAttributeSet::HandleHPChanged(const FEffectProperties& Props)
{
	SetHP(FMath::Clamp(GetHP(), 0.f, GetMaxHP()));

	if (IsValid(Props.TargetAvatarActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"),
			*Props.TargetAvatarActor->GetName(), GetHP());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on invalid actor, Health: %f"), GetHP());
	}
}

void UShadowAttributeSet::HandleIncomingDamage(const FEffectProperties& Props)
{
	if (!GetIncomingDamageAttribute().IsValid())
	{
		return;
	}

	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);

	if (LocalIncomingDamage <= 0.f)
	{
		return;
	}

	float DamageToApply = LocalIncomingDamage;

	// 1. 生命与死亡结算（包括死亡逻辑和 XP），返回是否致死
	const bool bFatal = HandleIncomingDamage_HealthAndDeath(Props, DamageToApply);

	// 2. 受击动画（只有在非致死且真正扣了血时才播放）
	HandleIncomingDamage_PlayHitReact(Props, DamageToApply, bFatal);

}

void UShadowAttributeSet::HandleEnergyChanged(const FEffectProperties& Props, int EnergyClass)
{
	if(EnergyClass == 1)
	{
		SetEnergyGreen(FMath::Clamp(GetEnergyGreen(), 0.f, 5.f));
		return;
	}
	if(EnergyClass == 2)
	{
		SetEnergyRed(FMath::Clamp(GetEnergyRed(), 0.f, 5.f));
		return;
	}
	if(EnergyClass == 3)
	{
		SetEnergyWhite(FMath::Clamp(GetEnergyWhite(), 0.f, 5.f));
		return;
	}
}

bool UShadowAttributeSet::HandleIncomingDamage_HealthAndDeath(const FEffectProperties& Props, float DamageToApply)
{
	if (DamageToApply <= 0.f)
	{
		return false;
	}

	const float NewHealth = GetHP() - DamageToApply;
	SetHP(FMath::Clamp(NewHealth, 0.f, GetMaxHP()));

	const bool bFatal = NewHealth <= 0.f;
	if (!bFatal)
	{
		return false;
	}

	// 原有死亡逻辑
	if (IsValid(Props.TargetAvatarActor))
	{

		ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
		if (CombatInterface)
		{
			CombatInterface->Die();
		}

		FGameplayTag DeathReactTag = FGameplayTag::RequestGameplayTag("State.Status.Dead");
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(DeathReactTag);
		Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute: TargetAvatarActor is invalid during fatal damage"));
	}

	return true;
}

void UShadowAttributeSet::HandleIncomingDamage_PlayHitReact(const FEffectProperties& Props, float DamageToApply,
	bool bFatal)
{
}
