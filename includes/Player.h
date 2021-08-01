//
// Created by anchi on 01/07/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_PLAYER_H
#define CG_PROJECT___LUNAR_LANDER_PLAYER_H

#include "Entity.h"


class Player: public Entity
{
private:
	static constexpr float turnAngle = 0.2;

public:
	bool isRunning = false;


	void moveForward();

	void moveBackward();

	void moveLeft();

	void moveRight();

	void render();
};

#endif //CG_PROJECT___LUNAR_LANDER_PLAYER_H
