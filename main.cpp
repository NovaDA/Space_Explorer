//Windows includes - DO NOT EDIT AS LOTS OF INTERDEPENDENCE
#include <math.h>						
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>	//Needed for console output (debugging)
#include "GLee.h"
#include <gl/freeglut.h>
#include <iostream>

#ifdef WIN32
#include "gltools.h"
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include "glm.h"

#endif

#pragma region My Personal Headers

#include "camera.h"
#include "AndromedaSystem.h"
#include "Crystal.h"
#include "Hoop.h"
#include "Planet.h"
#include "Satellite.h"
#include "Rings.h"
#include "Barrier.h"
#include "Atmosphere.h"
#include "CollisionManager.h"

#pragma endregion

#pragma region declerations
//note that this needs gltools.h and gltools.cpp to be included in the shared directory
void resetPerspectiveProjection();
void drawRotationAndPosition(GLfloat scale);
void setOrthographicProjection();
void ChangeSize(int w, int h);
void RenderScene(void);
void TimerFunc(int value);
void renderCrystals(void);
void renderHoops(void);
void renderSatellites(void);
void renderAtmospheres(void);

int Wwidth;
int Wheight;
//used for the framerate
int frame = 0, timeTot = 0, timebase = 0;
char frameRate[12];
char angleShipRotation[12];
char cameraPositionX[12];
char cameraPositionY[12];
char cameraPositionZ[12];

Camera camera;
GLfloat shipRotation_X = 0.0;
GLfloat shipRotation_Y = 0.0;
GLfloat shipRotation_Z = 0.0;
vectorXYZ positionCamera;
bool collisionDetection = false;
GLfloat hoop_0_rotation = 0.0;
bool HUD_ON_OFF = false;

GLfloat cameraX, cameraY,cameraZ;
bool camera1Active = false;
bool camera2Active = false;
vectorXYZ cameraPosition;

CollisionManager collision_Checker;
Crystal crystal_0(-50.0, 0.0, 50.0);
Crystal crystal_1(-50.0, 0.0, -20.0);
Crystal crystal_2(100.0, 0.0, -40.0);
Crystal crystal_3(80.0, 20.0, -60.0);
Crystal crystal_4(-30.0, 0.0, -80.0);
Crystal crystal_5(100.0, 0.0, -100.0);

Hoop hoop_0(crystal_0.getPosition(),5);
Hoop hoop_1(crystal_1.getPosition(),5);
Hoop hoop_2(crystal_2.getPosition(),5);
Hoop hoop_3(crystal_3.getPosition(),5);
Hoop hoop_4(crystal_4.getPosition(),5);
Hoop hoop_5(crystal_5.getPosition(),5);

Satellite hoop_0_satellite(crystal_0.getPosition(), 10.0);
Satellite hoop_1_satellite(crystal_1.getPosition(), 15.0);
Satellite hoop_2_satellite(crystal_2.getPosition(), 20.0);
Satellite hoop_3_satellite(crystal_3.getPosition(), 25.0);
Satellite hoop_4_satellite(crystal_4.getPosition(), 30.0);
Satellite hoop_5_satellite(crystal_5.getPosition(), 35.0);

Atmosphere atmosphere_0(0.0, 500.0, 0.0, 100.0, "Jupiter", 0.0, 0.0, 0.0, 0.2,false); // atmosphere created using image of Jupiter
Atmosphere atmosphere_1(-500.0, 500.0f, 500.0, 100.0, "Mercury", 0.0, 0.0, 0.0, 0.5,true);
Atmosphere atmosphere_2(0.0, 0.0, -1300.0, 500.0, "Venus", 0.0, 0.0, 0.0, 0.9,true);
Atmosphere atmosphere_3(-1000.0, -500.0, 1300.0, 300.0, "Uranus", 0.0, 0.0, 0.0, 0.2,true);
Atmosphere atmosphere_4(-1500.0, 0.0, 0.0, 350.0, "null", 0.5, 0.0, 0.0, 0.4,false); /// <= atmosphere of neptune
Atmosphere atmosphere_5(1500.0, 0.0, 0.0, 830.0, "null", 0.5, 0.6, 0.0, 0.3,false);/// <= atmosphere of Jupiter
Atmosphere atmosphere_6(0.0, 0.0, -1300.0, 520.0, "null", 0.5, 0.6, 0.0, 0.3, true);
Atmosphere atmosphere_7(0.0, 0.0, -1300.0, 540.0, "null", 0.5, 0.4, 0.0, 0.2, true);
Atmosphere atmosphere_8(0.0, 0.0, -1300.0, 560.0, "null", 0.5, 0.3, 0.0, 0.2, true);

