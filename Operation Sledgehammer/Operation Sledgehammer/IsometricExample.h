#ifndef ISOMETRIC_EXAMPLE_H
#define ISOMETRIC_EXAMPLE_H

#include "GameState.h"
#include "CollisionManager.h"
#include "Level.h"
#include <vector>

class GameObject;
class SDLGameObject;
class Level;

class IsometricExample : public GameState
{
public:

	virtual ~IsometricExample() { delete pLevel; }

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

private:

	static const std::string s_playID;

	CollisionManager m_collisionManager;

	std::vector<GameObject*> m_gameObjects;

	Level* pLevel;
};


#endif//DEFINED ISOMETRIC_EXAMPLE_H

