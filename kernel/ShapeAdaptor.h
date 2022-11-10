// =========================================================================================
// CAD kernel code
// =========================================================================================
//
// Author: Redblacksoup
//
// ShapeAdaptor.h
//

#ifndef _ShapeAdaptor_H
#define _ShapeAdaptor_H

// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "object3d.h"
#include "RbsMesh.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------
class ShapeAdaptor : public object3d
{
private:
	void builder(kernel::solid* model);

public:
	ShapeAdaptor();							// default constructor
	ShapeAdaptor(kernel::solid* model);
	void setColor(double r, double g, double b);
	void setColor(double r, double g, double b, double a);
};

#endif 
