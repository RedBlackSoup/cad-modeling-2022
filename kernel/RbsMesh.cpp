#include "prefix.h"
#include "RbsMesh.h"
#include "EulerOp.h"
#include "polypartition.h"

#include <Eigen/Dense>
#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <ranges>
#include <unordered_map>
using namespace kernel;

void RbsMesh::printLoop(const kernel::loop* lp)
{
	//face* fptr;
	//loop* lptr;
	//hfEdge* hfptr;
	//vertex* vptr;

	//int fcount = 0, vcount = 0;
	//for (vptr = model->svertices; vptr != nullptr; vptr = vptr->nextv)
	//	vcount++;
	//std::vector<std::array<double, 3>> vlist(vcount);
	//for (vptr = model->svertices; vptr != nullptr; vptr = vptr->nextv)
	//{
	//	point* pptr = vptr->p;
	//	vlist.push_back({pptr->px,pptr->py,pptr->pz});
	//}
	//std::vector<vertex*> vlist;
	//for (fptr = model->sfaces; fptr != nullptr; fptr = fptr->nextf)
	//{
	//	lptr = fptr->floops;
	//	for (;lptr != nullptr; lptr = lptr->nextl)
	//	{
	//		hfptr = lptr->ledges;
	//		for (; hfptr != nullptr; hfptr = hfptr->next) {
	//			vlist.push_back(hfptr->startv);

	//		}
	//	}
	//	fcount++;
	//}
	std::vector<std::array<double, 3>> vlist;

	hfEdge* startEdge = lp->ledges;
	auto hfptr = startEdge;
	do
	{
		point* pptr = hfptr->startv->p;
		vlist.push_back({ pptr->px,pptr->py,pptr->pz });
		hfptr = hfptr->next;
	} while (hfptr != startEdge);

	for (auto v : vlist)
	{
		std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
	}
}

void RbsMesh::printFace(const kernel::face* f)
{
	int lpcount = 0;
	for (auto lp = f->floops; lp != nullptr; lp = lp->nextl)
	{
		std::cout << "loop " << lpcount << ":" << std::endl;
		this->printLoop(lp);
		lpcount++;
	}
}

void RbsMesh::printSolid(const kernel::solid* s)
{
	int fcount = 0;
	for (auto f = s->sfaces; f != nullptr; f = f->nextf)
	{
		int lpcount = 0;
		for (auto lp = f->floops; lp != nullptr; lp = lp->nextl)
		{
			std::cout << "face " << fcount << ", ";
			std::cout << "loop " << lpcount << ":" << std::endl;
			this->printLoop(lp);
			lpcount++;
		}
		fcount++;
	}
}

