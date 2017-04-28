#ifndef SHOOTER_OBJECT_H
#define SHOOTER_OBJECT_H

#include <SDL.h>
#include "GameObject.h"

class ShooterObject : public GameObject
{
public:
    
    virtual ~ShooterObject() {}
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw();
    virtual void update();
	virtual void clean() {}
    virtual void collision(int weapon) {}
    virtual std::string type() { return m_type; }
    
protected:
    
    ShooterObject();
    void doDyingAnimation();
	int m_moveSpeed;

	//MACHINE GUN WEAPON
    int m_bulletFiringSpeed;
    int m_bulletCounter;

    // how long the death animation takes, along with a counter
    int m_dyingTime;
    int m_dyingCounter;
    
    // has the explosion sound played?
    bool m_bPlayedDeathSound;
	std::string m_type;
};

#endif//DEFINED SHOOTER_OBJECT_H
