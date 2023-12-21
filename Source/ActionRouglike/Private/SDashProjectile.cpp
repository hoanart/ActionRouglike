// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASDashProjectile::ASDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;
	MovementComp->InitialSpeed = 6000.0f;
}

void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp,Warning,TEXT("생성"));
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate,this,&ASDashProjectile::Explode,DetonateDelay);
}

// void ASDashProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
//                              FVector NormalImpulse, const FHitResult& Hit)
// {
// 	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
// 	if(GetInstigator()!=OtherActor)
// 	{
// 		GetInstigator()->TeleportTo(GetActorLocation(),GetActorRotation());	
// 	}
// 	
// }

// void ASDashProjectile::Explode()
// {
// 	//DrawDebugSphere(GetWorld(),GetActorLocation(),5.0f,10,FColor::Green,false,2.0f,0,1.0f);
// 	
// 	
// }

void ASDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),MagicParticle,GetActorLocation(),GetActorRotation());
	EffectComp->DeactivateSystem();
	
	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);
	
	//ASProjectileBase::Explode();
	GetWorldTimerManager().SetTimer(TimerHandle_Dash,this,&ASDashProjectile::Dash,TeleportDelay);
	
	//Super::Explode_Implementation();
}

void ASDashProjectile::Dash()
{
	if(ensure(GetInstigator()))
	{
		GetInstigator()->TeleportTo(GetActorLocation(),GetActorRotation());	
		Destroy();
	}
}
