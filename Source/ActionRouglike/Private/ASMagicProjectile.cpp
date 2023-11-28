// Fill out your copyright notice in the Description page of Project Settings.


#include "ASMagicProjectile.h"

#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AASMagicProjectile::AASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	
}

// Called when the game starts or when spawned
void AASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AASMagicProjectile::OnOverlap);
	//SphereComp->OnComponentHit.AddDynamic(this,&AASMagicProjectile::OnHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);	
	//Player->GetControlRotation()
}

void AASMagicProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if(GetInstigator()!=OtherActor&&OtherActor)
	{
		TObjectPtr<USAttributeComponent> AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(IsValid(AttributeComp))
		{
			AttributeComp->ApplyHealthChange(-20.0f);
		}
	Explode();
	}
}


// Called every frame
void AASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SetActorRotation(Cast<ASCharacter>( UGameplayStatics::GetPlayerPawn(GetWorld(),0))->OffsetRotation);
	
}

