
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
#include "..//Resource/sea.h"





int main(void)
{
	drawImage m_drawImage;
	XTime m_XTime;
	GameState m_Game;
	
	m_XTime.Restart();

	//m_drawImage.makeRandomTree();

	RS_Initialize(RS_WIDTH, RS_HEIGHT);

	Matrix2D2 m_matrix2D2((float)M_PI_4);
	int x = 250;
	int animationCounter = 0;
	Player n_players[2];

	n_players[0].SetState(PlayerState::inProcess);
	n_players[0].SetGridOffset(Player1PrimaryOffsetX, Player1PrimaryOffsetY, Player1TrackOffsetX, Player1TrackOffsetY);
	n_players[1].SetGridOffset(Player1PrimaryOffsetX + Player2ShiftX, Player1PrimaryOffsetY, Player1TrackOffsetX + Player2ShiftX, Player1TrackOffsetY);
	do
	{
		m_XTime.Signal();

		m_drawImage.cleanBackGround(RS_WIDTH, RS_HEIGHT);

		//Draw back ground
		for (int x = 0; x < RS_WIDTH; x += GridUnit)
		{
			for (int y = 0; y < RS_HEIGHT; y += GridUnit)
			{
				m_drawImage.BLIT(BackBuffer, x, y, sea_pixels, 273, 112, sea_width, GridUnit, GridUnit);
			}
		}

		//draw back ground
		for (int i = 0; i < 2; i++)
		{
			//Draw tacking
			m_drawImage.BLIT(BackBuffer, n_players[i].m_TrackGridX, n_players[i].m_TrackGridY, sea_pixels, 415, 22, sea_width, GridUnitMultiplyNumber, GridUnit);
			m_drawImage.BLIT(BackBuffer, n_players[i].m_TrackGridX - GridUnit, n_players[i].m_TrackGridY + GridUnit, sea_pixels, 423, 119, sea_width, GridUnit, GridUnitMultiplyNumber);

			//Draw primary
			m_drawImage.BLIT(BackBuffer, n_players[i].m_PrimaryGridX, n_players[i].m_PrimaryGridY, sea_pixels, 415, 22, sea_width, GridUnitMultiplyNumber, GridUnit);
			m_drawImage.BLIT(BackBuffer, n_players[i].m_PrimaryGridX - GridUnit, n_players[i].m_PrimaryGridY + GridUnit, sea_pixels, 423, 119, sea_width, GridUnit, GridUnitMultiplyNumber);

		}


		//Draw middle gap
		for (int y = 0; y < RS_HEIGHT; y += GridUnit)
		{
			m_drawImage.BLIT(BackBuffer, RS_WIDTH / 2 - GridUnit, y, sea_pixels, 520, 124, sea_width, GridUnit, GridUnit);
		}
		m_Game.m_State = state::play;
		switch (m_Game.m_State)
		{
		case state::init:

			for (int playerIndex = 0; playerIndex < 2; playerIndex++)
			{
				if (n_players[0].GetState() == PlayerState::assignFinish)
					n_players[1].SetState(PlayerState::inProcess);

				if (n_players[playerIndex].GetState() == PlayerState::inProcess)
				   n_players[playerIndex].AssignMarine();			

				if (n_players[1].GetState() == PlayerState::assignFinish)
				{
				   m_Game.m_State = state::play;
				   n_players[0].SetState(PlayerState::inProcess);
			    }												
			}
				
			break;
		case state::play:
			if (n_players[0].GetState() == PlayerState::wait)
			{
				n_players[1].SetState(PlayerState::inProcess);
				n_players[1].AssignRocket();
				m_drawImage.BLIT(BackBuffer, n_players[1].GetChoose().m_ChooseX + n_players[1].m_TrackGridX,
					n_players[1].GetChoose().m_ChooseY + n_players[1].m_TrackGridY + GridUnit,n_players[1].GetChoose()._sprite,
					n_players[1].GetChoose().m_SourceX,n_players[1].GetChoose().m_SourceY, sea_width, 
					n_players[1].GetChoose().m_SourceW,n_players[1].GetChoose().m_SourceH);

				if (n_players[1].GetState() == PlayerState::wait)
					n_players[0].SetState(PlayerState::inProcess);
			}
			else
			{
				n_players[0].SetState(PlayerState::inProcess);
				n_players[0].AssignRocket();
				m_drawImage.BLIT(BackBuffer, n_players[0].GetChoose().m_ChooseX + n_players[0].m_TrackGridX,
					n_players[0].GetChoose().m_ChooseY + n_players[0].m_TrackGridY + GridUnit,
					n_players[0].GetChoose()._sprite, n_players[0].GetChoose().m_SourceX,
					n_players[0].GetChoose().m_SourceY, sea_width, n_players[0].GetChoose().m_SourceW,
					n_players[0].GetChoose().m_SourceH);

				if (n_players[0].GetState() == PlayerState::wait)
					n_players[1].SetState(PlayerState::inProcess);
			}
				break;

		case state::over:
			break;
		default:
			break;
		}

		for (int playerIndex = 0; playerIndex < 2; playerIndex++)
		{
			for (int shipIndex = 0; shipIndex < 5; shipIndex++)
				m_drawImage.BLIT(BackBuffer, n_players[playerIndex].GetShip(shipIndex)->m_PosX + n_players[playerIndex].m_PrimaryGridX,
				n_players[playerIndex].GetShip(shipIndex)->m_PosY + n_players[playerIndex].m_PrimaryGridY + GridUnit,
				n_players[playerIndex].GetShip(shipIndex)->m_Sprite, n_players[playerIndex].GetShip(shipIndex)->m_sourceX,
				n_players[playerIndex].GetShip(shipIndex)->m_sourceY, sea_width, n_players[playerIndex].GetShip(shipIndex)->m_sourceW,
				n_players[playerIndex].GetShip(shipIndex)->m_sourceH);

		

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

