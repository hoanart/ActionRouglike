// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this,&ASProjectileBase::OnHit);
	
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);
	
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);
		
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	MovementComp->InitialSpeed = 8000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	ImpactShakeInnerRadius = 0.0f;
	ImpactShakeOuterRadius = 1500.0f;
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void ASProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             FVector NormalImpulse, const FHitResult& Hit)
{
	if(GetInstigator()!=OtherActor)
	{
		Explode();
	}
}

void ASProjectileBase::Explode_Implementation()
{
	if(ensure(IsValid(SphereComp)))
	{
		 DrawDebugSphere(GetWorld(),GetActorLocation(),10.0f,10,FColor::Magenta,false,2.0f,0,1.0f);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),MagicParticle,GetActorLocation(),GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ImpactSound,GetActorLocation());
		UGameplayStatics::PlayWorldCameraShake(GetWorld(),CameraShake,GetActorLocation(),ImpactShakeInnerRadius,ImpactShakeOuterRadius);
		EffectComp->DeactivateSystem();
		MovementComp->StopMovementImmediately();
		
		SetActorEnableCollision(false);
		
		//UE_LOG(LogTemp,Warning,TEXT("Hit : %s"),*OtherActor->GetName());
		//UE_LOG(LogTemp,Warning,TEXT("Hit : %s"),*GetActorRotation().ToString());
		Destroy();
	}
	
}

// Called every frame
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

