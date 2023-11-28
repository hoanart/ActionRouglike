// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

UCLASS()
class ACTIONROUGLIKE_API ASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class USAttributeComponent> AttributeComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UStaticMeshComponent> MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,class USAttributeComponent* OwningComp,float NewHealth,float Delta);
	
};
