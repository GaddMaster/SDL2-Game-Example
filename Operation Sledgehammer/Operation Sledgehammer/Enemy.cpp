#include <iostream>
#include "Enemy.h"

/*
Enemy::Enemy(const LoaderParams* pParams) :SDLGameObject(pParams)
{
	m_velocity.setY(2);
	m_velocity.setX(0.001);


}

*/
Enemy::Enemy() : SDLGameObject()
{
}

void Enemy::load(const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
	m_velocity.setY(2);
}


void Enemy::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Enemy::update()
{
//	m_x -= 1;
//	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

//	m_position.setX(m_position.getX() +1);
//	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

//	m_acceleration.setX(0.01); //page 77

//	SDLGameObject::update();


	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	if(m_position.getY() < 0)
	{
		m_velocity.setY(2);
	}
	else if(m_position.getY() > 400)
	{
		m_velocity.setY(-2);
	}

	SDLGameObject::update();

}

void Enemy::clean()
{
}

/*


void Enemy::load(int x, int y, int width, int height, std::string textureID)
{
	GameObject::load(x, y, width, height, textureID);
}

void Enemy::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
}

void Enemy::update()
{
	//using the runing cat as the enemy whihc has 6 frames
	m_x += 1;
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));


}
*/