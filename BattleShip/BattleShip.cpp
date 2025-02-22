
#define _USE_MATH_DEFINES


#include <iostream>
#include "RasterSurface.h"
#include "XTime.h"
#include "DrawImage.h"
#include "Player.h"
#include "GameState.h"
#include "Factors.h"
#include "..//Resource/sea.h"
#include "..//Resource/start.h"
#include "..//Resource/over.h"
#include <ctime>



int main(void)
{
	drawImage m_drawImage;
	XTime m_XTime;
	GameState m_Game;
	
	srand((unsigned)time(NULL));

	m_XTime.Restart();

	int currPlayerIndex = 0;
	int nextPlayerIndex = 1;


	RS_Initialize(RS_WIDTH, RS_HEIGHT);

	Matrix2D2 m_matrix2D2((float)M_PI_4);

	int animationCounter = 0;
	int sourceX = 0;
	int sourceY = 0;
	bool pause = false;
	

	int m_menuX = MenuX;
	int m_menuY = MenuY;
	bool playing = true;
	int m_menuOption = 0;
	Player n_players[2];

	n_players[0].SetState(PlayerState::inProcess);
	n_players[0].SetGridOffset(Player1PrimaryOffsetX, Player1PrimaryOffsetY, Player1TrackOffsetX, Player1TrackOffsetY);
	n_players[1].SetGridOffset(Player1PrimaryOffsetX + Player2ShiftX, Player1PrimaryOffsetY, Player1TrackOffsetX + Player2ShiftX, Player1TrackOffsetY);
	m_Game.m_State = state::start;
	do
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
			playing = false;

		m_XTime.Signal();

		m_drawImage.cleanBackGround(RS_WIDTH, RS_HEIGHT);


		if (!m_Game.m_State == state::start)
		{
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

			//draw ships
			for (int playerIndex = 0; playerIndex < 2; playerIndex++)
			{
				for (int shipIndex = 0; shipIndex < 5; shipIndex++)
					m_drawImage.BLIT(BackBuffer, n_players[playerIndex].GetShip(shipIndex)->m_PosX + n_players[playerIndex].m_PrimaryGridX,
					n_players[playerIndex].GetShip(shipIndex)->m_PosY + n_players[playerIndex].m_PrimaryGridY + GridUnit,
					n_players[playerIndex].GetShip(shipIndex)->m_Sprite, n_players[playerIndex].GetShip(shipIndex)->m_sourceX,
					n_players[playerIndex].GetShip(shipIndex)->m_sourceY, sea_width, n_players[playerIndex].GetShip(shipIndex)->m_sourceW,
					n_players[playerIndex].GetShip(shipIndex)->m_sourceH);
			}

			//draw flag
			for (int playerIndex = 0; playerIndex < 2; playerIndex++)
			{
				int opponenIndex = 0;
				if (playerIndex == 0)
					opponenIndex = 1;
				else
					opponenIndex = 0;

				for (int flagIndex = 0; flagIndex < n_players[opponenIndex].GetTotalDestroyShips(); flagIndex++)
					m_drawImage.BLIT(BackBuffer, flagIndex*GridUnit + n_players[playerIndex].m_TrackGridX,
					n_players[playerIndex].m_TrackGridY - GridUnit,
					n_players[currPlayerIndex].GetFlagSymbol().m_Sprite,
					n_players[currPlayerIndex].GetFlagSymbol().m_SourceX, n_players[currPlayerIndex].GetFlagSymbol().m_SourceY, sea_width,
					n_players[currPlayerIndex].GetFlagSymbol().m_SourceW, n_players[currPlayerIndex].GetFlagSymbol().m_SourceH);
			}

			//draw rocket
			for (int playerIndex = 0; playerIndex < 2; playerIndex++)
			{
				//Tracking system
				for (int x = 0; x < GridX; x++)
				{
					for (int y = 0; y < GridX; y++)
					{
						if (n_players[playerIndex].GetTrackBoard()->m_board[x][y] == boardState::hitMissile)
						{
							m_drawImage.BLIT(BackBuffer, x*GridUnit + n_players[playerIndex].m_TrackGridX,
								y*GridUnit + n_players[playerIndex].m_TrackGridY + GridUnit,
								n_players[currPlayerIndex].GetHitSymbol().m_Sprite,
								n_players[currPlayerIndex].GetHitSymbol().m_SourceX, n_players[currPlayerIndex].GetHitSymbol().m_SourceY, sea_width,
								n_players[currPlayerIndex].GetHitSymbol().m_SourceW, n_players[currPlayerIndex].GetHitSymbol().m_SourceH);
						}
						else if (n_players[playerIndex].GetTrackBoard()->m_board[x][y] == boardState::noHitMissle)
						{
							m_drawImage.BLIT(BackBuffer, x*GridUnit + n_players[playerIndex].m_TrackGridX,
								y*GridUnit + n_players[playerIndex].m_TrackGridY + GridUnit,
								n_players[currPlayerIndex].GetNoHitSymbol().m_Sprite,
								n_players[currPlayerIndex].GetNoHitSymbol().m_SourceX, n_players[currPlayerIndex].GetNoHitSymbol().m_SourceY, sea_width,
								n_players[currPlayerIndex].GetNoHitSymbol().m_SourceW, n_players[currPlayerIndex].GetNoHitSymbol().m_SourceH);
						}
					}
				}

				int opponent = 0;
				if (playerIndex == 0)
					opponent = 1;
				else
					opponent = 0;

				//primary system
				for (int x = 0; x < GridX; x++)
				{
					for (int y = 0; y < GridX; y++)
					{
						if (n_players[playerIndex].GetTrackBoard()->m_board[x][y] == boardState::hitMissile)
						{
							m_drawImage.BLIT(BackBuffer, x*GridUnit + n_players[opponent].m_PrimaryGridX,
								y*GridUnit + n_players[opponent].m_PrimaryGridY + GridUnit,
								n_players[currPlayerIndex].GetHitSymbol().m_Sprite,
								n_players[currPlayerIndex].GetHitSymbol().m_SourceX, n_players[currPlayerIndex].GetHitSymbol().m_SourceY, sea_width,
								n_players[currPlayerIndex].GetHitSymbol().m_SourceW, n_players[currPlayerIndex].GetHitSymbol().m_SourceH);
						}
						else if (n_players[playerIndex].GetTrackBoard()->m_board[x][y] == boardState::noHitMissle)
						{
							m_drawImage.BLIT(BackBuffer, x*GridUnit + n_players[opponent].m_PrimaryGridX,
								y*GridUnit + n_players[opponent].m_PrimaryGridY + GridUnit,
								n_players[currPlayerIndex].GetNoHitSymbol().m_Sprite,
								n_players[currPlayerIndex].GetNoHitSymbol().m_SourceX, n_players[currPlayerIndex].GetNoHitSymbol().m_SourceY, sea_width,
								n_players[currPlayerIndex].GetNoHitSymbol().m_SourceW, n_players[currPlayerIndex].GetNoHitSymbol().m_SourceH);
						}
					}
				}

			}
		}
		

		switch (m_Game.m_State)
		{
		case state::start:
			

			m_drawImage.BLIT(BackBuffer, 0,0,	start_pixels,0, 0, start_width,RS_WIDTH, RS_HEIGHT);
		
			sourceX = animationCounter % 7 * MarineW;
			sourceY = animationCounter / 7 * MarineW;

			if (m_XTime.TotalTimeExact() >= 1.0f / 1.0f)
			{
				animationCounter++;

				if (animationCounter >= 4)
					animationCounter = 0;

				m_XTime.Restart();
			}

			if (GetAsyncKeyState(VK_RIGHT) & 0x1)
			{
				m_menuOption++;

				if (m_menuOption >= 3)
					m_menuOption = 2;
				else
				   m_menuX += MenuShift;
			}

			if (GetAsyncKeyState(VK_LEFT) & 0x1)
			{

				m_menuOption--;

				if (m_menuOption <0)
					m_menuOption = 0;
				else
					m_menuX -= MenuShift;
			
			}

			m_drawImage.BLIT(BackBuffer, m_menuX, m_menuY, sea_pixels, MarineX + sourceX, MarineY + sourceY, sea_width, MarineW, MarineH);


			if (GetAsyncKeyState(VK_RETURN) & 0x1)
			{
				m_Game.m_State = state::init;

				switch (m_menuOption)
				{
				case 0:
					n_players[0].SetAI(false);
					n_players[1].SetAI(false);
					break;
				case 1:
					n_players[0].SetAI(false);
					n_players[1].SetAI(true);
					break;

				case 2:
					n_players[0].SetAI(true);
					n_players[1].SetAI(true);
					break;
				default:
					break;
				}
			}

			
			break;
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
				   n_players[currPlayerIndex].SetState(PlayerState::inProcess);
				   n_players[nextPlayerIndex].SetState(PlayerState::wait);
			    }					
			}
			
			m_drawImage.BLIT(BackBuffer, Player1NameX, Player1NameY, sea_pixels, Player1SourceX, Player1SourceY, sea_width, PlayerNameSourceW, PlayerNameSourceH);
			m_drawImage.BLIT(BackBuffer, Player2NameX, Player2NameY, sea_pixels, Player2SourceX, Player2SourceY, sea_width, PlayerNameSourceW, PlayerNameSourceH);
			break;
		case state::play:
			if (n_players[nextPlayerIndex].GetState() == PlayerState::wait)
			{
				n_players[currPlayerIndex].SetState(PlayerState::inProcess);
				n_players[currPlayerIndex].AssignRocket(&n_players[nextPlayerIndex]);
				m_drawImage.BLIT(BackBuffer, n_players[currPlayerIndex].GetChoose().m_ChooseX + n_players[currPlayerIndex].m_TrackGridX,
					n_players[currPlayerIndex].GetChoose().m_ChooseY + n_players[currPlayerIndex].m_TrackGridY + GridUnit, n_players[currPlayerIndex].GetChoose().m_Sprite,
					n_players[currPlayerIndex].GetChoose().m_SourceX, n_players[currPlayerIndex].GetChoose().m_SourceY, sea_width,
					n_players[currPlayerIndex].GetChoose().m_SourceW, n_players[currPlayerIndex].GetChoose().m_SourceH);
			}
				
			if (n_players[currPlayerIndex].GetState() == PlayerState::wait)
				{
					n_players[nextPlayerIndex].SetState(PlayerState::inProcess);

					if (currPlayerIndex == 0)
					{
						currPlayerIndex = 1;
						nextPlayerIndex = 0;
					}
							
					else
					{
						currPlayerIndex = 0;
						nextPlayerIndex = 1;
					}
						
				}
				
			for (int i = 0; i < 2; i++)
			{
				if (n_players[i].GetTotalDestroyShips() == TotalShip)
				{
					m_Game.m_State = state::over;
				}				
			}

			m_drawImage.BLIT(BackBuffer, Player1NameX, Player1NameY, sea_pixels, Player1SourceX, Player1SourceY, sea_width, PlayerNameSourceW, PlayerNameSourceH);
			m_drawImage.BLIT(BackBuffer, Player2NameX, Player2NameY, sea_pixels, Player2SourceX, Player2SourceY, sea_width, PlayerNameSourceW, PlayerNameSourceH);
				break;

		case state::over:
			if (n_players[0].GetTotalDestroyShips() != TotalShip)
			{
				m_drawImage.BLIT(BackBuffer, RS_WIDTH / 2, 0, over_pixels, RS_WIDTH / 2, 0, over_width, RS_WIDTH / 2, RS_HEIGHT );
			}
			else
			{
				m_drawImage.BLIT(BackBuffer, 0, 0, over_pixels, 0, 0, over_width, RS_WIDTH / 2, RS_HEIGHT );
			}

			break;
		default:
			break;
		}

	} while (RS_Update(BackBuffer, RS_NUMPIXELS) && playing);

	RS_Shutdown();

	return 0;
}

