#include "Ship.h"

#include "Factors.h"
Ship::Ship()
{
}


Ship::~Ship()
{
}

void Ship::ToggleRotate()
{
	if (m_Rotate == 0)
		m_Rotate = 1.57f;
	else
		m_Rotate = 0;
}

bool Ship::CalculateGrid()
{
	int x = m_PosX / GridUnit;
	int y = m_PosX / GridUnit;

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