//LIBRARIES & HEADER INCLUDES
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "Player.h"
#include "ScrollingBackground.h"
#include "SoundManager.h"
#include "RoofTurret.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Level1Boss.h"
#include "GameOverState.h"
#include "Crate.h"
#include <iostream>

using namespace std;

Game* Game::s_pInstance = 0;

//CONSTRUCTOR & DE-CONSTRUCTOR
Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_pGameStateMachine(0),
m_playerLives(3),
m_scrollSpeed(0.5),
m_bLevelComplete(false),
m_bChangingState(false)
{
    // add some level files to an array
    m_levelFiles.push_back("assets/map1.tmx");
    
    // start at this level
    m_currentLevel =  1;
}
Game::~Game()
{
    //CLEAN UP AFTER OURSELVES TO PREVENT MEMORY LEAKS
    m_pRenderer= 0;
    m_pWindow = 0;
}

//INITIALIZATION FUNCTION - SETS UP ALL INITIAL VALUES
bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    
    //GAME WIDTH AND HEIGHT
    m_gameWidth = width;
    m_gameHeight = height;
    
	//FULLSCREEN MODE - SET FLAG
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    //ATTEMPT TO INITIALIZE SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)//SDL INITIALIZATION - SUCCESS
    {cout << "SDL INITIALIZATION - SUCCESS\n";
        

        //ATTEMPT TO INITIALIZE THE WINDOW
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(m_pWindow != 0)//WINDOW INITIALIZE - SUCCESS
        {cout << "WINDOW INITIALIZATION - SUCCESS\n";
            
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
            if(m_pRenderer != 0)//RENDERER INITIALIZATION - SUCCESS
            {cout << "RENDERER INITIALIZATION - SUCCESS\n";
                SDL_SetRenderDrawColor(m_pRenderer, 0,0,0,255);
            }
            else//RENDERER INITIALIZATION - FAILED
            {cout << "RENDERER INITIALIZATION - FAILED\n";
                return false;
            }
        }
        else//WINDOW INITIALIZE - FAILED
        {cout << "WINDOW INITIALIZE - FAILED\n";
            return false; // window init fail
        }
    }
    else//SDL INITIALIZATION - FAILED
    {cout << "SDL INITIALIZATION - FAILED\n";
        return false;
    }
    
	//ADDING & PLAYING SOUND EFFECTS -  "TODO" MOVE TO BETTER PLACE
    TheSoundManager::Instance()->load("assets/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
    TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
    TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/missile.wav", "Missile", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/laser.wav", "Laser", SOUND_SFX);
    TheSoundManager::Instance()->playMusic("music1", -1);
    
	//CAN INITIALIZE JOYSTICK IF NEEDED
    //TheInputHandler::Instance()->initialiseJoysticks();
    
    //REGISTER ALL TYPES FOR THE GAME HERE
    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
    TheGameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
    TheGameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
    TheGameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
    TheGameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
    TheGameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
    TheGameObjectFactory::Instance()->registerType("Level1Boss", new Level1BossCreator());
	TheGameObjectFactory::Instance()->registerType("Crate", new CrateCreator());


    
    //START THE MENU STATE - OUR VERY FIRST STATE
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());
    
	//GAME RUNNING STATE 
    m_bRunning = true;

    return true;
}

//SET CURRENT LEVEL
void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;//SET LEVEL
    m_pGameStateMachine->changeState(new GameOverState());//CHANGE STATE TO GAME OVER STATE - MEANS GAME HAS FINISHED
    m_bLevelComplete = false;//LEVEL WASN'T COMPLETED 
}

//RENDER NEW WINDOW
void Game::render()
{
    SDL_RenderClear(m_pRenderer);//CLEAR EVERYTHING
    
	m_pGameStateMachine->render();//RENDER VIA CURRENT GAME STATE

    SDL_RenderPresent(m_pRenderer);//RENDER EVERYTHING TO WINDOW
}

//UPDATE VIA THE GAME STATE MACHINE
void Game::update()
{
	m_pGameStateMachine->update();
}

//HANDLE EVENTS VIA EVENT HANDLER SINGLETON
void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}

//CLEAN UP ENTIRE GAME - CLOSE AND QUIT EVERYTHING
void Game::clean()
{
    cout << "CLEANING GAME\n";
    
    TheInputHandler::Instance()->clean();
    
    m_pGameStateMachine->clean();
    
    m_pGameStateMachine = 0;
    delete m_pGameStateMachine;
    
    TheTextureManager::Instance()->clearTextureMap();
    
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}


