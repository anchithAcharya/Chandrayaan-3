#include <iostream>
#include <GL/freeglut.h>

#include "common.h"
#include "main.h"
#include "Drawable.h"
#include "Camera.h"
#include "Player.h"


SimpleObj_t* myObj = loadObj("D:\\Productivity\\Code\\CG Project - Lunar Lander\\includes\\ll.obj");

Player player;
Camera camera;
Cursor& cursor = Cursor::getInstance();

Drawable groundPlane = Drawable();

GLuint img_top, img_left, img_front, img_right, img_back;

void Player::render()
{
	glPushMatrix();
//		glLoadIdentity();

	offset.x = -cos(rotation.x);
	offset.z = -sin(rotation.x);
	glTranslatef(position.x - offset.x, 0.0 - offset.y, position.z - offset.z);
	glRotatef(-std::toDegrees(rotation.phi) - 90, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);

//		model.draw();
	drawObj((SimpleObj_t *) rover);
	glPopMatrix();
}

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

void handleKeyHold()
{
	array3f temp;
	if(player.isFlying)
	{
		temp = player.position;
		player.position = camera.position;
	}
	if( keyStates.W )	player.moveForward();
	if( keyStates.A )	player.moveLeft();
	if( keyStates.S )	player.moveBackward();
	if( keyStates.D )	player.moveRight();

	if( keyStates.SPACE )	if( player.isFlying ) player.moveUp();
	if( keyStates.LSHIFT )	if( player.isFlying ) player.moveDown();

	camera.position = player.position;
	if(player.isFlying) player.position = temp;

	float lookAngle= 0.005;

	if( keyStates.UP )		camera.set(0, {0.0, -lookAngle, 0.0}, true);
	if( keyStates.DOWN )	camera.set(0, {0.0, lookAngle, 0.0}, true);
	if( keyStates.LEFT )	camera.set(0, {-lookAngle, 0.0, 0.0}, true);
	if( keyStates.RIGHT )	camera.set(0, {lookAngle, 0.0, 0.0}, true);
	if(!player.isFlying) player.rotation = camera.rotation;
}

