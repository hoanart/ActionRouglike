// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AAIController> MyController = OwnerComp.GetAIOwner();
	if(!ensure(MyController))
	{
		return EBTNodeResult::Failed;
	}

	TObjectPtr<APawn> AIPawn = MyController->GetPawn();
	if(!ensure(AIPawn))
	{
		return EBTNodeResult::Failed;
	}

	TObjectPtr<USAttributeComponent> AttributeComp  = USAttributeComponent::GetAttributes(AIPawn);
	if(!ensure(AttributeComp))
	{
		return EBTNodeResult::Failed;
	}

	AttributeComp->ApplyHealthChange(AttributeComp->GetHealthMax());
	
	UE_LOG(LogTemp,Log,TEXT("%d"),AttributeComp->IsFullHealth());
	return EBTNodeResult::Succeeded;
	
}
