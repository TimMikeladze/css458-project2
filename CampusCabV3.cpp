#include "Angel.h"
#include <stdio.h>
#include <math.h>
#include "textureFileReader.h"

#include "drawBuildings.h"
using namespace std;

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

void animate();

#define CAB_SPEED 0.01
#define CAB_ROTATE 1
#define NECK_LIFT 0.1
#define NEAR_SPEED 0.1
#define ZOOM_SPEED 0.1

float frustumXY = 0.167;
float frustumNear = 0.25;

float eyeX = -9.46823, eyeY = 0.25, eyeZ = -0.576953, atX = 11.1201, atY = 0.25,
		atZ = 0.489;

int perspective = 1;

GLuint texture[1];

GLfloat u;

GLint nCtrlPts;

class wcPt3D {
public:
	GLfloat x, y, z;
};

wcPt3D ctrlPts[] =
		{ { -8.86803, .05, -0.427709 }, { -7.61702, .05, -0.452285 }, {-5.55406, 0.25, -0.413929}};
GLint *C;

/*  Compute binomial coefficients C for given value of n.  */
void binomialCoeffs(GLint n, GLint * C) {
	GLint k, j;

	for (k = 0; k <= n; k++) {
		/*  Compute n!/(k!(n - k)!).  */
		C[k] = 1;
		for (j = n; j >= k + 1; j--)
			C[k] *= j;
		for (j = n - k; j >= 2; j--)
			C[k] /= j;

		printf("%d ", C[k]);
	}
	printf("\n");
}

void computeBezPt(GLfloat u, wcPt3D * bezPt, GLint nCtrlPts, wcPt3D * ctrlPts,
		GLint * C) {
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn;

	bezPt->x = bezPt->y = bezPt->z = 0.0;

	/*  Compute blending functions and blend control points. */
	for (k = 0; k < nCtrlPts; k++) {
		bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
		bezPt->x += ctrlPts[k].x * bezBlendFcn;
		bezPt->y += ctrlPts[k].y * bezBlendFcn;
		bezPt->z += ctrlPts[k].z * bezBlendFcn;
	}
}

void drawCar() {
	float numColors = 256;
	float car_colors[] = { 0 / numColors, 100 / numColors, 0 / numColors };
	float tire_color[] = { .1, .1, .1 };
	float window_color[] = { 135 / numColors, 206 / numColors, 250 / numColors };

	glPushAttrib(GL_COLOR_MATERIAL);

	//main body of car
	glMaterialfv(GL_FRONT, GL_DIFFUSE, car_colors);
	glMaterialfv(GL_FRONT, GL_AMBIENT, car_colors);
	glPushMatrix();
	glScalef(1, .3, .5);
	glutSolidCube(1);
	glPopMatrix();

	//cab
	glPushMatrix();
	glTranslatef(0, .25, 0);
	glScalef(.5, .25, .3);
	glutSolidCube(1);
	glPopMatrix();
	glPopAttrib();

	//windows
	glMaterialfv(GL_FRONT, GL_DIFFUSE, window_color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, window_color);
	glPushMatrix();
	glTranslatef(0, .25, .15);
	glScalef(.45, .2, .01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, .25, -.15);
	glScalef(.45, .2, .01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.25, .25, 0);
	glScalef(.01, .2, .2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.25, .25, 0);
	glScalef(.01, .2, .2);
	glutSolidCube(1);
	glPopMatrix();

	//tires
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tire_color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, tire_color);
	glPushMatrix();
	glTranslatef(-.35, -.1, -.6 / 2);
	glScalef(.1, .1, .6);
	glutSolidCylinder(1, 1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.35, -.1, -.6 / 2);
	glScalef(.1, .1, .6);
	glutSolidCylinder(1, 1, 20, 20);
	glPopMatrix();

	glPopAttrib();

}

