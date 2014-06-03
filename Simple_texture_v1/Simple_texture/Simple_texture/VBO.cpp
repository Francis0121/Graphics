#include "VBO.h"


VBO::VBO(void){
	xMin = 0.2f;
	xMax = 0.8f;
	yMin = 0.3f;
	yMax = 0.9f;
}

VBO::~VBO(void){
	for(int i=0; i<5;i++){
		delete tIndecies[i].order;
		delete dIndecies[i].order;
	}
}

void VBO::InitGeometry() { 
	
	GLfloat whiteC[4] = { 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f }; // white color
	
	Vertex topV[20] = {
		2.9f, 4.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 0
		0.1f, 4.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 1
		0.1f, 2.2f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 2
		2.9f, 2.2f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 3
		
		2.9f, 2.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 4
		0.1f, 2.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 5
		0.1f, 0.2f,	0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 6
		2.9f, 0.2f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 7

		-0.1f, 4.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 8
		-2.9f, 4.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 9
		-2.9f, 2.2f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 10
		-0.1f, 2.2f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 11
		
		-0.1f, 2.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 12
		-2.9f, 2.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 13
		-2.9f, 0.2f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 14
		-0.1f, 0.2f,	 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 15

		2.9f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 16
		0.1f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 17
		-0.1f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 18
		-2.9f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3]	// 19
 	}; 

	memcpy(tVertex, topV, 20*sizeof(Vertex));

	Vertex downV[20] = {
		2.9f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 0
		0.1f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 1
		0.1f, -1.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 2
		2.9f, -1.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 3
		
		2.9f, -2.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 4
		0.1f, -2.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 5
		0.1f, -3.8f,	0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 6
		2.9f, -3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 7

		-0.1f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 8
		-2.9f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 9
		-2.9f, -1.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 10
		-0.1f, -1.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 11
		
		-0.1f, -2.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 12
		-2.9f, -2.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 13
		-2.9f, -3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 14
		-0.1f, -3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 15

		2.9f, -4.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 16
		0.1f, -4.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 17
		-0.1f, -4.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 18
		-2.9f, -4.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3]	// 19
	};

	memcpy(dVertex, downV, 20*sizeof(Vertex));

	GLubyte topI[5][48] ={	 
								{
									0, 9, 14, 14, 7, 0,  // Image
									7, 14, 19, 19, 16, 7 // Border
								},
								{
									0, 1, 6, 6, 7, 0, // Image
									8, 9, 14, 14, 15, 8, // Image
									1, 8, 15, 15, 6, 1, // Border
									7, 14, 19, 19, 16, 7 // Border
								},
								{
									0, 9, 10, 10, 3, 0, // Image
									4, 13, 14, 14, 7, 4, // Image
									3, 10, 13, 13, 4, 3, // Border
									7, 14, 19, 19, 16, 7 // Border
								},
								{
									0, 9, 10, 10, 3, 0, // Image
									12, 13, 14, 14, 15, 12, // Image
									4, 5, 6, 6, 7, 4, // Image
									3, 10, 13, 13, 4, 3, // Border
									7, 14, 19, 19, 16, 7, // Border
									5, 12, 15, 15, 6, 5 // Border
								},
								{
									0, 1, 2, 2, 3, 0, // Image
									4, 5, 6, 6, 7, 4, // Image
									8, 9, 10, 10, 11, 8, // Image
									12, 13, 14, 14, 15, 12, // Image
									3, 10, 13, 13, 4, 3, // Border
									7, 14, 19, 19, 16, 7, // Border
									5, 12, 15, 15, 6, 5, // Border
									1, 8, 11, 11, 2, 1 // Border
								}
						};	

	tIndecies[0].order = new GLubyte[12];
	tIndecies[0].size = 12;
	memcpy(tIndecies[0].order, topI[0], 12*sizeof(GLubyte));

	tIndecies[1].order = new GLubyte[24];
	tIndecies[1].size = 24;
	memcpy(tIndecies[1].order, topI[1], 24*sizeof(GLubyte));

	tIndecies[2].order = new GLubyte[24];
	tIndecies[2].size = 24;
	memcpy(tIndecies[2].order, topI[2], 24*sizeof(GLubyte));

	tIndecies[3].order = new GLubyte[36];
	tIndecies[3].size = 36;
	memcpy(tIndecies[3].order, topI[3], 36*sizeof(GLubyte));

	tIndecies[4].order = new GLubyte[48];
	tIndecies[4].size = 48;
	memcpy(tIndecies[4].order, topI[4], 48*sizeof(GLubyte));

	GLubyte downI[5][48] ={	 
								{
									0, 9, 14, 14, 7, 0,
									7, 14, 19, 19, 16, 7
								},
								{
									0, 1, 6, 6, 7, 0,
									8, 9, 14, 14, 15, 8,
									1, 8, 15, 15, 6, 1,
									7, 14, 19, 19, 16, 7
								},
								{
									0, 9, 10, 10, 3, 0,
									4, 13, 14, 14, 7, 4,
									3, 10, 13, 13, 4, 3,
									7, 14, 19, 19, 16, 7
								},
								{
									0, 9, 10, 10, 3, 0,
									12, 13, 14, 14, 15, 12,
									4, 5, 6, 6, 7, 4,
									3, 10, 13, 13, 4, 3,
									7, 14, 19, 19, 16, 7,
									5, 12, 15, 15, 6, 5
								},
								{
									0, 1, 2, 2, 3, 0,
									4, 5, 6, 6, 7, 4,
									8, 9, 10, 10, 11, 8,
									12, 13, 14, 14, 15, 12,
									3, 10, 13, 13, 4, 3,
									7, 14, 19, 19, 16, 7,
									5, 12, 15, 15, 6, 5,
									1, 8, 11, 11, 2, 1
								}
						};	

	dIndecies[0].order = new GLubyte[12];
	dIndecies[0].size = 12;
	memcpy(dIndecies[0].order, downI[0], 12*sizeof(GLubyte));

	dIndecies[1].order = new GLubyte[24];
	dIndecies[1].size = 24;
	memcpy(dIndecies[1].order, downI[1], 24*sizeof(GLubyte));

	dIndecies[2].order = new GLubyte[24];
	dIndecies[2].size = 24;
	memcpy(dIndecies[2].order, downI[2], 24*sizeof(GLubyte));

	dIndecies[3].order = new GLubyte[36];
	dIndecies[3].size = 36;
	memcpy(dIndecies[3].order, downI[3], 36*sizeof(GLubyte));

	dIndecies[4].order = new GLubyte[48];
	dIndecies[4].size = 48;
	memcpy(dIndecies[4].order, downI[4], 48*sizeof(GLubyte));
}


