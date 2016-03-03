#include "Player.h"
#include "..//Resource/sea.h"
#include <iostream>

Player::Player()
{
	m_Ships[0] = Ship(5, sea_pixels, 415, 50, 125, 25);
	m_Ships[1] = Ship(4, sea_pixels, 540, 50, 100, 25);
	m_Ships[2] = Ship(3, sea_pixels, 640, 50, 75, 25);
	m_Ships[3] = Ship(2, sea_pixels, 415, 75, 50, 25);
	m_Ships[4] = Ship(1, sea_pixels, 465, 75, 25, 25);


}


Player::~Player()
{
}

void Player::AssignRocket( Player* opponent)
{

	if (GetAsyncKeyState(VK_LEFT) & 0x1 )
	{

		m_Choose.m_ChooseX -= GridUnit;

		if (m_Choose.m_ChooseX <= 0)
			m_Choose.m_ChooseX = 0;


	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x1 )
	{
		m_Choose.m_ChooseX += GridUnit;
		
		if (m_Choose.m_ChooseX + GridUnit >= GridUnitMultiplyNumber)
			m_Choose.m_ChooseX = GridUnitMultiplyNumber - GridUnit;
		

	}

	if (GetAsyncKeyState(VK_UP) & 0x1 )
	{
		m_Choose.m_ChooseY -= GridUnit;

		if (m_Choose.m_ChooseY <= 0)
			m_Choose.m_ChooseY = 0;


	}

	if (GetAsyncKeyState(VK_DOWN) & 0x1 )
	{
		m_Choose.m_ChooseY += GridUnit;
	
		if (m_Choose.m_ChooseY >= GridUnitMultiplyNumber - GridUnit)
			m_Choose.m_ChooseY = GridUnitMultiplyNumber - GridUnit;
		
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x1 || m_AI)
	{
		LifeStruct temp;
		temp.m_NumberX = m_Choose.m_ChooseX/GridUnit;
		temp.m_NumberY = m_Choose.m_ChooseY / GridUnit;

		while (m_AI)
		{
			temp.m_NumberX = rand() % GridX;
			temp.m_NumberY = rand() % GridX;
			if (m_TrackBoard.CheckRocketOccupy(temp) == false)
				break;
		}

		if (m_TrackBoard.CheckRocketOccupy(temp) == false)
		{
			if (m_TrackBoard.CheckOpponetPrimaryBoard(temp, opponent->GetPrimaryBoard()))
			{
				m_TrackBoard.SetRocketBoard(temp, boardState::hitMissile);
				opponent->UpdateShips(temp);
			}
			   
			else
				m_TrackBoard.SetRocketBoard(temp, boardState::noHitMissle);

			m_State = PlayerState::wait;
		}
			
	}
}
void Player::UpdateShips(const LifeStruct& _life)
{
	for (int shipIndex = 0; shipIndex < TotalShip; shipIndex++)
	{
		auto iter = m_Ships[shipIndex].m_LifeStruct.begin();

		for (unsigned int lifeIndex = 0; lifeIndex < m_Ships[shipIndex].m_LifeStruct.size(); lifeIndex++)
		{
			
			if (iter->m_NumberX == _life.m_NumberX&& iter->m_NumberY == _life.m_NumberY)
			{
				m_Ships[shipIndex].m_LifeStruct.erase(iter);
				m_Ships[shipIndex].SetLife(m_Ships[shipIndex].GetLife() - 1);

				if (m_Ships[shipIndex].GetLife() == 0)
					m_TotalDestroyShips++;

				return;
			}	
			iter++;
		}
	}
}

