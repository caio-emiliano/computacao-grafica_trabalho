#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include <GL/glut.h>
#include <vector>
#include <string>
using namespace std;
#define pi (2*acos(0.0))

// fStream - STD File I/O Library
#include <fstream>

// OBJ_Loader - .obj Loader
#include "OBJ_Loader.h"

#define TREE_TRUNK 0
#define LEAFS 1


double car=0;
double X=10,Y=50,Z=10;
double leftRightMove=0;
double sky=-1000;

struct car_meshs{
  objl::Mesh cur_mesh;
};

struct tree_meshs{
  objl::Mesh cur_mesh;
};

struct point{
	double x,y,z;
};

vector<car_meshs> carro;
vector<tree_meshs> arvore;

void load_obj(string PathToOBJ, string OBJ_name){

  objl::Loader Loader;  

	// Load .obj File
	bool loadout = Loader.LoadFile(PathToOBJ);

  if (loadout){

    if(OBJ_name == "Car"){

      car_meshs Mesh;

      for (int i = 0; i < Loader.LoadedMeshes.size(); i++){
        Mesh.cur_mesh = Loader.LoadedMeshes[i];
        carro.push_back(Mesh);
      }

    }

    if(OBJ_name == "Tree"){

      tree_meshs Mesh;
      
      for (int i = 0; i < Loader.LoadedMeshes.size(); i++){
        Mesh.cur_mesh = Loader.LoadedMeshes[i];
        arvore.push_back(Mesh);
      }

    }

  }

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

void drawRoad(){

    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

    glBegin(GL_POLYGON);

    glVertex3f(100,5000,-30);
    glVertex3f(-100,5000,-30);

    glVertex3f(-100,-5000,-30);
    glVertex3f(100,-5000,-30);

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

void drawClouds(){

    glPushMatrix();

    glBegin(GL_QUADS);
    glVertex2f(500.0f, 700.0f); // top left
    glVertex2f(1.0f, 1.0f); // top right 
    glVertex2f(1.0f, -1.0f); // bottom right
    glVertex2f(-1.0f, -1.0f); // bottom left
    glEnd();

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

void drawCarOBJ(){

  glPushMatrix();
 
  // Render a color-cube consisting of 6 quads with different colors

  glTranslatef(leftRightMove,car,0);
  glRotatef(90,1,0,0);

  glBegin(GL_POLYGON);

  glColor3f(0, 0, 0);

  for (int i = 0; i < carro.size() ; i++){
  
    for (int j = 0; j < carro[i].cur_mesh.Vertices.size(); j++){
      glVertex3f(carro[i].cur_mesh.Vertices[j].Position.X, carro[i].cur_mesh.Vertices[j].Position.Y, carro[i].cur_mesh.Vertices[j].Position.Z);
      glNormal3f(carro[i].cur_mesh.Vertices[j].Normal.X, carro[i].cur_mesh.Vertices[j].Normal.Y, carro[i].cur_mesh.Vertices[j].Normal.Z);
    }

  }

  glEnd();

  glPopMatrix();

}

void drawTreeOBJ(int x, int y){

  glPushMatrix();
 
  // Render a color-cube consisting of 6 quads with different colors

  glTranslatef(x,-y,0);
  glRotatef(90,1,0,0);

  glBegin(GL_POLYGON);

  for (int i = 0; i < arvore.size() ; i++){

    //Colorindo as partes da árvore
    if(i == LEAFS){
      glColor3f(34.0 / 255, 139.0 / 255 ,34.0 / 255); //Green RGB Color
    }
    else if(i == TREE_TRUNK){
      glColor3f(139.0 / 255, 69.0 / 255, 19.0/ 255); //Brown RGB Color
    }
  
    for (int j = 0; j < arvore[i].cur_mesh.Vertices.size(); j++){
      glVertex3f(arvore[i].cur_mesh.Vertices[j].Position.X, arvore[i].cur_mesh.Vertices[j].Position.Y, arvore[i].cur_mesh.Vertices[j].Position.Z);
      glNormal3f(arvore[i].cur_mesh.Vertices[j].Normal.X, arvore[i].cur_mesh.Vertices[j].Normal.Y, arvore[i].cur_mesh.Vertices[j].Normal.Z);
    }

  }

  glEnd();

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

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

  //now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	gluLookAt(0,Y,10,	0,-30000,0,	0,0,1);

	/****************************
	/ Add your objects from here
	****************************/
	//add objects
  car-=.5;
  Y-=.5;
  sky-=.5;

  for(int i=0,j=0;i<=30;i++,j+=100){
      drawTreeOBJ(-35, j);
  }

  for(int i=0,j=0;i<=30;i++,j+=100){
      drawTreeOBJ(35, j);
  }

  drawCarOBJ();

  drawRoad();
  drawRoadMiddle();

  drawBackground();

  drawHill();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();

}

void animate(){
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization

  //Load Tree
  string path = "Objetos/Tree.obj";
  string obj_name = "Tree";
  load_obj(path, obj_name);

  //Load Car
  path = "Objetos/Car2.obj";
  obj_name = "Car";
  load_obj(path, obj_name);

  for(int i=0; i<= carro.size(); i++){
    printf("Tamanho carro: %d", i);
  }

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

    case GLUT_KEY_F2:		//down arrow key
			printf("Funcionei\n");
      gluLookAt(0,Y,10,-30000,0,0,0,0,1);
		break;

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
      sky+=5;

			break;

		case GLUT_KEY_LEFT:

      if(leftRightMove<15){
        leftRightMove+=5;
        car-=5;
        Y-=5;
        sky-=5;
      }

			break;
		
    case GLUT_KEY_RIGHT:

      if(leftRightMove>-15){
        leftRightMove-=5;
        car-=5;
        Y-=5;
        sky-=5;
      }
			break;

	}

}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 900);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Caio - Fomula 1");

  init();

  glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutSpecialFunc(specialKeyListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;

}
