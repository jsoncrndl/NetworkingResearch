// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionFactory.h"

void ActionSerializer::Serialize(UAction action, TArray<uint8>& bytes)
{
	FMemoryWriter writer(bytes, true);

	writer << action.flags;

	uint8 actionType = static_cast<uint8>(action.type);
	writer << actionType;

	if (action.HasFlag(EActionDataFlags::HAS_SELECTED))
	{
		writer << action.data.selectedID;
	}

	if (action.HasFlag(EActionDataFlags::HAS_POS))
	{
		writer << action.data.pos;
	}
}

void ActionSerializer::Deserialize(const TArray<uint8>& bytes, UAction& actionResult)
{
	FMemoryReader reader(bytes, true);

	reader << actionResult.flags;

	uint8 actionType;
	reader << actionType;
	actionResult.type = static_cast<EActionType>(actionType);

	if (actionResult.HasFlag(EActionDataFlags::HAS_SELECTED))
	{
		reader << actionResult.data.selectedID;
	}

	if (actionResult.HasFlag(EActionDataFlags::HAS_POS))
	{
		reader << actionResult.data.pos;
	}
}