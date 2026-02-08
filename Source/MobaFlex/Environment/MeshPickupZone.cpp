// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshPickupZone.h"

int32 GMobaFlexRotateOptimization = 0;
static FAutoConsoleVariableRef CVarEnableToto(TEXT("MobaFlex.RotateOptim"), GMobaFlexRotateOptimization, TEXT("MobaFlex.RotateOptim"));

// Sets default values
AMeshPickupZone::AMeshPickupZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMeshPickupZone::BeginPlay()
{
	Super::BeginPlay();
	this->StaticMesh.LoadAsync(FLoadSoftObjectPathAsyncDelegate::CreateLambda([this](const FSoftObjectPath& InSoftObjectPath, UObject* InObject)
	{
		StaticMeshComponent->SetStaticMesh(StaticMesh.Get());
		StaticMeshComponent->bUseAttachParentBound = true;
		StaticMeshComponent->SetCanEverAffectNavigation(false);
	}));
}

FRotator AMeshPickupZone::ComputeRotation(float DeltaTime)
{
	SCOPED_NAMED_EVENT_TEXT("ComputeRotation", FColor::Red)
	//Add aa scope to see it
	//FPlatformProcess::Sleep(0.001f);
	return FRotator(0.0f, 20.0f, 0.0f) * DeltaTime;
}

// Called every frame
void AMeshPickupZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GMobaFlexRotateOptimization == 2)
	{
		StaticMeshComponent->AddLocalRotation(ComputeRotation(DeltaTime));
	}
	else if (GMobaFlexRotateOptimization == 1)
	{
		UE::Tasks::TTask<FRotator> task1 = UE::Tasks::Launch(UE_SOURCE_LOCATION, [this, DeltaTime] { return ComputeRotation(DeltaTime); });
		UE::Tasks::Launch(UE_SOURCE_LOCATION, [this, task1] mutable
		{
			FRotator resultT1 = task1.GetResult();
			AsyncTask(ENamedThreads::GameThread, [this, resultT1]()
			{
				if (IsValid(StaticMeshComponent))
					StaticMeshComponent->AddLocalRotation(resultT1);
			});
		}, task1);
	}
	else if (GMobaFlexRotateOptimization == 0)
	{
		//FGraph
		TSharedPtr<FRotator> RotateResult = MakeShared<FRotator>();
		 
		//Task 1
		FGraphEventRef Task1 = FFunctionGraphTask::CreateAndDispatchWhenReady([this, RotateResult, DeltaTime]()
		{
			*RotateResult = ComputeRotation(DeltaTime);
		}, TStatId(), nullptr, ENamedThreads::AnyBackgroundThreadNormalTask);
		//Task 2
		FGraphEventRef Task2 = FFunctionGraphTask::CreateAndDispatchWhenReady([this, RotateResult]()
		{
			StaticMeshComponent->AddLocalRotation(*RotateResult);
		}, TStatId(), Task1, ENamedThreads::GameThread);
	}
}

