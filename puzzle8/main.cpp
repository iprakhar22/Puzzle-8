/* Made by Prakhar Vaish 16803025 

Compile using :
g++ main.cpp -o main.out -std=c++11 -framework GLUT -framework OpenGL -Wno-deprecated-declarations
*/

#include "gameheaders.h"
#include "game.cpp"
#include "ai.cpp"

#define COLUMNS 80
#define ROWS 80
#define FPS 3


void init()
{
	glClearColor(0.9,0.9,0.9,1.0);
}

void timer_callback(int)
{
	if(iii==3)
		printflag = false;
	if(printflag) 
	{
		printt();
		cout<<"yes\n";
		iii++;
	}
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timer_callback,0);
}

// This function is called at every frame of glutMainLoop
void dipsplay_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid(grid);
	printString(5,5,"Press S to Solve",{0,0,0});
	printString(55,5,"Press R to Randomize",{0,0,0});
	//printBigString(5,5,"Press A to be awesome",{0,0,0});
	printString(35,75,"Puzzle 8",{0,0,0});
	//trace(iii);
	glutSwapBuffers();
}

void reshape_callback(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,COLUMNS,0,ROWS,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard_callback(int key, int, int)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			moveUp();
			break;

		case GLUT_KEY_DOWN:
			moveDown();
			break;

		case GLUT_KEY_LEFT:
			moveLeft();
			break;

		case GLUT_KEY_RIGHT:
			moveRight();
			break;

		case 's':
		case 'S':
			solve();
			break;

		case 'R':
		case 'r':
			srand(time(NULL));
			reset();
			break;

		case 'p':
			iii=0;
			printflag = true;
			break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(700,700);
	glutCreateWindow("Puzzle 8 By Prakhar Vaish");
	glutDisplayFunc(dipsplay_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0,timer_callback,0);
	glutSpecialFunc(keyboard_callback);
	init();
	glutMainLoop();
	return 0;
}