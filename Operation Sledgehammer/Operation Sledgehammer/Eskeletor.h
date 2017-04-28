#ifndef SDL_Game_Programming_Book_Escalator_h
#define SDL_Game_Programming_Book_Escalator_h

#include "Enemy.h"

class Eskeletor : public Enemy
{
public:
    
    virtual ~Eskeletor() {}
    
    Eskeletor() : Enemy()
    {
        m_dyingTime = 50;
        m_health = 3;
        m_moveSpeed = 2;
        m_bulletFiringSpeed = 60;
    }
    
    virtual void collision(int damage)
    {
        m_health -= 1;
        
        if(m_health == 0)
        {
            if(!m_bPlayedDeathSound)
            {
                TheSoundManager::Instance()->playSound("explode", 0);
                
                m_textureID = "Explosion64";
                m_currentFrame = 0;
                m_numFrames = 14;
                m_width = 64;
                m_height = 64;
                m_bDying = true;
            }
            
        }
    }
    
    virtual void update()
    {
        if(!m_bDying)
        {
            scroll(TheGame::Instance()->getScrollSpeed());
            m_velocity.setY(m_moveSpeed);
            
			if (m_bulletCounter == (m_bulletFiringSpeed - 10))
			{
				m_currentRow = 1;
			}
            else if(m_bulletCounter == m_bulletFiringSpeed)
            {
				m_currentRow = 0;
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 16, 8, 8, "DroidPulse", 1, Vector2D(-3, 0), 0);
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 32, m_position.getY() + 16, 8, 8, "DroidPulse", 1, Vector2D(3, 0), 0);
                m_bulletCounter = 0;
            }
            m_bulletCounter++;
            
        }
        else
        {
            m_velocity.setY(0);
            doDyingAnimation();
        }
        
        ShooterObject::update();
    }
};

class EskeletorCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Eskeletor();
    }
};


#endif
