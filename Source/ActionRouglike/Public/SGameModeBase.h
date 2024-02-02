// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGLIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASGameModeBase();
	
	virtual void StartPlay() override;

protected:
	UFUNCTION()
	void SpawnBotTimerElapsed();
	
	UFUNCTION()
	void OnQueryCompleted(class UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	
protected:
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TSubclassOf<AActor> MinionClass;
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	 TObjectPtr<class UEnvQuery> SpawnBotQuery;
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TObjectPtr<class UCurveFloat> DifficultyCurve;
	
	UPROPERTY(EditDefaultsOnly,Category="AI")
	float SpawnTimerInterval;

protected:
	FTimerHandle TimerHandle_SpawnBots;
};
