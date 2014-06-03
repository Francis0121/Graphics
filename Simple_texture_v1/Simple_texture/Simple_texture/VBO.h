#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>

typedef struct {
	GLubyte *order;
	int size;
} Index;

typedef struct {
	GLfloat *order;
	int size;
} Texture;

typedef struct { 
	float location[3]; 
	float color[4]; 
} Vertex; 

class VBO
{
// ~ Variable
public:
	// Vertex & Color
	Vertex tVertex[20]; // Top Vertex
	Vertex dVertex[20]; // Down Vertex
	Index tIndecies[5]; // Top Indeices
	Index dIndecies[5]; // Down Indeices
	Texture texture[5]; // Texture

	// GL Buffer
	GLuint vacVBO[2]; // Vertex And Color Vertex Buffer Object
	GLuint tiVBO[5]; // top index Vertex Buffer Object
	GLuint diVBO[5]; // down index Vertex Buffer Object
	GLuint texVBO[5]; // Texture index Vertex Buffer Object

	GLfloat xMax;
	GLfloat xMin;
	GLfloat yMax;
	GLfloat yMin;
// ~ Function
public:
	VBO(void);
	~VBO(void);
	void InitGeometry();
	void InitVBO();
	void InitTexture();
};

