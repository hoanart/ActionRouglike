// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGLIKE_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()
public:
	ASDashProjectile();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	// void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	// UFUNCTION()
	// void Explode();
	virtual void Explode_Implementation() override;
	UFUNCTION()
	void Dash();

protected:
	UPROPERTY(EditDefaultsOnly,Category="Teleport")
	float TeleportDelay;
	UPROPERTY(EditDefaultsOnly,Category="Teleport")
	float DetonateDelay;
private:
	FTimerHandle TimerHandle_DelayedDetonate;
	FTimerHandle TimerHandle_Dash;
};
