#pragma once
#include "EulerOp.h"


class RbsMesh
{
public:
	void printLoop(const kernel::loop* lp);
	void printFace(const kernel::face* f);
	void printSolid(const kernel::solid* s);

	kernel::solid* buildCube();
	kernel::solid* testSweep();
	kernel::solid* build2ring();
	kernel::solid* testPolyToTri();
	kernel::solid* sweep(kernel::face* f, kernel::point vec, double d);
	kernel::solid* sweep(kernel::face *f, double x, double y, double z, double d);
	std::vector<std::array<int, 3>> polyToTri(kernel::face* poly, std::unordered_map<kernel::vertex*, int>& orederMap);

	void solidToTri(kernel::solid* s, std::vector<std::array<double, 3>>& pList, std::vector<std::array<int, 3>>& fList);
};