void VBO::InitVBO() {
	// ~ New Initiate Vertex & Color
	glGenBuffers(2, vacVBO); 
	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*20, tVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[1]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*20, dVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ~ New Initiatte Index
	glGenBuffers(5, tiVBO); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[0]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*tIndecies[0].size, tIndecies[0].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[1]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*tIndecies[1].size, tIndecies[1].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[2]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*tIndecies[2].size, tIndecies[2].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[3]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*tIndecies[3].size, tIndecies[3].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[4]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*tIndecies[4].size, tIndecies[4].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(5, diVBO); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[0]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecies[0].size, dIndecies[0].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[1]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecies[1].size, dIndecies[1].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[2]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecies[2].size, dIndecies[2].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[3]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecies[3].size, dIndecies[3].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[4]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecies[4].size, dIndecies[4].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VBO::InitTexture(){
	//std::cout << " X " << xMin << " " << xMax << std::endl;
	//std::cout << " Y " << yMin << " " << yMax << std::endl;

	GLfloat texOrder[5][32] ={	 
									{
											xMin, yMax,		0, 0,		0, 0,		0, 0,
											0, 0,		0, 0,		0, 0,		xMin, yMin,
											0, 0,		xMax, yMax,	0, 0,		0, 0,
											0, 0,		0, 0,		xMax, yMin,	0, 0
									 },
									 {
											xMin, yMax,  xMax, yMax,  0, 0,  0, 0,
											0, 0,  0, 0,  xMax, yMin,  xMin, yMin,
											yMin, xMax,  yMax, xMax,  0, 0,  0, 0,
											0, 0,  0, 0,  yMax, xMin,  yMin, xMin
									 },
									 {
											xMin, yMax,  0, 0,  0, 0,  xMin, yMin,
											yMin, xMax,  0, 0,  0, 0,  yMin, xMin,
											0, 0,  xMax, yMax,  xMax, yMin,  0, 0,
											0, 0,  yMax, xMax,  yMax, xMin,  0, 0
									 },
									 {
											xMin, yMax,  0, 0,  0, 0,  xMin, yMin,
											 xMin, yMax,  xMax, yMax,  xMax, yMin,  xMin, yMin,
											 0, 0,  xMax, yMax, xMax, yMin,  0, 0,
											 xMin, yMax,  xMax, yMax,  xMax, yMin, xMin, yMin
									 },
									 {
											xMin, yMax,  xMax, yMax,  xMax, yMin,  xMin, yMin,
											xMin, yMax,  xMax, yMax,  xMax, yMin,  xMin, yMin,
											yMin, xMax,  yMax, xMax,  yMax, xMin,  yMin, xMin,
											yMin, xMax,  yMax, xMax,  yMax, xMin,  yMin, xMin
									 }
						};	

	texture[0].order = new GLfloat[32];
	texture[0].size = 32;
	memcpy(texture[0].order, texOrder[0], 32*sizeof(GLfloat));

	texture[1].order = new GLfloat[32];
	texture[1].size = 32;
	memcpy(texture[1].order, texOrder[1], 32*sizeof(GLfloat));

	texture[2].order = new GLfloat[32];
	texture[2].size = 32;
	memcpy(texture[2].order, texOrder[2], 32*sizeof(GLfloat));

	texture[3].order = new GLfloat[32];
	texture[3].size = 32;
	memcpy(texture[3].order, texOrder[3], 32*sizeof(GLfloat));

	texture[4].order = new GLfloat[32];
	texture[4].size = 32;
	memcpy(texture[4].order, texOrder[4], 32*sizeof(GLfloat));

	// ~ Texture
	glGenBuffers(5, texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texture[0].size, texture[0].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, texVBO[1]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texture[1].size, texture[1].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, texVBO[2]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texture[2].size, texture[2].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, texVBO[3]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texture[3].size, texture[3].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, texVBO[4]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texture[4].size, texture[4].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}