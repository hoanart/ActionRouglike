// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SCharacter.generated.h"

UCLASS()
class ACTIONROUGLIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void PrimaryAttack(const FInputActionValue& Value);
	void BlackHoleAttack(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
	void PrimaryInteract(const FInputActionValue& Value);
	
private:
	UFUNCTION()
	FVector AttackLineTrace();
	UFUNCTION()
	void PrimaryAttack_TimeElapsed();
	UFUNCTION()
	void BlackHoleAttack_TimeElapsed();
	UFUNCTION()
	void Dash_TimeElapsed();
	
	UFUNCTION()
	void SpawnActor(const TSubclassOf<AActor>& ClassToSpawn);
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,class USAttributeComponent* OwningComp,float NewHealth,float Delta);

	UFUNCTION()
	void StartAttackEffect();
	
public:
	FRotator OffsetRotation;
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components",meta =(AllowPrivateAccess = true))
	TObjectPtr<class USAttributeComponent> AttributeComp;
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	TObjectPtr<class USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	TObjectPtr<class UCameraComponent> CameraComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	TObjectPtr<class USInteractionComponent> InteractionComp;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PrimaryAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> BlackHoleAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PrimaryInteractAction;
	
	UPROPERTY(EditAnywhere,Category ="SpawnClass")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere,Category ="SpawnClass")
	TSubclassOf<AActor> BlackHoleProjectileClass;
	UPROPERTY(EditAnywhere,Category ="SpawnClass")
	TSubclassOf<AActor> DashProjectileClass;
	UPROPERTY(EditAnywhere,Category = "Atack")
	TObjectPtr<class UAnimMontage> AttackAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<class UParticleSystem> CastingParticle;
	
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_BlackHoleAttack;
	FTimerHandle TimerHandle_Dash;

	UPROPERTY(VisibleAnywhere, Category="Effect")
	FName HandSocketName;
	UPROPERTY(VisibleAnywhere, Category="Effect")
	FName TimeToHitParamName;
};
