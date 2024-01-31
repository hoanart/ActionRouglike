// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

UCLASS()
class ACTIONROUGLIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();
protected:
	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,USAttributeComponent* OwningComp, float Health,float Delta);
protected:
	//Components
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UPawnSensingComponent> PawnSensingComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class USAttributeComponent> AttributeComp;

protected:
	UPROPERTY(VisibleAnywhere,Category="Effects")
	FName TimeToHitParamName;
};
