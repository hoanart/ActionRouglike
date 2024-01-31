// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTServiceCheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTServiceCheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	TObjectPtr<UBlackboardComponent> BlackBoardComp =  OwnerComp.GetBlackboardComponent();
	if(ensure(BlackBoardComp))
	{
		TObjectPtr<AActor> TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject(("TargetActor")));
		if(IsValid(TargetActor))
		{
			TObjectPtr<AAIController> MyController = OwnerComp.GetAIOwner();
			if(ensure(MyController))
			{
				TObjectPtr<APawn> AIPawn = MyController->GetPawn();
				if(ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(),AIPawn->GetActorLocation());

					bool bWithInRange = DistanceTo<2000.0f;

					bool bHasLOS = false;
					if(bWithInRange)
					{
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}
					
					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName,bWithInRange&&bHasLOS);
				}
			}
		}
	}
	
}
