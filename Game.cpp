#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include <GL/glut.h>
using namespace std;
#define pi (2*acos(0.0))

double car=0;
double X=10,Y=50,Z=10;
double leftRightMove=0;
double sky=-1000;

struct point
{
	double x,y,z;
};

void drawAxes(){
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
  glVertex3f( 100,0,0);
  glVertex3f(-100,0,0);

  glVertex3f(0,-100,0);
  glVertex3f(0, 100,0);

  glVertex3f(0,0, 100);
  glVertex3f(0,0,-100);
  glEnd();
}

void drawSquare(double a){
  glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
  glVertex3f( a, a,0);
  glVertex3f( a,-a,0);
  glVertex3f(-a,-a,0);
  glVertex3f(-a, a,0);
	}glEnd();
}

void drawCircle(double radius,int segments){
    int i;
    struct point points[100];
    glColor3f(1.0,0.0,1.0);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawRoad(){
    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,0,-30);
        glVertex3f(-100,0,-30);

        glVertex3f(-100,-2500,-30);
        glVertex3f(100,-2500,-30);

      glEnd();

    glPopMatrix();
}

void drawRoadMiddle(){

    glPushMatrix();
    glColor3f(1, 1, 1);

    glTranslatef(0,0,3);

    glBegin(GL_POLYGON);

    glVertex3f(-2,0,-30);
    glVertex3f(2,0,-30);

    glVertex3f(-2,-2500,-30);
    glVertex3f(2,-2500,-30);

    glEnd();

    glPopMatrix();
}

void drawMainCar(){
    glPushMatrix();
    cout<<car<<endl;

    glTranslatef(leftRightMove,car,0);
    glRotatef(90,0,0,1);

    /*******lower part********/
    glPushMatrix();
    glColor3f(1,.8,3);
    glScalef(2,1,.4);    
    glutSolidCube(10);
    glPopMatrix();

    /******* upper part********/
    glPushMatrix();
    glTranslatef(0,0,3);
    glColor3f(.67,.67,.67);   
    glScalef(1,1,.6);
    glutSolidCube(10);
    glPopMatrix();

    /******* front wheel left part********/
    glPushMatrix();
    glTranslatef(4,5,-2);
    glColor3f(1,.3,8);   
    glScalef(2,.7,1);
    glutSolidSphere(2,100,100);
    glPopMatrix();

    /******* front wheel right part********/
    glPushMatrix();
    glTranslatef(-4,5,-2);
    glColor3f(1,0,1);   
    glScalef(1,.7,1);
    glutSolidSphere(2,100,100);
    glPopMatrix();

    /******* behind wheel left part********/
    glPushMatrix();
    glTranslatef(4,-5,-2);
    glColor3f(1,.6,8);   
    glScalef(1,.7,1);
    glutSolidSphere(2,100,100);
    glPopMatrix();

    /******* behind wheel right part********/
    glPushMatrix();
    glTranslatef(-4,-5,-2);
    glColor3f(1,.3,8);   
    glScalef(1,.7,1);
    glutSolidSphere(2,100,100);
    glPopMatrix();

    glPopMatrix();

}

void drawBackground(){
    glPushMatrix();
    glTranslatef(0,sky,500);
    glRotatef(90,0,0,1);
    glColor3f(.3,0.9,.9);

    glScalef(.003,2,1);
    glutSolidCube(1000);

    glPopMatrix();

}

void drawHill(){

    glPushMatrix();
    glTranslatef(500,sky+30,0);
    glRotatef(90,0,0,1);
    glColor3f(0,0.9,0);
    glutSolidCone(200,400,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-500,sky+30,0);
    glRotatef(90,0,0,1);
    glColor3f(0,0.9,0.5);
    glutSolidCone(200,400,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-700,sky+30,0);
    glRotatef(90,0,0,1);
    glColor3f(0,0.9,0.5);
    glutSolidCone(200,400,20,20);
    glPopMatrix();

}

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.345, 0.4, 0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	gluLookAt(0,Y,10,	0,-30000,0,	0,0,1);
	//gluLookAt(60*cos(cameraAngle), 60*sin(cameraAngle), 0,		0,0,0,		0,0,1);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);
	//gluLookAt(pos.x, pos.y, pos.z,     pos.x + l.x,pos.y + l.y, pos.z + l.z,     u.x, u.y, u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//drawAxes();
