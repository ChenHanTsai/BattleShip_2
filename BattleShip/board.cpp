#include "board.h"


board::board()
{
	for (int x = 0; x < GridX; x++)
	{
		for (int y = 0; y < GridX; y++)
		{
			m_board[x][y] = boardState::noMissile;
		}
	}
}


board::~board()
{
}

void board::SetBoard(const std::list<LifeStruct>& _lifeStruct)
{
	auto iter = _lifeStruct.begin();
	for (unsigned int i = 0; i < _lifeStruct.size(); i++)
	{
		m_board[iter->m_NumberX][iter->m_NumberY] = boardState::shipOccupy;
		iter++;
	}
}

void board::SetRocketBoard(const LifeStruct& _lifeStruct,boardState _state)
{
	m_board[_lifeStruct.m_NumberX][_lifeStruct.m_NumberY] = _state;

}

bool board::CheckRocketOccupy(const LifeStruct& _lifeStruct)
{
	if (m_board[_lifeStruct.m_NumberX][_lifeStruct.m_NumberY] == boardState::noMissile)
		return false;
	
	return true;
}
bool board::CheckOpponetPrimaryBoard(const LifeStruct& _lifeStruct,const board* _board)
{
	if (_board->m_board[_lifeStruct.m_NumberX][_lifeStruct.m_NumberY] == boardState::shipOccupy)
	 return true;

	return false;
}
bool board::CheckShipOccupy(const std::list<LifeStruct>& _lifeStruct)
{
	auto iter = _lifeStruct.begin();
	for (unsigned int i = 0; i < _lifeStruct.size(); i++)
	{
		if (m_board[iter->m_NumberX][iter->m_NumberY] == boardState::shipOccupy)
			return true;

		iter++;
	}
	return false;
}