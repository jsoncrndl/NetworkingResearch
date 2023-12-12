// Fill out your copyright notice in the Description page of Project Settings.


#include "P2PPlayerController.h"

AP2PPlayerController::AP2PPlayerController(const FObjectInitializer& init)
{
	m_peer = NewObject<UNetworkPeer>();
	m_messenger = NewObject<UMessageHandler>();
	m_actionFactory = NewObject<UActionFactory>();

	m_messenger->SetPeer(m_peer);
	m_messenger->SetActionFactory(m_actionFactory);
}

void AP2PPlayerController::EnqueueAction(UAction action)
{
	TArray<uint8> bytes;
	ActionSerializer::Serialize(action, bytes);
	m_messenger->EnqueueSerializedAction(bytes);
}

UActionFactory* AP2PPlayerController::GetActionFactory()
{
	return m_actionFactory;
}
