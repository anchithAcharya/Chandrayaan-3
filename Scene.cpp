//
// Created by anchi on 01/08/2021.
//

#include "Player.h"
#include "Scene.h"
#include "rover.h"
#include "lander.h"


std::map<std::string, Material> materials;
Drawable lander, groundPlane;

void initMaterials()
{
	Material blackglass;
	blackglass.shininess = 0.83440448;
	blackglass.opacity = 0.95;
	blackglass.setColor(array3f(0.0, 0.0, 0.0));
	blackglass.specular = array3f(1.0, 1.0, 1.0);
	blackglass.emission = array3f(0.0, 0.0, 0.0);
	materials["blackglass"] = blackglass;

	Material blackplastic;
	blackplastic.shininess = 28.8;
	blackplastic.opacity = 1.0;
	blackplastic.setColor(array3f(0.024808, 0.024808, 0.024808));
	blackplastic.specular = array3f(0.0, 0.0, 0.0);
	blackplastic.emission = array3f(0.0, 0.0, 0.0);
	materials["blackplastic"] = blackplastic;

	Material camera_lens;
	camera_lens.shininess = 28.8;
	camera_lens.opacity = 1.0;
	camera_lens.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\camera_lens.psd");
	camera_lens.setColor(array3f(0.8, 0.8, 0.8));
	camera_lens.specular = array3f(0.5, 0.5, 0.5);
	camera_lens.emission = array3f(0.0, 0.0, 0.0);
	materials["camera_lens"] = camera_lens;

	Material glass;
	glass.shininess = 115.2;
	glass.opacity = 0.2;
	glass.setColor(array3f(0.562938, 0.640445, 0.8));
	glass.specular = array3f(1.0, 1.0, 1.0);
	glass.emission = array3f(0.0, 0.0, 0.0);
	materials["glass"] = glass;

	Material gold;
	gold.shininess = 62.880103424000005;
	gold.opacity = 1.0;
	gold.setColor(array3f(0.722376, 0.522467, 0.06178));
	gold.specular = array3f(0.604478, 0.604478, 0.604478);
	gold.emission = array3f(0.0, 0.0, 0.0);
	materials["gold"] = gold;

	Material greenlight;
	greenlight.shininess = 28.8;
	greenlight.opacity = 1.0;
	greenlight.setColor(array3f(0.0, 1.0, 0.0));
	greenlight.specular = array3f(0.0, 0.0, 0.0);
	greenlight.emission = array3f(0.0, 1.0, 0.0);
	materials["greenlight"] = greenlight;

	Material metal;
	metal.shininess = 87.824281856;
	metal.opacity = 1.0;
	metal.setColor(array3f(0.580219, 0.575928, 0.598395));
	metal.specular = array3f(0.679104, 0.679104, 0.679104);
	metal.emission = array3f(0.0, 0.0, 0.0);
	materials["metal"] = metal;

	Material redlight;
	redlight.shininess = 28.8;
	redlight.opacity = 1.0;
	redlight.setColor(array3f(1.0, 0.0, 0.0));
	redlight.specular = array3f(0.0, 0.0, 0.0);
	redlight.emission = array3f(1.0, 0.0, 0.0);
	materials["redlight"] = redlight;

	Material solar_panel;
	solar_panel.shininess = 28.8;
	solar_panel.opacity = 1.0;
	solar_panel.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\solar_panel.psd");
	solar_panel.setColor(array3f(0.8, 0.8, 0.8));
	solar_panel.specular = array3f(0.5, 0.5, 0.5);
	solar_panel.emission = array3f(0.0, 0.0, 0.0);
	materials["solar_panel"] = solar_panel;

	Material solar_panel_repeat;
	solar_panel_repeat.shininess = 28.8;
	solar_panel_repeat.opacity = 1.0;
	solar_panel_repeat.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\solar_panel.psd", true);
	solar_panel_repeat.setColor(array3f(0.8, 0.8, 0.8));
	solar_panel_repeat.specular = array3f(0.5, 0.5, 0.5);
	solar_panel_repeat.emission = array3f(0.0, 0.0, 0.0);
	materials["solar_panel_repeat"] = solar_panel_repeat;

	Material tyres;
	tyres.shininess = 28.8;
	tyres.opacity = 1.0;
	tyres.setColor(array3f(0.007926, 0.007926, 0.007926));
	tyres.specular = array3f(0.022388, 0.022388, 0.022388);
	tyres.emission = array3f(0.0, 0.0, 0.0);
	materials["tyres"] = tyres;

	Material flag;
	flag.shininess = 28.8;
	flag.opacity = 1.0;
	flag.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\flag.psd");
	flag.setColor(array3f(0.8, 0.8, 0.8));
	flag.specular = array3f(0.5, 0.5, 0.5);
	flag.emission = array3f(0.0, 0.0, 0.0);
	materials["flag"] = flag;
}


