#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"

/*
void GameObject::load(int x, int y, int width, int height, std::string textureID)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_textureID = textureID;
	m_currentRow = 1;
	m_currentFrame = 1;
}

void GameObject::draw(SDL_Renderer* pRenderer)
{
	TheTextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, pRenderer,SDL_FLIP_NONE);
}

void GameObject::update()
{
	m_x += 1;
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

*/

