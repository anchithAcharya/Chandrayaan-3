//
// Created by anchi on 01/07/2021.
//

#include "Player.h"
#include "Scene.h"
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
	float angle = isRunning? (turnModifier * turnAngle) : turnAngle;
	rotation.phi -= std::toRadians(angle);
}

void Player::moveRight()
{
	float angle = isRunning? (turnModifier * turnAngle) : turnAngle;
	rotation.phi += std::toRadians(angle);
}


void Player::drawLaser()
{
	materials["greenlight"].enable();

	glPushMatrix();
	array3f laserEnd = array3f(laserUnit.x * laserLength, laserUnit.y * laserLength, laserUnit.z * laserLength);
	laserEnd += laserStart;

	glBegin(GL_LINES);
		glVertex3fv(laserStart.values());
		glVertex3fv(laserEnd.values());
	glEnd();

	glPopMatrix();

	materials["none"].enable();

	float inc = 0.05;

	if( laserOn )
	{
		if( laserLength < laserMaxLength ) laserLength += inc;
		laserOn = false;
	}

	else laserLength -= inc;
}

void Player::render()
{
	glPushMatrix();

		glTranslatef(position.x, position.y, position.z);
		glRotatef(-std::toDegrees(rotation.phi), 0.0, 1.0, 0.0);

		model.draw();
		if( laserOn || laserLength > 0 ) drawLaser();

	glPopMatrix();
}