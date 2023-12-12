// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageHandler.h"

void UMessageHandler::ReceiveAction(uint8 fromPlayer, UNetworkPacket packet)
{
	UAction action;
	ActionSerializer::Deserialize(packet.data, action);
}

UNetworkPacket UMessageHandler::MakeActionPacket(UAction action)
{
	UNetworkPacket packet;
	TArray<uint8> actionData;
	ActionSerializer::Serialize(action, actionData);

	packet.data = actionData;
	packet.senderID = GetGameMode()->GetLocalPlayerID();

	packet.SetFlag(EPacketFlags::ACTION);
	packet.sequence = GetGameMode()->GetSequence() + actionData.Num();

	return packet;
}

UNetworkPacket UMessageHandler::MakeACKPacket(UNetworkPacket receivedPacket)
{
	UNetworkPacket packet;

	packet.SetFlag(EPacketFlags::ACK);
	packet.senderID = receivedPacket.senderID;
	packet.sequence = receivedPacket.sequence;

	return packet;
}

void UMessageHandler::BroadcastMessage(const UNetworkPacket& packet)
{
	TArray<uint8> bytes;
	PacketSerializer::Serialize(packet, bytes);

	m_peer->SendToPeers(bytes);
}

void UMessageHandler::ACKPacket(UNetworkPacket packet)
{
	BroadcastMessage(MakeACKPacket(packet));
}

void UMessageHandler::EnqueueSerializedAction(const TArray<uint8>& action)
{
	m_actionQueue.Add(action);
}

void UMessageHandler::ReceivePacket(uint8 fromPlayer, UNetworkPacket packet)
{
	if (packet.HasFlag(EPacketFlags::ACK))
	{
		ReceiveACK(fromPlayer, packet);
	}
	else if (packet.HasFlag(EPacketFlags::ACTION))
	{
		ReceiveAction(fromPlayer, packet);
	}
}

void UMessageHandler::SetPeer(UNetworkPeer* peer)
{
	m_peer = peer;
}

void UMessageHandler::SendAllActions()
{
	TArray<uint8> bytes;
	FMemoryWriter writer(bytes);
	writer << m_actionQueue;

	// Initialize packet data
	UNetworkPacket packet;
	packet.data = bytes;

	BroadcastMessage(packet);

	m_actionQueue.Empty();
}

void UMessageHandler::SetActionFactory(UActionFactory* actionFactory)
{
	m_actionFactory = actionFactory;
}

AP2PSimulatedGameMode* UMessageHandler::GetGameMode()
{
	return m_gameMode;
}

void UMessageHandler::SetGameMode(AP2PSimulatedGameMode* gameMode)
{
	m_gameMode = gameMode;
}