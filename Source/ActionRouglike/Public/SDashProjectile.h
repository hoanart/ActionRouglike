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
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	UFUNCTION()
	void Explode();
	UFUNCTION()
	void Dash();
private:
	FTimerHandle TimerHandle_Explode;
	FTimerHandle TimerHandle_Dash;
};
