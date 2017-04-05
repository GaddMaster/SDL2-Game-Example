#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "ShooterObject.h"

//ENEMY BASE CLASS
class Enemy : public ShooterObject
{
	public:
    
		virtual std::string type() { return "Enemy"; }
    
	protected:
    
		int m_health;
    
		Enemy() : ShooterObject() {}
		virtual ~Enemy() {}
};

#endif//DEFINED ENEMY_H
