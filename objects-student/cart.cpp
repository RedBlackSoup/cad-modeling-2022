// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "cart.h"
#include "utility.h"

// -----------------------------------------------------------------------------------------
// external globals
// -----------------------------------------------------------------------------------------
extern unsigned long	gPolygonCount;			// counts how many polygons get displayed each frame
extern bool             gWireFrameOnly;         // solid or wireframe drawing mode
extern vector<object3d*> gShapeVector;

cart::cart()
{
	setName("cart");
	wood = new texture("boxtex.jpg");

	bottom = new tcube();
	bottom->setDeformation(0.5, 0.25, 0.75);
	bottom->setColour(0.043, 0.321, 0.690);
	bottom->setParent(this);

	front1 = new tcube();
	front1->setParent(bottom);
	front1->setDeformation(0.5, 0.9, 0.5);
	front1->setPosition(0, 0.65, -1.25);
	front1->setColour(0.961, 0.867, 0.165);

	front2 = new tcube();
	front2->setParent(front1);
	front2->setDeformation(0.4, 0.3, 0.5);
	front2->setRotation('x', -45);
	front2->setPosition(0, 1.0, 0.2);
	front2->setColour(0.961, 0.867, 0.165);



	back1 = new tcube();
	back1->setParent(bottom);
	back1->setDeformation(0.5, 0.75, 0.5);
	back1->setPosition(0.0, 0.5, 1.25);
	back1->setColour(0.643, 0.604, 0.678);

	back2 = new tcube();
	back2->setParent(bottom);
	back2->setDeformation(0.3, 0.5, 0.5);
	back2->setPosition(0.0, 0.25, 2.25);
	back2->setColour(0.643, 0.604, 0.678);

	wheel1 = new torus(20, 20, 0.6, 0.1);
	wheel1->setParent(front1);
	wheel1->setRotation('z', 90);
	wheel1->setPosition(0.0, -1.3, -0.5);

	wheel2 = new torus(20, 20, 0.6, 0.1);
	wheel2->setParent(back2);
	wheel2->setRotation('z', 90);
	wheel2->setPosition(0, -0.6, 0);

	pole1 = new tcylinder(20,1.0,1.0);
	pole1->setParent(front2);
	pole1->setDeformation(0.1, 0.5, 0.1);
	pole1->setRotation('z', 90);
	pole1->setPosition(0.9, -0.18, 0.35);
	pole1->setColour(0.314, 0.306, 0.322);

	pole2 = new tcylinder(20,1.0,1.0);
	pole2->setParent(front2);
	pole2->setDeformation(0.1, 0.5, 0.1);
	pole2->setRotation('z', 90);
	pole2->setPosition(-0.9, -0.18, 0.35);
	pole2->setColour(0.314, 0.306, 0.322);

	mirror1 = new sweep("myprofile.txt", 10);
	mirror1->setParent(pole1);
	mirror1->setDeformation(0.2, 0.2, 0.2);
	mirror1->setRotation('x',90,'y',70);
	mirror1->setPosition(0.2, 0.37, 0.1);

	mirror2 = new sweep("myprofile.txt", 10);
	mirror2->setParent(pole2);
	mirror2->setDeformation(0.2, 0.2, 0.2);
	mirror2->setRotation('x', 90, 'y', 70);
	mirror2->setPosition(0.2, -0.37, 0.1);

	frtli = new sweep("myprofile2.txt", 10);
	frtli->setParent(front1);
	frtli->setDeformation(1, 0.05, 1);
	frtli->setRotation('x', -90);
	frtli->setPosition(0, 0, -0.55);
	frtli->setColour(1.0, 0.737, 0.01);
}

void cart::hide(void)
{
	pole1->hide();
	pole2->hide();
	bottom->hide();
	back1->hide();
	back2->hide();
	front1->hide();
	front2->hide();
	wheel1->hide();
	wheel2->hide();
	frtli->hide();
	mirror1->hide();
	mirror2->hide();
}

void cart::show(void)
{
	pole1->show();
	pole2->show();
	bottom->show();
	back1->show();
	back2->show();
	front1->show();
	front2->show();
	wheel1->show();
	wheel2->show();
	frtli->show();
	mirror1->show();
	mirror2->show();
}
