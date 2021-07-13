//
// Created by anchi on 01/07/2021.
//

#include "Camera.h"


void Camera::update()
{
	gluLookAt(position->x,	position->y,   position->z,
			  position->x + lookAt.x, 	position->y + lookAt.y,	  position->z + lookAt.z,
			  upVector.x,	upVector.y,   upVector.z);
}

void Camera::set( array3f pos, array3f at, array3f up, bool add = false )
{
	if( add )
	{
		*position += pos;
		lookAt += at;
		upVector += up;
	}

	else
	{
		*position = pos;
		lookAt = at;
		upVector = up;
	}
}

void Camera::set( array3f pos, array3f rot, bool add = false )
{
	if( add )
	{
		*position += pos;
		*rotation += rot;
	}

	else
	{
		*position = pos;
		*rotation = rot;
	}

	float temp = rotation->y;

	if( temp + rot.y < std::toRadians(0) )
		rotation->y = std::max(0.00001f, temp + rot.y);

	else if( temp + rot.y > std::toRadians(180) )
		rotation->y = std::min(temp + rot.y, (MY_PI - 0.0001f) );

	lookAt.x = r * cos(rotation->x) * sin(rotation->y);
	lookAt.z = r * sin(rotation->x) * sin(rotation->y);
	lookAt.y = r * cos(rotation->y);

	upVector = {0.0, std::abs(position->y) + 1.0f, 0.0};
}

bool Camera::isEnabled() { return enabled; }

void Camera::enable() { enabled = true; }
void Camera::disable() { enabled = false; }