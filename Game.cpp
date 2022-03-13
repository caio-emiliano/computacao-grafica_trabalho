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
double cloud_position=1200;

int VIEW_MODE = 0;

struct car_meshs{
  objl::Mesh cur_mesh;
};

struct tree_meshs{
  objl::Mesh cur_mesh;
};

struct cloud_meshs{
  objl::Mesh cur_mesh;
};

struct point{
	double x,y,z;
};

vector<car_meshs> carro;
vector<tree_meshs> arvore;
vector<cloud_meshs> nuvem;

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

    if(OBJ_name == "Cloud"){

      cloud_meshs Mesh;
      
      for (int i = 0; i < Loader.LoadedMeshes.size(); i++){
        Mesh.cur_mesh = Loader.LoadedMeshes[i];
        nuvem.push_back(Mesh);
      }

    }

  }

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

    glVertex3f(-2,5000,-30);
    glVertex3f(2,5000,-30);

    glVertex3f(-2,-5000,-30);
    glVertex3f(2,-5000,-30);

    glEnd();

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

void drawCloudOBJ(){

  if(cloud_position == -1200){
    cloud_position = 1200;
  }

  glPushMatrix();

  glTranslatef(cloud_position,sky+150,550);
  glRotatef(90,0,1,0);

  glBegin(GL_POLYGON);

  glColor3f(1, 1, 1);

  for (int i = 0; i < nuvem.size() ; i++){
  
    for (int j = 0; j < nuvem[i].cur_mesh.Vertices.size(); j++){
      glVertex3f(nuvem[i].cur_mesh.Vertices[j].Position.X, nuvem[i].cur_mesh.Vertices[j].Position.Y, nuvem[i].cur_mesh.Vertices[j].Position.Z);
      glNormal3f(nuvem[i].cur_mesh.Vertices[j].Normal.X, nuvem[i].cur_mesh.Vertices[j].Normal.Y, nuvem[i].cur_mesh.Vertices[j].Normal.Z);
    }

  }

  glEnd();

  glPopMatrix();

  cloud_position-=5; 

}

void cameraPosition(){

  //printf("View mode value inside camera position: %d\n", VIEW_MODE);

  if(VIEW_MODE == 0){ //Vista em 3º pessoa
    gluLookAt(leftRightMove,Y,10,	0,-30000,0,	0,0,1);
  }
  else if(VIEW_MODE == 1){ //Vista em 1º pessoa
    double dif = car - Y;
    gluLookAt(leftRightMove,Y+dif,10,	0,-30000,0,	0,0,1);
  }
  else if(VIEW_MODE == 2){ //Vista em 1º pessoa
    double dif = car - Y + 45;
    //printf("Dif: %f", dif);
    gluLookAt(leftRightMove,Y-dif,20,	0,-40000,0,	0,0,1);
  }

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

  cameraPosition();

  car-=.5;
  Y-=.5;
  sky-=.5;

	/****************************
	/ Add your objects from here
	****************************/
	//add objects
  for(int i=0,j=0;i<=45;i++,j+=100){
      drawTreeOBJ(-65, j);
  }

  for(int i=0,j=0;i<=45;i++,j+=100){
      drawTreeOBJ(65, j);
  }

  drawBackground();

  drawCloudOBJ();

  drawCarOBJ();

  drawRoad();
  drawRoadMiddle();

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
  path = "Objetos/Car.obj";
  obj_name = "Car";
  load_obj(path, obj_name);

  //Load Cloud
  path = "Objetos/Cloud.obj";
  obj_name = "Cloud";
  load_obj(path, obj_name);

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
      VIEW_MODE += 1;
      if(VIEW_MODE > 2){
        VIEW_MODE = 0;
      }
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
