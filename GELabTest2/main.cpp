#include <cstdio>
#include <glut.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include "OBJ_Loader.h"

bool renderCube[100] = { true };
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;
float lastx, lasty;
double rotate_y = 0;
double rotate_x = 0;
GLuint texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8;
float positionz[100];
float positionx[100];
float positiony[100];

// Function declarations
void cubepositions(void);
void LoadTextures();
void FreeTextures();
void square(float x, float y, float z, GLuint textureID1, GLuint textureID2, GLuint textureID3, GLuint textureID4);
GLuint LoadTexture(const char* filename, int width, int height);
void FreeTexture(GLuint texture);
void display(void);
void reshape(int w, int h);
void mouseMovement(int x, int y);

struct Cube {
	float x, y, z;
	float xRot, yRot;
	float color[3];
};

const int numCubes = 100;
Cube cubes[numCubes];
void drawPlayer(void)
{
	glPushMatrix();
	glTranslated(xpos, ypos, zpos);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(1.0);
	glPopMatrix();
}
void init(void) {
	cubepositions();
	LoadTextures();
	for (int i = 0; i < 100; i++) {
		renderCube[i] = true;
	}
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
void cube(void) {
	for (int i = 0; i < 100; i++)
	{
		if (!checkCollision(positionx[i], 0.0, positionz[i], 1.0) && renderCube[i])
		{
			glPushMatrix();
			glTranslated(positionx[i], 0.0, positionz[i]); // Translate the cube
			square(0.0, 0.0, 0.0, texture1, texture2, texture3, texture4);
			glPopMatrix();
		}
		else if (renderCube[i])
		{
			// Cube collided, update its position and mark it for no rendering
			positionz[i] = rand() % 100 + 5;
			positionx[i] = rand() % 100 + 5;
			renderCube[i] = false;
		}
	}
}
void cubepositions(void) {
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		positionz[i] = rand() % 100 + 5;
		positionx[i] = rand() % 100 + 5;
	}
}

void enable(void)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	//glEnable(GL_LIGHTING); //enable the lighting
	//glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	//glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}
void camera(void) {
	float cameraDistance = 3.0; // adjust this distance as needed
	float cameraHeight = 1.0;   // adjust this height as needed

	float xCam = xpos - cameraDistance * sin(yrot * (3.14159265 / 180.0));
	float zCam = zpos - cameraDistance * cos(yrot * (3.14159265 / 180.0));
	float yCam = ypos + cameraHeight;


	gluLookAt(xCam, yCam, zCam, xpos, ypos, zpos, 0.0, 1.0, 0.0);
}

void LoadTextures() {
	texture1 = LoadTexture("emoji.bmp", 256, 256);
	texture2 = LoadTexture("emoji1.bmp", 256, 256);
	texture3 = LoadTexture("emoji2.bmp", 256, 256);
	texture4 = LoadTexture("emoji3.bmp", 256, 256);
	texture5 = LoadTexture("emoji3.bmp", 256, 256);
	texture6 = LoadTexture("emoji2.bmp", 256, 256);
	texture7 = LoadTexture("emoji1.bmp", 256, 256);
	texture8 = LoadTexture("emoji.bmp", 256, 256);
}
void FreeTextures() {
	FreeTexture(texture1);
	FreeTexture(texture2);
	FreeTexture(texture3);
	FreeTexture(texture4);
	FreeTexture(texture5);
	FreeTexture(texture6);
	FreeTexture(texture7);
	FreeTexture(texture8);
}
GLuint LoadTexture(const char* filename, int width, int height)
{
	GLuint texture;
	unsigned char* data;
	FILE* file;

	if (fopen_s(&file, filename, "rb") != 0)
	{
		printf("Error opening file: %s\n", filename);
		return 0;
	}

	data = (unsigned char*)malloc(width * height * 3);

	if (data != NULL)
	{
		fread(data, width * height * 3, 1, file);
	}
	else
	{
		printf("Error allocating memory for texture data.\n");
		fclose(file);
		return 0;
	}

	fclose(file);

	glGenTextures(1, &texture);

	if (texture == 0)
	{
		printf("Error generating texture ID.\n");
		free(data);
		return 0;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Switch from GL_RGB to GL_BGR_EXT for bitmap image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	free(data);

	return texture;
}
void FreeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}

void square(float x, float y, float z, GLuint textureID1, GLuint textureID2, GLuint textureID3, GLuint textureID4) {

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glScalef(1,1,1);
	//Multi-colored side - FRONT
	glBindTexture(GL_TEXTURE_2D, textureID1);
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5); // P1 is red
	glTexCoord2d(1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);  // P2 is green
	glTexCoord2d(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); // P3 is blue
	glTexCoord2d(0.0, 1.0); glVertex3f(-0.5, -0.5, -0.5); // P4 purple
	glEnd();

	// White side - BACK
	glBindTexture(GL_TEXTURE_2D, textureID2);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBindTexture(GL_TEXTURE_2D, textureID3);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);

	glEnd();

	// Green side - LEFT
	glBindTexture(GL_TEXTURE_2D, textureID4);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBindTexture(GL_TEXTURE_2D, textureID1);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBindTexture(GL_TEXTURE_2D, textureID1);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glTexCoord3d(0.0, 0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord3d(0.0, 1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord3d(1.0, 1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord3d(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glPopMatrix();

}
void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera();
	enable();
	drawPlayer();

	cube();

	glutSwapBuffers();
	angle += 0.1;
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	}
void keyboard(unsigned char key, int x, int y) {
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

	// Initialize Loader
	objl::Loader Loader;

	// Load .obj File
	bool loadout = Loader.LoadFile("SimpleGoldCoin.obj");
	// If so continue
	if (loadout)
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Go through each loaded mesh and out its contents
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = Loader.LoadedMeshes[i];

			// Print Mesh Name
			file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

			// Print Vertices
			file << "Vertices:\n";

			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			for (int j = 0; j < curMesh.Vertices.size(); j++)
			{
				file << "V" << j << ": " <<
					"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
					"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
					"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
			}

			// Print Indices
			file << "Indices:\n";

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
			}

			// Print Material
			file << "Material: " << curMesh.MeshMaterial.name << "\n";
			file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
			file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
			file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
			file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
			file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
			file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
			file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
			file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
			file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
			file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
			file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
			file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

			// Leave a space to separate from the next mesh
			file << "\n";
		}

		// Close File
		file.close();
	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Output Error
		file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		file.close();
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set the display to Double buffer, with depth
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Window");
	
	init();
	LoadTextures();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	
	glutPassiveMotionFunc(mouseMovement);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	FreeTextures(); // Free the textures when the program ends

	return 0;


}