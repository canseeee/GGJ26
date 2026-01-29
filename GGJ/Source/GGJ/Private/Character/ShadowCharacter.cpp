// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShadowCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "GAS/ShadowAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Abilities/ShadowGameplayAbility.h"
#include "Player/ShadowPlayerController.h"
#include "Player/ShadowPlayerState.h"

// Sets default values
AShadowCharacter::AShadowCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 设置碰撞胶囊体大小
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 不让控制器旋转角色，只控制摄像机
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 配置角色移动
	GetCharacterMovement()->bOrientRotationToMovement = true; // 角色朝向移动方向...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...使用此旋转速率

	// 注意：下面的移动参数只是示例值，可根据需要调整
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// 创建摄像机弹簧臂（在碰撞时拉近玩家）
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	// 创建跟随摄像机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
}

TObjectPtr<UMaskDataAsset> AShadowCharacter::GetCurrentMask()
{
	return Masks[MaskIndex];
}

TArray<TObjectPtr<UMaskDataAsset>> AShadowCharacter::GetAllMasks()
{
	return Masks;
}

void AShadowCharacter::ChangeMask(int32 NewMask)
{
	if(MaskIndex == NewMask)return;
	for (int32 i = 0; i < Weapons[MaskIndex]->MeleeAttackComboAbilities.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(WeaponAbilityHandles[i]);
		WeaponAbilityHandles.Empty();
	}
	
	MaskIndex = NewMask;
	for (int32 i = 0; i < Weapons[MaskIndex]->MeleeAttackComboAbilities.Num(); i++)
	{
		const TSubclassOf<UGameplayAbility> AbilityClass = Weapons[MaskIndex]->MeleeAttackComboAbilities[i];
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UShadowGameplayAbility* ShadowAbility = Cast<UShadowGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(ShadowAbility->InputTag);
			const FGameplayAbilitySpecHandle& WeaponAbilityHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
			WeaponAbilityHandles.Add(WeaponAbilityHandle);
		}
	}
}

TObjectPtr<UCapsuleComponent> AShadowCharacter::GetWeaponCapsule()
{
	return Weapons[MaskIndex]->GetCollisionCapsule();
}

// Called when the game starts or when spawned
void AShadowCharacter::BeginPlay()
{
	InitialWeapons();
	Super::BeginPlay();
}

void AShadowCharacter::InitialWeapons()
{
	for (int32 i = 0; i<Masks.Num();i++)
	{
		AActor* WeaponActor = GetWorld()->SpawnActor(Masks[i]->WeaponClass);
		//WeaponActor->SetActorHiddenInGame(true);
		WeaponActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		Weapons.Add(Cast<AShadowWeapon>(WeaponActor));
	}
	for (int32 i = 0; i < Weapons[MaskIndex]->MeleeAttackComboAbilities.Num(); i++)
	{
		const TSubclassOf<UGameplayAbility> AbilityClass = Weapons[MaskIndex]->MeleeAttackComboAbilities[i];
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UShadowGameplayAbility* ShadowAbility = Cast<UShadowGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(ShadowAbility->InputTag);
			const FGameplayAbilitySpecHandle& WeaponAbilityHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
			WeaponAbilityHandles.Add(WeaponAbilityHandle);
		}
	}
	
}

void AShadowCharacter::InitAbilityActorInfo()
{
	AShadowPlayerState* ShadowPlayerState = GetPlayerState<AShadowPlayerState>();
	check(ShadowPlayerState);
	ShadowPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ShadowPlayerState, this);
	Cast<UShadowAbilitySystemComponent>(ShadowPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = ShadowPlayerState->GetAbilitySystemComponent();
	AttributeSet = ShadowPlayerState->GetAttributeSet();
	if(AShadowPlayerController* ShadowPlayerController = Cast<AShadowPlayerController>(GetController()))
	{
		//初始化HUD
	}
	InitialAttribute();
}

void AShadowCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}


