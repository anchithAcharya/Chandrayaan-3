//
// Created by anchi on 01/07/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_PLAYER_H
#define CG_PROJECT___LUNAR_LANDER_PLAYER_H

#include "Entity.h"


class Player: public Entity
{
private:
	float laserLength = 0.0;
	static constexpr float turnAngle = 0.5, laserMaxLength = 2.0;
	array3f laserStart = array3f(0.313372, 0.393902, 0.070902);
	array3f laserUnit = array3f(0.965924020666442, -0.25882578368388026, 0.0);

	void drawLaser();

protected:
	static constexpr float runModifier = 2.5, turnModifier = 3.0;

public:
	bool isRunning = false, laserOn = false;

	void moveForward();

	void moveBackward();

	void moveLeft();

	void moveRight();


	void render();
};

#endif //CG_PROJECT___LUNAR_LANDER_PLAYER_H
