// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionFactory.h"
#include "Actions.h"
#include "SimpleMoveActionFactory.generated.h"

/**
 * 
 */
UCLASS()
class P2P_API USimpleMoveActionFactory : public UActionFactory
{
	GENERATED_BODY()
	
public:
	UAction MakeMoveAction();
	UAction MakeAttackAction();
};
