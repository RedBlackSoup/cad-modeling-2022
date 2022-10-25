// =========================================================================================
// KXC354 - Computer Graphics & Animation - 2013
// Assignment 1 & 2
// 3D Engine Code
// =========================================================================================


#ifndef _cart_H
#define _cart_H


// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "object3d.h"
#include "tcylinder.h"
#include "tcube.h"
#include "torus.h"
#include "texture.h"
#include "sweep.h"

// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------
class cart : public object3d
{
public:
	tcylinder* pole1, * pole2;
	tcube* bottom, * back1, * back2, * front1, * front2;
	torus* wheel1, * wheel2;
	sweep* mirror1, * mirror2, *frtli;
	texture* wood;

	cart();							// default constructor

	virtual void		hide(void);
	virtual void		show(void);
};



#endif // _cart_H


