// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Controller))
	{
		if(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsytem->AddMappingContext(DefaultMappingContext,0);
		}
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ASCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ASCharacter::Look);
	}
}

void ASCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDir,MovementVector.Y);
		AddMovementInput(RightDir,MovementVector.X);
	}
}

void ASCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

