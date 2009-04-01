
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#endif

/* 
   Sebastian Arcila Valenzuela & Sergio Botero Uribe
   sebastianarcila@gmail.com sergiobuj@gmail.com
   2009-1
*/
#include <string>
#include "models/bohr.h"
#include "models/rutherford.h"
#include "models/thompson.h"
#include "models/schrodinger.h"
#include "lib/reader.h"
using namespace std;

string model;
bohr Bohr;
rutherford Rutherford ;

//tocao
gfloat eyex=0.0,eyey=0.1,eyez=0.1,cenx=0.0,ceny=0.0,cenz=0.0,th=0.0,ph=0.0;
const gfloat upx=0.0,upy=0.1,upz=0.0;
int keyup=2,keydown=4,keyleft=8,keyright=16,mov=0;;

//endtocao


void init()
{
  glClearColor(0, 0, 0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
	
  /* model for light */

  gfloat a[] = { 1.0, 0.0, 0.0, 0.0 };
  gfloat d[] = { 1.0, 0.0, 0.0, 0.0 };
  gfloat p[] = { 1.0, 0.0, 0.0, 0.0 };
  gfloat lma[] = { 0.4, 0.4, 0.4, 1.0 };
  gfloat lv[] = { 0.0 };
  
  reader Reader;
  model = Reader.tipo();
  if( model == "bohr")
    Bohr = bohr(Reader.num());
  else if (model == "rutherford")
    Rutherford = rutherford(Reader.num());
  
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  //tocao
  gluLookAt(0.0,0.1,0.1,0.0,0.0,0.0,0.0,0.1,0.0);
  //endtocao
  
  if( model == "bohr")
    Bohr.draw();
  else if (model == "rutherford")
    Rutherford.draw();
  glutSwapBuffers();	
}

void reshape(int W, int H)
/*           largo  ancho */
{
	
}

void moveCam(int dirs){
  //  glLoadIdentity();
  if((dirs&(1<<1)) || (dirs&(1<<2)))
    th = fmod( th + ((dirs&(1<<1)==2)? 5.0:-5.0)+360.0 ,360);
  if( (dirs&(1<<3)) || (dirs&(1<<4)))
    ph = fmod( ph + ((dirs&(1<<3)==8)? 5.0:-5.0)+180.0 ,180);
  gluLookAt(cos(ph)*sin(th),sin(th)*sin(ph),cos(th),cenx,ceny,cenz,upx,upy,upz);
  printf("eyex=%f eyey=%f eyez=%f centx=%f ceny=%f cenz=%f upx=%f upy=%f upz=%f\n",cos(ph)*sin(th),sin(th)*sin(ph),cos(th),cenx,ceny,cenz,upx,upy,upz);
  mov=0;
}



void keyboard(int key, int a , int b)
{

  if(key == GLUT_KEY_UP)
    mov|=keyup;
  if(key == GLUT_KEY_DOWN)
    mov|=keydown;
  if(key == GLUT_KEY_LEFT)
    mov|=keyleft;
  if(key == GLUT_KEY_RIGHT)
    mov|=keyright;
  moveCam(mov);
}   

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (600, 600);
  glutCreateWindow(argv[0]);
	
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(&display);
  glutIdleFunc(display);
  
  
  glutSpecialFunc(keyboard);
  
  glutMainLoop();
  
  return 0; 
}
