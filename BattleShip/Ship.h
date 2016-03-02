#pragma once

#include <cmath>
#include <iostream>
#include <list>
class Ship
{
private:
	int m_Life;
	bool m_isAssigned = false;



	struct LifeStruct
	{
		int m_NumberX = 0;
		int m_NumberY = 0;
	};
	
public:

	float m_Rotate = 0.0f;

	int GetLife()const
	{
		return m_Life;
	}


	std::list<LifeStruct> m_LifeStruct;
	bool GetAssigned()const
	{
		return m_isAssigned;
	}

	bool Ship::SetAssigned()
	{
		//m_Owner = _owner;
		m_isAssigned = CalculateGrid();
		return m_isAssigned;

	}

	bool CalculateGrid();

	void ToggleRotate();
	
	int m_sourceX, m_sourceY, m_sourceW, m_sourceH;
	const unsigned int* m_Sprite;
	int m_PosX;
	int m_PosY;
	Ship(int _length, const unsigned int* _sprite, int _x, int _y, int _w, int _h) :m_Life(_length), m_Sprite(_sprite),
		m_sourceX(_x), m_sourceY(_y), m_sourceW(_w), m_sourceH(_h)
	{
		m_PosX = 0;
		m_PosY =0;
	};

	const unsigned int* GetSprite()
	{
		return m_Sprite;
	}
	Ship();
	~Ship();
};

