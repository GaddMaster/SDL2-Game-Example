#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <vector>
#include "GameState.h"

class GameStateMachine
{
	public://///////////////////////////////////////
    
		//CONSTRUCTOR & DE-CONSTRUCTOR
		GameStateMachine() {}
		~GameStateMachine() {}
    
		void update();//UPDATE GAME STATES
		void render();//RENDER GAME STATES
    
		void pushState(GameState* pState);
		void changeState(GameState* pState);
		void popState();
    
		void clean();

		std::vector<GameState*>& getGameStates() { return m_gameStates; }
    
	private://///////////////////////////////////////

		std::vector<GameState*> m_gameStates;
};

#endif//DEFINE GAME_STATE_MACHINE_H
