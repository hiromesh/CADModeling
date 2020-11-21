#include "Model.h"

//欧拉公式
//v-e+f=2(s-h)+r
/*
v  e  f  h  r  s       s分离体 h亏格 r内环
1  1  0  0  0  0  mev
0  1  1  0  0  0  mef
1  0  1  0  0  1  mvfs
0 -1  0  0  1  0  kemr
0  0 -1  1  1  0  kfmrh
*/

//构造一个体 一个面 一个外环 一个点 
Solid* Model::mvfs(Coordinate *coordinate)
{
	Vertex* v = new Vertex(coordinate);//new vertex
	Solid *solid = new Solid;//new solid
	solid->face = new Face;//new face
	Face *f = solid->face;
	Loop* lp = new Loop();//new out loop
	v->pre = v;
	v->next = v;
	f->loop_out = lp;
	f->next = f;
	f->pre = f;
	f->solid = solid;
	lp->face = f;
	return solid;
}

//生成一个新点 同时构造一条连接新点与另一给定点的边（半边）
Vertex* Model::mev(Vertex *sv, Loop* lp, Coordinate* coordinate)
{
	Vertex *v = new Vertex(coordinate);//new vertex
	Edge *edge = new Edge();//new edge
	HalfEdge* hfedgel = new HalfEdge();
	HalfEdge* hfedger = new HalfEdge();

	edge->half_l = hfedgel;
	edge->half_r = hfedger;
	hfedgel->edge = edge;
	hfedger->edge = edge;
	hfedgel->peer = hfedger;
	hfedger->peer = hfedgel;
	hfedgel->startv = sv;
	hfedgel->endv = v;
	hfedger->startv = v;
	hfedger->endv = sv;

	v->next = sv->next;
	v->pre = sv;
	sv->next->pre = v;
	sv->next = v;

	if (lp->halfedge) {//find current first half edge
		HalfEdge* curHfEdge = GetHfEdgeByVertex(lp, sv);
		curHfEdge->next->pre = hfedger;
		hfedgel->next = hfedger;
		hfedger->pre = hfedgel;
		hfedger->next = curHfEdge->next;
		hfedgel->pre = curHfEdge;
		curHfEdge->next = hfedgel;
	}
	else {
		lp->halfedge = hfedgel;
		hfedgel->next = hfedger;
		hfedgel->pre = hfedger;
		hfedger->next = hfedgel;
		hfedger->pre = hfedgel;
	}
	if (Solid::Instance()->edge) {
		AddEdge(edge);
	}
	else {
		Solid::Instance()->edge = edge;
		edge->pre = edge;
		edge->next = edge;
	}
	//TODO
	return v;
}

//给定两个点，构造新边 新环 新面
void Model::mef(Vertex* sv, Vertex *ev, Loop *loop)
{
	//are sv and ev in the loop?
	bool isinloop = true;
	if (loop == nullptr)isinloop = false;
	else if (GetHfEdgeByVertex(loop, sv) == nullptr || GetHfEdgeByVertex(loop, ev) == nullptr)isinloop = false;

	//find the loop which the two vertex belong
	if (isinloop == false) {
		for (int i = 0; i < Loop::looparr.size(); i++) {
			if (GetHfEdgeByVertex(Loop::looparr[i], sv) && GetHfEdgeByVertex(Loop::looparr[i], ev)) {
				loop = Loop::looparr[i];
				break;
			}
		}
	}
	if (loop == nullptr || isinloop == false) {
		//TODO
		return;
	}
	HalfEdge* starthfEdge = GetHfEdgeByVertex(loop, sv);
	HalfEdge* endhfEdge = GetHfEdgeByVertex(loop, ev);

	//TODO

	Loop* newloop = new Loop();//new loop
	Face* newface = new Face();//new face
	Edge* newedge = new Edge();//new edge
	HalfEdge* newhfedgel = new HalfEdge();
	HalfEdge* newhfedger = new HalfEdge();

	//hfedge
	newhfedgel->endv = ev;
	newhfedgel->startv = sv;
	newhfedger->endv = sv;
	newhfedger->startv = ev;
	newhfedgel->edge = newedge;
	newhfedger->edge = newedge;

	//edge
	newedge->half_l = newhfedgel;
	newedge->half_r = newhfedger;

	//peer
	newhfedgel->peer = newhfedger;
	newhfedger->peer = newhfedgel;

	//face
	newface->loop_out = newloop;
	newloop->face = newface;
	newface->solid = Solid::Instance();

	newhfedgel->next = endhfEdge->next;
	newhfedgel->pre = starthfEdge;

	newhfedger->next = starthfEdge->next;
	newhfedger->pre = endhfEdge;

	endhfEdge->next->pre = newhfedgel;
	endhfEdge->next = newhfedger;
	starthfEdge->next->pre = newhfedger;
	starthfEdge->next = newhfedgel;

	//divide the original loop into two loop
	newloop->halfedge = newhfedger;
	loop->halfedge = newhfedgel;

	//add face and edge to the solid
	AddFace(newface);
	AddEdge(newedge);

	//TODO

}

