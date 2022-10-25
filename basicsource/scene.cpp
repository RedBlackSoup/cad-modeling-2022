// =========================================================================================
// KXC354 - Computer Graphics & Animation - 2013
// Assignment 1 & 2
// 3D Engine Code
// =========================================================================================
//
// Author: Tony Gray
//
// scene.cpp


// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "constants.h"			// system-wide constants
#include "utility.h"			// general utility functions
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "snd.h"
#include "skybox.h"
#include "fog.h"
#include "viewfrustum.h"
#include <iostream>

// #includes for geometry
#include "sweep.h"
#include "extrusion.h"
#include "cube.h"
#include "sphere.h"
#include "torus.h"
#include "terrain.h"
#include "billboard.h"
#include "plane.h"
#include "tsphere.h"
#include "cylinder.h"
#include "disc.h"
#include "cart.h"
#include "tcylinder.h"
#include "joint.h"
#include "sister.h"
#include "plane.h"
////

// -----------------------------------------------------------------------------------------
// global variables
// -----------------------------------------------------------------------------------------
extern ProgramMode		gProgramMode;							// initially, we're not animating

extern cameraClass		gCamera;								// the camera
extern object3d			*gSky;									// the global skybox
extern fog				*gFog;									// the global fog
extern viewfrustum		*gViewFrustum;							// the global view frustum object
extern float			gCurrentFrameTime;						// the time that the current animation frame was started

extern vector<object3d*> gShapeVector;
typedef vector<object3d*>::iterator shapeVectorIterator;

// -----------------------------------------------------------------------------------------
// variables that represent 3D objects being used in the animation
// -----------------------------------------------------------------------------------------
// these are really global variables, but you shouldn't need to access them from anywere
// except in this file 
// -----------------------------------------------------------------------------------------

// shapes
cart* porter;
plane* ground;
joint* people1;
sister* people2;
// some lights
light *ambient, *light0, *light1, *light2;

snd* s;


bool sce1 = false, sce2 = false, sce3 = false, sce4 = false, sce5 = false;



// -----------------------------------------------------------------------------------------
// constructScene
// -----------------------------------------------------------------------------------------
// This function constructs the objects required for the animation.  It is only called once
// when the program is first run.
// Use this to create child objects and bind them to their parents.
// -----------------------------------------------------------------------------------------

void constructScene()
{
	s = new snd("ost.ogg");
	// create the lights first
	ambient = new light(GL_LIGHT_MODEL_AMBIENT);
	light0 = new light(GL_LIGHT0);
	light1 = new light(GL_LIGHT1);
    
	ground = new plane();
	ground->setRotation('x', 90);
	ground->setScale(100);
	ground->setPosition(0, -1.5, 0);
	gSky = new skybox("sky30-");
	

	people1 = new joint();
	people1->setPosition(0.0, 1.85, 0.8);

	people2 = new sister();
	people2->setPosition(0.0, 1.35, 2.4);

	porter = new cart();
}

// -----------------------------------------------------------------------------------------
// resetScene
// -----------------------------------------------------------------------------------------
// This function is called whenever the animation is restarted.  Use it to reset objects
// to their starting position or size, or to reset any aspects of the objects that
// might have been altered during an animation sequence.
// -----------------------------------------------------------------------------------------

void resetScene()
{
	// initialise the camera
	gCamera.setPosition(0, 2, 5);
	gCamera.setTarget(0, 0, 0);
    
	ambient->setColour(0.5, 0.5, 0.5, 1.0);
    
	light0->turnOn();
	light0->setPosition(0, 20.0, 20);
	light0->setColour(0.7, 0.7, 0.7, 1.0);
	light0->setSpecularColour(0.7, 0.7, 0.7, 1.0);
	light0->makePositional();
	light0->setLinearAttenuation(0.1);
	
	light1->turnOn();
	light1->setPosition(10, 20.0, 0);
	light1->setColour(0.7, 0.7, 0.7, 1.0);
	light1->setSpecularColour(0.7, 0.7, 0.7, 1.0);
	light1->makePositional();
	light1->setLinearAttenuation(0.1);
}

// -----------------------------------------------------------------------------------------
// animateForNextFrame
// -----------------------------------------------------------------------------------------
// This function is called to animate objects ready for the next frame
// -----------------------------------------------------------------------------------------

