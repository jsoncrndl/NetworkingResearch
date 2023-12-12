// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum EPacketFlags
{
	ACK = 1,
	ACTION = 2,
	RESEND_REQUEST = 4,
	RESEND = 8,
	KEEP_ALIVE = 16
};

struct P2P_API UNetworkPacket
{
	uint8 senderID;
	uint16 flags;
	uint32 turn;
	uint32 sequence;
	TArray<uint8> data;

	bool HasFlag(EPacketFlags flag)
	{
		const int32 flagOffset = 0;
		return (flags & flag) != 0;
	}
	void SetFlag(EPacketFlags flag)
	{
		flags |= flag;
	}
};

struct PacketSerializer
{
	static void Serialize(UNetworkPacket, TArray<uint8>& result);
	static void Deserialize(TArray<uint8>& data, UNetworkPacket& result);
};