//消去环中一条边 构造一个内环
void Model::kemr(Edge* e, Loop *loop)
{
	Loop* newloop = new Loop();//new loop

	//to delete
	HalfEdge* eleft = e->half_l;
	HalfEdge* eright = e->half_r;

	//intend to delete the begin edge and can not continue the following steps
	if (loop->halfedge == eleft || loop->halfedge == eright) {
		//TODO
		return;
	}

	//divide the original loop into two
	HalfEdge* it = eleft;
	while (it != eright) {
		//newloop takes another one
		if (it == loop->halfedge) {
			newloop->halfedge = eright->next;
			break;
		}
		it = it->next;
	}
	//newloop takes that one
	if (it == eright) {
		newloop->halfedge = eleft->next;
	}

	//update the relationship
	HalfEdge* newlooppre = newloop->halfedge->pre->peer->next;
	HalfEdge* newlooppost = newloop->halfedge->pre->pre;

	newloop->halfedge->pre = newlooppre->pre->pre;
	newlooppre->pre->pre->next = newloop->halfedge;

	//old one
	newlooppre->pre = newlooppost;
	newlooppost->next = newlooppre;

	//add loop to the face
	loop->face->AddInnerLoop(newloop);

	//delete edge
	DeleteEdge(e);

	//TODO

}

//删除一个面 将其定义为一个内环 进而在体中构建一个亏格 或者将两个物体合并
void Model::kfmrh(Face *faceToDelete, Face *outerface)
{
	if (faceToDelete->loop_out == nullptr) {
		//TODO
		return;
	}

	//turn the face's outloop into outerface's inloop
	outerface->AddInnerLoop(faceToDelete->loop_out);

	//update the relationship
	faceToDelete->loop_out->face = outerface;

	//delete face
	DeleteFace(faceToDelete);

	//TODO

}

void Model::semv(Edge* e, Coordinate* coordinate)//给定边上构造一个新点，同时将边分离为两条边
{
	HalfEdge* left = e->half_l;
	HalfEdge* right = e->half_r;
	//新点
	Vertex *v = new Vertex(coordinate);
	//新边
	Edge *new_e = new Edge();
	HalfEdge*new_hfl = new HalfEdge();
	HalfEdge*new_hfr = new HalfEdge();

	//边之间的关系
	new_e->half_l = new_hfl;
	new_e->half_r = new_hfr;

	new_hfl->edge = new_e;
	new_hfr->edge = new_e;

	new_hfl->peer = new_hfr;
	new_hfr->peer = new_hfl;

	//边和点之间的关系
	new_hfl->startv = v;
	new_hfl->endv = left->endv;
	new_hfr->startv = left->endv;
	new_hfr->endv = v;
	left->endv = v;
	right->startv = v;

	//指针间的关系
	new_hfl->next = left->next;
	new_hfl->pre = left;

	new_hfr->next = right;
	new_hfr->pre = new_hfl->next;

	right->pre = new_hfr;
	left->next = new_hfl;
	AddEdge(new_e);
	//TODO
}

void Model::sweep(Coordinate* oritation, Loop *loop)//扫成操作
{
	HalfEdge* it = loop->halfedge;
	vector<Vertex*>arra, arrb;
	while (true) {
		arra.push_back(it->startv);
		it = it->next;
		if (it == loop->halfedge)break;
	}
	for (auto ele : arra) {
		arrb.push_back(mev(ele, loop, Coordinate::AddCoordinate(ele->coordinate, oritation)));
	}
	for (int i = 0; i < arrb.size()-1; i++) {
		mef(arrb[i], arrb[i + 1], loop);
	}
	mef(arrb[0], arrb[arrb.size() - 1], loop);
	
	//TODO 
	
}

void Model::clear()
{
	while (Solid::Instance()->edge) {
		DeleteEdge(Solid::Instance()->edge);
	}
	while (Solid::Instance()->face) {
		DeleteFace(Solid::Instance()->face);
	}
}

void Model::updateGUI()
{
}

Model::~Model()
{

}

HalfEdge* Model::GetHfEdgeByVertex(Loop* lp, Vertex* v) {
	if (!lp->halfedge) {
		//TODO
		return nullptr;
	}
	HalfEdge* it = lp->halfedge;
	while (true) {
		if (it->endv == v) {
			return it;
		}
		it = it->next;
		if (it == lp->halfedge) {
			//TODO
			return nullptr;
		}
	}
}

void Model::AddEdge(Edge* edge) {
	Solid::Instance()->edge->pre->next = edge;
	edge->pre = Solid::Instance()->edge->pre;
	edge->next = Solid::Instance()->edge;
	Solid::Instance()->edge->pre = edge;
}

void Model::AddFace(Face* face) {
	Solid::Instance()->face->pre->next = face;
	face->pre = Solid::Instance()->face->pre;
	face->next = Solid::Instance()->face;
	Solid::Instance()->face->pre = face;
}

void Model::DeleteEdge(Edge *edge) {
	Edge* it = Solid::Instance()->edge;
	while (true) {
		if (it == edge) {
			//only one edge delete it straightly
			if (it->next == it) {
				Solid::Instance()->edge = nullptr;
			}
			else {
				//the edge to delete is the beginnning
				if (Solid::Instance()->edge == it) {
					Solid::Instance()->edge = it->next;
				}
				it->pre->next = it->next;
				it->next->pre = it->pre;
			}
			if (it->half_l) {
				delete it->half_l;
			}
			if (it->half_r) {
				delete it->half_r;
			}
			delete it;
			return;
		}
		it = it->next;
		//has searched all the edges
		if (Solid::Instance()->edge == it) {
			//TODO
			return;
		}
	}
}

inline void Model::DeleteFace(Face *face) {
	if (face->next == face) {
		Solid::Instance()->face = nullptr;
		delete face;
		return;
	}
	if (Solid::Instance()->face == face) {
		Solid::Instance()->face = face->next;
	}
	face->next->pre = face->pre;
	face->pre->next = face->next;
	delete face;
}


