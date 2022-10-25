// =========================================================================================
// KXC354 - Computer Graphics & Animation - 2013
// Assignment 1 & 2
// 3D Engine Code
// =========================================================================================


#ifndef _sister_H
#define _sister_H


// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "object3d.h"
#include "tcylinder.h"
#include "tcube.h"
#include "torus.h"
#include "tsphere.h"
#include "texture.h"
#include "suger.h"
#include "extrusion.h"
// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------
class sister : public object3d
{
public:

	tcube* body, * head, * leg1, * leg2, * foot1, * foot2, * elbow1, * hand1, * elbow2, * hand2;
	suger* su;
	texture* wood;
	extrusion* dec1,*dec2;
	sister();							// default constructor

	virtual void		hide(void);
	virtual void		show(void);
};



#endif // _sister_H


