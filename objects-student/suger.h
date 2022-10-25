// =========================================================================================
// KXC354 - Computer Graphics & Animation - 2013
// Assignment 1 & 2
// 3D Engine Code
// =========================================================================================


#ifndef _suger_H
#define _suger_H


// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "object3d.h"
#include "tcylinder.h"
#include "tcube.h"
#include "torus.h"
#include "texture.h"
#include "tsphere.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------
class suger : public object3d
{
public:
	tcylinder* pole;
	tsphere* sweet;

	suger();							// default constructor

	virtual void		hide(void);
	virtual void		show(void);
};



#endif // _suger_H


