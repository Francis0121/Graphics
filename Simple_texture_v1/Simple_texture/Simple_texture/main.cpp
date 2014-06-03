#include <gl/glew.h>
#include <gl/glut.h>
#include <string>
#include "SOIL/SOIL.h"
#include <iostream>
#include "VBO.h"

#define TRUE 1
#define FALSE 0

#define STOP 0
#define DOWN 1
#define UP 2

VBO *vbo = new VBO; // Vertex Buffer Object 생성
int width = 300, height = 400; // 화면 크기 지정 shape 이용
// ~ Event Function
void onDisplay();
void onResize(int width, int height);
void onMouse(int button, int state, int x, int y);
void onMouseWheel(int wheel, int direction, int x, int y);
void onMouseMotion(int x, int y);
void onEffect(int values);
void onXdecrease(int values);
void onXincrease(int values);
void onYdecrease(int values);
void onYincrease(int values);
void onFloatingRestart(int values);

// ~ Function
void idle();
void getPosition(int x, int y);
int LoadGLTexture();
void DrawTopVBO();
void DrawDownVBO();

// ~ Texture Mapping
#define TEXTURE_ID_SIZE 10
GLuint texture_id[TEXTURE_ID_SIZE];

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

// Floating
int floatingFlag = TRUE;

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Assignment 3");

	if(glewInit() != GLEW_OK) {
		std::cout << "GLEW init is failed" << std::endl;
	}

	vbo->InitGeometry();
	vbo->InitVBO();
	vbo->InitTexture();

	LoadGLTexture();
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);
	glutMouseWheelFunc(onMouseWheel);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onResize);
	glutIdleFunc(idle);
	glutTimerFunc(3000, onXdecrease, 0);
	glutTimerFunc(3000, onYincrease, 0);

	glutMainLoop();

	delete vbo;
}


void onFloatingRestart(int values){
	floatingFlag = TRUE;

	glutTimerFunc(10, onXdecrease, 0);
	glutTimerFunc(10, onYincrease, 0);
}

void onXdecrease(int values){
	if(scaleFlag){
		return;
	}
	vbo->xMin -= 0.001f;
	vbo->xMax -= 0.001f;

	vbo->InitTexture();

	glutSwapBuffers();
	if(floatingFlag){
		if(vbo->xMin < 0.05f ){
			glutTimerFunc(1000, onXincrease, 0);
		}else{
			glutTimerFunc(25, onXdecrease, 0);
		}
	}
}

void onXincrease(int values){
	if(scaleFlag){
		return;
	}
	vbo->xMin += 0.001f;
	vbo->xMax += 0.001f;

	vbo->InitTexture();

	glutSwapBuffers();
	
	if(floatingFlag){
		if(vbo->xMax > 0.95f ){
			glutTimerFunc(1000, onXdecrease, 0);
		}else{
			glutTimerFunc(25, onXincrease, 0);
		}
	}
}

void onYdecrease(int values){
	if(scaleFlag){
		return;
	}
	vbo->yMin -= 0.001f;
	vbo->yMax -= 0.001f;

	vbo->InitTexture();

	glutSwapBuffers();
	if(floatingFlag){
		if(vbo->yMin < 0.05f ){
			glutTimerFunc(1000, onYincrease, 0);
		}else{
			glutTimerFunc(25, onYdecrease, 0);
		}
	}
}

void onYincrease(int values){
	if(scaleFlag){
		return;
	}
	vbo->yMin += 0.001f;
	vbo->yMax += 0.001f;

	vbo->InitTexture();

	glutSwapBuffers();
	if(floatingFlag){
		if(vbo->yMax > 0.95f ){
			glutTimerFunc(1000, onYdecrease, 0);
		}else{
			glutTimerFunc(25, onYincrease, 0);
		}
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

void onDisplay()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-orthoWidth-0.1, orthoWidth+0.1, -orthoHeight, orthoHeight+0.2, 0.1, 100.0);

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
	glutSwapBuffers();
}

