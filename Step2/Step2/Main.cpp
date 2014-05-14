#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>

#define TRUE 1
#define FALSE 0

using namespace std;

void InitGeometry();
void InitVBO();
void DrawTopVBO();
void DrawDownVBO();
void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mousewheel(int wheel, int direction, int x, int y);
void dragAndDrop(int x, int y);


typedef struct {
	GLubyte *order;
	int size;
} Index;

typedef struct { 
	float location[3]; 
	float color[4]; 
} Vertex; 

Vertex triangleVertex[40];
Vertex lineVertex[16]; 
Index indeices[5];
GLuint vboHandle[2];
GLuint indexVBO[5];

// ~ New Vertex
// Vertex & Color
Vertex tVertex[24]; // Top Vertex
Vertex dVertex[24]; // Down Vertex
Vertex lVertex[20]; // Line Vertex
Index tIndecies[6]; // Top Indeices
Index dIndecise[6]; // Down Indeices
// GL Buffer
GLuint vacVBO[3]; // Vertex And Color Vertex Buffer Object
GLuint tiVBO[6]; // top index Vertex Buffer Object
GLuint diVBO[6]; // down index Vertex Buffer Object

int frame_loop = 0;
GLdouble aspect = 3.0f/4.0f;
GLfloat eyex = 0.0f;
GLfloat eyez = 4.0f;

float scale = 1.0f;
int mouse_flag = FALSE;
int intrinsic_flag = TRUE;
int width = 300, height = 400;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Frame");
	
	if( glewInit() != GLEW_OK ) {
		std::cout << "GLEW faild to init. :-(" << std::endl;
	}
	
	InitGeometry();
	InitVBO();

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mousewheel);
	glutMotionFunc(dragAndDrop);
	glutDisplayFunc(display);
	glutMainLoop();

	for(int i=0; i<5;i++)
		delete indeices[i].order;
	return 0;
}

void InitGeometry() { 
	
	GLfloat blueC[4] = { 80.0f/255.0f, 80.0f/255.0f, 255.0f/255.0f, 1.0f }; // blueC_color
	GLfloat whiteC[4] = { 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f }; // white color
	GLfloat blackC[4] = { 0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.0f }; // black color

	Vertex topV[24] = {
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
		-2.8f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3] // 23
	};

	memcpy(tVertex, topV, 24*sizeof(Vertex));

	Vertex downV[24] = {
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
		-2.8f, 0.0f, 0.0f,		whiteC[0], whiteC[1], whiteC[2], whiteC[3] // 23
	};

	memcpy(dVertex, downV, 24*sizeof(Vertex));

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
								0, 1, 2, 2, 3, 0, // Top Right Blue
								4, 5, 6, 6, 7, 4, // Top Left Blue
								13, 16, 19, 19, 14, 13, // Background Horizintal
								15, 18, 23, 23, 20, 15 // Background Vertical
							},
							{
								0, 1, 9, 9, 8, 0, // Top Right Full Blue
								4, 5, 11, 11, 10, 4, // Top Left Full Blue
								13, 16, 22, 22, 21, 13 // Background Horizintal
							},
							{
								0, 1, 2, 2, 3, 0, // Top Right Blue
								4, 5, 11, 11, 10, 4, // Top Left Full Blue
								13, 16, 22, 22, 21, 13, // Background Horizintal
								15, 14, 21, 21, 20, 15 // Background Vertical
							},
							{
								0, 1, 9, 9, 8, 0, // Top Right Full Blue
								4, 5, 6, 6, 7, 4, // Top Left Blue
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
								0, 1, 2, 2, 3, 0, // Bottom Right Blue
								4, 5, 6, 6, 7, 4, // Bottom Left Blue
								20, 23, 17, 17, 12, 20, // Background Horizintal
								13, 16, 19, 19, 14, 13 // Background Vertical
							},
							{
								8, 9, 2, 2, 3, 8, // Bottom Right Full Blue
								10, 11, 6, 6, 7, 10, // Bottom Left Full Blue
								21, 22, 19, 19, 14, 21 // Background Vertical
							},
							{
								0, 1, 2, 2, 3, 0, // Bottom Right Blue
								10, 11, 6, 6, 7, 10, // Bottom Left Full Blue
								21, 22, 19, 19, 14, 21, // Background Horizintal
								20, 21, 13, 13, 12, 20 // Background Vertical
							},
							{
								8, 9, 2, 2, 3, 8, // Top Right Full Blue
								4, 5, 6, 6, 7, 4, // Top Left Blue
								21, 22, 19, 19, 14, 21, // Background Horizintal
								22, 23, 17, 17, 16, 22 // Background Vertical
							},
							{
								16, 11, 11, 14, 14, 19	
							}
						};	

	dIndecise[0].order = new GLubyte[12];
	dIndecise[0].size = 12;
	memcpy(dIndecise[0].order, downI[0], 12*sizeof(GLubyte));

	dIndecise[1].order = new GLubyte[24];
	dIndecise[1].size = 24;
	memcpy(dIndecise[1].order, downI[1], 24*sizeof(GLubyte));

	dIndecise[2].order = new GLubyte[18];
	dIndecise[2].size = 18;
	memcpy(dIndecise[2].order, downI[2], 18*sizeof(GLubyte));

	dIndecise[3].order = new GLubyte[24];
	dIndecise[3].size = 24;
	memcpy(dIndecise[3].order, downI[3], 24*sizeof(GLubyte));

	dIndecise[4].order = new GLubyte[24];
	dIndecise[4].size = 24;
	memcpy(dIndecise[4].order, downI[4], 24*sizeof(GLubyte));

	dIndecise[5].order = new GLubyte[6];
	dIndecise[5].size = 6;
	memcpy(dIndecise[5].order, downI[5], 6*sizeof(GLubyte));
}

