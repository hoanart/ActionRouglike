// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if(IsValid(FromActor))
	{
		return FromActor->FindComponentByClass<USAttributeComponent>();
	}
	return nullptr;
}

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	Health = 100;
	HealthMax = 100;
	LowThreshold = 40.0f;
	// ...	

}


// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool USAttributeComponent::IsAlive() const
{
	return Health>0.0f;
}

const bool USAttributeComponent::IsFullHealth() const
{
	return Health ==HealthMax;
}

const float& USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USAttributeComponent::IsLowHealth() const
{
	
	return Health <= LowThreshold;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	//Health += Delta;
	float NewHealth = FMath::Clamp(Health+Delta,0.0f,HealthMax);
	Health = NewHealth;
	OnHealthChanged.Broadcast(nullptr,this,Health,Delta);
	return true;
}

bool USAttributeComponent::ApplyHealthChangeByActor(AActor* InstigatorActor, float Delta)
{
	if(!ensure(InstigatorActor))
	{
		return false;
	}

	float OldHealth = Health;
	Health = FMath::Clamp(Delta + Health,0,HealthMax);

	float ActualDelta = Health -OldHealth;
	
	OnHealthChanged.Broadcast(InstigatorActor,this,Health,ActualDelta);
	return ActualDelta !=0;
}



