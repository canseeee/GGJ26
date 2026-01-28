// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShadowPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/ShadowInputComponent.h"



AShadowPlayerController::AShadowPlayerController()
{
	bReplicates = true;
}

void AShadowPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputContext,0);
	}

	// 隐藏鼠标光标，允许自由控制视角
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;

	// 设置为仅游戏模式，捕获鼠标输入
	FInputModeGameOnly InputModeData;
	InputModeData.SetConsumeCaptureMouseDown(false);
	SetInputMode(InputModeData);
}

void AShadowPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* OathInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	OathInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShadowPlayerController::Move);
	OathInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShadowPlayerController::Look);
}

void AShadowPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AShadowPlayerController::Look(const FInputActionValue& Value)
{
	// 输入是一个 Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	// 调试日志：检查是否接收到输入
	UE_LOG(LogTemp, Warning, TEXT("Look Input: X=%f, Y=%f"), LookAxisVector.X, LookAxisVector.Y);
	
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		// 鼠标X轴控制左右旋转（Yaw）
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		// 鼠标Y轴控制上下旋转（Pitch），取负值使上移对应向上看
		ControlledPawn->AddControllerPitchInput(-LookAxisVector.Y);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Controlled Pawn!"));
	}
}


void AShadowPlayerController::InputTagPressed(FGameplayTag InputTag)
{
}

void AShadowPlayerController::InputTagReleased(FGameplayTag InputTag)
{
}

void AShadowPlayerController::InputTagHeld(FGameplayTag InputTag)
{
}