void skybox()
{
	int texScale = 1, skyboxScale = 5, height = 5;

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	GLfloat temp[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat zero[] = { 0.0, 0.0, 0.0, 0.0 };
	glColor4fv(temp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, temp);


	glPushMatrix();
	glTranslatef(player.position.x, player.position.y, player.position.z);

	glBindTexture(GL_TEXTURE_2D, img_top);
	glBegin(GL_QUADS);
	glVertex3f(skyboxScale, height, skyboxScale);
	glTexCoord2f(texScale, texScale);
	glVertex3f(-skyboxScale, height, skyboxScale);
	glTexCoord2f(0, texScale);
	glVertex3f(-skyboxScale, height, -skyboxScale);
	glTexCoord2f(0, 0);
	glVertex3f(skyboxScale, height, -skyboxScale);
	glTexCoord2f(texScale, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, img_left);
	glBegin(GL_QUADS);
	glVertex3f(-skyboxScale, 0.0, -skyboxScale);
	glTexCoord2f(0, 0);
	glVertex3f(-skyboxScale, height, -skyboxScale);
	glTexCoord2f(0, texScale);
	glVertex3f(-skyboxScale, height, skyboxScale);
	glTexCoord2f(texScale, texScale);
	glVertex3f(-skyboxScale, 0.0, skyboxScale);
	glTexCoord2f(texScale, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, img_back);
	glBegin(GL_QUADS);
	glVertex3f(-skyboxScale, 0.0, skyboxScale);
	glTexCoord2f(0, 0);
	glVertex3f(-skyboxScale, height, skyboxScale);
	glTexCoord2f(0, texScale);
	glVertex3f(skyboxScale, height, skyboxScale);
	glTexCoord2f(texScale, texScale);
	glVertex3f(skyboxScale, 0.0, skyboxScale);
	glTexCoord2f(texScale, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, img_right);
	glBegin(GL_QUADS);
	glVertex3f(skyboxScale, 0.0, skyboxScale);
	glTexCoord2f(0, 0);
	glVertex3f(skyboxScale, height, skyboxScale);
	glTexCoord2f(0, texScale);
	glVertex3f(skyboxScale, height, -skyboxScale);
	glTexCoord2f(texScale, texScale);
	glVertex3f(skyboxScale, 0.0, -skyboxScale);
	glTexCoord2f(texScale, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, img_front);
	glBegin(GL_QUADS);
	glVertex3f(-skyboxScale, height, -skyboxScale);
	glTexCoord2f(0, 0);
	glVertex3f(skyboxScale, height, -skyboxScale);
	glTexCoord2f(0, texScale);
	glVertex3f(skyboxScale, 0.0, -skyboxScale);
	glTexCoord2f(texScale, texScale);
	glVertex3f(-skyboxScale, 0.0, -skyboxScale);
	glTexCoord2f(texScale, 0);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, zero);

	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void displayFunc()
{
	handleKeyHold();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.update();

	GLfloat	light_position[] = { 0.0, 1.0, 0.0 , 5.0 };
	glPushMatrix();
	glTranslatef(player.position.x + camera.lookAt.x, player.position.y + camera.lookAt.y, player.position.z + camera.lookAt.z);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();

	skybox();

	groundPlane.draw();

	glColor3f(0.0, 0.0, 1.0);
	player.render();

	glColor3f(1.0, 1.0, 1.0);
	drawObj(myObj);

//	draw satellite
//	 for(int i = -3; i < 3; i++) {
//		 for (int j = -3; j < 3; j++) {
//			 glPushMatrix();
//				 glTranslatef(i * 10.0, 0, j * 10.0);
//				 drawSnowMan();
//			 glPopMatrix();
//		 }
//	 }

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


		case 'f':	player.isFlying = !player.isFlying;
					if (!player.isFlying) player.position.y = 1.0;
					break;

		case ' ':	keyStates.SPACE = true; break;
		case 'r':	std::cout << std::toRadians(player.rotation.x) << std::endl; break;
		case 'l':	std::cout << player.position.x << " " << player.position.y << " " << player.position.z << std::endl; break;
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
		case GLUT_KEY_CTRL_L:	player.isRunning = true; break;
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
		case GLUT_KEY_CTRL_L:	player.isRunning = false; break;
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

		float anglePhi = (mouseMoveDistance[0] * 180) / ( screenWidth / 0.01 );
		float angleTheta = (mouseMoveDistance[1] * 180) / ( screenHeight / 0.01 );

		camera.set(0, {anglePhi, angleTheta, 0.0}, true);
		if(!player.isFlying) player.rotation = camera.rotation;

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
	groundPlane.addTexCoord(0, 0);
	groundPlane.addVertex({-100.0, 0.0,  100.0});
	groundPlane.addTexCoord(0, 35);
	groundPlane.addVertex({ 100.0, 0.0,  100.0});
	groundPlane.addTexCoord(35, 35);
	groundPlane.addVertex({ 100.0, 0.0, -100.0});
	groundPlane.addTexCoord(35, 0);

	groundPlane.textureID = loadImage("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\moon.psd");

	groundPlane.addFace({{0, 0, -1}, {1, 1, -1}, {2, 2, -1}, {3, 3, -1}});

	camera.set({0.0, 1.0, 5.0}, {std::toRadians(270), std::toRadians(90.0), 0.0}, false);

	img_top = loadImage("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\top.psd");
	img_left = loadImage("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\left.psd");
	img_front = loadImage("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\front.psd");
	img_right = loadImage("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\right.psd");
	img_back = loadImage("D:\\Productivity\\Code\\CG Project - Lunar Lander\\res\\back.psd");

	player.rover = loadObj("D:\\Productivity\\Code\\CG Project - Lunar Lander\\includes\\rover.obj");
}

void initLight()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat zero[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = { player.position.x, player.position.y, player.position.z , 0.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, zero);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_emission);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_specular);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


int main( int argc, char **argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(500,500);
    glutCreateWindow("Lunar Landing 3D");

//	glutFullScreen();

	glEnable(GL_DEPTH_TEST);

    glutIdleFunc(displayFunc);
    glutDisplayFunc(displayFunc);

	glutIgnoreKeyRepeat(1);

    glutKeyboardFunc(keyDownFunc);
	glutKeyboardUpFunc(keyUpFunc);

	glutSpecialFunc(specialKeyDownFunc);
	glutSpecialUpFunc(specialKeyUpFunc);

	glutMouseFunc(mouseFunc);
    glutPassiveMotionFunc(passiveMotionFunc);

    glutReshapeFunc(reshapeFunc);

    init();
	initLight();

    glutMainLoop();

    return 0;
}