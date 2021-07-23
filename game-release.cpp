//============================================================================
//	Hassan Shahzad
//	18i-0441
//	FAST-NUCES
//	Snake Game Project
//	Contact at : chhxnshah@gmail.com
//============================================================================

#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
using namespace std;
int snake[100][2];
int size=4, direct=4;
int time_pass, timer, Ptimer, pfoodx=700, pfoody=700;
int foodx[5], foody[5], hurdles[2];
int poisonx[2]={ 200,310} ,poisony[2]= {210, 300} , bar_length=0, score=10, level=0;
bool gameover=false;
int linex1[3]= {157}, linex2[3]= {163} , liney[3]= {210} ;
/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */

void ScoreBar()
{
		DrawLine(0, 640, 200, 640, 10, colors[WHITE]);
		DrawLine(0, 640, bar_length, 640,  10, colors[YELLOW]);
}

void Win()
{
if (score >= 100)
DrawString(270, 320, "YOU WIN!", colors[RED]);
        time_pass = time(NULL);
		if (time(NULL) - time_pass >= 5)
			{
			exit(1);
			} 
}

void Score()
{
	string s = to_string(score);
	string l = to_string(level);
	DrawString( 500, 630, "Score= ", colors[WHITE]); // Display the scores
	DrawString( 600, 630, s, colors[WHITE]);
	DrawString( 250, 630, "Level= ", colors[WHITE]);
	DrawString( 330, 630, l, colors[WHITE]);
}


void Death()
{
		for(int i=1; i<size; i++)
		{
			if( snake[0][0] == snake[i][0] and snake[0][1] == snake[i][1] )
		
			gameover=true;	
		}
		for (int i=0; i<10; i++)
		{
		if (snake[0][0]==(hurdles[0]+i)*10 and snake[0][1]==hurdles[1]*10)
			gameover=true;	
		}
}

void SetCanvasSize(int width, int height) 
	{
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	    glMatrixMode( GL_MODELVIEW);
	    glLoadIdentity();
	}								
void SetSnake()
	{
		//Snake ki starting position k liye function

		int temp=0;
		for(int i=0; i<size; i++)
			{
				snake[i][0]=300-temp;
				snake[i][1]=300;
				temp+=10;
			}
	}

void LevelUp()
{
		if (score >=100 )
		{
			score=0;
			bar_length=0;
			level++;

		}

}


void DrawSnake()
	{
		//Snake Draw hora
        DrawCircle(snake[0][0]+5, snake[0][1]+5, 6, colors[BLUE]);
		for(int i=1; i<size; i++)
			{
					DrawSquare(snake[i][0], snake[i][1], 10, colors[GREEN]);
			}
	}


void LimitSnake()
	{
		//Canvas main limit krne k liye
			for (int i=0; i<size; i++)
			{
				if (snake[i][0]==650)// right side se
					snake[i][0]=0;
				else if (snake[i][1]==650)// upper side se
					snake[i][1]=0;
				else if (snake[i][0]==0)// left side se
					snake[i][0]=650;
				else if (snake[i][1]==0)// downward side se
					snake[i][1]=650;
			}
	}

//void food()
//{	
	
//}
void ShiftArray()
	{
		//Direction change
		for( int i=(size-1); i>0;i--)
			{
				snake[i][0]= snake[i-1][0];
				snake[i][1]= snake[i-1][1];
			}
	}


void DirectSnake()
	{
		//direction where snake's individual elements have to move
		switch(direct)		
			{		
				case 1: snake[0][1]+=10;
					break;
				case 2: snake[0][1]-=10;
					break;
				case 3: snake[0][0]-=10;
					break;
				case 4: snake[0][0]+=10;
					break;
			}
	}


void DrawCanvas()
	{
		//Canvass draw kr ra hun
		for(int i=0; i<65; i++)
		{
			for(int j=0; j<65; j++)
				{
					DrawSquare( i*10 , j*10 ,10,colors[47]);
				}
		}
	}


void PoisonFood()
{
		if ( time(NULL) - time_pass >=10)
		    {
				for (int i=0; i<3; i++)
				{		
					poisonx[i]=(rand() % 63)*10;
					poisony[i]=(rand() % 60)*10;

					time_pass = time(NULL);
				}
			}
		for (int i=0; i<3; i++)
		DrawSquare(poisonx[i], poisony[i], 10, colors[PURPLE]);
		
	for(int i=0; i<3 ; i++)
		{
			if (snake[0][0]==poisonx[i] and snake[0][1]==poisony[i])
				{

					poisonx[i] = (rand()%63)*10;
					poisony[i] = (rand()%60)*10;
		
					DrawSquare( poisonx[i], poisony[i], 10 , colors[PURPLE]);
					score-=10;
					bar_length-=20;
					//exit(1);
				}		
		}
}

void EatPowerFood()
{
		if( (snake[0][0] == pfoodx) and (snake[0][1] == pfoody))
			{
					pfoodx = -5;
					pfoody= -5;
					size++;
					score+=20;
					bar_length+=40;
			}
}

