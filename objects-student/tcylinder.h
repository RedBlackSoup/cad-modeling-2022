// =========================================================================================
// KXC354 - Computer Graphics & Animation - 2013
// Assignment 1 & 2
// 3D Engine Code
// =========================================================================================
//
// Author: Tony Gray
//
// tcylinder.h
//
// This file declares a class for textured cylinders, which are
// derived from generic object3d objects


#ifndef _tcylinder_H
#define _tcylinder_H



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "object3d.h"




// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------
class tcylinder : public object3d
{
private:
	int     density;							// saved mesh density
	void 	builder(int r, double tr, double br);


public:
	tcylinder();							// default constructor
	tcylinder(int density,double ,double );				// constructor with density


};



#endif // _cylinder_H

