//
// Created by anchi on 01/07/2021.
//

#include "Camera.h"


void Camera::update()
{
	gluLookAt(position.x,	position.y,   position.z,
			  position.x + lookAt.x, 	position.y + lookAt.y,	  position.z + lookAt.z,
			  upVector.x,	upVector.y,   upVector.z);
}

void Camera::set( array3f pos, array3f at, array3f up, bool add = false )
{
	if( add )
	{
		position += pos;
		lookAt += at;
		upVector += up;
	}

	else
	{
		position = pos;
		lookAt = at;
		upVector = up;
	}
}

void Camera::set(array3f pos, array3f sphericalRot, bool add = false )
{
	if( add )
	{
		position += pos;
		rotation += sphericalRot;
	}

	else
	{
		position = pos;
		rotation = sphericalRot;
	}

	float temp = rotation.theta;

	if(temp + sphericalRot.theta < std::toRadians(0) )
		rotation.theta = std::max(0.00001f, temp + sphericalRot.theta);

	else if(temp + sphericalRot.theta > std::toRadians(180) )
		rotation.theta = std::min(temp + sphericalRot.theta, (MY_PI - 0.0001f) );

	lookAt.x = r * cos(rotation.phi) * sin(rotation.theta);
	lookAt.z = r * sin(rotation.phi) * sin(rotation.theta);
	lookAt.y = r * cos(rotation.theta);

	upVector = {0.0, std::abs(position.y) + 1.0f, 0.0};
}

bool Camera::isEnabled() { return enabled; }

void Camera::enable() { enabled = true; }
void Camera::disable() { enabled = false; }