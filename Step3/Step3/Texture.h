#pragma once
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <soil/SOIL.h>
#define TEXTURE_ID_SIZE 7

class Texture
{
// Variable
private:
	unsigned int textureId[TEXTURE_ID_SIZE]; // Texture 는 현재 7개
	
// Function
public:
	Texture(void);
	~Texture(void);
	
	void LoadTexture();
	int getTextureId(int index);

};
