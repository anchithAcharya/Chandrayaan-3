//
// Created by anchi on 31/07/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_ENTITY_H
#define CG_PROJECT___LUNAR_LANDER_ENTITY_H

#include "common.h"
#include "Drawable.h"


class Entity
{
protected:
	array3f position, rotation;
	static constexpr float step = 0.025, runModifier = 3.0;

public:
	Composite model;
	array3f getPosition();

	array3f getRotation();


	virtual void moveForward();

	virtual void moveBackward();

	virtual void moveLeft();

	virtual void moveRight();

	virtual void moveUp();

	virtual void moveDown();

	virtual void attach( const Entity &obj, array3f offset );


	virtual void render();
};

#endif //CG_PROJECT___LUNAR_LANDER_ENTITY_H
