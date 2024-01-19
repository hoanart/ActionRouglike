// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

UCLASS()
class ACTIONROUGLIKE_API ASPowerupActor : public AActor,public ISGamePlayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
protected:
	void OnRep_IsAlive();
	
	UFUNCTION()
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerState(bool&& bNewIsActive);

	
protected:
	bool bIsActive;
	UPROPERTY(EditAnywhere,Category = "Powerup")
	float RespawnTime;

	FTimerHandle TimerHandleRespawnTimer;

	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	TObjectPtr<class USphereComponent> SphereComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
};
