// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SummonBox.h"

#include "Components/CapsuleComponent.h"


// Sets default values for this component's properties
USummonBox::USummonBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FVector USummonBox::GetRandomPointInBox() const
{
	const FVector BoxCenter = GetComponentLocation();
	const FVector BoxExt = GetScaledBoxExtent();
	const FBox BoxBounds(BoxCenter - BoxExt, BoxCenter + BoxExt);

	const AActor* OwnerActor = GetOwner();
	const FVector OwnerLocation = OwnerActor ? OwnerActor->GetActorLocation() : BoxCenter;
	const FVector OwnerForward = OwnerActor ? OwnerActor->GetActorForwardVector() : FVector::ForwardVector;
	const FVector OwnerForward2D = FVector(OwnerForward.X, OwnerForward.Y, 0.0f).GetSafeNormal();

	UWorld* World = GetWorld();
	float CapsuleRadius = 66.0f;
	float CapsuleHalfHeight = 88.0f;
	if (const APawn* OwnerPawn = Cast<APawn>(OwnerActor))
	{
		if (const UCapsuleComponent* CapsuleComp = OwnerPawn->FindComponentByClass<UCapsuleComponent>())
		{
			CapsuleRadius = CapsuleComp->GetUnscaledCapsuleRadius();
			CapsuleHalfHeight = CapsuleComp->GetUnscaledCapsuleHalfHeight();
		}
	}

	constexpr int32 MaxTries = 64;
	for (int32 TryIndex = 0; TryIndex < MaxTries; ++TryIndex)
	{
		FVector Candidate = FMath::RandPointInBox(BoxBounds);
		Candidate.Z = 90.0f;

		const FVector ToCandidate2D = FVector(Candidate.X - OwnerLocation.X, Candidate.Y - OwnerLocation.Y, 90.0f);
		const FVector ToCandidateDir2D = ToCandidate2D.GetSafeNormal();

		const float ForwardDot = FVector::DotProduct(OwnerForward2D, ToCandidateDir2D);
		const bool bInFront90 = ForwardDot >= FMath::Cos(FMath::DegreesToRadians(45.0f));

		bool bOverlapsPawn = false;
		if (World)
		{
			FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(SummonBoxOverlap), false);
			QueryParams.AddIgnoredActor(OwnerActor);

			FCollisionObjectQueryParams ObjectParams;
			ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

			const FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);
			bOverlapsPawn = World->OverlapAnyTestByObjectType(Candidate, FQuat::Identity, ObjectParams, CapsuleShape, QueryParams);
		}

		if (!bInFront90 && !bOverlapsPawn)
		{
			return Candidate;
		}
	}

	// Fallback: return any random point with Z fixed at 0.
	FVector Fallback = FMath::RandPointInBox(BoxBounds);
	Fallback.Z = 90.0f;
	return Fallback;
}