void InitVBO() {
	// ~ New Initiate Vertex & Color
	glGenBuffers(3, vacVBO); 
	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*24, tVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[1]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*24, dVertex, GL_STATIC_DRAW);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecise[0].size, dIndecise[0].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[1]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecise[1].size, dIndecise[1].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[2]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecise[2].size, dIndecise[2].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[3]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecise[3].size, dIndecise[3].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[4]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecise[4].size, dIndecise[4].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[5]); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*dIndecise[5].size, dIndecise[5].order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawTopVBO(){
	// ~ Draw Top
	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[0]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[frame_loop]); 
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 
	
	glDrawElements(GL_TRIANGLES, tIndecies[frame_loop].size, GL_UNSIGNED_BYTE, (char*) NULL+0); 
	
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	// ~ Draw Top Line
	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[2]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tiVBO[5]); 
		
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_COLOR_ARRAY);
		
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 

	glDrawElements(GL_LINES, tIndecies[5].size, GL_UNSIGNED_BYTE, (char*) NULL+0);
	glLineWidth(2.0f);

	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);
}

void DrawDownVBO(){

	// ~ Draw Bottom

	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[1]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[frame_loop]); 
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 
	
	glDrawElements(GL_TRIANGLES, dIndecise[frame_loop].size, GL_UNSIGNED_BYTE, (char*) NULL+0); 
	
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	// ~ Draw Bottom Line

	glBindBuffer(GL_ARRAY_BUFFER, vacVBO[2]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diVBO[5]); 
		
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_COLOR_ARRAY);
		
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 

	glDrawElements(GL_LINES, dIndecise[5].size, GL_UNSIGNED_BYTE, (char*) NULL+0);
	glLineWidth(2.0f);

	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);
}

void display() { 

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);

	// ~ Intrinsic
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	if(intrinsic_flag){
		glOrtho(-3, 3, -4, 4, 0.1, 100.0); 
	}else{
		gluPerspective(90.0, aspect, 0.1, 100.0);
	}

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(	eyex, 0.0f, eyez,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);
	
	for(int i=0; i<5; i++){
		glPushMatrix();
		glTranslatef(0, 0, (GLfloat)-i*5);
		if(mouse_flag && i == 0){
			glScalef(1, scale, 1);
		}
		DrawTopVBO();
		DrawDownVBO();
		glPopMatrix();

		frame_loop+=1;
		if(frame_loop == 5)
			frame_loop = 0;
	}
	
	glFlush(); 
}

void reshape(int w, int h){
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	glutPostRedisplay(); 
}

void mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		mouse_flag = TRUE;
	}else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		frame_loop+=1;
		if(frame_loop == 5){
			frame_loop = 0;
		}
		mouse_flag = FALSE;
		scale = 1.0f;
		glutPostRedisplay();
	}
}

void mousewheel(int wheel, int direction, int x, int y){
	
	if(direction < 0){
		eyex = eyex == 0 ? 0 : eyex-1;
		eyez = eyez == 4 ? 4 : eyez-1;
	}else if(direction > 0){
		eyex = eyex == 10 ? 10 : eyex+1;
		eyez = eyex > 4 && eyez == 10 ? 10 : eyez+1;
	}

	intrinsic_flag = FALSE;
	if(eyex == 0 && eyez == 4){
		intrinsic_flag = TRUE;
	}

	glutPostRedisplay();
}

void dragAndDrop(int x, int y){
	if(intrinsic_flag){
		if(mouse_flag){
			scale *= 0.9f;
			glutPostRedisplay();
		}
	}
}