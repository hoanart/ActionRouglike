// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

UCLASS(Abstract)
class ACTIONROUGLIKE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	virtual void PostInitializeComponents() override;
	UFUNCTION()
	virtual void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere,Category="Effects")
	TObjectPtr<class UParticleSystem> MagicParticle;
	UPROPERTY(EditDefaultsOnly,Category="Effects")
	TObjectPtr<class USoundCue> ImpactSound;
	
	UPROPERTY(EditDefaultsOnly,Category="Effects|Shake")
	TSubclassOf<class UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly,Category="Effects|Shake")
	float ImpactShakeInnerRadius;

	UPROPERTY(EditDefaultsOnly,Category="Effects|Shake")
	float ImpactShakeOuterRadius;
	
protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UProjectileMovementComponent> MovementComp;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UParticleSystemComponent> EffectComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components")
	TObjectPtr<class UAudioComponent> AudioComp;


};
