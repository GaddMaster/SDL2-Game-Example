#ifndef SHOT_GLIDER_H
#define SHOT_GLIDER_H

#include "Glider.h"

class ShotGlider : public Glider
{
	public:
		virtual ~ShotGlider() {}
		ShotGlider() : Glider()
		{
			m_bulletFiringSpeed = 60;
			m_moveSpeed = 2;
		}
		virtual void load(std::unique_ptr<LoaderParams> const &pParams)
		{
			ShooterObject::load(std::move(pParams));

			m_velocity.setX(-m_moveSpeed);
		}
		virtual void update()
		{
			if(!m_bDying)
  			{
 				if (m_bulletCounter == (m_bulletFiringSpeed - 10))
				{
					m_currentRow = 1;
				}
				else if (m_bulletCounter == m_bulletFiringSpeed)
				{
					m_currentRow = 0;
					TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 12, 8, 8, "BulletPulse", 1, Vector2D(-10, 0), 0);
					m_bulletCounter = 0;
				}

            
				m_bulletCounter++;
			}
			else
			{
				m_velocity.setX(0);
				doDyingAnimation();
			}
        
			ShooterObject::update();
		}
};

class ShotGliderCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new ShotGlider();
    }
};


#endif//DEFINED SHOT_GLIDER_H
