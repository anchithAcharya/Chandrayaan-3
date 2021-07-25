//
// Created by anchi on 01/07/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_DRAWABLE_H
#define CG_PROJECT___LUNAR_LANDER_DRAWABLE_H


#include "common.h"


class Drawable
{
private:
	std::vector<array3f> vertices, texCoords, normals;
	std::vector<std::vector<array3f>> faces;

public:
	GLuint textureID;

	void addVertex( array3f v );

	void addTexCoord( float tx, float ty );

	void addNormal( array3f n );

	void addFace( std::vector<array3f> f );

	void draw();
};

class Composite
{
public:
	std::vector<Drawable> drawables;
	std::vector<Composite> composites;

	void addDrawable( Drawable d );

	void addComposite( Composite c );

	void draw();
};

#endif //CG_PROJECT___LUNAR_LANDER_DRAWABLE_H