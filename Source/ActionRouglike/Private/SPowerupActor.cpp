// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ASPowerupActor::ASPowerupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(RootComponent);
	RootComponent = SphereComp;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(RootComponent);

	RespawnTime = 10.0f;
	bIsActive = false;
}

// Called when the game starts or when spawned
void ASPowerupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPowerupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPowerupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	//ISGamePlayInterface::Interact_Implementation(InstigatorPawn);
}

void ASPowerupActor::OnRep_IsAlive()
{
	SetActorEnableCollision(bIsActive);
	RootComponent->SetVisibility(bIsActive,true);
}

void ASPowerupActor::ShowPowerup()
{
	SetPowerState(true);
}

void ASPowerupActor::HideAndCooldownPowerup()
{
	SetPowerState(false);
	GetWorldTimerManager().SetTimer(TimerHandleRespawnTimer,this,&ASPowerupActor::ShowPowerup,RespawnTime);
}

void ASPowerupActor::SetPowerState(bool&& bNewIsActive)
{
	bIsActive = bNewIsActive;
	OnRep_IsAlive();
}

