#include <cmath>
#include <iostream>
#include <GL/glut.h>

#include "common.h"
#include "main.h"
#include "Drawable.h"
#include "Camera.h"
#include "Player.h"
#include "Light.h"
#include "Scene.h"

Player rover;
Camera camera;
Light *light;
Cursor& cursor = Cursor::getInstance();

Drawable introScreen;

bool showingIntro = true, showingHelp = false;


void handleKeyHold()
{
	bool moved = false;

	if( camera.isFlying )
	{

		if( keyStates.W )	{ camera.moveForward(); moved = true; }
		if( keyStates.A )	{ camera.moveLeft(); moved = true; }
		if( keyStates.S )	{ camera.moveBackward(); moved = true; }
		if( keyStates.D )	{ camera.moveRight(); moved = true; }

		if( keyStates.SPACE )	{ camera.moveUp(); moved = true; }
		if( keyStates.LSHIFT )	{ camera.moveDown(); moved = true; }
	}

	else
	{
		if( keyStates.W ) { rover.moveForward(); moved = true; }
		if( keyStates.A ) { rover.moveLeft(); moved = true; }
		if( keyStates.S ) { rover.moveBackward(); moved = true; }
		if( keyStates.D ) { rover.moveRight(); moved = true; }

		if( moved )
		{
			array3f rotation = rover.getRotation();

			camera.offset.x = -2 * cos(rotation.phi);
			camera.offset.z = -2 * sin(rotation.phi);

			if( camera.follow ) camera.attach(rover, camera.offset);
		}
	}

	if( moved ) light->attach(camera);


	bool cameraModified = false;
	float lookAngle = 0.005;

	if( keyStates.UP )		{ camera.set(0, {0.0, -lookAngle, 0.0}, true); cameraModified = true; }
	if( keyStates.DOWN )	{ camera.set(0, {0.0, lookAngle, 0.0}, true); cameraModified = true; }
	if( keyStates.LEFT )	{ camera.set(0, {-lookAngle, 0.0, 0.0}, true); cameraModified = true; }
	if( keyStates.RIGHT )	{ camera.set(0, {lookAngle, 0.0, 0.0}, true); cameraModified = true; }

	if( cameraModified ) light->setSpotDirection(camera.getLookAtCoords());

	if( keyStates.LMB ) rover.laserOn = true;
}


void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if( showingIntro || showingHelp ) introScreen.draw();

	else
	{
		handleKeyHold();

		camera.update();
		light->update();

		camera.render();
		groundPlane.draw();
		lander.draw();
		rover.render();
	}

	glutSwapBuffers();
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
	if( showingIntro || showingHelp ) glOrtho(0, 1, 0, 1, 1, -1);
	else gluPerspective(45.0, aspectRatio, 0.1, 150.0);

	glMatrixMode(GL_MODELVIEW);
}


void menuFunc( int choice )
{
	switch( choice )
	{
		case 1:	glutFullScreenToggle(); break;

		case 2:	camera.follow = !camera.follow; break;

		case 3:	camera.isFlying = !camera.isFlying;
				if( !camera.isFlying && camera.follow ) camera.attach(rover, camera.offset);
				break;

		case 4: light->toggle(); break;

		case 5:	glutLeaveMainLoop(); break;
	}

	cursor.isReset = true;
}

