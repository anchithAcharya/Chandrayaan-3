//
// Created by anchi on 31/07/2021.
//

#include "Entity.h"
#include <cmath>


array3f Entity::getPosition() { return position; }

array3f Entity::getRotation() { return rotation; }


void Entity::moveForward()
{
	array3f temp;

	temp.x = step * cos(rotation.x);
	temp.z = step * sin(rotation.x);

	position += temp;
}

void Entity::moveBackward()
{
	array3f temp;

	temp.x = -step * cos(rotation.x);
	temp.z = -step * sin(rotation.x);

	position += temp;
}

void Entity::moveLeft()
{
	array3f temp;

	temp.x = -step * cos(rotation.x - std::toRadians(90));
	temp.z = -step * sin(rotation.x - std::toRadians(90));

	position -= temp;
}

void Entity::moveRight()
{
	array3f temp;

	temp.x = -step * cos(rotation.x - std::toRadians(90));
	temp.z = -step * sin(rotation.x - std::toRadians(90));

	position += temp;
}

void Entity::moveUp()
{
	position.y += step;
}

void Entity::moveDown()
{
	position.y -= step;
}


void Entity::attach( const Entity &obj, array3f offset )
{
	position.x = obj.position.x + offset.x;
	position.y = obj.position.y + offset.y;
	position.z = obj.position.z + offset.z;
}

void Entity::render()
{
	glPushMatrix();

		glTranslatef(position.x, position.y, position.z);
		model.draw();

	glPopMatrix();
}