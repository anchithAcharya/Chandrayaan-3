//
// Created by anchi on 23/06/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_CAMERA_H
#define CG_PROJECT___LUNAR_LANDER_CAMERA_H

#include "common.h"
#include "Player.h"


class Camera: public Player
{
private:
	array3f upVector, lookAt;
	static constexpr int distanceFromCamera = 25;

public:
	array3f offset = array3f(0, 0.5, 0);
	bool enabled = false, isFlying = false;


	array3f getLookAtCoords();


	void moveForward();

	void moveBackward();

	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();


	void update();

	void set(array3f pos, array3f sphericalRot, bool add );
};

#endif //CG_PROJECT___LUNAR_LANDER_CAMERA_H