void Player::AssignMarine()
{
	

	if (m_Ships[m_AssignedIndex].GetAssigned() == false)
	{


		if (m_AI)
		{
			m_Ships[m_AssignedIndex].m_PosX = (rand() % GridX)*GridUnit;
			m_Ships[m_AssignedIndex].m_PosY = (rand() % GridX)*GridUnit;
		}

		if (GetAsyncKeyState('R') & 0x1 || m_AI)
		{
			if (m_AI && rand() % 2 == 0)
				m_Ships[m_AssignedIndex].ToggleRotate();
			else if (m_AI == false)
				m_Ships[m_AssignedIndex].ToggleRotate();
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x1 || m_AI)
		{
			if (!m_AI)
			m_Ships[m_AssignedIndex].m_PosX -= GridUnit;
			
		    if (m_Ships[m_AssignedIndex].m_PosX <= 0)
				m_Ships[m_AssignedIndex].m_PosX = 0;
			
			
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x1 || m_AI)
		{
			if (!m_AI)
			m_Ships[m_AssignedIndex].m_PosX += GridUnit;
			
			if (m_Ships[m_AssignedIndex].m_Rotate == 0)
			{
				if (m_Ships[m_AssignedIndex].m_PosX + m_Ships[m_AssignedIndex].GetLife()*GridUnit >= GridUnitMultiplyNumber)
					m_Ships[m_AssignedIndex].m_PosX = GridUnitMultiplyNumber - m_Ships[m_AssignedIndex].GetLife()*GridUnit;
			}
			else
			{
				if (m_Ships[m_AssignedIndex].m_PosX  + GridUnit >= GridUnitMultiplyNumber)
					m_Ships[m_AssignedIndex].m_PosX = GridUnitMultiplyNumber - GridUnit;
			}
			
		}

		if (GetAsyncKeyState(VK_UP) & 0x1 || m_AI)
		{
			if (!m_AI)
			m_Ships[m_AssignedIndex].m_PosY -= GridUnit;
			
			if (m_Ships[m_AssignedIndex].m_PosY <= 0)
					m_Ships[m_AssignedIndex].m_PosY = 0;
			
			
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x1 || m_AI)
		{
			if (!m_AI)
			m_Ships[m_AssignedIndex].m_PosY += GridUnit;
		
			if (m_Ships[m_AssignedIndex].m_Rotate == 0)
			{
				if (m_Ships[m_AssignedIndex].m_PosY >= GridUnitMultiplyNumber - GridUnit)
					m_Ships[m_AssignedIndex].m_PosY = GridUnitMultiplyNumber - GridUnit;
			}
			else
			{
				if (m_Ships[m_AssignedIndex].m_PosY + m_Ships[m_AssignedIndex].GetLife()*GridUnit >= GridUnitMultiplyNumber - GridUnit)
					m_Ships[m_AssignedIndex].m_PosY = GridUnitMultiplyNumber - m_Ships[m_AssignedIndex].GetLife()*GridUnit;
			}
		}

		

		
		if (GetAsyncKeyState(VK_RETURN) & 0x1 || m_AI)
		{
			

			m_Ships[m_AssignedIndex].CalculateGrid();
			

			//m_PrimaryBoard
			if (m_PrimaryBoard.CheckShipOccupy(m_Ships[m_AssignedIndex].m_LifeStruct) == true)
			{
				m_Ships[m_AssignedIndex].m_LifeStruct.clear();
				m_Ships[m_AssignedIndex].SetAssigned(false);
			}
			else
			{
				m_PrimaryBoard.SetBoard(m_Ships[m_AssignedIndex].m_LifeStruct);
				m_Ships[m_AssignedIndex].SetAssigned(true);
				m_AssignedIndex++;
			}

				

			if (m_AssignedIndex >= 5 && m_State == PlayerState::inProcess)
				m_State = PlayerState::assignFinish;

		}

	}

	
}

void Player::SetGridOffset(int _PrimaryGridX, int _PrimaryGridY, int _TrackGridX, int _TrackGridY)
{
	m_PrimaryGridX = _PrimaryGridX;
	m_PrimaryGridY = _PrimaryGridY;
	m_TrackGridX = _TrackGridX;
	m_TrackGridY = _TrackGridY;

}