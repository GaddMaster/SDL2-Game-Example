
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "TileLayer.h"
#include "BulletHandler.h"
#include "RocketHandler.h"
#include "SoundManager.h"
#include <ctime>

using namespace std;

Player::Player() :  
ShooterObject(),
m_invulnerable(false),
m_invulnerableTime(200),
m_invulnerableCounter(0),
m_isShootingMachineGun(false),
m_isShootingRocket(false),
m_isShieldActive(false),
m_isShootingLaser(false),
m_rocket(false),
m_machineGun(false),
m_shield(false),
m_laser(false),
m_bomb(false),
m_rocketFireSpeed(0),
m_laserFireSpeed(0),
m_shieldTimer(600),
m_bombFireSpeed(0),
currentWeaponAnimationRow(0),//DEFAULT MACHINE GUN
m_weapon(0),
m_ammo(0)
{
	srand((unsigned)time(0));
}

void Player::collision(int damage)
{
    // if the player is not invulnerable then set to dying and change values for death animation tile sheet
    if((!m_invulnerable && !TheGame::Instance()->getLevelComplete() && !deathAnimationTrapDoor) && !m_shield == true)
    {
        m_textureID = "Explosion32";
        m_currentFrame = 0;
        m_numFrames = 13;
        m_width = 32;
        m_height = 32;
		changeAnimationTick = SDL_GetTicks();
        m_bDying = true;
		deathAnimationTrapDoor = true;
    }
}

void Player::load(std::unique_ptr<LoaderParams> const &pParams)
{
    // inherited load function
    ShooterObject::load(std::move(pParams));
    
    // can set up the players inherited values here
    
    // set up bullets
    m_bulletFiringSpeed = 5;
    m_moveSpeed = 2;
    
    // we want to be able to fire instantly
    m_bulletCounter = m_bulletFiringSpeed;
    
    //DYING TIME NEEDS TO MATCH OUR EXPLOSION FRAME COUNT WHICH IS 14 FRAMES FOR ALL EXPLOSIONS
    m_dyingTime = 14;
}

void Player::draw()
{
    // player has no special drawing requirements
    ShooterObject::draw();
}

void Player::handleAnimation()
{
	if (weaponStatus())
		m_currentRow = currentWeaponAnimationRow;
	else
		m_currentRow = 0;
	

    // if the player is invulnerable we can flash its alpha to let people know
    if(m_invulnerable)
    {
		//SHIELD MAKES YOU INVULNERABLE UNTIL AMMO/POWER IS GONE
		if (m_shield)
		{
			m_ammo--;
		}
        // invulnerability is finished, set values back
        else if(m_invulnerableCounter == m_invulnerableTime)
        {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        }
        else // otherwise, flash the alpha on and off
        {
            if(m_alpha == 255)
            {
                m_alpha = 0;
            }
            else
            {
                m_alpha = 255;
            }
        }
        
        // increment our counter
        m_invulnerableCounter++;
    }
    

    
    // our standard animation code - for helicopter propellors
    m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void Player::update()
{
	//SET WEAPON AS EMPTY BECAUSE NO BULLETS LEFT - CHANGE WEAPON ICON ON HUD
	if (m_ammo < 1)
	{
		m_weapon = 5;
		TheGame::Instance()->setCurrentWeapons(5, m_ammo);
		noWeapon();
	}
		
	//IF LEVEL HAS BEEN COMPLETED
    if(TheGame::Instance()->getLevelComplete())
    {
        if(m_position.getX() >= TheGame::Instance()->getGameWidth())
        {
            TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
        }
        else
        {
            m_velocity.setY(0);
            m_velocity.setX(3);
            ShooterObject::update();
            handleAnimation();
        }
    }
    else
    {
        //IF PLAYING IS NOT IN DYING STATE
        if(!m_bDying)
        {
            //RESET VELOCITY
            m_velocity.setX(0);
            m_velocity.setY(0);
            
            //HANDLE INPUTS
            handleInput();

			//HANDLE VELOCITY - VELOCITY IS AFFECTED BY ANGLE
			m_velocity.m_x = m_angle / 4;
            
            //DO NORMAL POSITION += VELOCITY UPDATE
            ShooterObject::update();
            
            //UPDATE ANIMATIONS
            handleAnimation();
        }
		//PLAYER IS IN DYING STATE
        else
        {
			//THIS PRINT LINE BELOW AND ADDITION TO THE GET TICK IS PART OF MY IMPROVED ANIMATION FUCNTIONALITY AS EXPLAINED IN MY DOCUMENT
			//WE CANNOT DEBUG AS THE TICK CONTINUES TO TICK EVEN IF WE PAUSE THE PROGRAM
			//SO WE NEED LEAVE THE PROGRAM RUN AND PRINT DATA TO INSPECT AFTERWARDS IN THE CONSOLE
            m_currentFrame = int((( (SDL_GetTicks() - changeAnimationTick) / (100)) % m_numFrames));
			//std:cout << "SDL - NT : " << SDL_GetTicks() - changeAnimationTick << "\tSDL TICK : " << SDL_GetTicks() <<  "\tNEW TICK : " << changeAnimationTick << "\t FRAME : " << m_currentFrame << std::endl;

            //IF DEATH ANIMATION HAS BEEN COMPLETED
            if(m_dyingCounter == m_dyingTime)
            {
                //RESSURECT PLAYER
                ressurect();
            }

            m_dyingCounter++;
        }
    }
}

void Player::ressurect()
{
    TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);
    
    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;
    
    m_textureID = "Player";
    
    m_currentFrame = 0;
    m_numFrames = 5;
    m_width = 64;
    m_height = 32;
    
    m_dyingCounter = 0;
    m_invulnerable = true;
	deathAnimationTrapDoor = false;
}

