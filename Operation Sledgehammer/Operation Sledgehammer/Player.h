
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:
    
    Player();
    virtual ~Player() {}
    
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    virtual void collision(int damage);
    
    virtual std::string type() { return "Player"; }

	void activateMachineGun();
	void activateRockets();
	void activateLaser();
	void activateShield();
	void activateBombs();
	void getRandomWeapon();
	void notShooting();
	void noWeapon();
	bool weaponStatus();
    
private:
    
    // bring the player back if there are lives left
    void ressurect();
    
    // handle any input from the keyboard, mouse, or joystick
    void handleInput();
    
    // handle any animation for the player
    void handleAnimation();

    // player can be invulnerable for a time
    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;

	//MACHINE GUN WEAPON
	bool m_isShootingMachineGun;
	bool m_machineGun;
	int m_ammo;

	//ROCKET WEAPON
	int m_rocketFireSpeed;
	int m_rocketCounter;
	bool m_isShootingRocket;
	bool m_rocket;

	//SHIELD PROTECTION
	bool m_isShieldActive;
	bool m_shieldTimer;
	bool m_shield;

	//LASER WEAPON
	int m_laserFireSpeed;
	int m_laserCounter;
	bool m_laser;
	bool m_isShootingLaser;

	//BOMBS WEAPON
	int m_bombFireSpeed;
	int m_bombCounter;
	bool m_bomb;
	bool m_isShootingBombs;

	//CURRENT WEAPON
	int currentWeaponAnimationRow;
	int m_weapon;
};

// for the factory
class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};


#endif//DEFINED PLAYER_H
