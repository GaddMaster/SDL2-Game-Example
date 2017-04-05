#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "GameStateMachine.h"
#include <vector>

class Game
{
	public://///////////////////////////////////////
    
		//SINGLETON POINTER TO INSTANCE
		static Game* Instance()
		{
			if(s_pInstance == 0)
			{
				s_pInstance = new Game();
				return s_pInstance;
			}
        
			return s_pInstance;
		}

		bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);//OUR INITIALIZATION FUNCTION
    
		void render();//RENDER FUNCTION
		void update();//UPDATE FUNCTION
		void handleEvents();//EVENT HANDLER FUNCTION
		void clean();//CLEAN UP AFTER GAME HAS EXITED
    
		SDL_Renderer* getRenderer() const { return m_pRenderer; }//RETRIEVE POINTER TO RENDERER
		SDL_Window* getWindow() const { return m_pWindow; }//RETRIEVE POINTER TO WINDOW
		GameStateMachine* getStateMachine() { return m_pGameStateMachine; }//RETRIEVE POINTER TO GAME STATE MACHINE
    
		void setPlayerLives(int lives) { m_playerLives = lives; }
		int getPlayerLives() { return m_playerLives; }
    
		void setCurrentLevel(int currentLevel);
		const int getCurrentLevel() { return m_currentLevel; }
    
		void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
		const int getNextLevel() { return m_nextLevel; }
    
		void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
		const bool getLevelComplete() { return m_bLevelComplete; }
    
		bool running() { return m_bRunning; }
    
		void quit() { m_bRunning = false; }
    
		int getGameWidth() const { return m_gameWidth; }
		int getGameHeight() const { return m_gameHeight; }
		float getScrollSpeed() { return m_scrollSpeed; }

		bool changingState() { return m_bChangingState; }
		void changingState(bool cs) { m_bChangingState = cs; }
    
		std::vector<std::string> getLevelFiles() { return m_levelFiles; }
    
	private://///////////////////////////////////////

		bool m_bChangingState;
    
		SDL_Window* m_pWindow;//WINDOW POINTER
		SDL_Renderer* m_pRenderer;//RENDERER POINTER
		GameStateMachine* m_pGameStateMachine;//GAME STATE MACHINE POINTER
    
		bool m_bRunning;//RUNNING STATE
    
		static Game* s_pInstance;//INSTANCE FOR SINGLETON
    
		int m_gameWidth;
		int m_gameHeight;
		float m_scrollSpeed;//SCROLL SPEED
    
		int m_playerLives;//AMOUNT OF LIVES PLAYER HAS
    
		int m_currentLevel;//CURRENTLY RUNNING LEVEL
		int m_nextLevel;
		bool m_bLevelComplete;
    
		std::vector<std::string> m_levelFiles;
    
		Game();//PRIVATE FOR SINGLETON 
		~Game();//PRIVATE FOR SINGLETON 
    
		Game(const Game&);
		Game& operator=(const Game&);
};

typedef Game TheGame;//OUR SINGLETON INSTANCE TYPE

#endif//DEFINE GAME_H