void PowerFood()
{
			if ( time(NULL) - Ptimer >=60)
				{
				pfoodx= (rand() % 63)*10;
				pfoody= (rand() % 60)*10;
				Ptimer= time(NULL);
				}
				DrawCircle( pfoodx, pfoody, 10 , colors[WHITE]);

			if (time(NULL)-Ptimer >= 15)
				{pfoodx= -700;
				pfoody= -700;}
			DrawCircle( pfoodx, pfoody, 10 , colors[WHITE]);
			
}

void DrawFood()
{
		if ( time(NULL) - time_pass >=15)
		    {	
					for(int i=0; i<5; i++)
					{
						bool repeat=true;
						while(repeat == true)
						{
							foodx[i]=(rand() % 63)*10;
							foody[i]=(rand() % 60)*10;
							time_pass = time(NULL);
							if (foodx[i] != foodx[i+1]  and foody[i] != foody[i+1])			
								{
									repeat=false;
								}
						}
					}
			}
		for (int i=0; i<5; i++)		
		{
			DrawSquare( foodx[i], foody[i], 10 , colors[WHITE]);
		}
}



void hurdle()
{	if (level == 1)
	{
		if (time(NULL)-timer==30)
		{
			srand(time(NULL));
			hurdles[0]=rand()%63;
			hurdles[1]=rand()%60;
			timer=time(NULL);
		}
			for (int i=0; i<10; i++)
			{
				DrawSquare((hurdles[0]+i)*10, (hurdles[1])*10, 10, colors[RED]);
			}
	}

	if (level == 2) 

	{
		if (time(NULL)-timer==20)
		{
			srand(time(NULL));
			hurdles[0]=rand()%63;
			hurdles[1]=rand()%60;
			timer=time(NULL);
		}
			for (int i=0; i<10; i++)
			{
				DrawSquare((hurdles[0]+i)*10, (hurdles[1])*10, 10, colors[RED]);
			}
		}

	if (level == 3 )
	{
		if (time(NULL)-timer==10)
		{
			srand(time(NULL));
			hurdles[0]=rand()%63;
			hurdles[1]=rand()%60;
			timer=time(NULL);
		}
			for (int i=0; i<10; i++)
			{
				DrawSquare((hurdles[0]+i)*10, (hurdles[1])*10, 10, colors[RED]);
			}
	}

	if (level == 4)
	{
		if (time(NULL)-timer==5)
		{
			srand(time(NULL));
			hurdles[0]=rand()%63;
			hurdles[1]=rand()%60;
			timer=time(NULL);
		}
			for (int i=0; i<10; i++)
			{
				DrawSquare((hurdles[0]+i)*10, (hurdles[1])*10, 10, colors[RED]);
			}
	}

}

void FoodEat()
{
	for(int i=0; i<5 ; i++)
	{
		if( snake[0][0] == foodx[i] && snake[0][1] == foody[i] )
		{
			foodx[i] = (rand()%65)*10;
			foody[i] = (rand()%65)*10;
		
		DrawSquare( foodx[i], foody[i], 10 , colors[WHITE]);
			size++;
			bar_length+=20;
			score+=10;
		}
	}
}



void Display()
{ 
if (gameover == false)
{
		glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
           0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		 glClear(GL_COLOR_BUFFER_BIT);//Update the colors 


//DrawCanvas();
DrawSnake();
LimitSnake();
ShiftArray();
DirectSnake();
hurdle();
DrawFood();
PowerFood();
EatPowerFood();
FoodEat();
PoisonFood();
ScoreBar();
Score();
LevelUp();	
//Win();
Death();

//Level2();
	
//String generate matlab username wagera	
//DrawString( 200, 600, "Username: ", colors[WHITE]); // This will display the username
	


}

		else if (gameover=true)
{
		DrawSquare( 0, 0, 650, colors[YELLOW]);
		DrawString(200, 320, "GAME OVERRRRRR!!!!!!!!!", colors[RED]);
		
		string s = to_string(score);
		DrawString( 200, 600, " Your Score Is: ", colors[BLUE]); // Display the scores
		DrawString( 400, 600, s, colors[BLUE]);
}
	glutSwapBuffers(); // do not modify this line..
}


void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		if (direct !=4)			
		direct=3;			// what to do when left key is pressed...
      
    } else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if (direct !=3)		
		direct=4;
    } else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
		if (direct !=2)        	
		direct=1;
    }
    else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
		if (direct !=1)		
		direct=2;
    }
    
     glutPostRedisplay();

}


void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
	}
    
    glutPostRedisplay();
}



void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}


int main(int argc, char*argv[]) 
{
    int width = 650, height = 650; 					// I have set my window size to be 650 x 650
    InitRandomizer(); 							// seed the random number generator...
    glutInit(&argc, argv); 						// initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 			// we will be using color display mode
    glutInitWindowPosition(50, 50); 					// set the initial position of our window
    glutInitWindowSize(width, height); 					// set the size of our window
    glutCreateWindow("HXN's Snake Game"); 				// set the title of our game window
    SetCanvasSize(width, height); 					// set the number of pixels...
	   
    SetSnake();
	time_pass = time(NULL)-15;
	timer = time(NULL)-10;
	Ptimer = time(NULL);
	

    glutDisplayFunc(Display); 

// tell library which function to call for drawing Canvas.

    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters

// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...

    glutTimerFunc(5.0 / FPS, Timer, 0);
    
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

