#include <math.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glut.h>
#include <cstdio>
#include <string>

GLuint texture; //the array for our texture
GLuint texture1;
const int MAP_SIZE = 30;
int gameMap[MAP_SIZE][MAP_SIZE] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
float xpos = 15.0 * 5.0, ypos = 0, zpos = 10.0, xrot = 0, yrot = 0, angle = 0.0;
float lastx, lasty;
float positionz[100];
float positionx[100];
float positiony[100];
int score = 0;
// Global Variables
double rotate_y = 0;
double rotate_x = 0;
//function to load the RAW file
GLuint LoadTexture(const char* filename, int width, int	height)
{
	GLuint texture;
	unsigned char* data;
	FILE* file;
	//The following code will read in our RAW file
	if (fopen_s(&file, filename, "rb") != 0) return 0;

	data = (unsigned char*)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);
	glGenTextures(1, &texture); //generate the texture with the loaded data
	glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it’s array
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //set texture environment parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Generate the texture
	//Please be informed to switch from GL_RGB to GL_BGR_EXT for bitmap image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	free(data); //free the texture
	return texture; //return whether it was successfull
}
void FreeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}
void cubepositions(void)
{
    srand(time(NULL));
    int cubeCount = 0;
    while (cubeCount < 100)
    {
        int i = rand() % MAP_SIZE;
        int j = rand() % MAP_SIZE;
        if (gameMap[i][j] == 1)
        {
            positionz[cubeCount] = j * 5.0 + 0.5; // Adjust for cube size
            positionx[cubeCount] = i * 5.0 + 0.5; // Adjust for cube size
            cubeCount++;
        }
    }
}
void ground(void)
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2d(0.0, 0.0); glVertex3f(-0.5, 0.0, -0.5);
	glTexCoord2d(1.0, 0.0); glVertex3f(0.5, 0.0, -0.5);
	glTexCoord2d(1.0, 1.0); glVertex3f(0.5, 0.0, 0.5);
	glTexCoord2d(0.0, 1.0); glVertex3f(-0.5, 0.0, 0.5);
	glEnd();
}
void square(void)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, -0.5, -0.5); // P1 is red
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, -0.5); // P2 is green
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5); // P3 is blue
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5); // P4 purple
	glEnd();
	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glEnd();
	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture1);
	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glEnd();
	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}
