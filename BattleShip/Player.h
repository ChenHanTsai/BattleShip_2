#pragma once
#include "Ship.h"
#include "tiles_12.h" // town
#include "fire_01.h"
#include "..//Resource/sea.h"
#include <windows.h>
#include "Factors.h"
#include "board.h"
enum PlayerState{wait,inProcess,assignFinish};
class Player
{
private:
	Ship m_Ships[5];
	PlayerState m_State = PlayerState::wait;
	int m_AssignedIndex = 0;
	board m_TrackBoard;
	board m_PrimaryBoard;


	
public:
	struct Choose
	{
		int m_ChooseX = 0;
		int m_ChooseY = 0;

		int m_SourceW = GridUnit;
		int m_SourceH = GridUnit;
		int m_SourceX = ChooseSourceX;
		int m_SourceY = ChooseSourceY;
		const unsigned int* _sprite = sea_pixels;

	};

	Choose m_Choose;

	const Choose& GetChoose()const
	{
		return m_Choose;
	}

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
	void AssignRocket();
};

