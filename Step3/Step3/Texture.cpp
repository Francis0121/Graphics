#include "Texture.h"

Texture::Texture(void){
}

Texture::~Texture(void){
}

void Texture::LoadTexture(){
	textureId[0] = SOIL_load_OGL_texture("IU/IU_01.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	textureId[1] = SOIL_load_OGL_texture("IU/IU_02.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	textureId[2] = SOIL_load_OGL_texture("IU/IU_03.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	textureId[3] = SOIL_load_OGL_texture("IU/IU_04.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	textureId[4] = SOIL_load_OGL_texture("IU/IU_05.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	textureId[5] = SOIL_load_OGL_texture("IU/IU_06.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	textureId[6] = SOIL_load_OGL_texture("IU/IU_07.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	for(int i=0; i < TEXTURE_ID_SIZE; i++){
		glBindTexture(GL_TEXTURE_2D, textureId[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
}

int Texture::getTextureId(int index){
	if(index >= TEXTURE_ID_SIZE){
		std::cout << "Error Texture Size " << std::endl;
		return textureId[0];
	}
	return textureId[index];
}