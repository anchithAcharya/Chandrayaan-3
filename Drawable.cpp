//
// Created by anchi on 01/07/2021.
//

#include "Drawable.h"

void Material::setTexture( std::string imgPath ) { Material::textureID = loadImage(imgPath); }

void Material::setColor( array3f color ) { ambient = diffuse = color; }

void Material::enable()
{
	float ambient4[4] = { ambient.r, ambient.g, ambient.b, 1.0 };
	float diffuse4[4] = { diffuse.r, diffuse.g, diffuse.b, opacity };
	float specular4[4] = { specular.r, specular.g, specular.b, 1.0 };
	float emission4[4] = { emission.r, emission.g, emission.b, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission4);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	if( textured )
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	else glDisable(GL_TEXTURE_2D);
}


void Drawable::addVertex( array3f v ) { vertices.push_back(v); }

void Drawable::addTexCoord( float tx, float ty ) { texCoords.push_back(array3f(tx, ty, 0.0)); }

void Drawable::addNormal( array3f n ) { normals.push_back(n); }

void Drawable::addFace( std::vector<float> f )
{
	std::vector<array3f> facevtn;

	for( auto vertex: f )
		facevtn.push_back( array3f(vertex, -1, -1) );

	faces.push_back(facevtn);
}

void Drawable::addFacevn( std::vector<std::array<float, 2>> f )
{
	std::vector<array3f> facevn;

	for( auto point: f )
		facevn.push_back( array3f(point[0], -1, point[1]) );

	faces.push_back(facevn);
}

void Drawable::addFacevtn( std::vector<array3f> f ) { faces.push_back(f); }

void Drawable::setMaterial( Material mat ) { material = mat; }

void Drawable::setSmoothing( bool value ) { smoothing = value; }

void Drawable::draw()
{
	if( smoothing ) glShadeModel(GL_SMOOTH);
	else glShadeModel(GL_FLAT);

	material.enable();

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

	Material().enable();
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