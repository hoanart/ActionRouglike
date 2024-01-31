// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTaskRangeAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTaskRangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//컨트롤러 찾기
	 TObjectPtr<AAIController> MyController  = OwnerComp.GetAIOwner();
	if(!ensure(MyController))
	{
		return EBTNodeResult::Failed;
	}

	TObjectPtr<ACharacter> MyPawn = Cast<ACharacter> (MyController->GetPawn());

	if(!IsValid(MyPawn))
	{
		return EBTNodeResult::Failed;
	}
	FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");
	TObjectPtr<AActor> TargetActor = Cast<AActor> (OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	if(!IsValid(TargetActor))
	{
		return EBTNodeResult::Failed;
	}
	
	FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
	FRotator MuzzleRotation = Direction.Rotation();

	//발사체 생성
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.Instigator = MyPawn;
	
	TObjectPtr<AActor> NewObj = GetWorld()->SpawnActor<AActor>(ProjectileClass,MuzzleLocation, MuzzleRotation,Params);

	return NewObj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	
}