void init(void) {
	nCtrlPts = sizeof(ctrlPts) / sizeof(*ctrlPts);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	// Initialize shader lighting parameters
	point4 light_position(0.0, 0.0, 5.0, 0.0);
	color4 light_ambient(0.3, 0.3, 0.3, 1.0);
	color4 light_diffuse(0.7, 0.7, 0.7, 1.0);
	color4 light_specular(0.0, 0.0, 0.0, 1.0);
	color4 light_global_ambient(0, 0, 0, 1);

	color4 material_ambient(1, 1, 1, 1.0);
	color4 material_diffuse(1, 1, 1, 1.0);
	color4 material_specular(0.0, 0.0, 0.0, 1.0);
	float material_shininess = 5.0;

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

	Image *image1 = loadTexture("CampusMap.bmp");
	// jm  note:   these bit map files work a lot better if the width and height
	//               are multiples of 4.

	if (image1 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(1);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Create Texture
	glGenTextures(1, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image1->data);
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

	C = new GLint[nCtrlPts];
	binomialCoeffs(nCtrlPts - 1, C);

}

void drawMap() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glNormal3f(0, 1, 0);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10, 0, 5);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-10, 0, -5);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(10, 0, -5);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(10, 0, 5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void display(void) {
	int i;
	int r;
	int closeUp = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

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

	animate();
}

void animate() {
	wcPt3D bezCurvePt;

	computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);

	glPushMatrix();

	glTranslatef(bezCurvePt.x, bezCurvePt.y, bezCurvePt.z);
	glScalef(.2, .2, .2);
	//glRotatef(45, 0, 1, 0);
	drawCar();
	glPopMatrix();

	glutSwapBuffers();

	glLoadIdentity();

	//gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, 0.0, 1.0, 0.0);
	gluLookAt(bezCurvePt.x - 1, bezCurvePt.y + 0.25, bezCurvePt.z, 0, 0, 0, 0, 1, 0);
}

float slowFactor = 10.0;
float angInc = 4; //2*3.14159/360;
float angle = 0;

void initParams() {
	angle = 0;
	u = 0;
}

void idle() {
	angle += angInc * slowFactor;
	if (u > 1) {
		initParams();
	} else {
		//x += 0.005*slowFactor;
		//y += 0.0005*slowFactor;
		u += 0.004 * slowFactor;
	}

	glutPostRedisplay();
}

void myspecialkey(int key, int mousex, int mousey) {

	if (key == 100) { // left
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
	if (key == 102) { // right
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
	if (key == 101) { // up
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
	if (key == 103) { // down
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
	std::cout << " eyeX = ";
	std::cout << eyeX;
	std::cout << ", eyeY = ";
	std::cout << eyeY;
	std::cout << ", eyeZ = ";
	std::cout << eyeZ;
	std::cout << " , atX = ";
	std::cout << atX;
	std::cout << " , atY = ";
	std::cout << atY;
	std::cout << " , atZ = ";
	std::cout << atZ;

	std::cout << "\n\n";

	glutPostRedisplay();
}

void setProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (perspective) {
		glFrustum(-frustumXY, frustumXY, -frustumXY, frustumXY, frustumNear,
				20.0);
	} else {
		float orthoXY = 20 * frustumXY / frustumNear;
		glOrtho(-orthoXY, orthoXY, -orthoXY, orthoXY, frustumNear, 20.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	setProjection();
}

void keyboard(unsigned char key, int x, int y) {
	float dirX, dirY, dirZ, length;

	switch (key) {
	case 27: // escape key
		exit(0);
		break;
	case 112: // perspective on/off
		/*   perspective doesn't yet work.  Maybe CampusCabV3?
		 perspective = ! perspective;
		 setProjection();
		 glutPostRedisplay();
		 */
		break;

	case 110: // 'n' = near
		//frustumNear += NEAR_SPEED;
		frustumXY = (1 - ZOOM_SPEED) * frustumXY;
		setProjection();
		glutPostRedisplay();
		break;
	case 98: // 'b' = back (reverse of near)
		//frustumNear -= NEAR_SPEED;
		frustumXY = (1 + ZOOM_SPEED) * frustumXY;
		setProjection();
		glutPostRedisplay();
		break;

	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Debugging");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(myspecialkey);
	glutMainLoop();
	return 0;
}
