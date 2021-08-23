//
// Created by anchi on 07/08/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_SCENE_H
#define CG_PROJECT___LUNAR_LANDER_SCENE_H

#include <map>
#include "common.h"
#include "Drawable.h"


extern std::map<std::string, Material> materials;
extern Drawable lander, groundPlane;


void initMaterials();

void initScene();


void initSkyBox( Drawable &skybox );

void initPlayerModel( Drawable &playerModel );

#endif //CG_PROJECT___LUNAR_LANDER_SCENE_H