void defineSkyBox( Drawable &skybox )
{
	Material space;
	space.shininess = 0;
	space.opacity = 1.0;
	space.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\space.psd");
	space.setColor(1.0);
	space.specular = array3f(0);
	space.emission = array3f(1.0);
	materials["space"] = space;

	Material earth;
	earth.shininess = 0;
	earth.opacity = 1.0;
	earth.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\earth.psd");
	earth.setColor(1.0);
	earth.specular = array3f(0);
	earth.emission = array3f(1.0);
	materials["earth"] = earth;

	Material sun;
	sun.shininess = 0;
	sun.opacity = 1.0;
	sun.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\sun.psd");
	sun.setColor(1.0);
	sun.specular = array3f(0);
	sun.emission = array3f(1.0);
	materials["sun"] = sun;


	Drawable top;
	top.noCulling = true;
	top.addVertex({-1, 1, -1});
	top.addTexCoord(0, 0);
	top.addVertex({-1, 1, 1});
	top.addTexCoord(0, 1);
	top.addVertex({ 1, 1, 1});
	top.addTexCoord(1, 1);
	top.addVertex({ 1, 1, -1});
	top.addTexCoord(1, 0);

	top.setMaterial(space);

	top.addFacevtn({{0, 0, -1}, {1, 1, -1}, {2, 2, -1}, {3, 3, -1}});


	Drawable bottom;
	bottom.noCulling = true;
	bottom.addVertex({-1, -1, -1});
	bottom.addTexCoord(0, 0);
	bottom.addVertex({-1, -1, 1});
	bottom.addTexCoord(0, 1);
	bottom.addVertex({ 1, -1, 1});
	bottom.addTexCoord(1, 1);
	bottom.addVertex({ 1, -1, -1});
	bottom.addTexCoord(1, 0);

	bottom.setMaterial(space);

	bottom.addFacevtn({{0, 0, -1}, {1, 1, -1}, {2, 2, -1}, {3, 3, -1}});


	Drawable right;
	right.noCulling = true;
	right.addVertex({-1, -1, 1});
	right.addTexCoord(0, 0);
	right.addVertex({-1, 1, 1});
	right.addTexCoord(0, 1);
	right.addVertex({ 1, 1, 1});
	right.addTexCoord(1, 1);
	right.addVertex({ 1, -1, 1});
	right.addTexCoord(1, 0);

	right.setMaterial(space);

	right.addFacevtn({{0, 0, -1}, {1, 1, -1}, {2, 2, -1}, {3, 3, -1}});


	Drawable left;
	left.noCulling = true;
	left.addVertex({-1, -1, -1});
	left.addTexCoord(1, 0);
	left.addVertex({-1, 1, -1});
	left.addTexCoord(0, 0);
	left.addVertex({ 1, 1, -1});
	left.addTexCoord(0, 1);
	left.addVertex({ 1, -1, -1});
	left.addTexCoord(1, 1);

	left.setMaterial(space);

	left.addFacevtn({{0, 0, -1}, {1, 1, -1}, {2, 2, -1}, {3, 3, -1}});


	Drawable front;
	front.noCulling = true;
	front.addVertex({1, 1, 1});
	front.addTexCoord(0, 0);
	front.addVertex({1, -1, 1});
	front.addTexCoord(0, 1);
	front.addVertex({1, -1, -1});
	front.addTexCoord(1, 1);
	front.addVertex({1, 1, -1});
	front.addTexCoord(1, 0);

	front.setMaterial(sun);

	front.addFacevtn({{0, 0, -1}, {1, 1, -1}, {2, 2, -1}, {3, 3, -1}});


	Drawable back;
	back.noCulling = true;
	back.addVertex({-1, -1, -1});
	back.addTexCoord(0, 0);
	back.addVertex({-1, 1, -1});
	back.addTexCoord(0, 1);
	back.addVertex({-1, 1, 1});
	back.addTexCoord(1, 1);
	back.addVertex({-1, -1, 1});
	back.addTexCoord(1, 0);

	back.setMaterial(earth);

	back.addFacevtn({{0, 0, -1}, {1, 1, -1}, {2, 2, -1}, {3, 3, -1}});


	skybox.addDrawable(top);
	skybox.addDrawable(bottom);
	skybox.addDrawable(right);
	skybox.addDrawable(left);
	skybox.addDrawable(front);
	skybox.addDrawable(back);

	skybox.noDepthTest = true;
}

void defineGroundPlane()
{
	Material moon;
	moon.shininess = 0;
	moon.opacity = 1.0;
	moon.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\moon.psd", true);
	moon.setColor(0.3);
	moon.specular = array3f(0);
	moon.emission = array3f(0.5);
	materials["moon"] = moon;

	groundPlane.addVertex({-100.0, 0.0, -100.0});
	groundPlane.addTexCoord(0, 0);
	groundPlane.addVertex({-100.0, 0.0,  100.0});
	groundPlane.addTexCoord(0, 35);
	groundPlane.addVertex({ 100.0, 0.0,  100.0});
	groundPlane.addTexCoord(35, 35);
	groundPlane.addVertex({ 100.0, 0.0, -100.0});
	groundPlane.addTexCoord(35, 0);

	groundPlane.setMaterial(moon);

	groundPlane.addFacevtn({{0, 0, -1}, {1, 1, -1}, {2, 2, -1}, {3, 3, -1}});
}


void initScene()
{
	defineLander(lander);
	defineGroundPlane();
}


void initSkyBox( Drawable &skybox )
{ defineSkyBox(skybox); }

void initPlayerModel( Drawable &playerModel )
{ defineRover(playerModel); }
