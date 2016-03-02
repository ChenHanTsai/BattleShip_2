#include "Ship.h"
#include "..//Resource/sea.h"
#include "Factors.h"

Ship::Ship()
{
}

Ship::Ship(int _length, const unsigned int* _sprite, int _x, int _y, int _w, int _h) :m_Life(_length), m_Sprite(_sprite),
m_sourceX(_x), m_sourceY(_y), m_sourceW(_w), m_sourceH(_h)
{
	m_PosX = 0;
	m_PosY = 0;
};

Ship::~Ship()
{
}

void Ship::ToggleRotate()
{
	if (m_Rotate == 0)
	{
		
		switch (m_Life)
		{
		case 1:
			*this = Ship(1, sea_pixels, 652, 107, 25, 25);
			break;
		case 2:
			*this = Ship(2, sea_pixels, 627, 107, 25, 50);
			break;
		case 3:
			*this = Ship(3, sea_pixels, 604, 107, 25, 75);
			break;
		case 4:
			*this = Ship(4, sea_pixels, 580, 107, 25, 100);
			break;
		case 5:
			*this = Ship(5, sea_pixels, 557, 107, 25, 125);
			break;
		default:
			break;
		}
		m_Rotate = 1.57f;
	}
	
	else
	{
		
		switch (m_Life)
		{
		case 1:
			*this = Ship(1, sea_pixels, 465, 75, 25, 25);
			break;
		case 2:
			*this = Ship(2, sea_pixels, 415, 75, 50, 25);
			break;
		case 3:
			*this = Ship(3, sea_pixels, 640, 50, 75, 25);
			break;
		case 4:
			*this = Ship(4, sea_pixels, 540, 50, 100, 25);
			break;
		case 5:
			*this = Ship(5, sea_pixels, 415, 50, 125, 25);
			break;
		default:
			break;
		}
		m_Rotate = 0;
		
	}
		
}

bool Ship::CalculateGrid()
{
	int x = m_PosX / GridUnit;
	int y = m_PosY / GridUnit;

	LifeStruct temp;
	
	for (int i = 0; i < m_Life; i++)
	{
		if (m_Rotate == 0)
		{
			temp.m_NumberX = x + i;
			temp.m_NumberY = y;



		}
		else
		{
			temp.m_NumberX = x;
			temp.m_NumberY = y + i;

		}


		m_LifeStruct.push_back(temp);


	//	if (CheckCollideWithOtherShips())
	//		return false;
	}

	return true;
}