Barrier barrier_0(0.0,500.0,0.0,100.0);
Barrier barrier_1(-1500.0, 0.0, 0.0, 360.0);  //// barriers are wiredsphere i like to rate a kind of barrier  
											  /// mixing a colored sphere with alpha channel applied and wiresphere to create a shield/barrier

Rings ring_0(-1000.0, -500.0, 1300.0, 50.0, 200.0, 2);
Rings ring_1(0.0, 0.0, -1300.0, 150.0, 600.0, 3);

Planet planet_1(-1500.0, 0.0, 0.0, "Neptune", 300.0);
Planet planet_0(1500.0, 0.0, 0.0, "Jupiter", 800.0);
Planet spaceSystem(0.0, 0.0, 0.0, "Space", 2500.0);


Atmosphere atmospheresPositions[9] =
{
	atmosphere_0,atmosphere_1,
	atmosphere_2,atmosphere_3,
	atmosphere_4,atmosphere_5,
	atmosphere_6,atmosphere_7,
	atmosphere_8
};

vectorXYZ crystalsPosition[6] =
{
	crystal_0.getPosition(),crystal_1.getPosition(),
	crystal_2.getPosition(),crystal_3.getPosition(),
	crystal_4.getPosition(),crystal_5.getPosition()
};

bool crystalActivated[6]
{
	false,false,false,
	false,false,false
};

Crystal Crystals[6] = 
{
	crystal_0,crystal_1,crystal_2,crystal_3,crystal_4,crystal_5,
};

Hoop Hoops[6] =
{
	hoop_0,hoop_1,hoop_2,hoop_3,hoop_4,hoop_5
};

Satellite Satellites[6]
{
	hoop_0_satellite,hoop_1_satellite,
	hoop_2_satellite,hoop_3_satellite,
	hoop_4_satellite,hoop_5_satellite

};

int num_Crystals = sizeof(crystalsPosition) / sizeof(vectorXYZ);
int num_Atmospheres = sizeof(atmospheresPositions) / sizeof(Atmosphere);

bool timerON = false;
GLfloat timer = 5.0f;
GLint crystalPassed = 0;

int num_elements;  /// USED IN ARRAY TO FIND NUMBER OF ELEMNTS IN IT

float rotationSphere = 0.0;
GLint iWidth, iHeight, iComponents;
GLenum eFormat;
// this is a pointer to memory where the image bytes will be held 
GLbyte *pBytes0;
#pragma endregion


#pragma region ColorLight 

GLfloat mKa[4] = { 0.11f,0.11f,0.11f,1.0f }; //ambient
GLfloat mKd[4] = { 0.43f,0.43f,0.43f,1.0f }; //diffuse
GLfloat mKs[4] = { 1.0f,1.0f,1.0f,1.0f }; //specular
GLfloat mKe[4] = { 0.5f,0.5f,0.0f,1.0f }; //emission

GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat no_mat2[] = { 0.0f, 0.0f, 0.0f, 0.5f };
GLfloat  mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat  mat_ambient_color[] = { 0.8f, 0.8f, 0.2f, 1.0f };
GLfloat  mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
GLfloat  mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  no_shininess[] = { 0.0f };
GLfloat  low_shininess[] = { 5.0f };
GLfloat  high_shininess[] = { 100.0f };
GLfloat  mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };
GLfloat  mat_emission2[] = { 0.5f, 0.2f, 0.2f, 0.0f };
GLfloat  black_ambient[] = { 0.0,0.0,0.0,0.0 };
//spot position and direction
GLfloat	 lightPos[] = { 0.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir[] = { 50.0, 25.0, 0.0 };

GLfloat	 lightPos2[] = { 50.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir2[] = { 50.0, 15.0, 0.0 };

GLfloat	 lightPos3[] = { -50.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir3[] = { 50.0, 15.0, 0.0 };


// Useful lighting colour values
GLfloat  whiteLightBright[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat  greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat  blueLight[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat  whiteLightLessBright[] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat  redLight2[] = { 1.0f, 0.0f, 0.0f, 0.5f };

GLfloat  crystal0pos[] = { -50.0, 0.0,0.0, 0.5f };          ////   wanted to set light in crystal positions


#pragma endregion

#pragma region change projection function
// orthographics projection 2D overlay
void setOrthographicProjection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, Wwidth, 0, Wheight);
	glScalef(1, -1, 1);
	glTranslatef(0, -Wheight, 0);
	glMatrixMode(GL_MODELVIEW);
}
//back to the last projection
void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void displayText(float x, float y, int r, int g, int b, const char *string, bool stroke) {
	int j = strlen(string);

	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		if (stroke) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);
		}
		else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
		}

	}
}