//
// @brief: 利用欧拉操作，构建一个立方体
//
solid* RbsMesh::buildCube()
{
	vertex* v0, * v1, * v2, * v3, * v4, * v5, * v6, * v7;
	vertex* v0r, * v1r, * v2r, * v3r, * v4r, * v5r, * v6r, * v7r;

	solid* cube = EulerOp::mvsf(v0);
	v1 = EulerOp::mev(*v0, *cube->sfaces->floops);
	v2 = EulerOp::mev(*v1, *cube->sfaces->floops);
	v3 = EulerOp::mev(*v2, *cube->sfaces->floops);
	auto f1 = EulerOp::mef(*v0, *v3, *cube->sfaces->floops);

	v4 = EulerOp::mev(*v0, *cube->sfaces->floops);
	v5 = EulerOp::mev(*v1, *cube->sfaces->floops);
	v6 = EulerOp::mev(*v2, *cube->sfaces->floops);
	v7 = EulerOp::mev(*v3, *cube->sfaces->floops);
	auto f2 = EulerOp::mef(*v5, *v4, *cube->sfaces->floops);
	auto f3 = EulerOp::mef(*v6, *v5, *cube->sfaces->floops);
	auto f4 = EulerOp::mef(*v7, *v6, *cube->sfaces->floops);
	auto f5 = EulerOp::mef(*v4, *v7, *cube->sfaces->floops);

	v0->p = new point(0, 0, 0);
	v1->p = new point(3, 0, 0);
	v2->p = new point(3, 3, 0);
	v3->p = new point(0, 3, 0);
	v4->p = new point(0, 0, 3);
	v5->p = new point(3, 0, 3);
	v6->p = new point(3, 3, 3);
	v7->p = new point(0, 3, 3);

	// f0 -- top, f1 -- bottom, f2 -- front
	// f3 -- right, f4 -- behind, f5 -- left

	v4r = EulerOp::mev(*v4, *cube->sfaces->floops);
	v5r = EulerOp::mev(*v4r, *cube->sfaces->floops);
	v6r = EulerOp::mev(*v5r, *cube->sfaces->floops);
	v7r = EulerOp::mev(*v6r, *cube->sfaces->floops);

	v4r->p = new point(1, 1, 3);
	v5r->p = new point(2, 1, 3);
	v6r->p = new point(2, 2, 3);
	v7r->p = new point(1, 2, 3);
	
	// top ring and fake face
	auto f0 = EulerOp::mef(*v4r, *v7r, *cube->sfaces->floops);
	EulerOp::kemr(*v4, *v4r, *f0->floops);
	v0r = EulerOp::mev(*v4r, *cube->sfaces->floops);
	v1r = EulerOp::mev(*v5r, *cube->sfaces->floops);
	v2r = EulerOp::mev(*v6r, *cube->sfaces->floops);
	v3r = EulerOp::mev(*v7r, *cube->sfaces->floops);
	v0r->p = new point(1, 1, 0);
	v1r->p = new point(2, 1, 0);
	v2r->p = new point(2, 2, 0);
	v3r->p = new point(1, 2, 0);

	auto f7 = EulerOp::mef(*v0r, *v3r, *cube->sfaces->floops);
	auto f8 = EulerOp::mef(*v3r, *v2r, *cube->sfaces->floops);
	auto f9 = EulerOp::mef(*v2r, *v1r, *cube->sfaces->floops);
	auto f10 = EulerOp::mef(*v1r, *v0r, *cube->sfaces->floops);
	EulerOp::kfmrh(*cube->sfaces, *f1);
	return cube;
}

kernel::solid* RbsMesh::testSweep()
{
	vertex* v0, * v1, * v2, * v3, * v0r, * v1r, * v2r, * v3r;
	double x = 0, y = 1, z = 5, d = 3;
	solid* cube = EulerOp::mvsf(v0);
	v1 = EulerOp::mev(*v0, *cube->sfaces->floops);
	v2 = EulerOp::mev(*v1, *cube->sfaces->floops);
	v3 = EulerOp::mev(*v2, *cube->sfaces->floops);
	// 0 -- clockwise 1 -- c clockwise
	auto F0 = EulerOp::mef(*v0, *v3, *cube->sfaces->floops);
	v0r = EulerOp::mev(*v0, *cube->sfaces->floops); 
	v1r = EulerOp::mev(*v0r, *cube->sfaces->floops);
	v2r = EulerOp::mev(*v1r, *cube->sfaces->floops);
	v3r = EulerOp::mev(*v2r, *cube->sfaces->floops);
	// top ring and fake face
	auto F1 = EulerOp::mef(*v0r, *v3r, *cube->sfaces->floops);
	auto f1 = cube->sfaces;

	EulerOp::kemr(*v0, *v0r, *F1->floops);
	EulerOp::kfmrh(*f1, *F0);
	v0->p = new point(0, 0, 0);
	v1->p = new point(3, 0, 0);
	v2->p = new point(3, 3, 0);
	v3->p = new point(0, 3, 0);
	v0r->p = new point(1, 1, 0);
	v1r->p = new point(2, 1, 0);
	v2r->p = new point(2, 2, 0);
	v3r->p = new point(1, 2, 0);

	//this->polyToTri(cube->sfaces->floops);
	this->sweep(cube->sfaces, x, y, z, d);

	return cube;
}

