// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "suger.h"
#include "utility.h"

// -----------------------------------------------------------------------------------------
// external globals
// -----------------------------------------------------------------------------------------
extern unsigned long	gPolygonCount;			// counts how many polygons get displayed each frame
extern bool             gWireFrameOnly;         // solid or wireframe drawing mode
extern vector<object3d*> gShapeVector;

suger::suger()
{
	setName("suger");
	//wood = new texture("boxtex.jpg");

	pole = new tcylinder(50,0.1,0.1);
	//pole->setDeformation(0.05, 0.3, 0.05);
	//bottom->setTexture(wood);
	pole->setParent(this);

	sweet = new tsphere(50);
	sweet->setDeformation(0.8, 0.8, 0.8);
	sweet->setPosition(0.0, -1.75, 0.0);
	sweet->setParent(pole);
	sweet->setColour(0.961, 0.718, 0.357);
	// calculate the face and vertex normals
	calculateNormals();
	diffuseShading = false;


	// put the shape onto the shapeVector so it gets draw messages
	gShapeVector.push_back(this);
}

void suger::hide(void)
{
	pole->hide();
	sweet->hide();

}

void suger::show(void)
{
	pole->show();
	sweet->show();
}
