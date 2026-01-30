// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/ShadowDodgeAbility.h"
#include "GameFramework/Character.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionMoveToForce.h"

void UShadowDodgeAbility::Dodge()
{
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	FVector InputDir;
	if(Character->GetLastMovementInputVector()==FVector::ZeroVector)
	{
		InputDir = Character->GetActorForwardVector();
	}
	else InputDir = Character->GetLastMovementInputVector();
	FVector StartLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	
	// 使用 Root Motion 任务进行位移
	UAbilityTask_ApplyRootMotionMoveToForce* MoveTask =
		UAbilityTask_ApplyRootMotionMoveToForce::ApplyRootMotionMoveToForce(
			this,
			TEXT("DodgeMove"),
			StartLocation + InputDir * DodgeDistance,
			DodgeTime,
			false,                // bSetNewMovementMode
			MOVE_Walking,         // NewMovementMode
			true,                 // bRestrictSpeedToExpected
			nullptr,              // PathOffsetCurve
			ERootMotionFinishVelocityMode::MaintainLastRootMotionVelocity,
			FVector::ZeroVector,  // SetVelocityOnFinish
			0.f                   // ClampVelocityOnFinish
		);
	MoveTask->ReadyForActivation();
}
