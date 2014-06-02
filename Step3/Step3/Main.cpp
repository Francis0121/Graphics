#include <iostream>
#include "VBO.h"
#include <soil/SOIL.h>
//#include "Texture.h"

#define TRUE 1
#define FALSE 0

#define STOP 0
#define DOWN 1
#define UP 2

using namespace std;

VBO *vbo = new VBO; // Vertex Buffer Object 생성
//Texture *texture = new Texture;
int width = 300, height = 400; // 화면 크기 지정 shape 이용

// ~ Function
void DrawTopVBO();
void DrawDownVBO();
void display();
void effect(int values);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseWheel(int wheel, int direction, int x, int y);
void mouseMotion(int x, int y);
// ~ Test
void getPosition(int x, int y);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Assignment2");
	
	if( glewInit() != GLEW_OK ) {
		std::cout << "GLEW faild to init. :-(" << std::endl;
	}
	
	vbo->InitGeometry();
	vbo->InitVBO();

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mouseWheel);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(display);
	glutMainLoop();
	
	delete vbo;
	return 0;
}

unsigned int tex_id;

void init(){
	//texture->LoadTexture();
	tex_id = SOIL_load_OGL_texture("img_cheryl.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	glBindTexture(GL_TEXTURE_2D, tex_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

// 확대 축소 Variable
GLdouble orthoWidth = 3.0;
GLdouble orthoHeight = 4.0;

// 책장넘김 효과 관련 Variable
int isTop = STOP;
int isDown = STOP;
GLfloat topAngle;
GLfloat downAngle;

// Frame 선택 Variable
int frame_loop = 0;
int topLoop = 0;
int downLoop = 0;

// 화면 이동 Variable
GLdouble lookX = 0.0f;
GLdouble lookY = 0.0f;

// 확대가 되었으면 frame 넘김효과 제한
int mouseFlag = FALSE;
int scaleFlag = FALSE;

// 이동시 전 Pos 후 Pos
GLdouble bPosX, bPosY;
GLdouble posX, posY, posZ;

GLfloat motionRate = 0.03f;

void display() { 

	glEnable(GL_DEPTH_TEST);
	// GL_Texture 이용하기 위한 추가부분
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);

	// ~ Intrinsic
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, 0.1, 100.0); 

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(	lookX, lookY, 4.0f,
				lookX, lookY, 0.0f,
				0.0f, 1.0f, 0.0f);
	
	topLoop = frame_loop;
	downLoop = frame_loop;

	for(int i=0; i<5; i++){

		// ~ Top
		glPushMatrix();
		glTranslatef(0, 0, (GLfloat)-i*5);
		if(isTop && i == 0){
			glRotatef(topAngle, 1.0f, 0.0f, 0.0f);
		}
		DrawTopVBO();
		glPopMatrix();
		if(++topLoop == 5)
			topLoop = 0;

		// ~ Down
		glPushMatrix();
		glTranslatef(0, 0, (GLfloat)-i*5);
		if(isDown && i == 0){
			glRotatef(downAngle, 1.0f, 0.0f, 0.0f);
		}
		DrawDownVBO();
		glPopMatrix();
		if(--downLoop  == -1)
			downLoop = 4;
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
		mouseFlag = TRUE;
	}else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		if(!scaleFlag){ // 확대가 되지 않은 상태에서만 책장 넘김 효과가 발생한다.
			if( height/2 > y){ // 상단을 클릭 했을 때
				isTop = DOWN;
				topAngle = 0.0f;
			}else{ // 하단을 클릭했을 때
				isDown = DOWN;
				downAngle = 0.0f;
			}
			glutTimerFunc(15, effect, 0);
		}
		mouseFlag = FALSE;
	}
}

void mouseWheel(int wheel, int direction, int x, int y){
	scaleFlag = TRUE;
	if(direction < 0){		
		orthoHeight*=1.1;
		orthoWidth*=1.1;
		if(motionRate < 0.03f){
			motionRate += 0.005f;
		}
	}else if(direction > 0){
		if(orthoHeight > 0.5){
			orthoHeight*=0.9;
			orthoWidth*=0.9;
		}
		if(motionRate > 0.005f){
			motionRate -= 0.005f;
		}
	}
	
	if( orthoHeight > 4 ){
		scaleFlag = FALSE;
		orthoHeight = 4;
		orthoWidth = 3;
		lookX = 0.0f;
		lookY = 0.0f;
	}
	
	glutPostRedisplay();
}



void mouseMotion(int x, int y){
	if(scaleFlag && mouseFlag){
		getPosition(x,y);

		if(bPosX < posX){ // 감소하고 있는중
			lookX-=motionRate;
		}else{
			lookX+=motionRate;
		}

		if(bPosY < posY){
			lookY-=motionRate;
		}else{
			lookY+=motionRate;
		}

		bPosX = posX;
		bPosY = posY;

		glutPostRedisplay();
	}
}

void getPosition(int x, int y){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
}

void effect(int values){
	if(isTop == DOWN){
		if(topAngle < 45){
			topAngle += 5.0f;
		}else if(topAngle < 90){
			topAngle += 8.0f;
		}else{
			downAngle = 90;
			isDown = UP;
			isTop = STOP;
			if(++frame_loop == 5)
				frame_loop = 0;
		}
		glutPostRedisplay();
		glutTimerFunc(20, effect, 0);
	}else if(isTop == UP){
		if(topAngle > 45 ){
			topAngle -= 8.0f;
			glutPostRedisplay();
			glutTimerFunc(20, effect, 0);
		}else if(topAngle > 0){
			topAngle -= 5.0f;
			glutPostRedisplay();
			glutTimerFunc(20, effect, 0);
		}else{
			isTop = STOP;
			glutPostRedisplay();
		}
	}else if(isDown == DOWN){
		if(downAngle < 90){
			downAngle += 5.0f;
		}else if(downAngle < 45){
			downAngle += 8.0f;
		}else{
			topAngle = 90;
			isTop = UP;
			isDown = STOP;
			if(--frame_loop == -1)
				frame_loop = 4;
		}
		glutPostRedisplay();
		glutTimerFunc(20, effect, 0);
	}else if(isDown == UP){
		if(downAngle > 45 ){
			downAngle -= 8.0f;
			glutPostRedisplay();
			glutTimerFunc(20, effect, 0);
		}else if(downAngle > 0){
			downAngle -= 5.0f;	
			glutPostRedisplay();
			glutTimerFunc(20, effect, 0);
		}else{
			isDown = STOP;
			glutPostRedisplay();
		}
	}
}

void DrawTopVBO(){
	float texcoords[] = {
		// Top
		1,1, 1,0, 0,0, 0,1,
		// Horizinatal
		1,1, 1,0, 0,0, 0,1
};
	// ~ 추가
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[0]); 
	
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	// ~ 추가
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 
	// ~ 추가
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->tiVBO[topLoop]);
	glDrawElements(GL_TRIANGLES, vbo->tIndecies[topLoop].size, GL_UNSIGNED_BYTE, (char*) NULL+0); 
	
	glDisableClientState(GL_VERTEX_ARRAY); 
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void DrawDownVBO(){
	glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[1]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->diVBO[downLoop]); 
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 
	
	glDrawElements(GL_TRIANGLES, vbo->dIndecies[downLoop].size, GL_UNSIGNED_BYTE, (char*) NULL+0); 
	
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}