void animateForNextFrame(float time, long frame)
{
	//float xAngle=0, yAngle=0;

	//if (time < 8)
	//	yAngle = time * 45;
	//else if (time < 16)
	//	xAngle = time * 45;
    
	//porter->setPosition(4 * sin_d(time * 90), 0, 4 * cos_d(time * 90));
	//people1->setPosition(4 * sin_d(time * 90), 0, 4 * cos_d(time * 90));
	//people2->setPosition(4 * sin_d(time * 90), 0, 4 * cos_d(time * 90));

	gCamera.setTarget(people2);
	
	people1->connect(porter);
	people2->connect(porter);

	//gCamera.setPosition(5, 2,  - 2);
	porter->setPosition(0, 0, -(time) * 2);
	if (time <= 1) {
		porter->hide();
		people1->hide();
		people2->hide();
	}
	else {
		porter->show();
		people1->show();
		people2->show();
	}
	if (time <= 2)
		gCamera.setPosition(15, 15, -15);
		
	if (time >= 2 && !s->isPlaying()) {
		s->startSound();
	}

	if (time >= 2 && time<=13) {
		if (sce1 == false) {
			sce1 = true;
			// do something

		}
		gCamera.setPosition(5, 2, -2-(time)*2);
		gCamera.setTarget(porter->getPosition().data[0], porter->getPosition().data[1] + 2, porter->getPosition().data[2] + 1);//1
	}
	if (time >= 2 && time <= 4)
		people2->head->setOffset(0, 0.02 * cos_d((time-2) * 1080), 0);

	if (time >= 4 && time <= 7)
		people2->head->setRotation('y', 180-(time - 4) * 15);

	if (time >= 7 && time <= 10)
		people2->elbow1->setRotation('x', 60 + 10 * (time - 7));

	if (time >= 8 && time <= 10)
		people2->head->setOffset(0, 0.02 * cos_d((time - 8) * 1080), 0);

	if (time >= 10 && time <= 10.5)
		people1->head->setRotation('y', 180 - (time - 10) * 140);

	if (time >= 10.5 && time <= 11)
		people1->head->setRotation('y', 110 + (time - 10.5) * 140);

	if (time >= 11 && time <= 12) {
		people2->elbow1->setRotation('x', (time - 11) * 3600);
		people2->elbow2->setRotation('x', (time - 11) * 3600);
	}
	

	if (time >= 12 && time <=19) {
		if (sce2 == false) {
			sce2 = true;
			people2->elbow1->setOffset(0, -0.3, 0.3);
			people2->elbow2->setOffset(0, -0.3, 0.3);
			people2->head->setRotation('y', 180);

		}
		gCamera.setPosition(2, 2.5, 1.1 - (time) * 2);
		gCamera.setTarget(porter->getPosition().data[0], porter->getPosition().data[1] + 2, porter->getPosition().data[2] + 2.4);

	}
	if (time >= 13.0 && time <= 17)
		people2->head->setOffset(0, 0.02 * cos_d((time - 12) * 1080), 0);

	//}
	if (time >= 19 && time <= 23) {
		if (sce3 == false) {
			sce3 = true;
		}
		gCamera.setPosition(-20, 30, 1.1 - (time) * 2);
		gCamera.setTarget(porter->getPosition().data[0], porter->getPosition().data[1] + 2, porter->getPosition().data[2] + 2.4);
	}

	if (time >= 23 && time <= 26) {
		if (sce4 == false) {
			sce4 = true;
			// do something

		}
		gCamera.setPosition(5, 2, -2 - (time) * 2);
		gCamera.setTarget(porter->getPosition().data[0], porter->getPosition().data[1] + 2, porter->getPosition().data[2] + 1);//1
		people2->head->setRotation('y', 180 - cos_d(360*(time - 23)) * 10);

	}
		



	if (time >= 26&& time <= 30) {
		if (sce5 == false) {
			sce5 = true;

			people2->elbow1->setRotation('z', 15, 'x', 60);
			people2->elbow2->setRotation('z', -15, 'x', 60);
			people2->elbow1->setOffset(0, 0, 0);
			people2->elbow2->setOffset(0, 0, 0);
		}
		gCamera.setPosition(2, 2.5, 1.1 - (time) * 2);
		gCamera.setTarget(porter->getPosition().data[0], porter->getPosition().data[1] + 2, porter->getPosition().data[2] + 2.4);

	}
	if (time >= 26 && time <= 26.7)
		people2->head->setOffset(0, 0.02 * cos_d((time - 12) * 1080), 0);

	if (time >= 27.2 && time <= 30) {
		people2->head->setRotation('y',180,'x',(time-27.2)*10);
		people2->hand1->setRotation('x', 30 + (time - 27.2) * 8, 'z', -(time - 27.2) * 25);
		people2->hand2->setRotation('x', 30 + (time - 27.2) * 8, 'z', (time - 27.2) * 25);
	}
	if (time >= 30)
		gProgramMode = kpmFinished;
}


