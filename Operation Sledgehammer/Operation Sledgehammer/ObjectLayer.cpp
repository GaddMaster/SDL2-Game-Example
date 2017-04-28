
#include "ObjectLayer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Game.h"
#include "Level.h"

ObjectLayer::~ObjectLayer()
{
    for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)// < m_gameObjects.size(); i++)
    {
        delete (*it);
    }
    m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
    m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
    m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
	m_collisionManager.checkEnemyPlayerRocketCollision((const std::vector<GameObject*>&)m_gameObjects);
    m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);
	//m_collisionManager.checkPlayerCrateCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);


	if(pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
	{
		m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
	}
    
    // iterate through the objects
    if(!m_gameObjects.empty())
    {
        for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)// < m_gameObjects.size(); i++)
        {
			//if ((*it)->type() == "Crate")
				//std::cout << "CRATE" << std::endl;

            if((*it)->getPosition().getX() <= TheGame::Instance()->getGameWidth())
            {
                (*it)->setUpdating(true);
                (*it)->update();
            }
            else
            {
                if((*it)->type() != std::string("Player"))
                {
                    (*it)->setUpdating(false);
                    (*it)->scroll(TheGame::Instance()->getScrollSpeed());
                }
				else if ((*it)->type() == std::string("Crate"))
				{

				}
                else
                {
                    (*it)->update();
                }
            }

            // check if dead or off screen
            if((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheGame::Instance()->getGameHeight()) || ((*it)->dead()))
            {
                delete * it;
                it = m_gameObjects.erase(it); // erase from vector and get new iterator
            }
            else
            {
                ++it; // increment if all ok
            }
            
        }
    }
}

void ObjectLayer::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        if(m_gameObjects[i]->getPosition().getX() <= TheGame::Instance()->getGameWidth())
        {
            m_gameObjects[i]->draw();
        }
    }
}