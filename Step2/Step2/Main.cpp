#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include "VBO.h"

#define TRUE 1
#define FALSE 0

#define STOP 0
#define DOWN 1
#define UP 2

using namespace std;

void DrawTopVBO();
void DrawDownVBO();
void display();
void effect(int values);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mousewheel(int wheel, int direction, int x, int y);
void dragAndDrop(int x, int y);

int frame_loop = 0;
GLdouble aspect = 3.0f/4.0f;

float scale = 1.0f;
int mouse_flag = FALSE;
int width = 300, height = 400;

VBO *vbo = new VBO;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Frame");
	
	if( glewInit() != GLEW_OK ) {
		std::cout << "GLEW faild to init. :-(" << std::endl;
	}
	
	vbo->InitGeometry();
	vbo->InitVBO();

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mousewheel);
	glutMotionFunc(dragAndDrop);
	glutDisplayFunc(display);
	glutMainLoop();
	
	delete vbo;
	return 0;
}

void DrawTopVBO(){
	// ~ Draw Top
	glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[0]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->tiVBO[frame_loop]); 
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 
	
	glDrawElements(GL_TRIANGLES, vbo->tIndecies[frame_loop].size, GL_UNSIGNED_BYTE, (char*) NULL+0); 
	
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	// ~ Draw Top Line
	glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[2]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->tiVBO[5]); 
		
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_COLOR_ARRAY);
		
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 

	glDrawElements(GL_LINES, vbo->tIndecies[5].size, GL_UNSIGNED_BYTE, (char*) NULL+0);
	glLineWidth(2.0f);

	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);
}

void DrawDownVBO(){

	// ~ Draw Bottom

	glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[1]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->diVBO[frame_loop]); 
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 
	
	glDrawElements(GL_TRIANGLES, vbo->dIndecies[frame_loop].size, GL_UNSIGNED_BYTE, (char*) NULL+0); 
	
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	// ~ Draw Bottom Line

	glBindBuffer(GL_ARRAY_BUFFER, vbo->vacVBO[2]); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->diVBO[5]); 
		
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_COLOR_ARRAY);
		
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 12); 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*) NULL+ 0); 

	glDrawElements(GL_LINES, vbo->dIndecies[5].size, GL_UNSIGNED_BYTE, (char*) NULL+0);
	glLineWidth(2.0f);

	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);
}

int isTop = STOP;
int isDown = STOP;
GLfloat changeRateTop = 0;
GLfloat changeRateDown = 0;
GLdouble orthoWidth = 3.0;
GLdouble orthoHeight = 4.0;

void display() { 

	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);

	// ~ Intrinsic
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, 0.1, 100.0); 

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(	0.0f, 0.0f, 4.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);
	
	for(int i=0; i<5; i++){
		glPushMatrix();
		glTranslatef(0, 0, (GLfloat)-i*5);
		if(isTop && i == 0){
			glScalef(1, changeRateTop, 1);
		}

		if(mouse_flag && i == 0){
			glScalef(1, scale, 1);
		}

		DrawTopVBO();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, (GLfloat)-i*5);
		if(isDown && i == 0){
			glScalef(1, changeRateDown, 1);
		}

		if(mouse_flag && i == 0){
			glScalef(1, scale, 1);
		}
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
		if( height/2 > y){
			isTop = DOWN;
			changeRateTop = 1.0f;
		}else{
			isDown = DOWN;
			changeRateDown = 1.0f;
		}
		
		cout << " Y Position " << y << endl;
		mouse_flag = FALSE;
		scale = 1.0f;
		glutTimerFunc(15, effect, 0);
	}
}

void mousewheel(int wheel, int direction, int x, int y){
	if(direction < 0){
		orthoHeight*=1.1;
		orthoWidth*=1.1;		
	}else if(direction > 0){
		orthoHeight*=0.9;
		orthoWidth*=0.9;
	}
	
	glutPostRedisplay();
}

void effect(int values){
	if(isTop == DOWN){
		/*if(changeRateTop > 0.001){
			changeRateTop *= 0.8f;
			glutPostRedisplay();
			glutTimerFunc(15, effect, 0);
		}else{
			changeRateDown = changeRateTop;
			isDown = UP;

			changeRateTop = 1.0f;
			isTop = STOP;

			frame_loop+=1;
			if(frame_loop == 5){
				frame_loop = 0;
			}
			glutPostRedisplay();
			glutTimerFunc(15, effect, 0);
		}*/
	}else if(isTop == UP){
		/*if(changeRateTop < 1){
			changeRateTop *= 1.2f;
			glutPostRedisplay();
			glutTimerFunc(15, effect, 0);
		}else{
			changeRateTop = 1.0f;
			isTop = STOP;
			glutPostRedisplay();
		}*/
	}else if(isDown == DOWN){
		/*if(changeRateDown > 0.001){
			changeRateDown *= 0.8f;
			glutPostRedisplay();
			glutTimerFunc(15, effect, 0);
		}else{
			changeRateTop = changeRateDown;
			isTop = UP;

			changeRateDown = 1.0f;
			isDown = STOP;

			frame_loop-=1;
			if(frame_loop == -1){
				frame_loop = 4;
			}
			glutTimerFunc(15, effect, 0);
		}*/
	}else if(isDown == UP){
		/*if(changeRateDown < 1){
			changeRateDown *= 1.2f;
			glutPostRedisplay();
			glutTimerFunc(15, effect, 0);
		}else{
			changeRateDown = 1.0f;
			isDown = STOP;
			glutPostRedisplay();
		}*/
	}
}


void dragAndDrop(int x, int y){

}