void Player::clean()
{
    ShooterObject::clean();
}

//PLAYER INPUT HANDLER FOR CONTROLS AND WEAPONS
void Player::handleInput()
{
	//IF PLAYER IS NOT IN DYING STATE
    if(!m_bDead)
    {
		//CHANGE WEAPON WITH NUMBER 1 TO 5 - DEBUGGING - PARACHUTE DROPS WILL DEFINE WHAT WEAPONS WE HAVE LATER
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_1) && m_machineGun)activateMachineGun();
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_2) && m_rocket)activateRockets();
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_3) && m_laser)activateLaser();
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_4) && m_shield)activateShield();
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_5) && m_bomb)activateBombs();

        //HANDLE ALTITUDE DECENT AND ACCENT
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
        {
            m_velocity.setY(-1);
        }
        else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && (m_position.getY() + m_height) < TheGame::Instance()->getGameHeight() - 10)
        {
            m_velocity.setY(2);
        }
        
		//HANDLE TILTING HELICOPTER FORWARD AND BACKWARDS - SPEED DEPENDS ON TILT(UPDATE FUNCTION)
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
        {
			if (m_angle > -10 || m_angle == 0)
				m_angle -= 0.5;;
        }
        else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth())
        {
			if (m_angle < 10 || m_angle == 0)
				m_angle += 0.5;
        }
		else
		{
			//HANDLE DAMPING
			if (m_angle > 0)
				m_angle--;
			else if (m_angle < 0)
				m_angle++;
		}

        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
			if (m_machineGun)
			{
				m_isShootingMachineGun = true;//LOCK

				//IF GUN IS READY FIRE AGAIN -> SHOOT
				if ((m_bulletCounter == m_bulletFiringSpeed) && m_ammo > 0)
				{
					TheSoundManager::Instance()->playSound("shoot", 0);//PLAY SOUND

					//GET BULLET HEADING & CALL BULLET HANDLE TO CREATE BULLET
					int x = 10 * (cos(m_angle * 3.14 / 180));
					int y = 10 * (sin(m_angle * 3.14 / 180));
					TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 65, m_position.getY() + 20, 3, 1, "BulletSmall", 1, Vector2D(x, y), m_angle);
					m_ammo--;
					TheGame::Instance()->setAmmo(m_ammo);
					m_bulletCounter = 0;//RESET BULLET TIMER
				}

				m_bulletCounter++;
			}
			else if (m_rocket)
			{
				m_isShootingRocket = true;//LOCK
				if ((m_rocketCounter == m_rocketFireSpeed) && m_ammo > 0)
				{
					TheSoundManager::Instance()->playSound("Missile", 0);//PLAY ROCKET SOUND

					//GET ROCKET HEADING & CALL ROCKET HANDLER TO CREATE ROCKET
					int x = 10 * (cos(m_angle * 3.14 / 180));
					int y = 10 * (sin(m_angle * 3.14 / 180));
					TheRocketHandler::Instance()->addRocket(m_position.getX() + 65, m_position.getY() + 20 + m_angle, 24, 6, "Rocket", 1, Vector2D(x, y), m_angle);
					m_rocketCounter = 0;//RESET ROCKET TIMER
					m_ammo--;
					TheGame::Instance()->setAmmo(m_ammo);
				}
				m_rocketCounter++;//INCREMENT ROCKET TIMER
			}
			else if (m_laser)
			{
				m_isShootingLaser = true;//LOCK
				if ((m_laserCounter == m_laserFireSpeed) && m_ammo > 0)
				{
					TheSoundManager::Instance()->playSound("Laser", 0);//PLAY LASER SOUND

					//GET LASER HEADING & HIJACK BULLET HANDLER TO FIRE LASER(FLOW OF RED BARS FOR NOW - WILL MAKE IT A STRIGHT LINE OBJECT LATER)
					int x = 10 * (cos(m_angle * 3.14 / 180));
					int y = 10 * (sin(m_angle * 3.14 / 180));
					TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 65, m_position.getY() + 20 + m_angle, 5, 1, "Laser", 1, Vector2D(x, y), m_angle);
					m_laserCounter = 0;//RESET ROCKET TIMER
					m_ammo--;
					TheGame::Instance()->setAmmo(m_ammo);
				}
				m_laserCounter++;//INCREMENT ROCKET TIMER
			}
        }
        else
        {
            m_bulletCounter = m_bulletFiringSpeed;
			m_rocketCounter = m_rocketFireSpeed;
			m_laserCounter = m_laserFireSpeed;
			m_bombCounter = m_bombFireSpeed;
			notShooting();
        }
        
        /* handle joysticks
        if(TheInputHandler::Instance()->joysticksInitialised())
        {
            if(TheInputHandler::Instance()->getButtonState(0, 2))
            {
                if(m_bulletCounter == m_bulletFiringSpeed)
                {
                    TheSoundManager::Instance()->playSound("shoot", 0);
                    TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
                    m_bulletCounter = 0;
                }
                
                m_bulletCounter++;
            }
            else
            {
                m_bulletCounter = m_bulletFiringSpeed;
            }
            
            if((TheInputHandler::Instance()->getAxisX(0, 1) > 0 && (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth()) || (TheInputHandler::Instance()->getAxisX(0, 1) < 0 && m_position.getX() > 0))
            {
                m_velocity.setX(m_moveSpeed * TheInputHandler::Instance()->getAxisX(0, 1));
            }
            
            if((TheInputHandler::Instance()->getAxisY(0, 1) > 0 && (m_position.getY() + m_height) < TheGame::Instance()->getGameHeight() - 10 ) || (TheInputHandler::Instance()->getAxisY(0, 1) < 0 && m_position.getY() > 0))
            {
                m_velocity.setY(m_moveSpeed * TheInputHandler::Instance()->getAxisY(0, 1));
            }
        }
        */
    }
}

