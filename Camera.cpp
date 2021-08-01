//
// Created by anchi on 01/07/2021.
//

#include "Camera.h"
#include <cmath>

array3f Camera::getLookAtCoords() { return lookAt; }


void Camera::moveForward()
{
	array3f temp;
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	temp.x = stepDistance * cos(rotation.x);
	temp.z = stepDistance * sin(rotation.x);
	if( isFlying ) temp.y = stepDistance * cos(rotation.y);
	else temp.y = 1.0 - position.y;

	position += temp;
}

void Camera::moveBackward()
{
	array3f temp;
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	temp.x = -stepDistance * cos(rotation.x);
	temp.z = -stepDistance * sin(rotation.x);
	if( isFlying ) temp.y = -stepDistance * cos(rotation.y);
	else temp.y = 1.0 - position.y;

	position += temp;
}

void Camera::moveLeft()
{
	array3f temp;
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	temp.x = -stepDistance * cos(rotation.x - std::toRadians(90));
	temp.z = -stepDistance * sin(rotation.x - std::toRadians(90));

	position -= temp;
}

void Camera::moveRight()
{
	array3f temp;
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	temp.x = -stepDistance * cos(rotation.x - std::toRadians(90));
	temp.z = -stepDistance * sin(rotation.x - std::toRadians(90));

	position += temp;
}

void Camera::moveUp()
{
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	position.y += stepDistance;
}

void Camera::moveDown()
{
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	position.y -= stepDistance;
}


void Camera::update()
{
	gluLookAt(position.x,	position.y,   position.z,
			  position.x + lookAt.x, 	position.y + lookAt.y,	  position.z + lookAt.z,
			  upVector.x,	upVector.y,   upVector.z);
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

	lookAt.x = distanceFromCamera * cos(rotation.phi) * sin(rotation.theta);
	lookAt.z = distanceFromCamera * sin(rotation.phi) * sin(rotation.theta);
	lookAt.y = distanceFromCamera * cos(rotation.theta);

	upVector = {0.0, std::abs(position.y) + 1.0f, 0.0};
}