#pragma once

enum state{ start, init, play, over };

class GameState
{

public:
	state m_State = state::init;
	GameState();
	~GameState();
};