kernel::solid* RbsMesh::build2ring()
{
	vertex* v0, * v1, * v2, * v3, * v0r, * v1r, * v2r, * v3r, *v0rr, *v1rr, *v2rr, *v3rr;
	double x = 1, y = 0, z = 5, d = 1;
	solid* cube = EulerOp::mvsf(v0);
	v1 = EulerOp::mev(*v0, *cube->sfaces->floops);
	v2 = EulerOp::mev(*v1, *cube->sfaces->floops);
	v3 = EulerOp::mev(*v2, *cube->sfaces->floops);
	// 0 -- clockwise 1 -- c clockwise
	auto F0 = EulerOp::mef(*v0, *v3, *cube->sfaces->floops);
	v0r = EulerOp::mev(*v0, *cube->sfaces->floops);
	v1r = EulerOp::mev(*v0r, *cube->sfaces->floops);
	v2r = EulerOp::mev(*v1r, *cube->sfaces->floops);
	v3r = EulerOp::mev(*v2r, *cube->sfaces->floops);

	v1rr = EulerOp::mev(*v1, *cube->sfaces->floops);
	v2rr = EulerOp::mev(*v1rr, *cube->sfaces->floops);
	v3rr = EulerOp::mev(*v2rr, *cube->sfaces->floops);
	v0rr = EulerOp::mev(*v3rr, *cube->sfaces->floops);

	// top ring and fake face
	auto F1 = EulerOp::mef(*v0r, *v3r, *cube->sfaces->floops);
	auto f1 = cube->sfaces;

	EulerOp::kemr(*v0, *v0r, *F1->floops);
	EulerOp::kfmrh(*f1, *F0);

	auto f2 = EulerOp::mef(*v1rr, *v0rr, *cube->sfaces->floops,1);
	//f1 = cube->sfaces;

	EulerOp::kemr(*v1, *v1rr, *cube->sfaces->floops);

	v0->p = new point(0, 0, 0);
	v1->p = new point(6, 0, 0);
	v2->p = new point(6, 3, 0);
	v3->p = new point(0, 3, 0);
	v0r->p = new point(1, 1, 0);
	v1r->p = new point(2, 1, 0);
	v2r->p = new point(2, 2, 0);
	v3r->p = new point(1, 2, 0);
	v0rr->p = new point(4, 1, 0);
	v1rr->p = new point(5, 1, 0);
	v2rr->p = new point(5, 2, 0);
	v3rr->p = new point(4, 2, 0);
	EulerOp::kfmrh(*cube->sfaces->nextf, *cube->sfaces->nextf->nextf);

	auto l1 = cube->sfaces->floops;
	auto l2 = cube->sfaces->nextf->floops->nextl;
	auto l3 = l1->nextl;
	l1->nextl = l1->nextl->nextl;
	l1->nextl->nextl = l2->nextl;
	l2->nextl = l3;
	l3->nextl = nullptr;
	l3->lface = cube->sfaces->nextf;

	l1->nextl->nextl->lface = cube->sfaces;
	//l1->nextl = l3->nextl;
	//l1->nextl = l2->nextl;
	//l2->nextl = l3;
	printSolid(cube);
	//this->polyToTri(cube->sfaces->floops);
	this->sweep(cube->sfaces, x, y, z, d);

	return cube;
}

kernel::solid* RbsMesh::testPolyToTri()
{
	vertex* v0, * v1, * v2, * v3, * v4, * v5, * v6, * v7;
	double x = 0, y = 1, z = 5, d = 1;
	solid* cube = EulerOp::mvsf(v0);
	v1 = EulerOp::mev(*v0, *cube->sfaces->floops);
	v2 = EulerOp::mev(*v1, *cube->sfaces->floops);
	v3 = EulerOp::mev(*v2, *cube->sfaces->floops);
	v4 = EulerOp::mev(*v3, *cube->sfaces->floops);
	v5 = EulerOp::mev(*v4, *cube->sfaces->floops);
	v6 = EulerOp::mev(*v5, *cube->sfaces->floops);
	v7 = EulerOp::mev(*v6, *cube->sfaces->floops);
	// 0 -- clockwise 1 -- c clockwise
	auto F0 = EulerOp::mef(*v7, *v0, *cube->sfaces->floops);
	v0->p = new point(0, 0, 0);
	v1->p = new point(2, 0, 0);
	v2->p = new point(2, 1, 0);
	v3->p = new point(1, 1, 0);
	v4->p = new point(1, 2, 0);
	v5->p = new point(2, 2, 0);
	v6->p = new point(2, 3, 0);
	v7->p = new point(0, 3, 0);
	cube = this->sweep(cube->sfaces, x, y, z, d);
	this->printSolid(cube);
	return cube;
}

kernel::solid* RbsMesh::sweep(kernel::face* f, kernel::point vec, double d)
{
	
	return nullptr;
}

