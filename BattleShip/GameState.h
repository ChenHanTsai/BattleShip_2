#pragma once

enum state{ init, play, over };

class GameState
{

public:
	state m_State = state::init;
	GameState();
	~GameState();
};

