//
// Created by anchi on 01/07/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_PLAYER_H
#define CG_PROJECT___LUNAR_LANDER_PLAYER_H


#include "Drawable.h"

class Player
{
public:
	Composite model;
	bool isFlying = false, isRunning = false;
	array3f position, rotation;

	static constexpr float step = 0.025, runModifier = 3.0;



	void moveForward();

	void moveBackward();

	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	void render();
};

#endif //CG_PROJECT___LUNAR_LANDER_PLAYER_H
