// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	TObjectPtr<UBlackboardComponent> BBComp = OwnerComp.GetBlackboardComponent();
	if(!ensure(BBComp))
	{
		return;
	}
	
	TObjectPtr<AAIController> MyController = OwnerComp.GetAIOwner();
	if(!ensure(MyController))
	{
		return;
	}

	TObjectPtr<APawn> AIPawn = MyController->GetPawn();
	if(!ensure(AIPawn))
	{
		return;
	}

	TObjectPtr<USAttributeComponent> AttributeComp = USAttributeComponent::GetAttributes(AIPawn);
	if(!ensure(AttributeComp))
	{
		return;
	}

	bool bLowHealth = AttributeComp->IsLowHealth();
	
	BBComp->SetValueAsBool(IsLowHealthKey.SelectedKeyName,bLowHealth);
}
