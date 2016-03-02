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

	int m_TotalDestroyShips = 0;
	
public:

	const int GetTotalDestroyShips()const
	{
		return m_TotalDestroyShips;
	}

	const board* GetTrackBoard()const
	{
		return &m_TrackBoard;
	}

	const board* GetPrimaryBoard()const
	{
		return &m_PrimaryBoard;
	}

	struct Choose
	{
		int m_ChooseX = 0;
		int m_ChooseY = 0;

		
		int m_SourceX = ChooseSourceX;
		int m_SourceY = ChooseSourceY;
		int m_SourceW = GridUnit;
		int m_SourceH = GridUnit;
		const unsigned int* m_Sprite = sea_pixels;

		Choose(int _SourceX, int _SourceY, int _SourceW, int _SourceH,const unsigned int* _sprite) :
			m_SourceW(_SourceW), m_SourceH(_SourceH), m_SourceX(_SourceX), m_SourceY(_SourceY), m_Sprite(_sprite)
		{
		}
	};

	Choose m_Choose = Choose(ChooseSourceX, ChooseSourceY, GridUnit, GridUnit, sea_pixels);
	Choose m_HitSymbol = Choose(HitSourceX, HitSourceY, GridUnit, GridUnit, sea_pixels);
	Choose m_NoHitSymbol = Choose(NoHitSourceX, NoHitSourceY, GridUnit, GridUnit, sea_pixels);
	Choose m_FlagSymbol = Choose(NoHitSourceX, NoHitSourceY, GridUnit, GridUnit, sea_pixels);

	const Choose& GetHitSymbol()const
	{
		return m_HitSymbol;
	}

	const Choose& GetNoHitSymbol()const
	{
		return m_NoHitSymbol;
	}

	const Choose& GetChoose()const
	{
		return m_Choose;
	}

	const Choose& GetFlagSymbol()const
	{
		return m_FlagSymbol;
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
	void AssignRocket( Player* opponent);
	void UpdateShips(const LifeStruct& _life);
};

