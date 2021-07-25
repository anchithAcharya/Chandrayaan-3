//
// Created by anchi on 01/07/2021.
//

#include "common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


array3f::array3f( float f1, float f2, float f3 ):	elements({f1, f2, f3}),
													x(elements[0]), y(elements[1]), z(elements[2]),
													r(elements[0]), g(elements[1]), b(elements[2]),
													v(elements[0]), t(elements[1]), n(elements[2]),
													phi(elements[0]), theta(elements[1]), radius(elements[2]) {}

array3f::array3f( float f ): array3f(f, f, f) {}

array3f::array3f(): array3f(0) {}

array3f::array3f( std::array<float, 3> e ): array3f(e[0], e[1], e[2]) {}

array3f::array3f( const array3f &other ): array3f(other.elements) {}


array3f& array3f::operator = ( const array3f &other ) { elements = other.elements; return *this; }

array3f& array3f::operator += ( const array3f &other )
{
	elements[0] = elements[0] + other.elements[0];
	elements[1] = elements[1] + other.elements[1];
	elements[2] = elements[2] + other.elements[2];

	return *this;
}

array3f array3f::operator + ( const array3f &other )
{
	return array3f() += other;
}

array3f& array3f::operator -= ( const array3f &other )
{
	elements[0] = elements[0] - other.elements[0];
	elements[1] = elements[1] - other.elements[1];
	elements[2] = elements[2] - other.elements[2];

	return *this;
}

array3f array3f::operator - ( const array3f &other )
{
	return array3f() += other;
}

bool array3f::operator == ( const array3f &other ) { return elements == other.elements; }

bool array3f::operator != ( const array3f &other ) { return elements != other.elements; }

std::array<float, 3>::pointer array3f::values()
{ return elements.data(); }


GLuint loadImage( std::string filename )
{
	GLuint img;
	glGenTextures(1, &img);
	glBindTexture(GL_TEXTURE_2D, img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);
	}

	else
	{
	std::cout << "Failed to load img" << std::endl;
	std::cout << stbi_failure_reason() << std::endl;
	}

	stbi_image_free(data);
	return img;
}