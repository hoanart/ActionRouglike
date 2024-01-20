// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "SPowerupActor.h"
#include "GameFramework/Actor.h"
#include "SPowerupHealthPotion.generated.h"

UCLASS()
class ACTIONROUGLIKE_API ASPowerupHealthPotion : public ASPowerupActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupHealthPotion();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	void TempStop();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:

private:
	FTimerHandle InActiveTimer;
};
