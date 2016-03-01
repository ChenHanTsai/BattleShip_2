#include "Player.h"
#include <iostream>

Player::Player()
{
	m_Ships[0] = Ship(1, Submarine_pixels,0,0,100,68);
	m_Ships[1] = Ship(2, Submarine_pixels, 0, 0, 100, 68);
	m_Ships[2] = Ship(3, Submarine_pixels, 0, 0, 100, 68);
	m_Ships[3] = Ship(4, Submarine_pixels, 0, 0, 100, 68);
	m_Ships[4] = Ship(5, Submarine_pixels, 0, 0, 100, 68);
}


Player::~Player()
{
}

void Player::AssignMarine()
{
	
	if (m_Ships[m_AssignedIndex].GetAssigned() == false)
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x1)
		{
			m_Ships[m_AssignedIndex].m_PosX -= 50;
			if (m_Ships[m_AssignedIndex].m_PosX <= 0)
				m_Ships[m_AssignedIndex].m_PosX = 0;
		}
			
		if (GetAsyncKeyState(VK_RIGHT) & 0x1)
		{
			m_Ships[m_AssignedIndex].m_PosX += 50;
			if (m_Ships[m_AssignedIndex].m_PosX >= RS_WIDTH)
				m_Ships[m_AssignedIndex].m_PosX = RS_WIDTH;
		}
				
		if (GetAsyncKeyState(VK_UP) & 0x1)
		{
			m_Ships[m_AssignedIndex].m_PosY -= 50;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x1)
		{
			m_Ships[m_AssignedIndex].m_PosY += 50;
		}

		if (GetAsyncKeyState('R') & 0x1)
		{
			m_Ships[m_AssignedIndex].ToggleRotate();
		}


		if (GetAsyncKeyState(VK_RETURN) & 0x1)
		{
			m_Ships[m_AssignedIndex].SetAssigned( true);
			m_AssignedIndex++;

			if (m_AssignedIndex >= 5 && m_State == PlayerState::inProcess)
				m_State = PlayerState::wait;

		}
			
	}

	
}