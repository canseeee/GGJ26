// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShadowCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
AShadowCharacterBase::AShadowCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* AShadowCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AShadowCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShadowCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AShadowCharacterBase::InitialAttribute()
{
	if(!DefaultAttributeSetEffectClass)return;
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeSetEffectClass, 1.f, EffectContext);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}
