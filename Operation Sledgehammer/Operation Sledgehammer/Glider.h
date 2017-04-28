#ifndef GLIDER_H
#define GLIDER_H

#include <iostream>
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include <math.h>
#include "Enemy.h"

class Glider : public Enemy
{
	public:
    
		Glider() : Enemy()
		{
			m_bulletFiringSpeed = 60;
			m_dyingTime = 25;
			m_health = 1;
			m_moveSpeed = 2;
			m_gap = 60;
		}
		virtual ~Glider(){}
		virtual void load(std::unique_ptr<LoaderParams> const &pParams)
		{
			ShooterObject::load(std::move(pParams));
        
			m_velocity.setX(-m_moveSpeed);
			m_velocity.setY(m_moveSpeed / 2);
        
			m_maxHeight = m_position.getY() + m_gap;
			m_minHeight = m_position.getY() - m_gap;
		}
		virtual void collision(int damage)
		{
			m_health -= 1;
        
			if(m_health == 0)
			{
				if(!m_bPlayedDeathSound)
				{
					TheSoundManager::Instance()->playSound("explode", 0);
                
					m_textureID = "Explosion32";
					m_currentFrame = 0;
					m_numFrames = 14;
					m_width = 32;
					m_height = 32;
					m_bDying = true;
				}
			}
		}
		virtual void update()
		{
			if(!m_bDying)
			{
				if(m_position.getY() >= m_maxHeight)
				{
					m_velocity.setY(-m_moveSpeed);
				}
				else if(m_position.getY() <= m_minHeight)
				{
					m_velocity.setY(m_moveSpeed);
				}

				if (m_bulletCounter == (m_bulletFiringSpeed - 10))
				{
					m_currentRow = 1;
				}
				else if (m_bulletCounter == m_bulletFiringSpeed)
				{
					m_currentRow = 0;
					TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() -5, m_position.getY() + 16, 8, 8, "BulletPulse", 1, Vector2D(-10, 0), 0);
					m_bulletCounter = 0;
				}

				m_bulletCounter++;
			}
			else
			{
				m_velocity.setX(0);
				m_velocity.setY(0);
				doDyingAnimation();
			}
        
			ShooterObject::update();
        
		}
	private:
		int m_maxHeight;
		int m_minHeight;
		int m_gap;
};

class GliderCreator : public BaseCreator
{
    GameObject* createGameObject() const{return new Glider();}
};

#endif//DEFINED GLIDER_H
