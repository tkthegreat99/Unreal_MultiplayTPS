// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectPlayerCharacter.h"
#include "Controller/SAIController.h"
#include "Character/SNonPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/SCharacter.h"

UBTService_DetectPlayerCharacter::UBTService_DetectPlayerCharacter(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("DetectPlayerCharacter");
	Interval = 1.f;
}

void UBTService_DetectPlayerCharacter::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASAIController* AIC = Cast<ASAIController>(OwnerComp.GetAIOwner());
	if (IsValid(AIC) == true)
	{
		ASNonPlayerCharacter* NPC = Cast<ASNonPlayerCharacter>(AIC->GetPawn());
		if (IsValid(NPC) == true)
		{
			UWorld* World = NPC->GetWorld();
			if (IsValid(World) == true)
			{
				FVector CenterPosition = NPC->GetActorLocation();
				float DetectRadius = 300.f;
				TArray<FOverlapResult> OverlapResults;
				FCollisionQueryParams CollisionQueryParams(NAME_None, false, NPC);
				bool bResult = World->OverlapMultiByChannel(
					OverlapResults,
					CenterPosition,
					FQuat::Identity,
					ECollisionChannel::ECC_GameTraceChannel2,
					FCollisionShape::MakeSphere(DetectRadius),
					CollisionQueryParams
				);

				if (bResult == true)
				{
					for (auto const& OverlapResult : OverlapResults)
					{
						ASCharacter* PC = Cast<ASCharacter>(OverlapResult.GetActor());
						if (IsValid(PC) == true)
						{
							if (PC->GetController()->IsPlayerController() == true)
							{
								OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, PC);

								if (ASAIController::ShowAIDebug == 1)
								{
									UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Detected!")));
									DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Red, false, 0.5f);
									DrawDebugPoint(World, PC->GetActorLocation(), 10.f, FColor::Red, false, 0.5f);
									DrawDebugLine(World, NPC->GetActorLocation(), PC->GetActorLocation(), FColor::Red, false, 0.5f, 0u, 3.f);
								}
							}
							else
							{
								OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, nullptr);

								if (ASAIController::ShowAIDebug == 1)
								{
									DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Green, false, 0.5f);
								}
							}
						}
					}
				}
				else
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, nullptr);
				}

				if (ASAIController::ShowAIDebug == 1)
				{
					DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Green, false, 0.5f);
				}
			}
		}
	}
}
