#pragma once
#include "Factors.h"
#include "LifeStruct.h"
#include <list>
enum boardState{missileOccupy,shipOccupy,noMissile,hitMissile,noHitMissle};
class board
{
private:
	

public:
	boardState m_board[GridX][GridX];
	 
	board();
	
	~board();

	void SetBoard(const std::list<LifeStruct>& _lifeStruct);
	void SetRocketBoard(const LifeStruct& _lifeStruct,boardState _state);
	bool CheckShipOccupy(const std::list<LifeStruct>& _lifeStruct);
	bool CheckRocketOccupy(const LifeStruct& _lifeStruct);
	bool CheckOpponetPrimaryBoard(const LifeStruct& _lifeStruct,const board* _board);
};

