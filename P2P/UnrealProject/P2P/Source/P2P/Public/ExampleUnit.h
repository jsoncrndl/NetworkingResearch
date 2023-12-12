// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimulatedActor.h"
#include "ExampleUnit.generated.h"

/**
 * 
 */
UCLASS()
class P2P_API AExampleUnit : public ASimulatedActor
{
	GENERATED_BODY()
	
	FVector m_targetPos;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float movementSpeed;

	virtual void SimulateStep() override;
};
