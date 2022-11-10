#pragma once
// =========================================================================================
// CAD kernel code
// =========================================================================================
//
// Author: Redblacksoup
//
// ShapeAdaptor.cpp
//

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "ShapeAdaptor.h"
#include "utility.h"
#include "EulerOp.h"
#include <array>
#include <vector>
// -----------------------------------------------------------------------------------------
// external globals
// -----------------------------------------------------------------------------------------
extern unsigned long	gPolygonCount;			// counts how many polygons get displayed each frame
extern bool             gWireFrameOnly;         // solid or wireframe drawing mode
extern vector<object3d*> gShapeVector;

// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
ShapeAdaptor::ShapeAdaptor() : object3d()
{
	setName("ShapeAdaptor");
}

ShapeAdaptor::ShapeAdaptor(kernel::solid* model)
{
	setName("ShapeAdaptor");
	builder(model);
}

void ShapeAdaptor::setColor(double r, double g, double b)
{
	setColour(r, g, b, 1.0);
}

void ShapeAdaptor::setColor(double r, double g, double b, double a)
{
	setColour(r, g, b, a);
}



// -----------------------------------------------------------------------------------------
// the "real" constructor
// not exported,  but called by the real constructor
// -----------------------------------------------------------------------------------------

void ShapeAdaptor::builder(kernel::solid* model)
{
	// Initialise the object's state
	setName("ShapeAdaptor");
	setColour(0.15, .85, .35, 1.0);					// default colour

	RbsMesh rhandle;
	std::vector<std::array<double, 3>> pList;
	std::vector<std::array<int, 3>> fList;
	rhandle.solidToTri(model, pList, fList);


	vertexCount = pList.size();
	faceCount = fList.size();
	polygonCount = 0;

	// allocate memory for the vertex and face arrays
	vertices.resize(vertexCount);
	faces.resize(faceCount);
	

	// Initialise the cube's vertices to create a cube centered around the origin
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].set(pList[i][0], pList[i][1], pList[i][2]);
	}

	for (int i = 0; i < faceCount; i++)
	{
		faces[i].init(fList[i][0], fList[i][1], fList[i][2]);
	}


	// calculate the face and vertex normals
	calculateNormals();


	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}