void initMenu()
{
	glutCreateMenu(menuFunc);

	glutAddMenuEntry("Toggle fullscreen", 1);
	glutAddMenuEntry("Attach / Detach camera from rover", 2);
	glutAddMenuEntry("Free-fly mode", 3);
	glutAddMenuEntry("Toggle light", 4);
	glutAddMenuEntry("Quit", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void mouseFunc( int button, int state, int x, int y )
{
	if( state == GLUT_DOWN && !showingIntro )
	{
		switch( button )
		{
			case GLUT_MIDDLE_BUTTON:if( camera.enabled )
									{
										camera.enabled = false;
										cursor.setCursor(Cursor::CursorIcon::DefaultArrow);
									}

									else
									{
										camera.enabled = true;

										cursor.isReset = true;
										cursor.setCursor(Cursor::CursorIcon::None);
									}

									break;

			case GLUT_LEFT_BUTTON:	keyStates.LMB = true; break;
		}
	}

	else if( button == GLUT_LEFT_BUTTON ) keyStates.LMB = false;
}

void keyDownFunc( unsigned char key, int x, int y )
{
	switch( key )
	{
		case 'W':
		case 'W' - 64:
		case 'w':	keyStates.W = true; break;

		case 'A':
		case 'A' - 64:
		case 'a':	keyStates.A = true; break;

		case 'S':
		case 'S' - 64:
		case 's':	keyStates.S = true; break;

		case 'D':
		case 'D' - 64:
		case 'd':	keyStates.D = true; break;

		case ' ':	keyStates.SPACE = true; break;


		case '\r':	if( showingIntro )
					{
						if( !showingHelp )
						{
							showingHelp = true;
							materials["screen2D"].setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\help_screen.png");
							introScreen.setMaterial(materials["screen2D"]);
						}

						else
						{
							showingIntro = showingHelp = false;

							initMenu();
							glutFullScreen();
							reshapeFunc(screenWidth, screenHeight);
						}
					}

					break;

		case 'h':	if( showingIntro ) break;
					showingHelp = !showingHelp;
					reshapeFunc(screenWidth, screenHeight);
					break;


		case 'l':	light->toggle(); break;

		case 'o':	camera.follow = !camera.follow; break;

		case 'f':	camera.isFlying = !camera.isFlying;
					if( !camera.isFlying && camera.follow ) camera.attach(rover, camera.offset);
					break;


		case 'r':	std::cout << std::toDegrees(rover.getRotation()) << std::endl; break;
		case 'p':	std::cout << rover.getPosition() << std::endl; break;
	}
}

void keyUpFunc( unsigned char key, int x, int y )
{
	switch( key )
	{
		case 'W':
		case 'W' - 64:
		case 'w':	keyStates.W = false; break;

		case 'A':
		case 'A' - 64:
		case 'a':	keyStates.A = false; break;

		case 'S':
		case 'S' - 64:
		case 's':	keyStates.S = false; break;

		case 'D':
		case 'D' - 64:
		case 'd':	keyStates.D = false; break;


		case ' ':	keyStates.SPACE = false; break;
	}
}

void specialKeyDownFunc( int key, int x, int y )
{
	switch ( key )
	{
		case GLUT_KEY_UP:		keyStates.UP = true; break;
		case GLUT_KEY_DOWN:		keyStates.DOWN = true; break;
		case GLUT_KEY_LEFT:		keyStates.LEFT = true; break;
		case GLUT_KEY_RIGHT:	keyStates.RIGHT = true; break;
		case GLUT_KEY_SHIFT_L:	keyStates.LSHIFT = true; break;
		case GLUT_KEY_CTRL_L: rover.isRunning = camera.isRunning = true; break;
	}
}

void specialKeyUpFunc( int key, int x, int y )
{
	switch ( key )
	{
		case GLUT_KEY_UP:		keyStates.UP = false; break;
		case GLUT_KEY_DOWN:		keyStates.DOWN = false; break;
		case GLUT_KEY_LEFT:		keyStates.LEFT = false; break;
		case GLUT_KEY_RIGHT:	keyStates.RIGHT = false; break;
		case GLUT_KEY_SHIFT_L:	keyStates.LSHIFT = false; break;
		case GLUT_KEY_CTRL_L: rover.isRunning = camera.isRunning = false; break;
	}
}

void mouseMotionFunc( int x, int y )
{
	if( camera.enabled )
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

		float anglePhi = (mouseMoveDistance[0] * 180) / ( screenWidth / 0.01 );
		float angleTheta = (mouseMoveDistance[1] * 180) / ( screenHeight / 0.01 );

		camera.set(0, {anglePhi, angleTheta, 0.0}, true);
		light->setSpotDirection(camera.getLookAtCoords());

		cursor.warpHandler();
	}
}


void initIntroAndHelpScreen()
{
	Material screen2D;
	screen2D.setColor(array3f(1.0));
	screen2D.setTexture("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\images\\intro.png");
	materials["screen2D"] = screen2D;

	introScreen.setMaterial(screen2D);


	introScreen.noCulling = true;
	introScreen.noDepthTest = true;
	introScreen.noLighting = true;


	introScreen.addVertex({0, 0, 0});
	introScreen.addTexCoord(0, 0);
	introScreen.addVertex({0, 1, 0});
	introScreen.addTexCoord(0, 1);
	introScreen.addVertex({1, 1, 0});
	introScreen.addTexCoord(1, 1);
	introScreen.addVertex({1, 0, 0});
	introScreen.addTexCoord(1, 0);

	introScreen.addFacevtn({{1, 1, -1}, {2, 2, -1}, {3, 3, -1}, {4, 4, -1}});
}

void init()
{
	initMaterials();
	initScene();

	initIntroAndHelpScreen();

	initSkyBox(camera.model);
	initPlayerModel(rover.model);

	camera.set({0.0}, {0, std::toRadians(90.0), 0.0}, false);

	array3f rotation = rover.getRotation();

	camera.offset.x = -2 * cos(rotation.phi);
	camera.offset.z = -2 * sin(rotation.phi);

	if( camera.follow ) camera.attach(rover, camera.offset);

	light = new Light(array3f(0.5), array3f(0.5), array3f(0.1));
	light->attach(camera);
	light->setSpotDirection(camera.getLookAtCoords());

	glClearColor (0.0, 0.0, 0.0, 0.0);
}


int main( int argc, char **argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(500,500);
	glutInitWindowPosition(500, 200);
    glutCreateWindow("Chandrayaan 3 - 3D");


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2);

	glutIgnoreKeyRepeat(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


    glutIdleFunc(displayFunc);
    glutDisplayFunc(displayFunc);

    glutReshapeFunc(reshapeFunc);

    glutKeyboardFunc(keyDownFunc);
	glutKeyboardUpFunc(keyUpFunc);

	glutSpecialFunc(specialKeyDownFunc);
	glutSpecialUpFunc(specialKeyUpFunc);

	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotionFunc);
	glutPassiveMotionFunc(mouseMotionFunc);


    init();

    glutMainLoop();

    return 0;
}