kernel::solid* RbsMesh::sweep(kernel::face* f, double x, double y, double z, double d)
{
	// f -- bottom
	// first loop is boundary and the remains are rings
	int count = 0;
	face* top, *ring;
	solid* s = f->fsolid;
	if (s->sfaces == nullptr || s->sfaces->nextf->nextf != nullptr)
	{
		std::cerr << "sweep -- only need two faces!" << std::endl;
		exit(0);
	}
	for (auto L = f->floops; L != nullptr; L = L->nextl)
	{
		std::cout << "loop: " << count << std::endl;
		vertex* firstV = L->ledges->startv;
		vertex* firstUp = EulerOp::mev(*firstV, *L);
		firstUp->p = new point(firstV->p->px + d * x, firstV->p->py + d * y, firstV->p->pz + d * z);
		std::cout << "point: ";
		std::cout << firstV->p->px << " " << firstV->p->py << " " << firstV->p->pz << std::endl;
		vertex* preUp = firstUp;
		vertex* nextV = L->ledges->next->startv;
		hfEdge* nextEdge = L->ledges->next;
		while (nextV != firstV)
		{
			std::cout << "point: ";
			std::cout << nextV->p->px << " " << nextV->p->py << " " << nextV->p->pz << std::endl;
			

			vertex* up = EulerOp::mev(*nextV, *L);
			up->p = new point(nextV->p->px + d * x, nextV->p->py + d * y, nextV->p->pz + d * z);

			auto newf = EulerOp::mef(*up, *preUp, *L);
			preUp = up;
			nextEdge = nextEdge->next;
			nextV = nextEdge->startv;
		}
		EulerOp::mef(*firstUp, *preUp, *L);

		if (count == 0)
		{
			top = L->lface;
		}
		else
		{
			ring = L->lface;
			//EulerOp::kfmrh(*ring, *top);
		}
		count++;
	}
	return s;
}

