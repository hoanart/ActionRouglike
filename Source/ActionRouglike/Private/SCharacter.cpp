// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this,&ASCharacter::OnHealthChanged);
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

	const float DrawScale = 100.0f;
	const float Thickness =5.0f;

	FVector LineStart = GetActorLocation();
	LineStart += GetActorRightVector()*100.0f;

	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector()*100.0f);

	DrawDebugDirectionalArrow(GetWorld(),LineStart,ActorDirection_LineEnd,DrawScale,FColor::Yellow,false,0.0f,0,Thickness);

	FVector ControllerDirection_LineEnd = LineStart+(GetControlRotation().Vector()*200.0f);
	DrawDebugDirectionalArrow(GetWorld(),LineStart,ControllerDirection_LineEnd,DrawScale,FColor::Green,false,0.0f,0,Thickness);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ASCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ASCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(PrimaryAttackAction,ETriggerEvent::Triggered,this,&ASCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(BlackHoleAttackAction,ETriggerEvent::Triggered,this,&ASCharacter::BlackHoleAttack);
		EnhancedInputComponent->BindAction(DashAction,ETriggerEvent::Triggered,this,&ASCharacter::Dash);
		EnhancedInputComponent->BindAction(PrimaryInteractAction,ETriggerEvent::Triggered,this,&ASCharacter::PrimaryInteract);
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

void ASCharacter::PrimaryAttack(const FInputActionValue& Value)
{
	
	PlayAnimMontage(AttackAnim);
	if(ensure(CastingParticle))
	{
		UGameplayStatics::SpawnEmitterAttached(CastingParticle,GetMesh(),"Muzzle_01");	
	}
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack_TimeElapsed,0.2f);
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ASCharacter::BlackHoleAttack(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack,this,&ASCharacter::BlackHoleAttack_TimeElapsed,0.2f);
}

void ASCharacter::Dash(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_Dash,this,&ASCharacter::Dash_TimeElapsed,0.2f);
}

void ASCharacter::Dash_TimeElapsed()
{
	SpawnActor(DashProjectileClass);
}

void ASCharacter::BlackHoleAttack_TimeElapsed()
{
	SpawnActor(BlackHoleProjectileClass);
}

void ASCharacter::SpawnActor(const TSubclassOf<AActor>& ClassToSpawn)
{
	
	if(ensure(ClassToSpawn))
	{
		FVector Offset = AttackLineTrace();
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		

		OffsetRotation = FRotationMatrix::MakeFromX(Offset-HandLocation).Rotator();
		FTransform SpawnTM = FTransform(OffsetRotation,HandLocation);
		UE_LOG(LogTemp,Warning,TEXT("Rotation : %s"),*OffsetRotation.ToString());
	
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		
		GetWorld()->SpawnActor<AActor>( ClassToSpawn,SpawnTM,SpawnParams);
	}
	
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if(Delta<0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
	}
	if(NewHealth<=0.0f&&Delta<0.0f)
	{
		TObjectPtr<APlayerController> PC = Cast<APlayerController>(GetController());
		
		DisableInput(PC);
	}
}

FVector ASCharacter::AttackLineTrace()
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	
	FVector End = CameraComp->GetComponentLocation()+(GetControlRotation().Vector()*5000.0f);
	FHitResult Hit;
	FCollisionShape Shape;
	Shape.SetSphere(20.0f);
	bool bBlockingHit =GetWorld()->SweepSingleByObjectType(Hit,CameraComp->GetComponentLocation(),End,FQuat::Identity,ObjectQueryParams,Shape,Params);
		//GetWorld()->LineTraceSingleByObjectType(Hit, GetActorLocation(),End,ObjectQueryParams);
	FColor LineColor = bBlockingHit? FColor::Green : FColor::Red;

	//DrawDebugLine(GetWorld(), CameraComp->GetComponentLocation(),End,LineColor,false,2.0f,0,2);

	
	return bBlockingHit? Hit.ImpactPoint : End;
}
void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector Offset = AttackLineTrace();
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	OffsetRotation = FRotationMatrix::MakeFromX(Offset-HandLocation).Rotator();
	FTransform SpawnTM = FTransform(OffsetRotation,HandLocation);
	UE_LOG(LogTemp,Warning,TEXT("Rotation : %s"),*OffsetRotation.ToString());
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	GetWorld()->SpawnActor<AActor>( ProjectileClass,SpawnTM,SpawnParams);
	
}


void ASCharacter::PrimaryInteract(const FInputActionValue& Value)
{
	if(IsValid(InteractionComp))
	{
		InteractionComp->PrimaryInteract();
	}
}





