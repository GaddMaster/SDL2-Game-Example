//
//  GameObject.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 31/12/2012.
//  Copyright (c) 2012 shaun mitchell. All rights reserved.
//

#ifndef SDL_Game_Programming_Book_SDLGameObject_h
#define SDL_Game_Programming_Book_SDLGameObject_h

#include <iostream>
#include "SDL.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

#include "TextureManager.h"
//#include "Game.h"

class SDLGameObject : public GameObject
{
public:

	//SDLGameObject(const LoaderParams* pParams);
	
	SDLGameObject();

	virtual void draw();
	virtual void update();
	virtual void clean();

	Vector2D& getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	// new load function
	virtual void load(const LoaderParams* pParams) = 0;

protected:

//	int m_x;
//	int m_y;

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration; //page 77

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;

	int m_numFrames;

};
#endif /* defined(__SDL_Game_Programming_Book__Chapter_3_SDLGameObject__) */