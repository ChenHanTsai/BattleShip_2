#pragma once

#include <cmath>
#include <iostream>
#include <list>
#include "LifeStruct.h"
class Ship
{
private:
	int m_Life;
	bool m_isAssigned = false;



	
public:

	float m_Rotate = 0.0f;

	int GetLife()const
	{
		return m_Life;
	}
	void SetLife(int _life)
	{
		m_Life = _life;
	}

	std::list<LifeStruct> m_LifeStruct;
	bool GetAssigned()const
	{
		return m_isAssigned;
	}

	void Ship::SetAssigned(bool _bool)
	{

		m_isAssigned = _bool;

	}

	bool CalculateGrid();

	void ToggleRotate();
	
	int m_sourceX, m_sourceY, m_sourceW, m_sourceH;
	const unsigned int* m_Sprite;
	int m_PosX;
	int m_PosY;
	Ship(int _length, const unsigned int* _sprite, int _x, int _y, int _w, int _h);


	const unsigned int* GetSprite()
	{
		return m_Sprite;
	}
	Ship();
	~Ship();
};

