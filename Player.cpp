//
// Created by anchi on 01/07/2021.
//

#include "Player.h"
#include <cmath>
#include "Drawable.h"


void Player::moveForward()
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

void Player::moveBackward()
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

void Player::moveLeft()
{
	array3f temp;
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	temp.x = -stepDistance * cos(rotation.x - std::toRadians(90));
	temp.z = -stepDistance * sin(rotation.x - std::toRadians(90));

	position -= temp;
}

void Player::moveRight()
{
	array3f temp;
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	temp.x = -stepDistance * cos(rotation.x - std::toRadians(90));
	temp.z = -stepDistance * sin(rotation.x - std::toRadians(90));

	position += temp;
}

void Player::moveUp()
{
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	position.y += stepDistance;
}

void Player::moveDown()
{
	float stepDistance = step;
	if( isRunning ) stepDistance *= runModifier;

	position.y -= stepDistance;
}

void Player::render()
{
	glPushMatrix();
//		glLoadIdentity();

		offset.x = -cos(rotation.x);
		offset.z = -sin(rotation.x);
//		glTranslatef(position.x - offset.x, 0.0 - offset.y, position.z - offset.z);
//		glRotatef(-std::toDegrees(rotation.phi) - 90, 0.0, 1.0, 0.0);
//		glScalef(0.1, 0.1, 0.1);

		model.draw();
	glPopMatrix();
}