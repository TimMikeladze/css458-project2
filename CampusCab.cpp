#include "Angel.h"
#include <stdio.h>
#include <math.h>
#include "textureFileReader.h"

#include "drawBuildings.h"
using namespace std;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

float yRot = 0.0;
float xRot = 0.0;

GLuint texture[1];

void init(void) 
{
    glClearColor (1.0, 1.0, 1.0 , 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    // Initialize shader lighting parameters
    point4 light_position( 0.0, 0.0, 5.0, 0.0 );
    color4 light_ambient( 0.3, 0.3, 0.3, 1.0 );
    color4 light_diffuse( 0.7, 0.7, 0.7, 1.0 );
    color4 light_specular( 0.0, 0.0, 0.0, 1.0 );
	color4 light_global_ambient( 0, 0, 0, 1);

    color4 material_ambient( 1,1,1, 1.0 );
    color4 material_diffuse(  1,1,1, 1.0 );
    color4 material_specular( 0.0, 0.0, 0.0, 1.0 );
    float  material_shininess = 5.0;

	// setting material properties
	//  will be used to set color of the cube
	//  if you want to use more than one color,
	//  then you have to SWITCH FROM ONE COLOR TO THE NEXT
	//  BY EXECUTING THIS CODE IN DISPLAY.
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);


    //////////////////////////////////////

    Image *image1 = loadTexture( "CampusMap.bmp");  
	    // jm  note:   these bit map files work a lot better if the width and height 
	    //               are multiples of 4.  

    if(image1 == NULL){
        printf("Image was not returned from loadTexture\n");
        exit(1);
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Create Texture
    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);



	

	// setting light properties
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);

    glEnable(GL_NORMALIZE);

}

void drawMap() {
   glScalef( 1 , 0.328/0.632, 1);  // to match the image proportions
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[0]);
   glNormal3f(0,1,0);

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-10,0,10);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(-10,0,-10);

   glTexCoord2f(1.0, 1.0);
   glVertex3f(10,0,-10);

   glTexCoord2f(1.0, 0.0);
   glVertex3f(10,0,10);
   glEnd();

   glDisable(GL_TEXTURE_2D);
}


void display(void)
{
   int i;
   int r;
   int closeUp = 0;
   glClear (GL_COLOR_BUFFER_BIT);
   glClear(GL_DEPTH_BUFFER_BIT);


   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glRotatef(xRot, 1,0,0);  //x
   glRotatef(yRot, 0,1,0);  // y

   if (!closeUp) {
       drawMap();
   }

   drawBuilding0(closeUp);

   glFlush ();

}



void myspecialkey(int key, int mousex, int mousey)
{

    if(key == 100) {  // left
        yRot -= 1;
        if (yRot < -360.0 ) {
	        yRot += 360.0;
	    }
	}
    if(key == 102) {
        yRot += 1;
        if (yRot > 360.0 ) {
	        yRot -= 360.0;
	    }
	}
    if(key == 101) {  // up
        xRot += -1;
        if (xRot < -360.0 ) {
	        xRot += 360.0;
	    }
	}
    if(key == 103) {
        xRot += 1;
        if (xRot > 360.0 ) {
	        xRot -= 360.0;
	    }
	}

    glutPostRedisplay();
}




void reshape (int width, int height)
{

    
   glViewport (0, 0, (GLsizei) width, (GLsizei) height); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
  // glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glOrtho (-11, 11, -11, 11, -20, 20);
   glMatrixMode (GL_MODELVIEW);

}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Debugging");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(myspecialkey);
   glutMainLoop();
   return 0;
}