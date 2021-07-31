//
// Created by anchi on 23/06/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_CAMERA_H
#define CG_PROJECT___LUNAR_LANDER_CAMERA_H


#include "common.h"


class Camera
{
private:
	array3f *position, *rotation, upVector;
	bool enabled = false;

	static constexpr int r = 25;

public:
	Camera( array3f &pos, array3f &rot): position(&pos), rotation(&rot) {};

	void update();

	void set( array3f pos, array3f at, array3f up, bool add );

	void set(array3f pos, array3f sphericalRot, bool add );

	bool isEnabled();

	void enable();
	void disable();

	array3f lookAt;
};

#endif //CG_PROJECT___LUNAR_LANDER_CAMERA_H