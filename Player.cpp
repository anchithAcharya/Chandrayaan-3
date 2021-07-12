//
// Created by anchi on 01/07/2021.
//

#include "Player.h"
#include <math.h>


void Player::moveForward()
{
	array3f temp;

	temp.x = step * cos(rotation.x);
	temp.z = step * sin(rotation.x);
	if( isFlying ) temp.y = step * cos(rotation.y);
	else temp.y = 1.0 - position.y;

	position += temp;
}

void Player::moveBackward()
{
	array3f temp;

	temp.x = -step * cos(rotation.x);
	temp.z = -step * sin(rotation.x);
	if( isFlying ) temp.y = -step * cos(rotation.y);
	else temp.y = 1.0 - position.y;

	position += temp;
}

void Player::moveLeft()
{
	array3f temp;

	temp.x = -step * cos(rotation.x - 90);
	temp.z = -step * sin(rotation.x - 90);

	position -= temp;
}

void Player::moveRight()
{
	array3f temp;

	temp.x = -step * cos(rotation.x - 90);
	temp.z = -step * sin(rotation.x - 90);

	position += temp;
}

void Player::moveUp() { position.y += step; }

void Player::moveDown() { position.y -= step; }

void Player::render()
{
	glPushMatrix();
	glLoadIdentity();
	glRotatef(rotation.x, 1.0, 0.0, 0.0);
	glRotatef(rotation.y, 0.0, 1.0, 0.0);
	glRotatef(rotation.z, 0.0, 0.0, 1.0);

	model.draw();
	glPopMatrix();
}