bool checkCollision(float cubeX, float cubeY, float cubeZ, float cubeSize)
{
	// Assuming player size is 1x1x1
	if (xpos + 0.5 > cubeX - cubeSize / 2 && xpos - 0.5 < cubeX + cubeSize / 2 &&
		ypos + 0.5 > cubeY - cubeSize / 2 && ypos - 0.5 < cubeY + cubeSize / 2 &&
		zpos + 0.5 > cubeZ - cubeSize / 2 && zpos - 0.5 < cubeZ + cubeSize / 2)
	{
		return true; // Collision detected
	}
	return false; // No collision
}
void cube(void)
{
	for (int i = 0; i < 100; i++)
	{
		if (!checkCollision(positionx[i], 0.0, positionz[i], 1.0))
		{
			glPushMatrix();
			glTranslated(positionx[i], 0.0, positionz[i]); //translate the cube
			square(); //draw the cube
			glPopMatrix();
		}
		else
		{
			// Cube collided, update its position
			score++;
			std::cout << "Score: " << score << std::endl;
			int k, l;
			do {
				k = rand() % MAP_SIZE;
				l = rand() % MAP_SIZE;
			} while (gameMap[k][l] != 1);

				positionz[i] = l * 5.0 + 0.5; // Adjust for cube size
				positionx[i] = k * 5.0 + 0.5; // Adjust for cube size
		}
	}
}
void drawPlayer(void) 
{
	glPushMatrix();
	glTranslated(xpos, ypos, zpos); 
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);  
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawMap(void)
{
	float groundSize = 5.0;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			glPushMatrix();
			float xTranslation = i * groundSize;
			float zTranslation = j * groundSize;
			glTranslated(xTranslation, -1.0, zTranslation);
			glScaled(groundSize, 1.0f, groundSize);
			if (gameMap[i][j] == 0)
			{
				glBindTexture(GL_TEXTURE_2D, texture);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, texture1);  // Path texture
			}

			ground();  // Draw the terrain

			glPopMatrix();
		}
	}
}
void renderScore(void)
{
	glPushMatrix();
	glColor3f(1.0, 2.0, 2.0);
	glRasterPos3f(xpos, 1.25, zpos); // Adjust position as needed
	std::string scoreText = "Score: " + std::to_string(score);
	for (char c : scoreText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
	glPopMatrix();
}
void init(void)
{
	cubepositions();
}
void enable(void)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	//glEnable(GL_LIGHTING); //enable the lighting
	//glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	//glShadeModel(GL_SMOOTH); //set the shader to smooth shader
	glEnable(GL_BLEND);
}
void camera(void)
{
	//glRotatef(xrot, 1.0, 0.0, 0.0); // rotate our camera on the x-axis (left and right)
	//glRotatef(yrot, 0.0, 1.0, 0.0); // rotate our camera on the y-axis (up and down)
	//glTranslated(-xpos, -ypos, -zpos);
	// Calculate the position of the camera in a third-person view
	float cameraDistance = 3.0; // adjust this distance as needed
	float cameraHeight = 1.0;   // adjust this height as needed

	float xCam = xpos - cameraDistance * sin(yrot * (3.14159265 / 180.0));
	float zCam = zpos - cameraDistance * cos(yrot * (3.14159265 / 180.0));
	float yCam = ypos + cameraHeight;


	gluLookAt(xCam, yCam, zCam, xpos, ypos, zpos, 0.0, 1.0, 0.0); 
}
void specialKeys(int key, int x, int y) 
{
	// Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
	{
		rotate_y += 5;
		angle = angle + 1;
	}
	// Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
	{
		rotate_y -= 5;
		angle = angle - 1;
	}
	else if (key == GLUT_KEY_UP)
	{
		rotate_x += 5;
		angle = angle + 1;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		rotate_x -= 5;
		angle = angle - 1;
	}
	// Request display update
	glutPostRedisplay();
}
void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera();
	enable();
	drawMap();
	drawPlayer();

	cube();

	renderScore();

	glutSwapBuffers();
	angle += 0.1;
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
void keyboard(unsigned char key, int x, int y) 
{
	float moveSpeed = 0.2; 
	float xrotrad; 
	float yrotrad;
	if (key == 'w')
	{
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad)) * moveSpeed;
		zpos += float(cos(yrotrad)) * moveSpeed;
		//ypos -= float(sin(xrotrad)) * moveSpeed;
	}
	if (key == 's')
	{
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad)) * moveSpeed;
		zpos -= float(cos(yrotrad)) * moveSpeed;
		//ypos += float(sin(xrotrad)) * moveSpeed;
	}
	if (key == 'd')
	{
		yrotrad = ((yrot + 90) / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad)) * moveSpeed;
		zpos -= float(cos(yrotrad)) * moveSpeed;
	}
	if (key == 'a')
	{
		yrotrad = ((yrot - 90) / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad)) * moveSpeed;
		zpos -= float(cos(yrotrad)) * moveSpeed;
	}
	if (key == 27)
	{
		exit(0);
	}
	glutPostRedisplay();
}
void mouseMovement(int x, int y)
{
	int diffx = x - lastx;//check the difference between the current x and the last x position
	int diffy = y - lasty; //check the difference between the current y and the last y position
	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	xrot += (float)diffy; //set the x rot to x rot with the addition of the difference in the y position
	yrot += (float)diffx; //set the x rot to y rot with the addition of the difference in the x position
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A basic OpenGL Window");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	//Load our texture
	texture = LoadTexture("New folder/paimon.bmp", 256, 256);
	texture1 = LoadTexture("New folder/delux.bmp", 256, 256);
	//glutSpecialFunc(specialKeys);
	glutPassiveMotionFunc(mouseMovement);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	//Free our texture
	FreeTexture(texture);
	FreeTexture(texture1);
}
