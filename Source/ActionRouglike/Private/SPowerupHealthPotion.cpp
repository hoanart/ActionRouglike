// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupHealthPotion.h"

#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASPowerupHealthPotion::ASPowerupHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh->SetGenerateOverlapEvents(true);

}

void ASPowerupHealthPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ASPowerupHealthPotion::BeginPlay()
{
	Super::BeginPlay();
}

void ASPowerupHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if(!ensure(InstigatorPawn))
	{
		return;
	}
	UE_LOG(LogTemp,Display,TEXT("상호작용"));
	TObjectPtr<USAttributeComponent> AttributeComp= USAttributeComponent::GetAttributes(InstigatorPawn);
	if(ensure(AttributeComp)&&!AttributeComp->IsFullHealth())
	{
		if(AttributeComp->ApplyHealthChangeByActor(this,AttributeComp->GetHealthMax()))
		{
			HideAndCooldownPowerup();
		}
		
	}
	
	
	
}

void ASPowerupHealthPotion::TempStop()
{
	RootComponent->SetVisibility(true);
	SetActorEnableCollision(true);
}

// Called every frame
void ASPowerupHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
