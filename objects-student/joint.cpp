// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "cart.h"
#include "utility.h"
#include "joint.h"

// -----------------------------------------------------------------------------------------
// external globals
// -----------------------------------------------------------------------------------------
extern unsigned long	gPolygonCount;			// counts how many polygons get displayed each frame
extern bool             gWireFrameOnly;         // solid or wireframe drawing mode
extern vector<object3d*> gShapeVector;

joint::joint()
{
	setName("body");
	wood = new texture("face1.jpg");

	body = new tcube();
	body->setDeformation(0.35, 0.6, 0.35);
	//bottom->setTexture(wood);
	body->setParent(this);
	body->setColour(0.471, 1.0, 0.824);

	head = new tcube();
	head->setDeformation(0.4, 0.4, 0.4);
	head->setParent(body);
	head->setRotation('y', 180);
	head->setPosition(0.0, 1.0, 0.0);
	head->setTexture(wood);

	
	leg1 = new tcube();
	leg1->setParent(body);
	leg1->setDeformation(0.2, 0.4, 0.2);
	leg1->setRotation('z', 15, 'x', 60);
	leg1->setPosition(0.3, -0.65, -0.5);
	leg1->setColour(0.176, 0.392, 0.710);

	foot1 = new tcube();
	foot1->setParent(leg1);
	foot1->setDeformation(0.201, 0.4, 0.2);
	foot1->setPosition(0.0, -0.45, 0.3);
	foot1->setRotation('x', -60);	
	foot1->setColour(0.949, 0.878, 0.815);

	leg2 = new tcube();
	leg2->setParent(body);
	leg2->setDeformation(0.2, 0.4, 0.2);
	leg2->setRotation('z', -15, 'x', 60);
	leg2->setPosition(-0.3, -0.65, -0.5);
	leg2->setColour(0.176, 0.392, 0.710);

	foot2 = new tcube();
	foot2->setParent(leg2);
	foot2->setDeformation(0.201, 0.4, 0.2);
	foot2->setPosition(0.0, -0.45, 0.3);
	foot2->setRotation('x', -60);
	foot2->setColour(0.949, 0.878, 0.815);

	elbow1 = new tcube();
	elbow1->setDeformation(0.2, 0.4, 0.2);
	elbow1->setParent(body);
	elbow1->setRotation('z', 15, 'x', 60);
	elbow1->setPosition(0.6, 0.3, -0.3);
	elbow1->setColour(0.471, 1.0, 0.824);

	hand1 = new tcube();
	hand1->setDeformation(0.201, 0.4, 0.2);
	hand1->setParent(elbow1);
	hand1->setRotation('x', 30);
	hand1->setPosition(0, -0.65, -0.2);	
	hand1->setColour(0.949, 0.878, 0.815);
	
	elbow2 = new tcube();
	elbow2->setDeformation(0.2, 0.4, 0.2);
	elbow2->setParent(body);
	elbow2->setRotation('z', -15, 'x', 60);
	elbow2->setPosition(-0.6, 0.3, -0.3);
	elbow2->setColour(0.471, 1.0, 0.824);

	hand2 = new tcube();
	hand2->setDeformation(0.201, 0.4, 0.2);
	hand2->setParent(elbow2);
	hand2->setRotation('x', 30);
	hand2->setPosition(0, -0.65, -0.2);
	hand2->setColour(0.949, 0.878, 0.815);
}

void joint::hide(void)
{
	body->hide();
	elbow1->hide();
	elbow2->hide();
	hand1->hide();
	hand2->hide();
	leg1->hide();
	leg2->hide();
	foot1->hide();
	foot2->hide();
	head->hide();
}

void joint::show(void)
{
	body->show();
	elbow1->show();
	elbow2->show();
	hand1->show();
	hand2->show();
	leg1->show();
	leg2->show();
	foot1->show();
	foot2->show();
	head->show();
}
