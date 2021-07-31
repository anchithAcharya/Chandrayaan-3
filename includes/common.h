//
// Created by anchi on 23/06/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_COMMON_H
#define CG_PROJECT___LUNAR_LANDER_COMMON_H

constexpr float MY_PI = 3.14159265358979323846;


#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <array>


class array3f
{
private:
	std::array<float, 3> elements;

public:
	float &x, &y, &z;
	float &r, &g, &b;
	float &v, &t, &n;
	float &phi, &theta, &radius;


	array3f( float f1, float f2, float f3 );

	array3f( float f );

	array3f();

	array3f( std::array<float, 3> e );

	array3f( const array3f &other );


	array3f &operator = ( const array3f &other );

	array3f &operator += ( const array3f &other );

	array3f operator + ( const array3f &other );

	array3f &operator -= ( const array3f &other );

	array3f operator - ( const array3f &other );

	bool operator == ( const array3f &other );

	bool operator != ( const array3f &other );


	std::array<float, 3>::pointer values();
};

namespace std
{
	inline float toRadians( float degrees ) { return ( degrees * (MY_PI/180) ); }

	inline float toDegrees( float radians ) { return ( radians * (180/MY_PI) ); }
}

GLuint loadImage( std::string filename );

#endif //CG_PROJECT___LUNAR_LANDER_COMMON_H