void drawRotationAndPosition(GLfloat scale) {

	glPushMatrix();
	glTranslatef(Wwidth / 2 - Wwidth / 20, Wheight / 5, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	sprintf_s(angleShipRotation, "Angle:%3.0f", shipRotation_Z);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(scale, scale, scale);
	displayText(500, 100, 1, 1, 1, angleShipRotation, true);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(Wwidth / 2 - Wwidth / 20, Wheight / 4, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	sprintf_s(cameraPositionX, "X_POS:%3.0f", positionCamera.x);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(scale, scale, scale);
	displayText(500, 100, 1, 1, 1, cameraPositionX, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(Wwidth / 2 - Wwidth / 20, Wheight / 3.5, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	sprintf_s(cameraPositionY, "Y_POS:%3.0f", positionCamera.y);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(scale, scale, scale);
	displayText(500, 100, 1, 1, 1, cameraPositionY, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(Wwidth / 2 - Wwidth / 20, Wheight / 3, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	sprintf_s(cameraPositionZ, "Z_POS:%3.0f", positionCamera.z);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(scale, scale, scale);
	displayText(500, 100, 1, 1, 1, cameraPositionZ, true);
	glPopMatrix();

}

#pragma endregion

#pragma region Drawing functions
void renderCrystals()
{

	for (int i = 0; i < num_Crystals; i++)
	{

		glPushMatrix();
		if (crystalActivated[i] == false)                     /// logic to make the crystals be rendered in red color 
		{													  /// but after the first the first crystal is collected			
			if (crystalActivated[i - 1] == true)			 //  next will be green
			{
				glColor4f(0.0, 1.0, 0.0, 0.5);
			}
			else
			{
				glColor4f(1.0, 0.0, 0.0, 0.5);
			}

			glDisable(GL_LIGHT0);                              // modifying light so the shineness doesn't look too white on the transparent red crystal
			glEnable(GL_LIGHT3);
			glMateriali(GL_FRONT, GL_SHININESS, 5);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			Crystals[i].Render();
			glDisable(GL_BLEND);
			glDisable(GL_LIGHT3);
			glEnable(GL_LIGHT0);          //// controls global light
			glPopMatrix();

		}

		//glMateriali(GL_FRONT, GL_SHININESS, 128);
	}

}
void renderAtmospheres()
{
	for (int i = 0; i < num_Atmospheres; i++)
	{
		glPushMatrix();
		atmospheresPositions[i].Render();
		glPopMatrix();
	}

}
void renderHoops()
{
	for (int i = 0; i < num_Crystals; i++)
	{
		glPushMatrix();

		Satellites[i].Render();

		glPopMatrix();
	}
}
void renderSatellites()
{
	for (int i = 0; i < num_Crystals; i++)
	{
		glPushMatrix();

		Hoops[i].Render();

		glPopMatrix();
	}
}
void drawHUD(int image)
{
	glEnable(GL_BLEND);
	glColor4f(0.8, 0.8, 0.8, 0.4);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	//bind the texture
	glBindTexture(GL_TEXTURE_2D, textures[image]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0);//repeated texture
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(Wwidth, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(Wwidth, Wheight, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(0.0, Wheight, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void init() {
	//glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
#pragma endregion

#pragma region Render Scene
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);


	glRotatef(shipRotation_X, 1.0, 0.0, 0.0);               ///   rotating the entire scene around an axes
	glRotatef(shipRotation_Y, 0.0, 1.0, 0.0);
	glRotatef(shipRotation_Z, 0.0, 0.0, 1.0);
	
	//glTranslatef(cameraX, 0.0, 0.0);                     /// old implementation of the camera translation, moving forward and back
	//glTranslatef(0.0, cameraY, 0.0);
	//glTranslatef(0.0, 0.0, cameraZ);
	
	camera.Render();									//// more advanced camera that let me rotate 3D
	
	glPushMatrix();

	glRotatef(90.0, 1.0, 0.0, 0.0);
	glDisable(GL_LIGHTING);
	planet_0.Render();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glDisable(GL_LIGHTING);
	planet_1.Render();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	barrier_0.Render();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	barrier_1.Render();
	glPopMatrix();

	glPushMatrix();
	ring_0.Render();
	glPopMatrix();

	glPushMatrix();                        ////// DRAWING SPACE AREA 
	glDisable(GL_LIGHTING);					///// not drawing the space last because i want to be able to see it through teh crystals
	glRotatef(90, 1.0, 0.0, 0.0);
	spaceSystem.Render();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	renderAtmospheres();    /////  render the atmospheres i set this position because i like the orange color that leave behind when the last atmosphere is set

	glPushMatrix();
	ring_1.Render();
	glPopMatrix();

	if (timer > 0.0f)     /////////  drawing crystals at the end because i want to see other 
	{					  ////////   objects through the crystals and hoops order matter for transparancy
		renderCrystals();
		renderHoops();
		renderSatellites();
	}
  
/// Elements Drawn Before HUD
		
		//draw the 2D overlay
		glPushMatrix();
		glLoadIdentity();
		setOrthographicProjection();                        /// calling the 2D overlay for the hud in ortographic projection

		if (HUD_ON_OFF == true)
		{
			drawRotationAndPosition(0.2f);
			drawHUD(HUD);
		}
		
		glPopMatrix();
		
	resetPerspectiveProjection();
	glutSwapBuffers();
}
#pragma endregion

#pragma region setupRC
void SetupRC()
{
	//textures
	GLuint texture;
	glGenTextures(1, &texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Load textures in a for loop
	glGenTextures(TEXTURE_COUNT, textures);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	for (int iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[iLoop]);
		pBytes0 = gltLoadTGA(textureFiles[iLoop], &iWidth, &iHeight,
			&iComponents, &eFormat);

		glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
		free(pBytes0);
	}

	//enable textures
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal   
	glFrontFace(GL_CCW);// Counter clock-wise polygons face out

	glEnable(GL_LIGHTING);
	glEnable(GL_POINT_SMOOTH);
	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLightBright);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLightBright);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mKs);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, redLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, redLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_SPECULAR, redLight);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f);
	//glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, whiteLightBright);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, mKs);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0f);
	//glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT3, GL_AMBIENT, redLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, whiteLightBright);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT3, GL_SPECULAR, whiteLightBright);
	glLightfv(GL_LIGHT3, GL_EMISSION, redLight);
	//glEnable(GL_LIGHT3);

	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mKs);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Black blue background clear colour
	glClearColor(0.0f, 0.0f, 0.03f, 1.0f);
}
#pragma endregion

#pragma region projection setup
void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	Wwidth = w;
	Wheight = h;
	// Prevent a divide by zero
	if (h == 0)
		h = 1;
	//need this for changing projection

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Calculate aspect ratio of the window
	fAspect = (GLfloat)w / (GLfloat)h;
	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// field of view of 45 degrees, near and far planes 1.0 and 3500
	gluPerspective(60.0f, fAspect, 1.0, 3500.0);
	glMatrixMode(GL_MODELVIEW);

}
#pragma endregion
#pragma region time Functions
void TimerFunc(int value)
{

	for (int i = 0; i < num_Crystals; i++)   /// to make the crystals and hoops disappear from the scene
	{
		if (crystalActivated[i] == true)
		{

			crystalPassed++;
		}
		if (crystalPassed == 6)
		{
			timerON = true;
		}
	}
	crystalPassed = 0;

    
	////////////////////// Updating elements in the Scene
	for (int i = 0; i < num_Crystals; i++)
	{
		Crystals[i].Update();
	}

	for (int i = 0; i < num_Crystals; i++){Hoops[i].Update();}

	for (int i = 0; i < num_Crystals; i++){ Satellites[i].Update();} //// for satellite

	for (int i = 0; i < num_Crystals; i++){
		vectorXYZ updatedPositions = Satellites[i].UpdatePosition();
		Satellites[i].setPosition(updatedPositions);	//Satellites[i].Update();  /// <=== was used to find collision with the hoops as satellites rotates in them
	}

	for (int i = 0; i < num_Atmospheres; i++) {atmospheresPositions[i].Update();}
	

	positionCamera = camera.getPlayerLocation();           // USED TO GET THE CURRENT LOCATION OF THE PLAYER/CAMERA FOR COLLISIONS CHECKS
	for (int i = 0; i < num_Crystals; i++)
	{
		collisionDetection = collision_Checker.collisionDetection(positionCamera, crystalsPosition[i], 0.5, 1.0);
		if (collisionDetection == true)
		{
			crystalActivated[i] = true;
		}
	}

	hoop_0_rotation += 0.2;
	planet_0.Update();
	planet_1.Update();

	ring_0.Update();
	ring_1.Update();

	barrier_0.Update();
	barrier_1.Update();

	glutPostRedisplay();
	glutTimerFunc(25, TimerFunc, 1);
}  /// timer
void timerCrystals(int value)
{
	if (timerON == true)
	{
		timer -= 1.0f;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, timerCrystals, 0);
}
#pragma endregion

#pragma region key handling
void KeyDown(unsigned char key, int x, int y)
{
	
		switch (key)
		{
		case 27:		//ESC
			PostQuitMessage(0);
			break;
		case 'q':
			camera.RotateY(5.0);
			glutPostRedisplay();
			break;
		case 'e':
			camera.RotateY(-5.0);
			glutPostRedisplay();
			break;
		case 'w':
			camera.MoveForwards(-1.0);
			glutPostRedisplay();
			break;
		case 's':
			camera.MoveForwards(1.0);
			glutPostRedisplay();
			break;
		case 'r':
			camera.RotateX(5.0);
			glutPostRedisplay();
			break;
		case 't':
			camera.RotateX(-5.0);
			glutPostRedisplay();
			break;
		case 'a':
			camera.StrafeRight(-1.0);
			glutPostRedisplay();
			break;
		case 'd':
			camera.StrafeRight(1.0);
			glutPostRedisplay();
			break;
		case 'h':
			if (HUD_ON_OFF == false)
			{
				HUD_ON_OFF = true;
			}
			else
			{
				HUD_ON_OFF = false;
			}
			break;
	}
}
void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera.MovePlayer(vectorXYZ(0.0, 1.0, 0.0));
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		camera.MovePlayer(vectorXYZ(0.0, -1.0, 0.0));
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		shipRotation_Z -= 1.0;
		if (shipRotation_Z < 0.0)
		{
			shipRotation_Z = 359;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		shipRotation_Z += 1.0;
		if (shipRotation_Z >= 360)
		{
			shipRotation_Z = 0;
		}
		glutPostRedisplay();
		break;
	}
	glutPostRedisplay();
}
#pragma endregion

#pragma region main GLUT loop
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);// a 4:3 ratio
	glutCreateWindow("Textures Tutorial");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(25, TimerFunc, 1);
	glutTimerFunc(1000, timerCrystals, 0);
	glutKeyboardFunc(KeyDown);
	glutSpecialFunc(SpecialInput);
	SetupRC();
	init();
	glutMainLoop();
	return 0;
}
#pragma endregion









