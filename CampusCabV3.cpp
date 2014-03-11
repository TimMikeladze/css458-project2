#include "Angel.h"
#include <stdio.h>
#include <math.h>
#include "textureFileReader.h"

#include "drawBuildings.h"
using namespace std;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

#define CAB_SPEED 0.01
#define CAB_ROTATE 1
#define NECK_LIFT 0.1
#define NEAR_SPEED 0.1
#define ZOOM_SPEED 0.1

float frustumXY = 0.167;
float frustumNear = 0.25;

float  eyeX = 0, eyeY = 0.25, eyeZ = 5,
       atX = 0, atY = 0.25, atZ = 0;

int perspective = 1;
      

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
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[0]);
   glNormal3f(0,1,0);

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-10,0,5);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(-10,0,-5);

   glTexCoord2f(1.0, 1.0);
   glVertex3f(10,0,-5);

   glTexCoord2f(1.0, 0.0);
   glVertex3f(10,0,5);
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
   gluLookAt (eyeX, eyeY, eyeZ, 
              atX, atY, atZ, 
              0.0, 1.0, 0.0);

   if (!closeUp) {
       drawMap();
   }
   
   glPushMatrix();
   drawBuilding0(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding1(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding2(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding3(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding4(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding5(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding6(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding7(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding9(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding10(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding11(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding12(closeUp);
   glPopMatrix();
   
   glPushMatrix();
   drawBuilding13(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding14(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding15(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding16(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding17(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding18(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding19(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding20(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding21(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding22(closeUp);
   glPopMatrix();
   
   glPushMatrix();
   drawBuilding23(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding24(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding25(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding26(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding28(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding29(closeUp);
   glPopMatrix();

   glPushMatrix();
   drawBuilding30(closeUp);
   glPopMatrix();
   
   glutSwapBuffers();

}



void myspecialkey(int key, int mousex, int mousey)
{

    if(key == 100) {  // left
         {
         vec4 v(atX - eyeX, atY - eyeY, atZ - eyeZ, 0);
         // move both camera location and look-at point in the same direction (forward)
         mat4 rotMat = RotateY(CAB_ROTATE);
         v = rotMat * v;
         atX = eyeX + v.x;
         atY = eyeY + v.y;
         atZ = eyeZ + v.z;

         glutPostRedisplay();
         }
	}
    if(key == 102) {  // right
         {
         vec4 v(atX - eyeX, atY - eyeY, atZ - eyeZ, 0);
         // move both camera location and look-at point in the same direction (forward)
         mat4 rotMat = RotateY(-CAB_ROTATE);
         v = rotMat * v;     
         atX = eyeX + v.x;
         atY = eyeY + v.y;
         atZ = eyeZ + v.z;

         glutPostRedisplay();
         }
	}
    if(key == 101) {  // up
         {
             if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
                 atY = atY + NECK_LIFT;
                 glutPostRedisplay();
             } else {
                 vec4 v(atX - eyeX, atY - eyeY, atZ - eyeZ, 0);
                 // move both camera location and look-at point in the same direction (forward)
                 v = v * CAB_SPEED;  
                 atX += v.x;
                 atZ += v.z;
                 eyeX += v.x;
                 eyeZ += v.z;

                 glutPostRedisplay();
             }
         }

	}
    if(key == 103) { // down
         {
             if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
                 atY = atY - NECK_LIFT;
                 glutPostRedisplay();
             } else {
                 vec4 v(atX - eyeX, atY - eyeY, atZ - eyeZ, 0);
                 // move both camera location and look-at point in the same direction (forward)
                 v = v * CAB_SPEED;  
                 atX -= v.x;
                 atZ -= v.z;
                 eyeX -= v.x;
                 eyeZ -= v.z;
                 glutPostRedisplay();
             }
         } 
	}

    glutPostRedisplay();
}

void setProjection() {
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if (perspective) {
       glFrustum (-frustumXY,  frustumXY, -frustumXY , frustumXY, frustumNear, 20.0);
   } else {
       float orthoXY = 20 * frustumXY / frustumNear; 
       glOrtho (-orthoXY, orthoXY, -orthoXY, orthoXY,             frustumNear, 20.0);
   }
   glMatrixMode (GL_MODELVIEW);
}

void reshape (int width, int height)
{
   glViewport (0, 0, (GLsizei) width, (GLsizei) height); 
   setProjection();
}

void keyboard(unsigned char key, int x, int y)
{
   float dirX, dirY, dirZ, length;

   switch (key) {
      case 27:  // escape key
         exit(0);
         break;
      case 112:  // perspective on/off
          /*   perspective doesn't yet work.  Maybe CampusCabV3?
         perspective = ! perspective;
         setProjection();
         glutPostRedisplay();
         */
         break;
          
      case 110:  // 'n' = near 
         //frustumNear += NEAR_SPEED;
         frustumXY = (1-ZOOM_SPEED) * frustumXY;
         setProjection();
         glutPostRedisplay();
         break;
      case 98:   // 'b' = back (reverse of near)
         //frustumNear -= NEAR_SPEED; 
         frustumXY = (1+ZOOM_SPEED) * frustumXY;
         setProjection();
         glutPostRedisplay();
         break;
      
   }
}

int main(int argc, char** argv)
{

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (700, 700); 
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