std::vector<std::array<int, 3>> RbsMesh::polyToTri(kernel::face* poly, std::unordered_map<kernel::vertex*,int> &orederMap)
{
	std::vector<vertex*> vList;
	std::vector<int> orderList;
	std::vector<int> faceSep;
	std::vector<std::array<double, 3>> plane_pts;
	std::vector<std::array<int, 3>> triList;

	faceSep.push_back(0);
	// add all vertices & not duplicate
	for (auto lptr = poly->floops; lptr != nullptr; lptr = lptr->nextl)
	{
		auto firstHf = lptr->ledges;
		auto hf = firstHf;
		do
		{
			auto v = hf->startv;
			if (std::ranges::find(vList, v) == vList.end())
			{
				vList.push_back(v);
				if (orederMap.count(v) == 0)
				{
					std::cerr << "polyToTri -- vertex is not in map!" << std::endl;
					exit(0);
				}
				orderList.push_back(orederMap[v]);
				plane_pts.push_back({ v->p->px,v->p->py,v->p->pz });
			}
			//vecList.push_back({ nextP->px - p->px,nextP->py - p->py,nextP->pz - p->pz });
			hf = hf->next;
		} while (hf != firstHf);
		faceSep.push_back(vList.size());
	}

	for (auto it : faceSep)
	{
		cout << it << " ";
	}
	cout << endl;
	// solve for the normal
	int pNum = vList.size();

	Eigen::Vector3d center = Eigen::Vector3d::Zero();
	for (const auto& pt : plane_pts) 
	{
		center(0) += pt[0];
		center(1) += pt[1];
		center(2) += pt[2];
	}
	center /= plane_pts.size();

	Eigen::MatrixXd A(plane_pts.size(), 3);
	for (int i = 0; i < plane_pts.size(); i++) {
		A(i, 0) = plane_pts[i][0] - center[0];
		A(i, 1) = plane_pts[i][1] - center[1];
		A(i, 2) = plane_pts[i][2] - center[2];
	}

	Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinV);
	const double a = svd.matrixV()(0, 2);
	const double b = svd.matrixV()(1, 2);
	const double c = svd.matrixV()(2, 2);
	const double d = -(a * center[0] + b * center[1] + c * center[2]);
	Eigen::Vector3d N(a, b, c);
	Eigen::Vector3d z(0, 0, 1);
	Eigen::Matrix3d rotY, rotX;
	std::cout << "Normal: " << N(0) << " " << N(1) << " " << N(2) << std::endl;

	Eigen::Vector3d Ny(N(0), 0, N(2));
	double cosY, sinY;
	if (Ny.norm() == 0)
	{
		cosY = 1;
		sinY = 0;
	}
	else
	{
		cosY = Ny.dot(z) / Ny.norm();
		sinY = Ny.cross(z).norm() / Ny.norm();
	}


	if (Ny.cross(z).dot(Eigen::Vector3d(0, 1, 0)) > 0)
	{
		sinY = -sinY;
	}
	rotY << cosY, 0, -sinY,
		0, 1, 0,
		sinY, 0, cosY;

	Eigen::Vector3d Nx = rotY * N;

	double cosX, sinX;
	if (Nx.norm() == 0)
	{
		cosX = 1;
		sinX = 0;
	}
	else
	{
		cosX = Nx.dot(z) / Nx.norm();
		sinX = Nx.cross(z).norm() / Nx.norm();
	}


	if (Nx.cross(z).dot(Eigen::Vector3d(1, 0, 0)) > 0)
	{
		sinX = -sinX;
	}

	rotX << 1, -0, 0,
		0, cosX, sinX,
		0, -sinX, cosX;
	

	TPPLPartition pp;
	std::list<TPPLPoly> testpolys, result;
	for (int i = 0; i < faceSep.size() - 1; i++)
	{
		int start = faceSep[i];
		int end = faceSep[i + 1];

		TPPLPoly tppPoly;
		tppPoly.Init(end - start);
		if (i == 0)
		{
			tppPoly.SetHole(false);
		}
		else
		{
			tppPoly.SetHole(true);
		}

		for (int j = start; j < end; j++)
		{
			std::cout << j << std::endl;
			Eigen::Vector3d vec;
			vec = A.row(j);
			vec = rotX * rotY * vec;
			tppPoly[j - start].x = vec(0);
			tppPoly[j - start].y = vec(1);
			tppPoly[j - start].id = orderList[j];
		}
		testpolys.push_back(tppPoly);
	}
	
	int flag, inverFlag = 0;
	flag = pp.Triangulate_EC(&testpolys, &result);

	if (flag == 0)
	{
		std::cerr << "Invert the order!" << std::endl;
		inverFlag = 1;
		for (auto& it : testpolys)
		{
			it.Invert();
		}
		flag = pp.Triangulate_EC(&testpolys, &result);
	}

	if (flag == 0)
	{
		std::cerr << "Ear clip failed!" << std::endl;
		exit(0);
	}

	std::list<TPPLPoly>::iterator iter;
	for (iter = result.begin(); iter != result.end(); iter++) {
		if (inverFlag)
		{
			iter->Invert();
		}
		triList.push_back({ iter->GetPoint(0).id ,iter->GetPoint(1).id ,iter->GetPoint(2).id });
	}
	return triList;
}

void RbsMesh::solidToTri(kernel::solid* s, std::vector<std::array<double, 3>>& pList, std::vector<std::array<int, 3>>& fList)
{
	pList.clear();
	fList.clear();
	std::unordered_map<vertex*, int> vList;

	face* fptr;
	loop* lptr;

	int count = 0;
	for (fptr = s->sfaces; fptr != nullptr; fptr = fptr->nextf)
	{
		for (lptr = fptr->floops; lptr != nullptr; lptr = lptr->nextl)
		{
			auto firstHf = lptr->ledges;
			auto hf = firstHf;
			do
			{
				auto v = hf->startv;
				if (vList.count(v) == 0)
				{
					vList[v] = count;
					pList.push_back({ v->p->px,v->p->py,v->p->pz });
					count++;
				}
				hf = hf->next;
			} while (hf != firstHf);
		}
	}

	std::cout << "-----point list-----" << std::endl;
	for (auto p : pList)
	{
		std::cout << p[0] << " " << p[1] << " " << p[2] << std::endl;
	}

	for (fptr = s->sfaces; fptr != nullptr; fptr = fptr->nextf)
	{
		auto faces = this->polyToTri(fptr, vList);
		for (auto f : faces)
		{
			fList.push_back(f);
			std::cout << f[0] << " " << f[1] << " " << f[2] << std::endl;
		}
		std::cout << std::endl;
	}
}

