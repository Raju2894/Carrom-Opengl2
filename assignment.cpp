#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdio.h>
#define PI 3.1417
#define DEG2RAD(deg) (deg * PI / 180)
using namespace std;


// defined class of ball
struct carrom{
	float rad;
    float mass;
    float flag;
    float x;
    float y;
    float velx;
    float vely;
};
void spacefunc();
//void handleMouseclick(int button, int state, int x, int y);
void DrawCircle(float cx, float cy, float r, int num_segments);
void drawBox(float len);
void drawCircle(float rad);
void handleKeypress1(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void handleKeypress2(int key, int x, int y);
void mouseMove(int x, int y);
void initRendering();
void handleResize(int w, int h);
void drawScene();
void update(int value);
void drawBall(float rad);
void timer(int value1);
void mouseWheel(int button, int dir, int x, int y);

float speedx1=0.0f;
float speedy1=0.0f;
float speedx2=0.0f;
float speedy2=0.0f;
float tri1_y = 0.0f;
float tri1_x = 0.0f;
float box_len  = 6.0f;
float box_len2  = 4.5f;
float finalxposition = 3.5f;
float finalyposition = 0.0f;
float coefficient = 1.0f;
int score = 30; 
float speed = -2.5f;
float slope ;
float ball_rad = 0.2f;
carrom ball[11];
float s1 = 3.5f;
float s2 = -0.7f;
float s3 = 1.1f;
float s4 = 3.5f;
float s5 = 0.0f;
float marker_x;
float marker_y;
int count =0,fl=0,game=0,game1=0,game2=1;
int w1 ,h1;
void motion(int x, int y);

int main(int argc, char** argv) {
    //Initialize GLUT
    glutInit(&argc ,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    int w = glutGet(GLUT_SCREEN_WIDTH);
    w1=w;
    
    int h = glutGet(GLUT_SCREEN_HEIGHT);
     h1=h;
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
    
    //Create the Window
    glutCreateWindow("CaRrOm'S");
    initRendering();

    //set handler functions
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    //glutMouseFunc(handleMouseclick);
    glutMouseFunc(mouseButton); 
    glutMotionFunc(mouseMove); 
    glutMouseWheelFunc(mouseWheel);
    //glutMouseFunc(motion);
    glutReshapeFunc(handleResize);
    
    //Add a timer
    glutTimerFunc(25, update, 0);
     glutTimerFunc(2500, timer, 0);

    glutMainLoop();
    return 0;
}

void timer(int value1)
{
    if(score < 0)
        score = 30;
    score = score -1;
    if(game2 == 1)//starting timer 
        glutTimerFunc(2500, timer, 0);
}


void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);


    //draw power bar
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.4f,0.5f,0.8f);
    glVertex2f(-4.0f, -2.5f);
    glVertex2f(-4.0f, 3.2f);
    glVertex2f(-4.5f, 3.2f);
    glVertex2f(-4.5f, -2.5f);
    glEnd();
    glPopMatrix();

    // pointer for power bar 
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-3.9f,speed);
    glVertex2f(-4.6f,speed);
    glEnd();
    glPopMatrix();

    //coin placing boxes 
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex2f(4.25f, 2.0f);
    glVertex2f(5.75f, 2.0f);
    glVertex2f(5.75f, 1.6f);
    glVertex2f(4.25f, 1.6f);
    glEnd();
    glPopMatrix();


     //coin placing boxes
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1.0f,0.0f,1.0f);
    glVertex2f(3.25f, 1.4f);
    glVertex2f(5.75f, 1.4f);
    glVertex2f(5.75f, 0.9f);
    glVertex2f(3.25f, 0.9f);
    glEnd();
    glPopMatrix();
    
    //coin placing boxes
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex2f(3.25f, 0.8f);
    glVertex2f(5.75f, 0.8f);
    glVertex2f(5.75f, 0.3f);
    glVertex2f(3.25f, 0.3f);
    glEnd();
    glPopMatrix();

    // coin placing boxes
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.0f,1.0f,0.4f);
    glVertex2f(3.25f, 0.2f);
    glVertex2f(5.75f, 0.2f);
    glVertex2f(5.75f, -0.3f);
    glVertex2f(3.25f, -0.3f);
    glEnd();
    glPopMatrix();

    // coin placing boxes
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1.0f,1.0f,0.4f);
    glVertex2f(3.25f, -0.9f);
    glVertex2f(5.75f, -0.9f);
    glVertex2f(5.75f, -0.4f);
    glVertex2f(3.25f, -0.4f);
    glEnd();
    glPopMatrix();


    

    // text for mentioning controls
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(-5.3, -2.8);
    std::string str1 = "Power-Controller";
    void * font1 = GLUT_BITMAP_HELVETICA_12;
    int p1;
    for (p1 = 0; p1 != 17; p1++)
    {
        char c1 = str1[p1];
        glutBitmapCharacter(font1, c1);
    }
    glPopMatrix();


    // text for mentioning controls
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(-5.7, -3.0);
    std::string str2 = "ArrowUp & ArrowDown";
    void * font2 = GLUT_BITMAP_HELVETICA_18;
    int p2;
    for (p2 = 0; p2 != 19; p2++)
    {
        char c2 = str2[p2];
        glutBitmapCharacter(font2, c2);
    }
    glPopMatrix();



 
    

    // text for mentioning controls 
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(3.25, -2.5);
    std::string str3 = "pointer-Controlkeys-> w s a d ";
    void * font3 = GLUT_BITMAP_HELVETICA_12;
    int p3;
    for (p3 = 0; p3 != 31; p3++)
    {
        char c3 = str3[p3];
        glutBitmapCharacter(font3, c3);
    }
    glPopMatrix();

    //text for mentioning controls
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(3.25, -2.9);
    std::string str4 = "striker-> spacebar, sidemove <- ->";
    void * font4 = GLUT_BITMAP_HELVETICA_12;
    int p4;
    for (p4 = 0; p4 != 34; p4++)
    {
        char c4 = str4[p4];
        glutBitmapCharacter(font4, c4);
    }
    glPopMatrix();

    //text for mentioning controls
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(3.25, -3.1);
    std::string str5 = "reset striker-> b ";
    void * font5 = GLUT_BITMAP_HELVETICA_12;
    int p5;
    for (p5 = 0; p5 != 18; p5++)
    {
        char c5 = str5[p5];
        glutBitmapCharacter(font5, c5);
    }
    glPopMatrix();

   
    // text for displaying score 
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(4.5, 1.75);
    std::string str = "Score :";
    std::string s = std::to_string(score);
    void * font = GLUT_BITMAP_HELVETICA_18;
    int p;
    for (p = 0; p != 8; p++)
    {
        char c = str[p];
        glutBitmapCharacter(font, c);
    }
    for (p = 0; p != 3; p++)
    {
        char c = s[p];
        glutBitmapCharacter(font, c);
    }
    glPopMatrix();

    //Draw Carrom Board
    
    // Draw Box right vertical border 
    glPushMatrix();
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);//begin drawing of Rectagle polygon
      glVertex3f(3.0f,-3.0f,0.0f);//first vertex
      glVertex3f( 3.2f, -3.0f,0.0f);//second vertex
      glVertex3f(3.2f, +3.0f,0.0f);//third vertex
      glVertex3f(3.0f, +3.0f,0.0f);//fourth vertex 
    glEnd();//end drawing of Rectangle polygon
    glPopMatrix();

    // Draw Box upper horizontal border
    glPushMatrix();
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);//begin drawing of rectangle polygon
      glVertex3f(-3.2f,3.0f,0.0f);//first vertex
      glVertex3f( -3.2f, 3.2f,0.0f);//second vertex
      glVertex3f(+3.2f, +3.2f,0.0f);//third vertex
      glVertex3f(+3.2f, +3.0f,0.0f);//fourth vertex
    glEnd();//end drawing of polygon
    glPopMatrix();

    // Draw Box left vertical border
    glPushMatrix();
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);//begin drawing of rectangle polygon
      glVertex3f(-3.0f,-3.0f,0.0f);//first vertex
      glVertex3f( -3.2f, -3.0f,0.0f);//second vertex
      glVertex3f(-3.2f, +3.0f,0.0f);//third vertex
      glVertex3f(-3.0f, +3.0f,0.0f);//fourth vertex
    glEnd();//end drawing of polygon
    glPopMatrix();


    // Draw Box bottom border 
    glPushMatrix();
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);//begin drawing of rectangle polygon
      glVertex3f(-3.2f,-3.2f,0.0f);//first vertex
      glVertex3f(3.2f, -3.2f,0.0f);//second vertex
      glVertex3f(3.2f, -3.0f,0.0f);//third vertex
      glVertex3f(-3.2f, -3.0f,0.0f);//fourth vertex
    glEnd();//end drawing of polygon
    glPopMatrix();


    // Draw Box inner square  part
    glPushMatrix();
    glColor3f(1.0f,0.8f,0.45f);
    glBegin(GL_POLYGON);//begin drawing of square polygon
      glVertex3f(-3.0f,-3.0f,0.0f);//first vertex
      glVertex3f(3.0f, -3.0f,0.0f);//second vertex
      glVertex3f(3.0f, 3.0f,0.0f);//third vertex
      glVertex3f(-3.0f, 3.0f,0.0f);//fourth vertex 
    glEnd();//end drawing of polygon
   

   //draw black circle corner holes "1"
    glPushMatrix();
    glTranslatef(2.85f, 2.85f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawBall(0.150);
    glPopMatrix();

    //draw black circle corner holes  "2"
    glPushMatrix();
    glTranslatef(-2.85f, 2.85f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawBall(0.150);
    glPopMatrix();
       
    //draw black circle corner holes "3"
    glPushMatrix();
    glTranslatef(2.85f, -2.85f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawBall(0.15);
    glPopMatrix();

    //draw black circle corner holes  "4"
    glPushMatrix();
    glTranslatef(-2.85f, -2.85f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawBall(0.150);
    glPopMatrix();

    //draw rectanglar outline for placing striker Upper horizontal
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -8.0f);
    glBegin(GL_LINES);
    glVertex2f(4.0f,4.0f);
    glVertex2f(4.0f,4.3f);
    glVertex2f(4.0f,4.3f);
    glVertex2f(-4.0f,4.3f);
    glVertex2f(-4.0f,4.3f);
    glVertex2f(-4.0f,4.0f);
    glVertex2f(-4.0f,4.0f);
    glVertex2f(4.0f,4.0f);
    glEnd();
    glPopMatrix();

    //draw red circles on rectangular outline
    glPushMatrix();
    glTranslatef(-3.85f, 4.15f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

    //draw red circles on rectangular outline 
    glPushMatrix();
    glTranslatef(3.85f, 4.15f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

    //draw rectangles outline for placing Striker Bottom Horizontal
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -8.0f);
    glBegin(GL_LINES);
    glVertex2f(4.0f,-4.0f);
    glVertex2f(4.0f,-4.3f);
    glVertex2f(4.0f,-4.3f);
    glVertex2f(-4.0f,-4.3f);
    glVertex2f(-4.0f,-4.3f);
    glVertex2f(-4.0f,-4.0f);
    glVertex2f(-4.0f,-4.0f);
    glVertex2f(4.0f,-4.0f);
    glEnd();
    glPopMatrix();

    //draw red circles on rectangular outline
    glPushMatrix();
    glTranslatef(-3.85f, -4.15f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

    //draw red circles on rectangular outline
    glPushMatrix();
    glTranslatef(3.85f, -4.15f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

    //draw rectanglar outline for placing  Striker Right Vertical
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -8.0f);
    glBegin(GL_LINES);
    glVertex2f(4.0f,4.0f);
    glVertex2f(4.3f,4.0f);
    glVertex2f(4.3f,4.0f);
    glVertex2f(4.3f,-4.0f);
    glVertex2f(4.3f,-4.0f);
    glVertex2f(4.0f,-4.0f);
    glVertex2f(4.0f,-4.0f);
    glVertex2f(4.0f,4.0f);
    glEnd();
    glPopMatrix();

    //draw red circles
    glPushMatrix();
    glTranslatef(4.15f, 3.85f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

    //draw red circles
    glPushMatrix();
    glTranslatef(4.15f, -3.85f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();


    //draw rectangles left vertical outline for placing striker
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -8.0f);
    glBegin(GL_LINES);
    glVertex2f(-4.0f,4.0f);
    glVertex2f(-4.3f,4.0f);
    glVertex2f(-4.3f,4.0f);
    glVertex2f(-4.3f,-4.0f);
    glVertex2f(-4.3f,-4.0f);
    glVertex2f(-4.0f,-4.0f);
    glVertex2f(-4.0f,-4.0f);
    glVertex2f(-4.0f,4.0f);
    glEnd();
    glPopMatrix();



    //draw red circles on rectangular outline
    glPushMatrix();
    glTranslatef(-4.15f, 3.85f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

    //draw red circles on rectangular outline
    glPushMatrix();
    glTranslatef(-4.15f, -3.85f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

   //draw red circles on rectangular outline
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawBall(1.0f);
    glPopMatrix();




    
    //draw red circles on rectangular outline
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(0.85f);
    glPopMatrix();

    //Draw Coins
    int temp=0;
    for (int j =0,i=0; i< 9; j=j+45,i++)
    {
        glPushMatrix();
        if(j<360)
        {
            if (temp==0)   
            {
                glColor3f(0.8f,0.4f,0.0f);
                temp=1;
            }
            else
            {
                glColor3f(0.0f, 0.0f, 0.0f);
                    temp=0;
            }
            glTranslatef(ball[i].x, ball[i].y, 0.0f);
            drawCircle(ball[i].rad);
        }
        else
        {

            glColor3f(1.0f, 0.0f, 0.0f);
            glTranslatef(ball[i].x, ball[i].y, 0.0f);
            drawCircle(ball[i].rad);

        }
        glPopMatrix();
    }
    
    //drawing striker 
    glPushMatrix();
    glColor3f(0.5f, 0.8f, 1.0f);
    glTranslatef(ball[9].x, ball[9].y, 0.0f);
    drawCircle(ball[9].rad);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    glTranslatef(ball[10].x, ball[10].y, 0.0f);
    if(ball[9].flag ==1)
    {   
        glBegin(GL_LINES);
         glVertex2f(ball[9].x, ball[9].y);
         glVertex2f(tri1_x,tri1_y);
         glEnd();
          
    }
    glPopMatrix();
    glPopMatrix();

    if(game1==1 && game == 4)
    {
    //text for mentioning controls
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(-1.0, 0.0);
    std::string str8 = "Game Over! Congrats";
    void * font8 = GLUT_BITMAP_HELVETICA_18;
    int p8;
    for (p8 = 0; p8 != 19; p8++)
    {
    char c8 = str8[p8];
    glutBitmapCharacter(font8, c8);
    }
    glPopMatrix();
    }

     if(fl==1)
    {
    //text for mentioning controls
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(3.25, 3.0);
    std::string str10 = "your target is White";
    void * font10 = GLUT_BITMAP_HELVETICA_18;
    int p10;
    for (p10 = 0; p10 != 20; p10++)
    {
    char c10 = str10[p10];
    glutBitmapCharacter(font10, c10);
    }
    glPopMatrix();
    }

     if(count == 1)
    {
    //text for mentioning controls
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(3.25, 3.0);
    std::string str11 = "your target is Black";
    void * font11 = GLUT_BITMAP_HELVETICA_18;
    int p11;
    for (p11 = 0; p11 != 20; p11++)
    {
    char c11 = str11[p11];
    glutBitmapCharacter(font11, c11);
    }
    glPopMatrix();
    }

    //text for mentioning controls
    glPushMatrix();
    //needs to be called before RasterPos
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(3.25, -2.0);
    std::string str9 = "press Enter to reset game";
    void * font9 = GLUT_BITMAP_HELVETICA_12;
    int p9;
    for (p9 = 0; p9 != 25; p9++)
    {
    char c9 = str9[p9];
    glutBitmapCharacter(font9, c9);
    }
    glPopMatrix();
    glPopMatrix();//end of intial pushmatrix
    glutSwapBuffers();
}



void update(int value) 
{
    for (int i = 0; i < 10; i++)
    {
        if(ball[i].x + ball[i].rad > box_len/2 || ball[i].x - ball[i].rad < -box_len/2)
            ball[i].velx *=-1;
        if(ball[i].y + ball[i].rad > box_len/2 || ball[i].y - ball[i].rad < -box_len/2)
            ball[i].vely *=-1;
    }


    for(int i = 0; i < 10; i++)
    {
       for(int j=i+1;j<10;j++)
		{
			float a = ball[i].x - ball[j].x;
			float b = ball[i].y - ball[j].y;
			float sumrad = (ball[i].rad + ball[j].rad);
			float sqrrad = sumrad * sumrad ;
			float distsqr = (a * a) + (b * b);
			if( distsqr <= sqrrad  )
			{
				float collision[2];
				collision[0]=a;
				collision[1]=b;
				float distance = sqrt((a*a) + (b*b)) ;
				float unor[2];   unor[0]=collision[0]/distance;  unor[1] = collision[1]/distance;
				float u1[2]; u1[0]=ball[i].velx; u1[1]=ball[i].vely;
				float u2[2]; u2[0]=ball[j].velx; u2[1]=ball[j].vely;
				float utang[2]; utang[0]=-1*unor[1]; utang[1]=unor[0];
				float u1n = unor[0] * u1[0] + unor[1] * u1[1];
				float u1t = utang[0] * u1[0] + utang[1] * u1[1];
				float u2n = unor[0] * u2[0] + unor[1] * u2[1];
				float u2t = utang[0] * u2[0] + utang[1] * u2[1];	
				float v1n = (u1n * (ball[i].mass - ball[j].mass)+ (2 * ball[j].mass * u2n))/(ball[i].mass + ball[j].mass);
				float v2n = (u2n * (ball[j].mass - ball[i].mass)+ (2 * ball[i].mass * u1n))/(ball[i].mass + ball[j].mass);
				float v1nf[2]; v1nf[0] = v1n * unor[0]; v1nf[1] = v1n * unor[1];
				float v1tf[2]; v1tf[0] = u1t * utang[0]; v1tf[1] = u1t * utang[1];
				float v2nf[2]; v2nf[0] = v2n * unor[0]; v2nf[1] = v2n * unor[1];
				float v2tf[2]; v2tf[0] = u2t * utang[0]; v2tf[1] = u2t * utang[1];
				float v1[2]; v1[0] = v1nf[0] + v1tf[0];  v1[1] = v1nf[1] + v1tf[1];
				float v2[2]; v2[0] = v2nf[0] + v2tf[0];  v2[1] = v2nf[1] + v2tf[1];
				ball[i].velx = v1[0];
				ball[i].vely = v1[1];
				ball[j].velx = v2[0];
				ball[j].vely = v2[1];
				ball[i].velx *= 0.98;
				ball[i].vely *= 0.98;
				ball[j].velx *= 0.98;
				ball[j].vely *= 0.98;
				ball[i].x += ball[i].velx/coefficient;
				ball[i].y += ball[i].vely/coefficient;
				ball[j].x += ball[j].velx/coefficient;
				ball[j].y += ball[j].vely/coefficient;
			}
		}
		ball[i].velx *= 0.98;
		ball[i].vely *= 0.98;
		ball[i].x += ball[i].velx/coefficient;
		ball[i].y += ball[i].vely/coefficient;
		
        if( (ball[i].x >= 2.67f && ball[i].y >= 2.67f) || (ball[i].x <= -2.67f && ball[i].y >= 2.67f) || (ball[i].x <= -2.67f && ball[i].y <= -2.67f) || (ball[i].x >= 2.67f && ball[i].y <= -2.67f) )
        {
            if(i==8)
            {
                
                ball[i].x= s1;
                ball[i].y= s3;
                ball[i].flag=0;
                score = score+50;
                game1++;
            }
            else if(i==9)
            {
                ball[i].x= s1;
                ball[i].y= s2;
                ball[i].flag=0;
                score = score-5;
                
            }
            else if(i!=8 && i!=9)
            {
                if(count ==0){
                    if(i%2){
                        count = 1;
                        
                    }
                    else
                        fl=1;
                }
            if(count == 1){
                if(i%2 && i!= 8)//hitting of black coin
                {
                    ball[i].x= finalxposition;
                    ball[i].y= finalyposition;
                    ball[i].flag=0;
                    finalxposition = finalxposition+0.3f;
                    score = score + 10;
                    game++;

                }
                else if (i%2==0 && i!=9)  // hitting of white coin
                {
                    ball[i].x= s4;
                    ball[i].y= s5+0.5f;
                    ball[i].flag=0;
                    s4 = s4+0.3f;
                    score = score - 5;
                }
            }

            if(fl == 1)
            {
                 if(i%2 && i!= 8 )//hitting of black coin
                {
                    ball[i].x= finalxposition;
                    ball[i].y= finalyposition;
                    ball[i].flag=0;
                    finalxposition = finalxposition+0.3f;
                    score = score - 5;

                }
                else if (i%2==0 && i!=9)  // hitting of white coin
                {
                    ball[i].x= s4;
                    ball[i].y= s5+0.5f;
                    ball[i].flag=0;
                    s4 = s4+0.3f;
                    score = score + 10;
                    game++;
                }
               count = -1;

            }
        }
        

            ball[i].velx=0;
            ball[i].vely=0;
            
            if(game1 == 1 && game == 4)
                game2 = 0;
            
        }

        coefficient = coefficient * 1.001;
    }

    
    glutTimerFunc(25, update, 0);

}


void drawCircle(float rad)
{
    if (rad < 0.4) glBegin(GL_TRIANGLE_FAN); //for Coins 
    else glBegin(GL_LINE_LOOP);  
    for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}
void drawBall(float rad) {
    
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}


void DrawCircle(float cx, float cy, float r, int num_segments) 
{ 
    glBegin(GL_LINE_LOOP); 
    for(int ii = 0; ii < num_segments; ii++) 
    { 
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 

        glVertex2f(x + cx, y + cy);//output vertex 

    } 
    glEnd(); 
}

//When a key is pressed
void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    if (key == 13) {
       //ball[10].flag=0;
        initRendering();
        game2 = 1;
        score = 30;
        glutTimerFunc(2500, timer, 0);
        tri1_x = 0.0f;
        tri1_y = 0.0f;
        speed = -2.5f;

    }//
    if( key == 97 && tri1_x > -2.9f)
    	 tri1_x -= 0.1;
    if (key == 100 && tri1_x < +2.9f)
    	 tri1_x += 0.1;
    if(key == 119 && tri1_y < 2.9f)
    	 tri1_y += 0.1;
    if (key == 115 && tri1_y > -2.9f)
    	 tri1_y -= 0.1;
    if(key == 98)
    {
			ball[9].x=0.0f;
		    ball[9].y=-2.05f;
		    ball[9].velx=0.0f;
		    ball[9].vely=0.0f;
		    ball[9].flag=1;
		    ball[10].x=0.0f;
		    ball[10].y=0.0f;
		    //ball[10].flag=1;
		    tri1_x = 0.0f;
		    tri1_y = 0.0f;
            speed = -2.5f;
    }
    if (key == 32) {
        //ball[10].flag=1;
      /*  ball[9].flag=0;
        float t = atan2(ball[9].y-tri1_y, ball[9].x-tri1_x);
        ball[9].velx = -(2.5f + speed) * 0.01 * cos(t) ;
        ball[9].vely = -(2.5f + speed) * 0.01 * sin(t) ;
        coefficient = 0.19f;  
        glutTimerFunc(25, update,0);*/
        spacefunc();
    }
}



void handleKeypress2(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT && ball[9].x > -2.0f) 
        ball[9].x -= 0.1;
    if (key == GLUT_KEY_RIGHT && ball[9].x < 2.0f )
        ball[9].x += 0.1;
    if (key == GLUT_KEY_DOWN && speed > -2.5) 
        speed -= 0.1;
    if (key == GLUT_KEY_UP && speed < 3.1)
        speed += 0.1;
}



//Initialize 3D rendering
void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL); //enable color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //changes the background color to black
    for (int j =0,i=0; i< 9; j=j+45,i++)
    {
        if(j<360)
        {
            ball[i].x= 0.5f * cos(DEG2RAD(j));
            ball[i].y= 0.5f * sin(DEG2RAD(j));
            ball[i].velx=0.0f;
            ball[i].vely=0.0f;
            ball[i].rad=0.125f;
        }
        else
        {

            ball[i].x=0.0f;
            ball[i].y=0.0f;
            ball[i].velx=0.0f;
            ball[i].vely=0.0f;
            ball[i].rad=0.125f;
        }
        ball[i].mass=2.0f;
        ball[i].flag=1;
    }
    ball[9].x=0.0f;
    ball[9].y=-2.05f;
    ball[9].velx=0.0f;
    ball[9].vely=0.0f;
    ball[9].mass=4.0f;
    ball[9].rad=0.15f;
    ball[9].flag=1;
    ball[10].x=0.0f;
    ball[10].y=0.0f;
    ball[10].flag=1;

}

void spacefunc()
{
        ball[9].flag=0;
        float t = atan2(ball[9].y-tri1_y, ball[9].x-tri1_x);
        ball[9].velx = -(2.5f + speed) * 0.01 * cos(t) ;
        ball[9].vely = -(2.5f + speed) * 0.01 * sin(t) ;
        coefficient = 0.19f;  
        glutTimerFunc(25, update,0);

}


//When the window is resized 
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
float pointer=0.0f;
float marker_x1,marker_y1;
int flag1;


float a,b;
int isDragging=0;

void mouseMove(int x, int y)
{
if (isDragging) {


a=(float)x;
b=(float)y;
a=(0.0129)*a-5.89f;
b=(-0.0128*b)+3.28f;

if(a>-2.0f && a<2.0f)
ball[9].x = a;

}
}

void mouseButton(int button, int state, int x, int y)
{
switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
            {  
                    a=(float)x;
                    b=(float)y;
                    //cout << x << " " << y << endl;
                    a=(0.0129)*a-5.89f;
                    b=(-0.0128*b)+3.28f;
                    //cout << a << " - " << b << endl;
                    if(sqrt((a-ball[9].x)*(a-ball[9].x)+(b-ball[9].y)*(b-ball[9].y)) < ball[9].rad)
                    isDragging = 1; // start dragging
                    }
                    else {
                    isDragging = 0;
                    }
            
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN)
            {
                a=(float)x;
                b=(float)y;
                a=(0.0129)*a-5.89f;
                b=(-0.0128*b)+3.28f;
                if( a > -3.0f && a < 3.0f && b<3.0f && b > -3.0f){
                tri1_x = a;
                tri1_y = b;
                }
                if(b > -2.0)
                speed = b; 
                else {
                    speed = 0.4f;
                }
            }
            if(state == GLUT_UP)
            {
                spacefunc();
            }
            break;
    }

}
void mouseWheel(int button, int dir, int x, int y)
{
    if (speed > 2.5)
    {
        speed = -2.5;
    }
    else
    {
      speed += 0.3f;   
    }
}


 