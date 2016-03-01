
#define _USE_MATH_DEFINES


#include <iostream>
#include "RasterSurface.h"
#include "tiles_12.h" // town
#include "fire_01.h"
#include "XTime.h"
#include "DrawImage.h"
#include "Player.h"
#include "GameState.h"
#include "Factors.h"






int main(void)
{
	drawImage m_drawImage;
	XTime m_XTime;
	GameState m_Game;
	Player n_players[2];
	n_players[0].SetState(PlayerState::inProcess);

	m_XTime.Restart();

	//m_drawImage.makeRandomTree();

	RS_Initialize(RS_WIDTH, RS_HEIGHT);

	Matrix2D2 m_matrix2D2((float)M_PI_4);
	int x = 250;
	int animationCounter = 0;
	do
	{
		m_XTime.Signal();

		m_drawImage.cleanBackGround(RS_WIDTH, RS_HEIGHT);

		//draw back ground
		for (int x = 0; x < RS_WIDTH; x += 50)
		{
			for (int y = 0; y < RS_HEIGHT; y += 50)
			{
				m_drawImage.BLIT(BackBuffer, x, y, tiles_12_pixels, 273, 113, tiles_12_width, 50, 50);
			}
		}

		switch (m_Game.m_State)
		{
		case state::init:

			for (int playerIndex = 0; playerIndex < 2; playerIndex++)
			{
				if (n_players[playerIndex].GetState() == PlayerState::inProcess)
				   n_players[playerIndex].AssignMarine();

				if (n_players[0].GetState() == PlayerState::wait)
					n_players[1].SetState(PlayerState::inProcess);

				for (int shipIndex = 0; shipIndex < 5; shipIndex++)
					m_drawImage.BLIT(BackBuffer, n_players[playerIndex].GetShip(shipIndex)->m_PosX, n_players[playerIndex].GetShip(shipIndex)->m_PosY,
					n_players[playerIndex].GetShip(shipIndex)->m_Sprite, n_players[playerIndex].GetShip(shipIndex)->m_sourceX,
					n_players[playerIndex].GetShip(shipIndex)->m_sourceY, 757, n_players[playerIndex].GetShip(shipIndex)->m_sourceW, 
					n_players[playerIndex].GetShip(shipIndex)->m_sourceH);
			}
				
			break;
		case state::play:
				break;

		case state::over:
			break;
		default:
			break;
		}
		////draw tree
		//for (int i = 0; i <5; i++)
		//{
		//	m_drawImage.BLIT(BackBuffer, m_drawImage.m_position[i].x, m_drawImage.m_position[i].y, tiles_12_pixels, 321, 14, tiles_12_width, 64, 85);
		//}
		//for (int i = 6; i < 10; i++)
		//{
		//	//	m_drawImage.BLIT(BackBuffer, m_drawImage.m_position[i].x, m_drawImage.m_position[i].y, tiles_12_pixels, 321,
		//	//	14, tiles_12_width, 64, 85, (float)M_PI, m_drawImage.m_position[i].x + 64 / 2, m_drawImage.m_position[i].y + 85 / 2);

		//	m_drawImage.BLIT(BackBuffer, m_drawImage.m_position[i].x, m_drawImage.m_position[i].y, tiles_12_pixels, 321,
		//		14, tiles_12_width, 64, 85, (float)M_PI, m_drawImage.m_position[i].x + 64 / 2, m_drawImage.m_position[i].y + 85 / 2);
		//}

		int sourceX = 0;
		int sourceY = 0;

		sourceX = animationCounter % 8 * 128;
		sourceY = animationCounter / 8 * 128;
		if (GetAsyncKeyState(VK_LEFT) & 0x1)
			x += 10;
		/*
		m_drawImage.BLIT(BackBuffer, x, 250, fire_01_pixels, sourceX, sourceY, fire_01_height, 128, 128, m_matrix2D2, 250 + 128 / 2, 250 + 128 / 2);

		if (m_XTime.TotalTimeExact() >= 1.0f / 30.0f)
		{
			animationCounter++;

			if (animationCounter >= 64)
				animationCounter = 0;

			m_XTime.Restart();
		}
*/

	} while (RS_Update(BackBuffer, RS_NUMPIXELS));

	RS_Shutdown();

	return 0;
}

