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
	void* rover;
	bool isFlying = false, isRunning = false;
	array3f position, rotation, offset;

	static constexpr float step = 0.01, runModifier = 3.0;


	Player()
	{
		Drawable d = Drawable();

		d.addVertex({-1.0, 0.5, -1.0});
		d.addVertex({-1.0, 0.5,  1.0});
		d.addVertex({ 1.0, 0.5,  1.0});
		d.addVertex({ 1.0, 0.5, -1.0});

		d.addFace({{0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}});

		model.addDrawable(d);
	}

	void moveForward();

	void moveBackward();

	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	void render();
};

#endif //CG_PROJECT___LUNAR_LANDER_PLAYER_H
