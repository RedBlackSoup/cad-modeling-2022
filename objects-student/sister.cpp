// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "cart.h"
#include "utility.h"
#include "sister.h"

// -----------------------------------------------------------------------------------------
// external globals
// -----------------------------------------------------------------------------------------
extern unsigned long	gPolygonCount;			// counts how many polygons get displayed each frame
extern bool             gWireFrameOnly;         // solid or wireframe drawing mode
extern vector<object3d*> gShapeVector;

sister::sister()
{
	setName("body");
	wood = new texture("face2.jpg");

	body = new tcube();
	body->setDeformation(0.35, 0.6, 0.35);

	body->setParent(this);
	body->setColour(0.329, 0.298, 0.294);

	head = new tcube();
	head->setDeformation(0.4, 0.4, 0.4);
	head->setParent(body);
	head->setPosition(0.0, 1.0, 0.0);
	head->setRotation('y', 180);
	head->setTexture(wood);

	leg1 = new tcube();
	leg1->setParent(body);
	leg1->setDeformation(0.2, 0.4, 0.2);
	leg1->setRotation('z', 30, 'x', 60);
	leg1->setPosition(0.6, -0.58, -0.4);
	leg1->setColour(0.980, 0.667, 0.890);

	foot1 = new tcube();
	foot1->setParent(leg1);
	foot1->setDeformation(0.201, 0.4, 0.2);
	foot1->setPosition(0.0, -0.45, 0.3);
	foot1->setRotation('x', -60);
	foot1->setColour(0.967, 0.933, 0.922);

	leg2 = new tcube();
	leg2->setParent(body);
	leg2->setDeformation(0.2, 0.4, 0.2);
	leg2->setRotation('z', -30, 'x', 60);
	leg2->setPosition(-0.6, -0.58, -0.4);
	leg2->setColour(0.980, 0.667, 0.890);

	foot2 = new tcube();
	foot2->setParent(leg2);
	foot2->setDeformation(0.201, 0.4, 0.2);
	foot2->setPosition(0.0, -0.45, 0.3);
	foot2->setRotation('x', -60);
	foot2->setColour(0.967, 0.933, 0.922);

	elbow1 = new tcube();
	elbow1->setDeformation(0.2, 0.4, 0.2);
	elbow1->setParent(body);
	elbow1->setRotation('z', 15, 'x', 60);
	elbow1->setPosition(0.6, 0.3, -0.3);
	elbow1->setColour(0.329, 0.298, 0.294);

	hand1 = new tcube();
	hand1->setDeformation(0.201, 0.4, 0.2);
	hand1->setParent(elbow1);
	hand1->setRotation('x', 30);
	hand1->setOffset(0, -0.65, 0.2);
	//hand1->setOffset(0, -0.65, -0.2);
	hand1->setColour(0.967, 0.933, 0.922);

	elbow2 = new tcube();
	elbow2->setDeformation(0.2, 0.4, 0.2);
	elbow2->setParent(body);
	elbow2->setRotation('z', -15, 'x', 60);
	elbow2->setPosition(-0.6, 0.3, -0.3);
	elbow2->setColour(0.329, 0.298, 0.294);


	hand2 = new tcube();
	hand2->setDeformation(0.201, 0.4, 0.2);
	hand2->setParent(elbow2);
	hand2->setRotation('x', 30);
	hand2->setPosition(0, -0.65, -0.2);
	hand2->setColour(0.967, 0.933, 0.922);

	su = new suger();
	su->setParent(hand1);
	su->setScale(0.2);
	su->setRotation('x', 90);
	su->setPosition(0, -0.2, -0.3);

	dec1 = new extrusion("myprofile3.txt", "mypath1.txt");
	dec1->setParent(head);
	dec1->setColour(0.980, 0.384, 0.106);
	dec1->setDeformation(0.1, 0.1, 0.08);
	dec1->setPosition(0, 0.45, 0.2);

	dec2 = new extrusion("myprofile4.txt", "mypath2.txt");
	dec2->setParent(body);
	dec2->setDeformation(0.35, 0.6, 0.35);
	dec2->setPosition(0, 0, -0.351);
}

void sister::hide(void)
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
	su->hide();
	dec1->hide();
	dec2->hide();
}

void sister::show(void)
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
	su->show();
	dec1->show();
	dec2->show();
}
