// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(RootComponent);
	RootComponent = SphereComp;
	SphereComp->SetGenerateOverlapEvents(true);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	Mesh->SetGenerateOverlapEvents(true);

}

void ASHealthPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGamePlayInterface::Interact_Implementation(InstigatorPawn);
	UE_LOG(LogTemp,Display,TEXT("상호작용"));
	TObjectPtr<USAttributeComponent> AttributeComp= USAttributeComponent::GetAttributes(InstigatorPawn);
	RootComponent->SetVisibility(false);
	SetActorEnableCollision(false);
	if(AttributeComp->ApplyHealthChangeByActor(this,AttributeComp->GetHealthMax()))
	{
		GetWorldTimerManager().SetTimer(InActiveTimer,this,&ASHealthPotion::TempStop,10.0f);
	}
	
}

void ASHealthPotion::TempStop()
{
	RootComponent->SetVisibility(true);
	SetActorEnableCollision(true);
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
