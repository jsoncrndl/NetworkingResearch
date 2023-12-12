// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSimulation.h"

void UGameSimulation::Simulate()
{
	// Process all the actions
	for (UAction action; m_actionQueue.Dequeue(action);)
	{
		ExecuteAction(action);
	}

	for (ASimulatedActor* actor : m_actors)
	{
		actor->SimulateStep();
	}

	m_turn++;
}

void UGameSimulation::ExecuteAction(const UAction& action)
{
	switch (action.type)
	{
	case EActionType::ATTACK:
		break;
	case EActionType::MOVE_TO:
		break;
	}
}

void UGameSimulation::StartTurn()
{
	m_elapsedTime = 0;
	m_turnDone = false;
}

bool UGameSimulation::AllPlayersDone()
{
	return false;
}

uint32 UGameSimulation::GetTurn()
{
	return m_turn;
}

void UGameSimulation::AddSimulatedActor(ASimulatedActor* actor)
{
	m_actors.Add(actor);
}

void UGameSimulation::Tick(float deltaTime)
{
	if (m_elapsedTime < TURN_TIME)
	{
		//Receive and broadcast messages
		return;
	}

	if (!m_turnDone)
	{
		// Send a message to everyone
		m_turnDone = true;
	}

	if (AllPlayersDone())
	{
		Simulate();
	}
	//Send turn done message
	//Wait for all
}

bool UGameSimulation::Init()
{
	// Game initialization stuff? Check if all games have the same state to start?
	return true;
}

uint32 UGameSimulation::Run()
{
	float deltaTime = 0;
	while (true)
	{
		auto startTime = FPlatformTime::ToMilliseconds(FPlatformTime::Cycles());
		Tick(deltaTime);
		deltaTime = FPlatformTime::ToMilliseconds(FPlatformTime::Cycles()) - startTime;
		m_elapsedTime += deltaTime;
	}
}

void UGameSimulation::Stop()
{
}
