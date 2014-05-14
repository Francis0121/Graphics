#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>

typedef struct {
	GLubyte *order;
	int size;
} Index;

typedef struct { 
	float location[3]; 
	float color[4]; 
} Vertex; 

class VBO
{
// ~ Variable
public:
	// Vertex & Color
	Vertex tVertex[48]; // Top Vertex
	Vertex dVertex[48]; // Down Vertex
	Vertex lVertex[20]; // Line Vertex
	Index tIndecies[6]; // Top Indeices
	Index dIndecies[6]; // Down Indeices

	// GL Buffer
	GLuint vacVBO[3]; // Vertex And Color Vertex Buffer Object
	GLuint tiVBO[6]; // top index Vertex Buffer Object
	GLuint diVBO[6]; // down index Vertex Buffer Object
// ~ Function
public:
	VBO(void);
	~VBO(void);
	void InitGeometry();
	void InitVBO();
};

