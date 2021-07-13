//
// Created by anchi on 23/06/2021.
//

#ifndef CG_PROJECT___LUNAR_LANDER_MAIN_H
#define CG_PROJECT___LUNAR_LANDER_MAIN_H


#include "common.h"

int screenHeight, screenWidth;

class Cursor
{
private:
	Cursor() {}

	Cursor( Cursor const& ) = delete;
	void operator = ( Cursor const& ) = delete;

public:
	std::array<int, 2> pos = {0,0};
	int &xPos = pos[0], &yPos = pos[1];

	bool isWarping = false, isReset = true;

	static Cursor& getInstance()
	{
		static Cursor cursor;
		return cursor;
	}

	void warpHandler()
	{
		if( xPos > (screenWidth/4.0)*3 )
		{
			glutWarpPointer((screenWidth/4.0),yPos);
			isWarping = true;
		}

		if( xPos < (screenWidth/4.0) )
		{
			glutWarpPointer((screenWidth/4.0)*3,yPos);
			isWarping = true;
		}

		if( yPos > (screenHeight/4.0)*3 )
		{
			glutWarpPointer(xPos,(screenHeight/4.0));
			isWarping = true;
		}

		if( yPos < (screenHeight/4.0) )
		{
			glutWarpPointer(xPos,(screenHeight/4.0)*3);
			isWarping = true;
		}
	}

	enum class CursorIcon
	{
		None = GLUT_CURSOR_NONE,
		DefaultArrow = GLUT_CURSOR_INHERIT
	};

	void setCursor( CursorIcon i ) { glutSetCursor((int) i); }
};

struct Keys
{
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool SPACE = false;
	bool UP = false;
	bool DOWN = false;
	bool LEFT = false;
	bool RIGHT = false;
	bool LSHIFT = false;
} keyStates;

#endif //CG_PROJECT___LUNAR_LANDER_MAIN_H