void DrawTopVBO(){

	int indexSize = vbo->tIndecies[topLoop].size;
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[0]); 
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+(sizeof(GLfloat)*3)); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+0); 
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->tiVBO[topLoop]);
	glDrawElements(GL_TRIANGLES, indexSize/2, GL_UNSIGNED_BYTE, (char*)NULL+(indexSize/2)); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY); 

	for(int i = 0; i<(indexSize/12); i++){
		glBindTexture(GL_TEXTURE_2D, texture_id[i+topLoop]);
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[0]); 
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 
		glBindBuffer(GL_ARRAY_BUFFER,0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo->texVBO[topLoop]);
		glTexCoordPointer(2, GL_FLOAT, 0, (char*) NULL+0);
		glBindBuffer(GL_ARRAY_BUFFER,0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->tiVBO[topLoop]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*) NULL+(i*6)); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

		glDisableClientState(GL_VERTEX_ARRAY); 
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void DrawDownVBO(){
	int indexSize = vbo->dIndecies[4-downLoop].size;
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[1]);
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+(sizeof(GLfloat)*3)); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+0); 
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->diVBO[4-downLoop]);
	glDrawElements(GL_TRIANGLES, indexSize/2, GL_UNSIGNED_BYTE, (char*) NULL+(sizeof(GLubyte) * indexSize/2)); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY); 

	for(int i = 0; i<(indexSize/12); i++){
		glBindTexture(GL_TEXTURE_2D, texture_id[TEXTURE_ID_SIZE-(i+1+downLoop)]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[1]); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->diVBO[4-downLoop]); 
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[1]); 
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 
		glBindBuffer(GL_ARRAY_BUFFER,0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo->texVBO[4-downLoop]);
		glTexCoordPointer(2, GL_FLOAT, 0, (char*) NULL+0);
		glBindBuffer(GL_ARRAY_BUFFER,0);
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->diVBO[4-downLoop]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*) NULL+(i*6)); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	
		glDisableClientState(GL_VERTEX_ARRAY); 
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	
	
}

void onResize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, 0.1, 100.0);
	glutPostRedisplay();
}

void idle()
{
	glutPostRedisplay();
}

int LoadGLTexture()
{
	char fileNameFormat[] = "IU/IU_%d.jpg";

	for(int i=0; i < TEXTURE_ID_SIZE; i++){
		char fileName[100];
		sprintf(fileName, fileNameFormat, i+1);
		texture_id[i] = SOIL_load_OGL_texture(
		fileName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);

		glBindTexture(GL_TEXTURE_2D, texture_id[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	return true;
}

// ~ Event Function 
void onMouse(int button, int state, int x, int y){
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
			glutTimerFunc(15, onEffect, 0);
		}
		mouseFlag = FALSE;
		if(floatingFlag){
			
			vbo->xMax = 0.8f;
			vbo->yMax = 0.9f;
			vbo->xMin = 0.2f;
			vbo->yMin = 0.3f;
			vbo->InitTexture();

			floatingFlag = FALSE;
			glutTimerFunc(3000, onFloatingRestart, 0);
		}
	}
}

void onMouseWheel(int wheel, int direction, int x, int y){
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

void onMouseMotion(int x, int y){
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

void onEffect(int values){
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
		glutTimerFunc(20, onEffect, 0);
	}else if(isTop == UP){
		if(topAngle > 45 ){
			topAngle -= 8.0f;
			glutPostRedisplay();
			glutTimerFunc(20, onEffect, 0);
		}else if(topAngle > 0){
			topAngle -= 5.0f;
			glutPostRedisplay();
			glutTimerFunc(20, onEffect, 0);
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
		glutTimerFunc(20, onEffect, 0);
	}else if(isDown == UP){
		if(downAngle > 45 ){
			downAngle -= 8.0f;
			glutPostRedisplay();
			glutTimerFunc(20, onEffect, 0);
		}else if(downAngle > 0){
			downAngle -= 5.0f;	
			glutPostRedisplay();
			glutTimerFunc(20, onEffect, 0);
		}else{
			isDown = STOP;
			glutPostRedisplay();
		}
	}
}