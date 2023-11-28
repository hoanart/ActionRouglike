// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASDashProjectile::ASDashProjectile()
{
}

void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp,Warning,TEXT("생성"));
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	GetWorldTimerManager().SetTimer(TimerHandle_Explode,this,&ASDashProjectile::Explode,0.2f);
}

void ASDashProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	if(GetInstigator()!=OtherActor)
	{
		GetInstigator()->TeleportTo(GetActorLocation(),GetActorRotation());	
	}
	
}

void ASDashProjectile::Explode()
{
	DrawDebugSphere(GetWorld(),GetActorLocation(),5.0f,10,FColor::Green,false,2.0f,0,1.0f);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),MagicParticle,GetActorLocation(),GetActorRotation());
	EffectComp->DeactivateSystem();
	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);
	//ASProjectileBase::Explode();
	GetWorldTimerManager().SetTimer(TimerHandle_Dash,this,&ASDashProjectile::Dash,0.2f);
	
}

void ASDashProjectile::Dash()
{
	GetInstigator()->TeleportTo(GetActorLocation(),GetActorRotation());
	Destroy();
}
