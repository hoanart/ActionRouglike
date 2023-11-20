// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "ASMagicProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosivBarrel::AExplosivBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetGenerateOverlapEvents(true);
	//StaticMeshComp->SetNotifyRigidBodyCollision(false);
	StaticMeshComp->SetCollisionProfileName("PhysicsActor");

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 600.0f;
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void AExplosivBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	StaticMeshComp->OnComponentHit.AddDynamic(this,&AExplosivBarrel::OnHit);
}

// Called when the game starts or when spawned
void AExplosivBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplosivBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("Proj Blocking"));
	Explode();
	if(Hit.bBlockingHit)
	{
		UE_LOG(LogTemp,Warning,TEXT("Blocking"));
	}
	FString CombinedString = FString::Printf(TEXT("Hit at location : %s"),*Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(),Hit.ImpactPoint,CombinedString,nullptr,FColor::Green,2.0f,true);
	if(TObjectPtr<AASMagicProjectile> Projectile = Cast<AASMagicProjectile>(OtherActor))
	{
		
	}
	
}

// Called every frame
void AExplosivBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosivBarrel::Explode()
{
	RadialForceComp->FireImpulse();	
}

