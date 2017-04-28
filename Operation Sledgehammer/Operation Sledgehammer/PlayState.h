#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "CollisionManager.h"
#include "Level.h"
#include <vector>

class GameObject;
class SDLGameObject;
class Level;

class PlayState : public GameState
{
	public:
    
		virtual ~PlayState(){delete pLevel;};
		virtual void update();
		virtual void render();
		virtual bool onEnter();
		virtual bool onExit();
    
		virtual std::string getStateID() const { return s_playID; }
    
	private:
    
		static const std::string s_playID;
    
		//CollisionManager m_collisionManager;
    
		std::vector<GameObject*> m_gameObjects;
    
		Level* pLevel;
};


#endif//DEFINED PLAY_STATE_H
