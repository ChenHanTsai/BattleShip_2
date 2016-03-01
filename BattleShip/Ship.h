#pragma once

#include <cmath>
#include <iostream>
class Ship
{
private:
	int m_Length;
	bool m_isAssigned = false;
	bool m_Rotate = false;
public:
	bool GetAssigned()const
	{
		return m_isAssigned;
	}

	void SetAssigned(bool _bool)
	{
		m_isAssigned = _bool;
	}

	void ToggleRotate()
	{
		m_Rotate = !m_Rotate;
	}
	int m_sourceX, m_sourceY, m_sourceW, m_sourceH;
	const unsigned int* m_Sprite;
	int m_PosX;
	int m_PosY;
	Ship(int _length, const unsigned int* _sprite, int _x, int _y, int _w, int _h) :m_Length(_length), m_Sprite(_sprite),
		m_sourceX(_x), m_sourceY(_y), m_sourceW(_w), m_sourceH(_h)
	{
		m_PosX = std::rand() % 1000;
		m_PosY = std::rand() % 1000;
	};

	const unsigned int* GetSprite()
	{
		return m_Sprite;
	};
	Ship();
	~Ship();
};

