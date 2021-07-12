//
// Created by anchi on 01/07/2021.
//

#include "Drawable.h"


void Drawable::addVertex( array3f v ) { vertices.push_back(v); }

void Drawable::addTexCoord(array3f t) { texCoords.push_back(t); }

void Drawable::addNormal( array3f n ) { normals.push_back(n); }

void Drawable::addFace( std::vector<array3f> f ) { faces.push_back(f); }

void Drawable::draw()
{
	for( auto face: faces )
	{
		glBegin(GL_POLYGON);

			for( auto index : face )
			{
				if( index.t >= 0 ) glTexCoord3fv(texCoords[index.t].values());
				if( index.n >= 0 ) glNormal3fv(normals[index.n].values());
				glVertex3fv(vertices[index.v].values());
			}

		glEnd();
	}
}


void Composite::addDrawable( Drawable d ) { drawables.push_back(d); }

void Composite::addComposite( Composite c ) { composites.push_back(c); }

void Composite::draw()
{
	for( Composite c: composites )
		c.draw();

	for( Drawable d: drawables )
		d.draw();
}