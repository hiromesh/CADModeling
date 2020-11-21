#include "BClass.h"
int Vertex::vertexnum = 0;
int Edge::edgenum = 0;
int Loop::loopnum = 0;
int Face::facenum = 0;
int Solid::solidnum = 0;

vector<Vertex*>Vertex::vertexarr = vector<Vertex*>();
vector<Loop*>Loop::looparr = vector<Loop*>();

Face::~Face() {
	this->pre->next = this->next;
	this->next->pre = this->pre;
}

void Face::AddInnerLoop(Loop* &lp) {
	if (loop_inner) {//已经有了内环
		loop_inner->pre->next = lp;
		lp->next = loop_inner;
		lp->pre = loop_inner->pre;
		loop_inner->pre = lp;
		lp->face = this;
	}
	else {//第一个内环
		loop_inner = lp;
		lp->face = this;
		lp->next = lp;
		lp->pre = lp;
	}
}

Coordinate* Loop::GetOritation() {
	Coordinate *tmp;
	HalfEdge *iterator = halfedge;
	if (iterator == nullptr) {
		tmp->x = 1;
		tmp->y = 0;
		tmp->z = 0;
	}
	while (true) {
		//cross product
		Coordinate* a = Coordinate::SubCoordinate(iterator->startv->coordinate, iterator->endv->coordinate);
		Coordinate* b = Coordinate::SubCoordinate(iterator->next->startv->coordinate, iterator->next->endv->coordinate);
		Coordinate* c = Coordinate::CrossProduct(a, b);
		tmp = Coordinate::AddCoordinate(tmp, c);
		iterator = iterator->next;
		if (iterator == halfedge)//return to the beginning edge
			break;
	}
	//normalised
	tmp = Coordinate::Normalised(tmp);
	return tmp;
}

void Vertex::PrintVertex() {
	//TODO
}

void HalfEdge::PrintHalfEdge() {
	//TODO
}

void Loop::PrintLoop() {
	//TODO
}

void Solid::PrintSolid() {
	//TODO
}

Coordinate* Coordinate::CrossProduct(Coordinate* a, Coordinate* b) {
	Coordinate *res = new Coordinate;
	res->x = a->y*b->z - b->y*a->z;
	res->y = b->x*a->z - a->x*b->z;
	res->z = a->x*b->y - b->x*a->y;
	return res;
}

Coordinate*  Coordinate::Normalised(Coordinate* c) {
	float sum = sqrt(c->x*c->x + c->y*c->y + c->z*c->z);
	Coordinate* res = new Coordinate;
	res->x = c->x / sum;
	res->y = c->y / sum;
	res->z = c->z / sum;
	return res;
}

Coordinate* Coordinate::AddCoordinate(Coordinate* a, Coordinate* b) {
	Coordinate *res = new Coordinate;
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	return res;
}

Coordinate* Coordinate::SubCoordinate(Coordinate* a, Coordinate* b) {
	Coordinate* res = new Coordinate;
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return res;
}

QVector3D Coordinate::ToQVec3d(Coordinate * coor)
{
	return QVector3D(coor->x, coor->y, coor->z);
}

QVector3D Coordinate::operator+(Coordinate * a)
{
	return QVector3D(a->x+this->x,a->y+this->y,a->z+this->z);
}

QVector3D Coordinate::operator-(Coordinate * a)
{
	return QVector3D(this->x-a->x,this->y-a->y,this->z-a->z);
}

Matrix4::Matrix4()
{
}

Matrix4::Matrix4(QVector3D axis, double angle)
{
	axis.normalize();
	double n1 = axis.x(), n2 = axis.y(), n3 = axis.z();
	double tmp[4][4] = {
		n1*n1 + (1 - n1*n1)*cos(angle), n1*n2*(1 - cos(angle)) + n3*sin(angle),n1*n3*(1 - cos(angle)) - n2*sin(angle),0,
		n1*n2*(1 - cos(angle)) - n3*sin(angle),  n2*n2 + (1 - n2*n2)*cos(angle), n3*n2*(1 - cos(angle)) + n1*sin(angle),0,
		n1*n3*(1 - cos(angle)) + n2*sin(angle), n2*n3*(1 - cos(angle)) - n1*sin(angle),  n3*n3 + (1 - n3*n3)*cos(angle), 0,
		0,0,0,1
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			val[i][j] = tmp[i][j];
		}
	}
}

QVector3D Matrix4::dotProduct(QVector3D axis)
{
	double a[4] = { axis.x(),axis.y(), axis.z(),1 };
	double b[4] = { 0,0,0,0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			b[i] += val[i][j] * a[j];
		}
	}
	return QVector3D(b[0], b[1], b[2]);
}
