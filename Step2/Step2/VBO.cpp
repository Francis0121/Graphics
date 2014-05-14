#include "VBO.h"


VBO::VBO(void){
}

VBO::~VBO(void){
	for(int i=0; i<5;i++){
		delete tIndecies[i].order;
		delete dIndecies[i].order;
	}
}

void VBO::InitGeometry() { 
	
	GLfloat blueC[4] = { 80.0f/255.0f, 80.0f/255.0f, 255.0f/255.0f, 1.0f }; // blue color
	GLfloat yellowC[4] = { 255.0f/255.0f, 255.0f/255.0f, 0.0f/255.0f, 1.0f }; // Yellow color
	GLfloat redC[4] = { 255.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.0f }; // Red color
	GLfloat whiteC[4] = { 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f }; // white color
	GLfloat blackC[4] = { 0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.0f }; // black color

	Vertex topV[48] = {
		2.8f, 3.8f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3],	// 0 Top Right Blue			
		0.1f, 3.8f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 1
		0.1f, 0.1f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 2
		2.8f, 0.1f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 3

		-0.1f, 3.8f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 4 Top Left Blue
		-2.8f, 3.8f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 5
		-2.8f, 0.1f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 6
		-0.1f, 0.1f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 7

		2.8f, 0.0f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 8 Top Background Blue
		0.1f, 0.0f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 9
		-0.1f, 0.0f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 10
		-2.8f, 0.0f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 11

		2.8f, 3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3],	// 12 Top Right White			
		0.1f, 3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 13
		0.1f, 0.1f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 14
		2.8f, 0.1f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 15

		-0.1f, 3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 16 Top Left White
		-2.8f, 3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 17
		-2.8f, 0.1f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 18
		-0.1f, 0.1f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 19

		2.8f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 20 Etc Background Vertex
		0.1f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 21
		-0.1f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 22
		-2.8f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 23

		2.8f, 3.8f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3],	// 24 Top Right Yellow
		0.1f, 3.8f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 25
		0.1f, 0.1f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 26
		2.8f, 0.1f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 27

		-0.1f, 3.8f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 28 Top Left Yellow
		-2.8f, 3.8f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 29
		-2.8f, 0.1f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 30
		-0.1f, 0.1f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 31

		2.8f, 0.0f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 32 Top Background Yellow
		0.1f, 0.0f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 33
		-0.1f, 0.0f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 34
		-2.8f, 0.0f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 35

		2.8f, 3.8f, 0.0f,		redC[0], redC[1], redC[2], redC[3],	// 36 Top Right Red
		0.1f, 3.8f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 37
		0.1f, 0.1f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 38
		2.8f, 0.1f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 39

		-0.1f, 3.8f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 40 Top Left Red
		-2.8f, 3.8f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 41
		-2.8f, 0.1f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 42
		-0.1f, 0.1f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 43

		2.8f, 0.0f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 44 Top Background Red
		0.1f, 0.0f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 45
		-0.1f, 0.0f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 46
		-2.8f, 0.0f, 0.0f,		redC[0], redC[1], redC[2], redC[3] // 47
	};

	memcpy(tVertex, topV, 48*sizeof(Vertex));

	Vertex downV[48] = {
		2.8f, -0.1f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 0 Bottom Right Blue
		0.1f, -0.1f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 1
		0.1f, -3.8f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 2
		2.8f, -3.8f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 3

		-0.1f, -0.1f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 4 Bottom Left Blue
		-2.8f, -0.1f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 5
		-2.8f, -3.8f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 6
		-0.1f, -3.8f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 7

		2.8f, 0.0f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 8 Etc Background Vertex
		0.1f, 0.0f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 9
		-0.1f, 0.0f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 10
		-2.8f, 0.0f, 0.0f,		blueC[0], blueC[1], blueC[2], blueC[3], // 11

		2.8f, -0.1f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 12 Bottom Right White
		0.1f, -0.1f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 13
		0.1f, -3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 14
		2.8f, -3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 15

		-0.1f, -0.1f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 16 Bottom Left White
		-2.8f, -0.1f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 17
		-2.8f, -3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 18
		-0.1f, -3.8f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 19

		2.8f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 20 Etc Background Vertex
		0.1f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 21
		-0.1f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 22
		-2.8f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3], // 23

		2.8f, -0.1f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 24 Bottom Right Yellow
		0.1f, -0.1f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 25
		0.1f, -3.8f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 26
		2.8f, -3.8f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 27

		-0.1f, -0.1f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 28 Bottom Left Yellow
		-2.8f, -0.1f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 29
		-2.8f, -3.8f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 30
		-0.1f, -3.8f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 31

		2.8f, 0.0f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 32 Etc Background Vertex
		0.1f, 0.0f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 33
		-0.1f, 0.0f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 34
		-2.8f, 0.0f, 0.0f,		yellowC[0], yellowC[1], yellowC[2], yellowC[3], // 35

		2.8f, -0.1f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 24 Bottom Right Red
		0.1f, -0.1f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 25
		0.1f, -3.8f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 26
		2.8f, -3.8f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 27

		-0.1f, -0.1f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 28 Bottom Left Red
		-2.8f, -0.1f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 29
		-2.8f, -3.8f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 30
		-0.1f, -3.8f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 31

		2.8f, 0.0f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 32 Etc Background Vertex
		0.1f, 0.0f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 33
		-0.1f, 0.0f, 0.0f,		redC[0], redC[1], redC[2], redC[3], // 34
		-2.8f, 0.0f, 0.0f,		redC[0], redC[1], redC[2], redC[3] // 35
	};

	memcpy(dVertex, downV, 48*sizeof(Vertex));

	Vertex lineV[24] = {
		2.8f, 3.8f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 0 Top Left 
		0.1f, 3.8f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 1
		0.1f, 0.1f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 2
		2.8f, 0.1f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 3

		-0.1f, 3.8f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 4 Top Right
		-2.8f, 3.8f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 5
		-2.8f, 0.1f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 6
		-0.1f, 0.1f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 7

		2.8f, -0.1f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 8 Bottom Left
		0.1f, -0.1f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 9
		0.1f, -3.8f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 10
		2.8f, -3.8f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 11

		-0.1f, -0.1f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 12 Bottom Right
		-2.8f, -0.1f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 13
		-2.8f, -3.8f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 14
		-0.1f, -3.8f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 15

		2.8f, 0.0f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 16 Etc Background Vertex
		0.1f, 0.0f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 17
		-0.1f, 0.0f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3], // 18
		-2.8f, 0.0f, 0.0f,		blackC[0], blackC[1], blackC[2], blackC[3] // 19
	};

	memcpy(lVertex, lineV, 20*sizeof(Vertex));

	GLubyte topI[6][24] ={	 
							{
								0, 5, 6, 6, 3, 0, // Top Blue
								15, 18, 23, 23, 20, 15 // Background Horizintal
							},
							{
								24, 25, 26, 26, 27, 24, // Top Right Blue
								28, 29, 30, 30, 31, 28, // Top Left Blue
								13, 16, 19, 19, 14, 13, // Background Horizintal
								15, 18, 23, 23, 20, 15 // Background Vertical
							},
							{
								0, 1, 9, 9, 8, 0, // Top Right Full Blue
								4, 5, 11, 11, 10, 4, // Top Left Full Blue
								13, 16, 22, 22, 21, 13 // Background Horizintal
							},
							{
								24, 25, 26, 26, 27, 24, // Top Right Blue
								28, 29, 35, 35, 34, 28, // Top Left Full Blue
								13, 16, 22, 22, 21, 13, // Background Horizintal
								15, 14, 21, 21, 20, 15 // Background Vertical
							},
							{
								36, 37, 45, 45, 44, 36, // Top Right Full Blue
								40, 41, 42, 42, 43, 40, // Top Left Blue
								13, 16, 22, 22, 21, 13, // Background Horizintal
								19, 18, 23, 23, 22, 19 // Background Vertical
							},
							{
								0, 5, 5, 19, 16, 0	
							}
						};	

	tIndecies[0].order = new GLubyte[12];
	tIndecies[0].size = 12;
	memcpy(tIndecies[0].order, topI[0], 12*sizeof(GLubyte));

	tIndecies[1].order = new GLubyte[24];
	tIndecies[1].size = 24;
	memcpy(tIndecies[1].order, topI[1], 24*sizeof(GLubyte));

	tIndecies[2].order = new GLubyte[18];
	tIndecies[2].size = 18;
	memcpy(tIndecies[2].order, topI[2], 18*sizeof(GLubyte));

	tIndecies[3].order = new GLubyte[24];
	tIndecies[3].size = 24;
	memcpy(tIndecies[3].order, topI[3], 24*sizeof(GLubyte));

	tIndecies[4].order = new GLubyte[24];
	tIndecies[4].size = 24;
	memcpy(tIndecies[4].order, topI[4], 24*sizeof(GLubyte));

	tIndecies[5].order = new GLubyte[6];
	tIndecies[5].size = 6;
	memcpy(tIndecies[5].order, topI[5], 6*sizeof(GLubyte));

	GLubyte downI[6][24] ={	 
							{
								0, 5, 6, 6, 3, 0, // Bottom Blue
								20, 23, 17, 17, 12, 20 // Background Horizintal
							},
							{
								24, 25, 26, 26, 27, 24, // Bottom Right Blue
								28, 29, 30, 30, 31, 28, // Bottom Left Blue
								20, 23, 17, 17, 12, 20, // Background Horizintal
								13, 16, 19, 19, 14, 13 // Background Vertical
							},
							{
								8, 9, 2, 2, 3, 8, // Bottom Right Full Blue
								10, 11, 6, 6, 7, 10, // Bottom Left Full Blue
								21, 22, 19, 19, 14, 21 // Background Vertical
							},
							{
								24, 25, 26, 26, 27, 24, // Bottom Right Blue
								34, 35, 30, 30, 31, 34, // Bottom Left Full Blue
								21, 22, 19, 19, 14, 21, // Background Horizintal
								20, 21, 13, 13, 12, 20 // Background Vertical
							},
							{
								44, 45, 38, 38, 39, 44, // Top Right Full Blue
								40, 41, 42, 42, 43, 40, // Top Left Blue
								21, 22, 19, 19, 14, 21, // Background Horizintal
								22, 23, 17, 17, 16, 22 // Background Vertical
							},
							{
								16, 11, 11, 14, 14, 19	
							}
						};	

	dIndecies[0].order = new GLubyte[12];
	dIndecies[0].size = 12;
	memcpy(dIndecies[0].order, downI[0], 12*sizeof(GLubyte));

	dIndecies[1].order = new GLubyte[24];
	dIndecies[1].size = 24;
	memcpy(dIndecies[1].order, downI[1], 24*sizeof(GLubyte));

	dIndecies[2].order = new GLubyte[18];
	dIndecies[2].size = 18;
	memcpy(dIndecies[2].order, downI[2], 18*sizeof(GLubyte));

	dIndecies[3].order = new GLubyte[24];
	dIndecies[3].size = 24;
	memcpy(dIndecies[3].order, downI[3], 24*sizeof(GLubyte));

	dIndecies[4].order = new GLubyte[24];
	dIndecies[4].size = 24;
	memcpy(dIndecies[4].order, downI[4], 24*sizeof(GLubyte));

	dIndecies[5].order = new GLubyte[6];
	dIndecies[5].size = 6;
	memcpy(dIndecies[5].order, downI[5], 6*sizeof(GLubyte));
}


void VBO::InitVBO() {
	// ~ New Initiate Vertex & Color
	glGenBuffers(3, vacVBO); 
	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*48, tVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[1]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*48, dVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[2]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*20, lVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ~ New Initiatte Index
	glGenBuffers(6, tiVBO); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[0]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*tIndecies[0].size, tIndecies[0].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[5]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*tIndecies[5].size, tIndecies[5].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(6, diVBO); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[0]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecies[0].size, dIndecies[0].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[5]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecies[5].size, dIndecies[5].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}