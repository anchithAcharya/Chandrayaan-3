//
// Created by anchi on 01/07/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_DRAWABLE_H
#define CG_PROJECT___LUNAR_LANDER_DRAWABLE_H

#include "common.h"
#include <string>


class Material
{
public:
	GLuint textureID;
	bool textured = false;
	float shininess = 0.0, opacity = 1.0;
	array3f ambient = array3f(0.2), diffuse = array3f(0.8), specular = {0}, emission = {0};


	void setTexture( std::string imgPath, bool repeat = false );

	void setColor( array3f color );

	void enable();
};


class Drawable
{
private:
	std::vector<array3f> vertices, texCoords, normals;
	std::vector<std::vector<array3f>> faces;
	std::vector<Drawable> drawables;
	Material material;
	bool smoothing = false;

public:
	bool noCulling = false, noDepthTest = false, noLighting = false;

	void addVertex( array3f v );

	void addTexCoord( float tx, float ty );

	void addNormal( array3f n );

	void addFace( std::vector<float> f );

	void addFacevn( std::vector<std::array<float, 2>> f );

	void addFacevtn( std::vector<array3f> f );

	void addDrawable( Drawable d );

	void setMaterial( Material mat );

	void setSmoothing( bool value );

	void draw();
};

#endif //CG_PROJECT___LUNAR_LANDER_DRAWABLE_H