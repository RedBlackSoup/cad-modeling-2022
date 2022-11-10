#pragma once

namespace kernel 
{
	struct point;
	struct curve;
	struct surface;
	struct solid;
	struct face;
	struct loop;
	struct hfEdge;
	struct edge;
	struct vertex;
	struct point
	{
		point(double x, double y, double z)
		{
			px = x;
			py = y;
			pz = z;
		}
		double px, py, pz;
	};

	struct curve
	{

	};

	struct surface
	{

	};
	struct solid
	{
		solid* nexts = nullptr;
		face* sfaces = nullptr;
		vertex* svertices = nullptr;
	};
	struct face
	{
		face* nextf = nullptr;
		solid* fsolid = nullptr;
		loop* floops = nullptr;
	};

	struct loop
	{
		loop* nextl = nullptr;
		face* lface = nullptr;
		hfEdge* ledges = nullptr;
	};
	struct hfEdge
	{
		hfEdge* next = nullptr;
		vertex* startv = nullptr;
		edge* edg = nullptr;
		loop* wlp = nullptr;
	};
	struct edge
	{
		hfEdge* hf1 = nullptr, * hf2 = nullptr;

	};
	struct vertex
	{
		vertex* nextv = nullptr;
		point* p = nullptr;
	};



	class EulerOp
	{
	public:
		static solid* mvsf(vertex*& v0);
		void kvsf();

		static vertex* mev(vertex& v1, loop& lp);
		void kev();

		static face* mef(vertex& v1, vertex& v2, loop& lp);
		static face* mef(vertex& v1, vertex& v2, loop& lp, int mode);
		static void kef();

		static void kemr(vertex& v1, vertex& v2, loop& lp);

		void mekr();
		static void kfmrh(face& f1, face& f2);
		void mfkrh();
		void semv();
	};
}