//	drawGrid();

    //glColor3f(1,0,0);
    car-=.5;
    Y-=.5;
    sky-=.5;

    if(abs(car)<=1500)
    {
        for(int i=0,j=0;i<=10;i++,j+=200){

            if(i<=5){

             glPushMatrix();
             glTranslatef(-120,-j,0);
             glPushMatrix();
             {
               glTranslatef(0,0,0);
               glColor3f(.6,.6,.6);
               glRotatef(90,1,0,0);
               glutSolidCube(50);
             }glPopMatrix();

             glPushMatrix();
            {
               glTranslatef(0,0,20);
               glColor3f(.6,.6,0);
            //glRotatef(90,1,0,0);
               glutSolidCone(40,30,30,40);
             }glPopMatrix();

             glPopMatrix();
            }

            else{
                glPushMatrix();
             glTranslatef(-120,-j,0);
             glPushMatrix();
             glColor3f(0,1,0);
             glutSolidCone(20,30,20,20);

             glPopMatrix();

             glPushMatrix();
             glColor3f(.5,.5,.3);
             glScalef(.01,.4,5);
             glutSolidSphere(7,10,10);

             glPopMatrix();

             glPopMatrix();
            }
      }

       for(int i=0,j=0;i<=10;i++,j+=200){
            if(i<=4){


                 glPushMatrix();
                {
                    glColor3f(.345,.78,0);
                   glTranslatef(80,-j,-15);
                   glTranslatef(0,55,0);
                   glutSolidSphere(9,5,5);
                 }glPopMatrix();

            glPushMatrix();
            glTranslatef(120,-j,0);
            glPushMatrix();
            {
               glTranslatef(0,0,0);
               glColor3f(.6,.6,.6);
               glRotatef(90,1,0,0);
               glutSolidCube(50);
            }glPopMatrix();

            glPushMatrix();
            {
               glTranslatef(0,0,20);
               glColor3f(1,.6,0);
              //glRotatef(90,1,0,0);
              glutSolidCone(40,30,30,40);
             }glPopMatrix();

              glPopMatrix();
            }
            else if(i==5)
            {
                glPushMatrix();

                glTranslatef(120,-j,0);

                glPushMatrix();
                glColor3f(.5,.5,.3);
                glScalef(.01,.4,5);
                glutSolidSphere(7,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(5,0,1);
                glColor3f(0,.5,.3);
                glutSolidSphere(10,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-5,0,1);
                glColor3f(0,.5,.3);
                glutSolidSphere(10,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0,0,20);
                glColor3f(0,.5,.2);
                glutSolidSphere(15,10,10);
                glPopMatrix();

    glPopMatrix();
            }
            else{
                glPushMatrix();
             glTranslatef(120,-j,0);
             glPushMatrix();
             glColor3f(0,1,0);
             glutSolidCone(20,30,20,20);

             glPopMatrix();

             glPushMatrix();
             glColor3f(.5,.5,.3);
             glScalef(.01,.4,5);
             glutSolidSphere(7,10,10);

             glPopMatrix();

             glPopMatrix();
            }
    }




    drawRoad();

    drawRoadMiddle();

    }
    else if(abs(car)<=2000)
    {
        cout<<"problem\n";;
        for(int i=0,j=0;i<=15;i++,j+=200){

             glPushMatrix();
             glTranslatef(-120,-j,0);
             glPushMatrix();
             glColor3f(0,1,0);
             glutSolidCone(20,30,20,20);

             glPopMatrix();

             glPushMatrix();
             glColor3f(.5,.5,.3);
             glScalef(.01,.4,5);
             glutSolidSphere(7,10,10);

             glPopMatrix();

             glPopMatrix();
            }

       for(int i=0,j=0;i<=15;i++,j+=200){
            glPushMatrix();
            glTranslatef(120,-j,0);
            glPushMatrix();
            {
               glTranslatef(0,0,0);
               glColor3f(.6,.6,.6);
               glRotatef(90,1,0,0);
               glutSolidCube(50);
            }glPopMatrix();



            glPushMatrix();
            {
               glTranslatef(0,0,20);
               glColor3f(1,.6,0);
              //glRotatef(90,1,0,0);
              glutSolidCone(40,30,30,40);
             }glPopMatrix();

              glPopMatrix();
        }

    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,0,-30);
        glVertex3f(2,0,-30);

        glVertex3f(-2,-2500,-30);
        glVertex3f(2,-2500,-30);

      glEnd();

    glPopMatrix();

    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-1000,-30);
        glVertex3f(-100,-1000,-30);

        glVertex3f(-100,-2700,-30);
        glVertex3f(100,-2700,-30);

      glEnd();

    glPopMatrix();

    }
    else
    {
        for(int i=0,j=2200;i<=10;i++,j+=100){

             glPushMatrix();
             glTranslatef(-120,-j,0);
             glPushMatrix();
             {
               glTranslatef(0,0,0);
               glColor3f(.6,.6,.6);
               glRotatef(90,1,0,0);
               glutSolidCube(50);
             }glPopMatrix();

             glPushMatrix();
            {
               glTranslatef(0,0,20);
               glColor3f(.6,.6,0);
            //glRotatef(90,1,0,0);
               glutSolidCone(40,30,30,40);
             }glPopMatrix();

             glPopMatrix();
            }

       for(int i=0,j=2200;i<=10;i++,j+=100){
            glPushMatrix();
            glTranslatef(120,-j,0);
            glPushMatrix();
            {
               glTranslatef(0,0,0);
               glColor3f(.6,.6,.6);
               glRotatef(90,1,0,0);
               glutSolidCube(50);
            }glPopMatrix();



            glPushMatrix();
            {
               glTranslatef(0,0,20);
               glColor3f(1,.6,0);
              //glRotatef(90,1,0,0);
              glutSolidCone(40,30,30,40);
             }glPopMatrix();

              glPopMatrix();
       }






    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-1800,-30);
        glVertex3f(2,-1800,-30);

        glVertex3f(-2,-4000,-30);
        glVertex3f(2,-4000,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-2000,-30);
        glVertex3f(-100,-2000,-30);

        glVertex3f(-100,-4000,-30);
        glVertex3f(100,-4000,-30);

      glEnd();

    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,0,-30);
        glVertex3f(2,0,-30);

        glVertex3f(-2,-1700,-30);
        glVertex3f(2,-1700,-30);

      glEnd();

    glPopMatrix();

    }
    drawMainCar();

    drawBackground();

    drawHill();

   // drawSS();



    //drawCone(20,50,24);

	//drawSphere(30,24,20);



	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	30000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)

}

void specialKeyListener(int key, int x,int y){

	switch(key){

		case GLUT_KEY_UP:		//down arrow key
			
			car-=10;
			Y-=10;
			X-=5;
      sky-=10;
			
      if(Y==-10000){
        Y=50;car=0;sky=-1000;
		  }

			break;
		
    case GLUT_KEY_DOWN:		// up arrow key
			
			car+=5;
			Y+=5;
			X+=5;

			break;

		case GLUT_KEY_LEFT:

      leftRightMove+=5;
      car+=5;
      Y+=5;
			
			break;
		
    case GLUT_KEY_RIGHT:

		  leftRightMove-=5;
		  car-=5;
			Y-=5;

			break;

	}

}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 900);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutSpecialFunc(specialKeyListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;

}
