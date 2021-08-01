//
// Created by anchi on 01/07/2021.
//

#include "Player.h"
#include <cmath>


void Player::moveForward()
{
	array3f temp;
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	temp.x = stepDistance * cos(rotation.x);
	temp.z = stepDistance * sin(rotation.x);

	position += temp;
}

void Player::moveBackward()
{
	array3f temp;
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	temp.x = -stepDistance * cos(rotation.x);
	temp.z = -stepDistance * sin(rotation.x);

	position += temp;
}

void Player::moveLeft()
{
	float angle = isRunning? (runModifier * turnAngle) : turnAngle;
	rotation.phi -= std::toRadians(angle);
}

void Player::moveRight()
{
	float angle = isRunning? (runModifier * turnAngle) : turnAngle;
	rotation.phi += std::toRadians(angle);
}


void Player::render()
{
	glPushMatrix();

		glTranslatef(position.x, position.y, position.z);
		glRotatef(-std::toDegrees(rotation.phi) - 90, 0.0, 1.0, 0.0);		// - 90 to compensate for model bias
		glScalef(0.1, 0.1, 0.1);												// also to compensate for model bias

		model.draw();

	glPopMatrix();
}