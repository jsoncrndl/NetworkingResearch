// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <SimulatedSceneComponent.h>
#include <SimulatedActorComponent.h>
#include "SimulatedActor.generated.h"

UCLASS()
class P2P_API ASimulatedActor : public AActor
{
	GENERATED_BODY()
	
	USimulatedSceneComponent* m_sceneComponent;
	TArray<USimulatedActorComponent*> m_simulatedComponents;

public:	
	// Sets default values for this actor's properties
	ASimulatedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SimulateStep();

};
