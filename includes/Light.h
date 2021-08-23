//
// Created by anchi on 01/08/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_LIGHT_H
#define CG_PROJECT___LUNAR_LANDER_LIGHT_H

#include "common.h"
#include "Entity.h"


class Light: public Entity
{
private:
	bool lightOn = true;
	array3f spot_direction;
	static constexpr float spotLightDistance = 25;

public:
	Light( array3f ambient, array3f diffuse, array3f specular);


	void toggle();

	void setSpotDirection( array3f lookAt );

	void update();
};

#endif //CG_PROJECT___LUNAR_LANDER_LIGHT_H