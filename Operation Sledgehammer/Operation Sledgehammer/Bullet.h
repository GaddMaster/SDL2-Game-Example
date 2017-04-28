
#ifndef BULLET_H
#define BULLET_H

#include "ShooterObject.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

class PlayerBullet : public ShooterObject
{
	public:
		PlayerBullet() : ShooterObject() { m_dyingTime = 5; }
		virtual ~PlayerBullet() {}
		virtual std::string type() { return "PlayerBullet"; }
		virtual void load(std::unique_ptr<LoaderParams> pParams, Vector2D heading, float angle)
		{
			ShooterObject::load(std::move(pParams));
			m_heading = heading;
			m_angle = angle;
		}
		virtual void draw(){ShooterObject::draw();}
		virtual void collision(int damage)
		{
			m_textureID = "Explosion8";
			m_currentFrame = 0;
			m_numFrames = 13;
			m_width = 8;
			m_height = 8;
			m_bDying = true;
		}
		virtual void update()
		{
			if(!m_bDying)
			{
				m_velocity.setX(m_heading.getX());
				m_velocity.setY(m_heading.getY());
				scroll(TheGame::Instance()->getScrollSpeed());
				ShooterObject::update();
			}
			else
			{
				m_velocity.setX(0);
				m_velocity.setY(0);
				doDyingAnimation();
			}
		}
		virtual void clean()
		{
			ShooterObject::clean();
		}
	private:
		Vector2D m_heading;
};

class EnemyBullet : public PlayerBullet
{
public:
    EnemyBullet() : PlayerBullet()
    {
		m_numFrames = 4;
    }
    
    virtual ~EnemyBullet() {}
    
    virtual std::string type() { return "EnemyBullet"; }
};

#endif//DEFINED BULLET_H
