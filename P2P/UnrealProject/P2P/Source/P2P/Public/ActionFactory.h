// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionFactory.generated.h"


enum EActionType
{
	MOVE_TO,
	ATTACK,
};

enum EActionDataFlags
{
	HAS_SELECTED,
	HAS_POS
};

struct UActionData
{
	int32 selectedID;
	FVector pos;
};

struct UAction
{
	EActionType type;
	uint32 flags;
	UActionData data;

	bool HasFlag(EActionDataFlags flag)
	{
		const int32 flagOffset = 0;
		return (flags & flag) != 0;
	}
	void AddFlag(EActionDataFlags flag)
	{
		flags |= flag;
	}
};

struct ActionSerializer
{
	static void Serialize(UAction action, TArray<uint8>& bytes);
	static void Deserialize(const TArray<uint8>& bytes, UAction& actionResult);
};

/**
 * 
 */
UCLASS()
class P2P_API UActionFactory : public UObject
{
	GENERATED_BODY()
public:
private:
};