//SETTING WEAPON STATUS - ACTIVATING A SINGLE WEAPON AND DISABLING THE REMAINING WEAPONS
void Player::activateMachineGun()
{
	m_machineGun = true;
	m_ammo = 100;
	m_weapon = 0;
	currentWeaponAnimationRow = 0;
	m_rocket, m_shield, m_laser, m_bomb = false;
	TheGame::Instance()->setCurrentWeapons(0, m_ammo);
}
void Player::activateRockets()
{
	m_rocket  = true;
	m_weapon = 1;
	m_ammo = 5;
	currentWeaponAnimationRow = 1;
	m_machineGun, m_shield, m_laser, m_bomb = false;
	TheGame::Instance()->setCurrentWeapons(1, m_ammo);
}
void Player::activateLaser()
{
	m_laser = true;
	m_weapon = 2;
	m_ammo = 30;
	currentWeaponAnimationRow = 2;
	m_machineGun, m_shield, m_rocket, m_bomb = false;
	TheGame::Instance()->setCurrentWeapons(2, m_ammo);
}
void Player::activateShield()
{
	m_shield = true;
	m_invulnerable = true;
	m_weapon = 3;
	m_ammo = 200;
	currentWeaponAnimationRow = 3;
	m_machineGun, m_laser, m_rocket, m_bomb = false;
	TheGame::Instance()->setCurrentWeapons(3, m_ammo);
}
void Player::activateBombs()
{
	m_bomb = true;
	m_weapon = 4;
	m_ammo = 1;
	currentWeaponAnimationRow = 4;
	m_machineGun, m_shield, m_rocket, m_laser = false;
	TheGame::Instance()->setCurrentWeapons(4, m_ammo);
}
void Player::getRandomWeapon()
{
	m_weapon = rand() % 4;
	std::cout << m_weapon << std::endl;
	switch (m_weapon)
	{
		case 0: activateMachineGun(); break;
		case 1: activateRockets(); break;
		case 2: activateLaser(); break;
		case 3: activateShield(); break;
		case 4: activateBombs(); break;
	}
}

//RESET ALL SHOOTING BOOLEANS
void Player::notShooting()
{
	m_isShootingMachineGun = false;
	m_isShootingRocket = false;
	m_isShieldActive = false;
	m_isShootingLaser = false;
	m_isShootingBombs = false;
}
void Player::noWeapon()
{
	m_machineGun = false;
	m_rocket = false;
	m_shield = false;
	m_laser = false;
	m_bomb = false;
}
bool Player::weaponStatus()
{
	if (m_machineGun)return true;
	if (m_rocket)return true;
	if (m_shield)return true;
	if (m_laser)return true;
	if (m_bomb)return true;
	return false;
}