// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,AActor*,InstigatorActor,USAttributeComponent*,OwningComp, float,Health,float,Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGLIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
	

public:
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
public:

	UFUNCTION(BlueprintCallable)
	const bool IsFullHealth() const;
	UFUNCTION(BlueprintCallable)
	const float& GetHealthMax() const;
	UFUNCTION(BlueprintCallable)
	 bool IsLowHealth() const;
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChange(float Delta);

	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChangeByActor(AActor* InstigatorActor,float Delta);
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Attributes")
	float Health;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float HealthMax;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Attributes")
	float LowThreshold;

};
