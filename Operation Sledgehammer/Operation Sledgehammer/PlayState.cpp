
#include <iostream>
#include "PlayState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "Level.h"
#include "BulletHandler.h"
#include "RocketHandler.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if(m_loadingComplete && !m_exiting)
    {
		//IF PAUSE IS PRESSED CONSTRUCT A PAUSE STATE
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            TheGame::Instance()->getStateMachine()->pushState(new PauseState());
        }
        
        TheBulletHandler::Instance()->updateBullets();
		TheRocketHandler::Instance()->updateRockets();
        
        if(TheGame::Instance()->getPlayerLives() == 0)
        {
            TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
        }
        
        if(pLevel != 0)
        {
            pLevel->update();
        }
    }
}

void PlayState::render()
{
    if(m_loadingComplete)
    {
        if(pLevel != 0)
        {
            pLevel->render();
        }
        
        for(int i = 0; i < TheGame::Instance()->getPlayerLives(); i++)
        {
            TheTextureManager::Instance()->drawFrame("Lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
        }

		for (int i = 0; i < TheGame::Instance()->getAmmo(); i++)
		{
			TheTextureManager::Instance()->drawFrame("Ammo", i * 3, 32, 2, 4, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
		}

		switch (TheGame::Instance()->getCurrentWeapons())
		{
			case 0 : TheTextureManager::Instance()->drawFrame("Weapon", 608, 0, 32, 32, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);break;
			case 1 : TheTextureManager::Instance()->drawFrame("Weapon", 608, 0, 32, 32, 0, 1, TheGame::Instance()->getRenderer(), 0.0, 255); break;
			case 2 : TheTextureManager::Instance()->drawFrame("Weapon", 608, 0, 32, 32, 0, 2, TheGame::Instance()->getRenderer(), 0.0, 255); break;
			case 3 : TheTextureManager::Instance()->drawFrame("Weapon", 608, 0, 32, 32, 0, 3, TheGame::Instance()->getRenderer(), 0.0, 255); break;
			case 4 : TheTextureManager::Instance()->drawFrame("Weapon", 608, 0, 32, 32, 0, 4, TheGame::Instance()->getRenderer(), 0.0, 255); break;
			case 5: TheTextureManager::Instance()->drawFrame("Weapon", 608, 0, 32, 32, 0, 5, TheGame::Instance()->getRenderer(), 0.0, 255); break;
		}
        
        TheBulletHandler::Instance()->drawBullets();
		TheRocketHandler::Instance()->drawRockets();
    }
}

bool PlayState::onEnter()
{
    TheGame::Instance()->setPlayerLives(3);
    
    LevelParser levelParser;
    pLevel = levelParser.parseLevel(TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());
    
    TheTextureManager::Instance()->load("assets/Bullets/bulletSmall.png", "BulletSmall", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/Bullets/bulletPulse.png", "BulletPulse", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/Bullets/droidPulse.png", "DroidPulse", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("assets/HUD/lives.png", "Lives", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/HUD/weapon.png", "Weapon", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/HUD/ammo.png", "Ammo", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/Rockets/rocketSmall.png", "Rocket", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/Laser/laserSmall.png", "Laser", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("assets/Bullets/bullet.png", "Bullet", TheGame::Instance()->getRenderer());


    if(pLevel != 0)
    {
        m_loadingComplete = true;
    }
    
    std::cout << "ENTERING PLAY STATE" << std::endl;
    return true;
}

bool PlayState::onExit()
{
    m_exiting = true;
    
    TheInputHandler::Instance()->reset();
    TheBulletHandler::Instance()->clearBullets();
    
    std::cout << "EXITING PLAY STATE" << std::endl;
    return true;
}
