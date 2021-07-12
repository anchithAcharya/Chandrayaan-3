#include <iostream>
#include <GL/glut.h>

#include "common.h"
#include "main.h"
#include "Drawable.h"
#include "Camera.h"
#include "Player.h"


Player player;
Camera camera(player.position, player.rotation);
Cursor& cursor = Cursor::getInstance();

Drawable groundPlane = Drawable();

void drawSnowMan()
{

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.update();

	groundPlane.draw();
	//draw satellite
	 for(int i = -3; i < 3; i++) {
		 for (int j = -3; j < 3; j++) {
			 glPushMatrix();
			 glTranslatef(i * 10.0, 0, j * 10.0);
			 drawSnowMan();
			 glPopMatrix();
		 }
	 }

	glutSwapBuffers();
}


void mouseFunc( int button, int state, int x, int y )
{
	if( state == GLUT_DOWN )
	{
		switch( button )
		{
			case GLUT_RIGHT_BUTTON:	if( camera.isEnabled() )
									{
										camera.disable();
										cursor.setCursor(Cursor::CursorIcon::DefaultArrow);
									}

									else
									{
										camera.enable();
										cursor.isReset = true;
										cursor.setCursor(Cursor::CursorIcon::None);
									}

									break;
		}
	}
}

void keyboardFunc( unsigned char key, int x, int y )
{
	switch( key )
	{
		case 'w':	player.moveForward();
					break;

		case 'a':	player.moveLeft();
					break;

		case 's':	player.moveBackward();
					break;

		case 'd':	player.moveRight();
					break;

		case 'f':	player.isFlying = !player.isFlying;
					if( !player.isFlying ) player.position.y = 1.0;
					break;

		case ' ': 	if( player.isFlying ) player.moveUp();
					break;

		case 'c': 	if( player.isFlying ) player.moveDown();
					break;

		case 'l': 	std::cout << std::toDegrees(player.rotation.x) << " " << std::toDegrees(player.rotation.y) << " " << std::toDegrees(player.rotation.z) << std::endl;
					break;
	}
}

void specialKeyFunc( int key, int, int y )
{
	float lookAngle= 0.1;

	switch( key )
	{
		case GLUT_KEY_UP:		camera.set(0, {0.0, -lookAngle, 0.0}, true);
								break;

		case GLUT_KEY_DOWN:		camera.set(0, {0.0, lookAngle, 0.0}, true);
								break;

		case GLUT_KEY_LEFT:		camera.set(0, {-lookAngle, 0.0, 0.0}, true);
								break;

		case GLUT_KEY_RIGHT:	camera.set(0, {lookAngle, 0.0, 0.0}, true);
								break;
	}
}

void passiveMotionFunc( int x, int y )
{
	if( camera.isEnabled() )
	{
		if( cursor.isWarping  )
		{
			cursor.isWarping = false;
			cursor.pos = {x,y};
			return;
		}

		if( cursor.isReset )
		{
			cursor.pos = {x,y};
			cursor.isReset = false;
		}

		std::array<int, 2> mouseMoveDistance;

		mouseMoveDistance[0] = x - cursor.pos[0];
		mouseMoveDistance[1] = y - cursor.pos[1];

		cursor.pos = {x,y};

		float angleX = (mouseMoveDistance[0] * 180) / ( screenWidth / 0.01 );
		float angleY = (mouseMoveDistance[1] * 180) / ( screenHeight / 0.01 );

		camera.set(0, {angleX, angleY, 0.0}, true);

		cursor.warpHandler();
	}
}


void reshapeFunc( int w, int h )
{
	screenWidth = w;
	screenHeight = h;

	if ( h == 0 ) h = 1;
	double aspectRatio = (double) w / h;
	cursor.isReset = true;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluPerspective(45.0, aspectRatio, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
}


void init()
{
	groundPlane.addVertex({-100.0, 0.0, -100.0});
	groundPlane.addVertex({-100.0, 0.0,  100.0});
	groundPlane.addVertex({ 100.0, 0.0,  100.0});
	groundPlane.addVertex({ 100.0, 0.0, -100.0});

//	groundPlane.addFace({{0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}});

	camera.set({0.0, 1.0, 5.0}, {std::toRadians(270), std::toRadians(90.0), 0.0}, false);
}

int main( int argc, char **argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(500,500);
    glutCreateWindow("Lunar Landing 3D");

//	glutFullScreen();

	glEnable(GL_DEPTH_TEST);

    glutMouseFunc(mouseFunc);
    glutIdleFunc(displayFunc);
    glutDisplayFunc(displayFunc);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialKeyFunc);
    glutPassiveMotionFunc(passiveMotionFunc);

    init();

	groundPlane.addFace({{0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}});

    glutMainLoop();

    return 0;
}