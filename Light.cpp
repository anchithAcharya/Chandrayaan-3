//
// Created by anchi on 15/08/2021.
//

#include "Light.h"

Light::Light( array3f ambient, array3f diffuse, array3f specular )
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float ambient4[4] = { ambient.r, ambient.g, ambient.b, 0.1 };
	float diffuse4[4] = { diffuse.r, diffuse.g, diffuse.b, 0.1 };
	float specular4[4] = { specular.r, specular.g, specular.b, 0.1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient4);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse4);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular4);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
}

void Light::toggle()
{
	lightOn = !lightOn;

	if( lightOn ) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);
}

void Light::setSpotDirection( array3f lookAt )
{
	spot_direction.x = position.x + (lookAt.x * spotLightDistance);
	spot_direction.y = position.y + (lookAt.y * spotLightDistance);
	spot_direction.z = position.z + (lookAt.z * spotLightDistance);
}

void Light::update()
{
	float position4[4] = { position.x, position.y, position.z, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position4);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction.values());
}
