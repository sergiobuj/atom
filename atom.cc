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
#include "lib/textureloader.h"

using namespace std;

string model;
bohr Bohr;
rutherford Rutherford ;
thompson Thompson;
schrodinger Schrodinger;
unsigned int textura;
void init()
{
  glClearColor(0, 0, 0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
	
  /* model for light */
  
  GLfloat light_position[] = { 0, 0, 0, 1.0 }; 
  glLightfv(GL_LIGHT0, GL_POSITION, light_position); /* set the position of GL_LIGHT0 */
  GLfloat spot_direction[] = { 0, 1, 1 , 1 }; /* direction is specified in homogenous coordinates */
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction); /* set the direction of GL_LIGHT0 */
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 360); /* set the cutoff angle */
  
  gfloat amb[] = { 0.5f, 0.5f, 0.5f, 1.0f };	// Ambient Light Values
  gfloat dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };

  glLightfv(GL_LIGHT0, GL_AMBIENT, amb );
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif );

  //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
  //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
  //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
  //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  /* end light */
  
  /* Load the atomic model */
  reader Reader;
  model = Reader.tipo();
  if( model == "bohr")
    Bohr = bohr(Reader.num());
  else if (model == "rutherford")
    Rutherford = rutherford(Reader.num());
  else if ( model == "thompson")
    Thompson = thompson(Reader.num());
  else if ( model == "schrodinger")
    Schrodinger = schrodinger(Reader.num());
  /* end load atomic*/
    Image *image1;
    
// allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }
    char path[]={'B','M','P','/','e','l','e','c','t','r','o','n','.','b','m','p'};
    if (!ImageLoad(path, image1)) {
	exit(1);
    }        
    
    // Create Texture	
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);  

}


void display()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0,0.1,0.1,0,0,0,0,0.1,0);
  if( model == "bohr")
    Bohr.draw(textura);
  else if (model == "rutherford")
    Rutherford.draw(textura);
  else if( model == "thompson")
    Thompson.draw(textura);
  else if ( model == "schrodinger")
    Schrodinger.draw(textura);
  glutSwapBuffers();	
}

void reshape(int W, int H)
/*           largo  ancho */
{
	
}


void keyboard(unsigned char key, int a , int b)
{
}
int main(int argc, char** argv)
{
  srand(time(NULL));
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (600, 600);
  glutCreateWindow(argv[0]);
	
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(&display);
  glutIdleFunc(display);
	
  glutKeyboardFunc (keyboard);
  
  glutMainLoop();
  
  return 0; 
}
