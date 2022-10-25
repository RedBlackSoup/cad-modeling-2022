// =========================================================================================
// KXC354 - Computer Graphics & Animation - 2013
// Assignment 1 & 2
// 3D Engine Code
// =========================================================================================
//
// Author: Tony Gray
//
// tcylinder.cpp
//
// This file defines a class for (optionally textured) tcylinders (if a texture has been
// assigned to the tcylinder, it is drawn, otherwise a non-textured tcylinder is drawn).
//
// This class was developed as a demonstration of texturing.  It currently does
// not draw the end-caps.
//
// This class doesn't create any stored-geometry - just a display list of the vertex
// data and texture coordinates.  Because of this, it can't show face normals if this
// feature is turned on ("n" key).
//
// One (optional) parameter may be used:
// density	- the mesh density for radial sweep



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "tcylinder.h"
#include "utility.h"



// -----------------------------------------------------------------------------------------
// external globals
// -----------------------------------------------------------------------------------------
extern unsigned long	gPolygonCount;			// counts how many polygons get displayed each frame
extern bool             gWireFrameOnly;         // solid or wireframe drawing mode
extern vector<object3d*> gShapeVector;




// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
tcylinder::tcylinder() : object3d()
{
	setName("tcylinder");
	builder(16, 1.0, 1.0);								// if no density provided, default to 16
}


tcylinder::tcylinder(int r, double r1, double r2) : object3d()
{
	builder(r, r1, r2);
}

// -----------------------------------------------------------------------------------------
// the "real" constructor
// not exported,  but called by the real constructor
// -----------------------------------------------------------------------------------------

void tcylinder::builder(int r, double tr, double br)
{
	density = r;
	polygonCount = 3 * r;
	// create a list and start recording into it
	listName = glGenLists(1); // 分配一个显示列表
	if (listName == 0) fatal("tsphere constructor couldn't create an OpenGL list");
	glNewList(listName, GL_COMPILE);

	// we draw the tcylinder as a strip of quads
	glBegin(GL_QUAD_STRIP);

	for (int i = 0; i <= density; i++)
	{
		float angle = i * (360.0 / density);
		float x = -cos_d(angle);
		float z = sin_d(angle);

		// normal for lighting
		glNormal3f(x, 0, z);

		// texture and geometry top coordinate
		glTexCoord2f((angle / 360.0), 1.0);
		glVertex3f(tr*x, 1.0, tr*z);

		// texture and geometry bottom coordinate
		glTexCoord2f((angle / 360.0), 0.0);
		glVertex3f(br*x, -1.0, br*z);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.5);
	glVertex3f(0.0, 1.0, 0.0);

	for (int i = 0; i <= density; i++)
	{
		float angle = i * (360.0 / density);
		float x = -cos_d(angle);
		float z = sin_d(angle);

		// normal for lighting
		glNormal3f(x, 0, z);

		// texture and geometry top coordinate
		glTexCoord2f((angle / 360.0), 1.0);
		glVertex3f(tr*x, 1.0, tr*z);

	}

	glEnd();

	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0, -1, 0);
	glTexCoord2f(0.0, 0.5);
	glVertex3f(0.0, -1.0, 0.0);

	for (int i = 0; i <= density; i++)
	{
		float angle = 360.0 - i * (360.0 / density);
		float x = -cos_d(angle);
		float z = sin_d(angle);

		// normal for lighting
		glNormal3f(x, 0, z);

		// texture and geometry bottom coordinate
		glTexCoord2f((angle / 360.0), 0.0);
		glVertex3f(br*x, -1.0, br*z);
	}

	glEnd();
	// stop recording the list
	glEndList();


	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}


