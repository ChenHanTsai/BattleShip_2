#pragma once
#include "Ship.h"
#include "tiles_12.h" // town
#include "fire_01.h"
#include "../Resource/Submarine.h"
#include <windows.h>
#include "Factors.h"

enum PlayerState{wait,inProcess};
class Player
{
private:
	Ship m_Ships[5];
	PlayerState m_State = PlayerState::wait;
	int m_AssignedIndex = 0;
public:
	const PlayerState& GetState()const
	{
		return m_State;
	}
	void SetState(PlayerState _state)
	{
		m_State = _state;
	}
	const Ship* GetShip(int index)const
	{
		return &m_Ships[index];
	}

	int m_PrimaryGridX = 0;
	int m_PrimaryGridY = 0;
	int m_TrackGridX = 0;
	int m_TrackGridY = 0;
	void SetGridOffset(int _PrimaryGridX, int _PrimaryGridY, int _TrackGridX, int _TrackGridY);

	Player();
	~Player();

	void AssignMarine();
};

