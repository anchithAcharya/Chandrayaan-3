//
// Created by anchi on 23/06/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_CAMERA_H
#define CG_PROJECT___LUNAR_LANDER_CAMERA_H


#include "common.h"
#include <math.h>


class Camera
{
private:
	array3f upVector;
	bool enabled = false;

	static constexpr int r = 1;

public:
	void update();

	void set( array3f pos, array3f at, array3f up, bool add );

	void set(array3f pos, array3f sphericalRot, bool add );

	bool isEnabled();

	void enable();
	void disable();

	array3f lookAt;
	array3f position;
	array3f rotation;
};

#endif //CG_PROJECT___LUNAR_LANDER_CAMERA_H