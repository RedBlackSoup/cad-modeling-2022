#include "prefix.h"
#include "EulerOp.h"

namespace kernel
{
	solid* EulerOp::mvsf(vertex*& v0)
	{
		face* f = new face;
		solid* s = new solid;
		vertex* v = new vertex;
		loop* lp = new loop;
		v0 = v;
		s->sfaces = f;
		f->fsolid = s;
		f->floops = lp;
		lp->lface = f;
		lp->ledges = nullptr;
		return s;
	}

	vertex* EulerOp::mev(vertex& v1, loop& lp)
	{
		hfEdge* he1 = new hfEdge;
		hfEdge* he2 = new hfEdge;
		edge* eg = new edge;
		vertex* v2 = new vertex;
		he1->wlp = &lp;
		he2->wlp = &lp;
		he1->startv = &v1;
		he2->startv = v2;
		he1->next = he2;
		eg->hf1 = he1;
		eg->hf2 = he2;
		he1->edg = eg;
		he2->edg = eg;
		if (lp.ledges == nullptr)
		{
			he2->next = he1;
			lp.ledges = he1;
		}
		else
		{
			hfEdge* he = lp.ledges;
			for (; he->next->startv != &v1; he = he->next);
			he2->next = he->next;
			he->next = he1;
		}
		return v2;
	}

	face* EulerOp::mef(vertex& v1, vertex& v2, loop& lp)
	{
		hfEdge* he1 = new hfEdge;
		hfEdge* he2 = new hfEdge;
		face* f = new face;
		loop* newLp = new loop;
		newLp->lface = f;
		f->floops = newLp;

		he1->wlp = &lp;
		he2->wlp = &lp;

		he1->next = he2;

		hfEdge* he = lp.ledges;
		for (; he->next->startv != &v1; he = he->next);
		he2->next = he->next;
		he->next = he1;
		for (; he->next->startv != &v2; he = he->next);
		he1->next = he->next;
		he->next = he2;

		lp.ledges = he2->next;
		newLp->ledges = he1;

		he = he1;
		do
		{
			he->wlp = newLp;
			he = he->next;
		} while (he != he1);

		he1->startv = &v1;
		he2->startv = &v2;

		f->nextf = lp.lface->nextf;
		lp.lface->nextf = f;
		f->fsolid = lp.lface->fsolid;
		
		return f;
	}

	face* EulerOp::mef(vertex& v1, vertex& v2, loop& lp, int mode)
	{
		hfEdge* he1 = new hfEdge;
		hfEdge* he2 = new hfEdge;
		face* f = new face;
		loop* newLp = new loop;
		newLp->lface = f;
		f->floops = newLp;

		he1->wlp = &lp;
		he2->wlp = &lp;

		he1->next = he2;

		hfEdge* he = lp.ledges;
		if (mode == 1)
		{
			for (; he->next->startv != &v2; he = he->next);
		}
		for (; he->next->startv != &v1; he = he->next);
		he2->next = he->next;
		he->next = he1;
		for (; he->next->startv != &v2; he = he->next);
		he1->next = he->next;
		he->next = he2;

		lp.ledges = he2->next;
		newLp->ledges = he1;

		he = he1;
		do
		{
			he->wlp = newLp;
			he = he->next;
		} while (he != he1);

		he1->startv = &v1;
		he2->startv = &v2;

		f->nextf = lp.lface->nextf;
		lp.lface->nextf = f;
		f->fsolid = lp.lface->fsolid;

		return f;
	}

	void EulerOp::kemr(vertex& v1, vertex& v2, loop& lp)
	{
		auto he = lp.ledges;
		hfEdge* he1 = nullptr, *he2 = nullptr;
		// look for he1, he2
		do
		{
			if (he->next->startv == &v1 && he->next->next->startv == &v2)
			{
				he1 = he;
			}
			if (he->next->startv == &v2 && he->next->next->startv == &v1)
			{
				he2 = he;
			}
			he = he->next;
		} while (he != lp.ledges && (he1 == nullptr || he2 == nullptr));

		if (he1 == nullptr || he2 == nullptr)
		{
			std::cerr << "kemr -- pass error loop point!" << std::endl;
			exit(0);
		}

		// change half edge connection 
		auto delHe1 = he1->next;
		auto delHe2 = he2->next;
		he1->next = delHe2->next;
		he2->next = delHe1->next;
		he1->wlp->ledges = he1->next;		
		delete delHe1, delHe2;

		// add ring
		loop* rlp = new loop;
		auto f = he1->wlp->lface;
		rlp->ledges = he2->next;
		rlp->lface = f;
		rlp->nextl = f->floops->nextl;
		f->floops->nextl = rlp;
	}

	void EulerOp::kfmrh(face& f1, face& f2)
	{
		// kill f1 and make ring in f2
		solid* obj = f1.fsolid;
		if (obj != f2.fsolid)
		{
			std::cerr << "kfmrh -- faces should belong to one object." << std::endl;
			exit(0);
		}
		loop* lp = f2.floops;
		for (; lp->nextl != nullptr; lp = lp->nextl);
		lp->nextl = f1.floops;
		if (obj->sfaces == &f1)
		{
			obj->sfaces = f1.nextf;
		}
		else
		{
			face* f = obj->sfaces;
			for (; f->nextf != &f1; f = f->nextf);
			f->nextf = f1.nextf;
		}
		delete& f1;
	}
}

