
#ifndef TURRET_H
#define TURRET_H

#include <iostream>
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include "SoundManager.h"
#include <math.h>
#include "Enemy.h"
#include <ctime>

class Turret : public Enemy
{
	public:
		Turret();
		virtual ~Turret() {}
		virtual void collision(int damage);
		virtual void update();
		//std::string type() { return "Turret"; }
		virtual void angleControl();//CONTROLS THE TURRETS ROTATION BEHAVIOUR

		//WE NEED TO ROATE THE BULLET SPAWN POINTS TO MATCH TURRETS ANGLE
		virtual Vector2D rotatePoint(Vector2D pivot, Vector2D point, float angle);

	private:
		int wait;
		double rotateTo;
		bool shoot;
		Vector2D bulletSpawnPoint;
};

class TurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Turret();
    }
};

#endif//DEFINED TURRET_H
