#pragma once
#include<iostream>	
#include<vector>
#include"Singleton.h"
#include<QVector3d>
using namespace std;

class Vertex;
class HalfEdge;
class Edge;
class Loop;
class Face;
class Solid;
class Coordinate;

class Vertex {
public:
	int id;
	static vector<Vertex*>vertexarr;
	QVector3D coordinate;//����ϵ
	Vertex* next, *pre;
	static int vertexnum;
	Vertex(QVector3D co) :next(nullptr), pre(nullptr) {
		coordinate = co;
		id = vertexnum++;
		vertexarr.push_back(this);
	}
	void PrintVertex();
};


class HalfEdge {
public:
	Edge *edge;//�����
	Vertex *startv, *endv;//��� �յ�
	Loop *lp;//ָ��Ļ�
	HalfEdge *next, *pre;
	HalfEdge *peer;//�����෴���������
	HalfEdge() :edge(nullptr), startv(nullptr), endv(nullptr), next(nullptr), pre(nullptr), peer(nullptr) {}
	void PrintHalfEdge();
};

class Edge {
public:
	HalfEdge *half_l, *half_r;//ָ�������߼����
	Edge* next, *pre;
	int id;
	static int edgenum;
	Edge(void) :half_l(nullptr), half_r(nullptr), next(nullptr), pre(nullptr) {
		id = edgenum++;
	}
};

class Loop {
public:
	int id;
	static vector<Loop*>looparr;
	static int loopnum;
	HalfEdge *halfedge;
	Face *face;
	Loop* next, *pre;
	QVector3D normal;//����
	Loop() :halfedge(nullptr), face(nullptr), next(nullptr), pre(nullptr) {
		id = loopnum++;
		looparr.push_back(this);
	}
	QVector3D GetOritation();
	void PrintLoop();
};

class Face {
public:
	int id;
	Solid* solid;
	Loop *loop_out, *loop_inner;//�⻷ �ڻ�
	Face *next, *pre;
	static int facenum;
	Face() :solid(nullptr), loop_inner(nullptr), loop_out(nullptr), next(nullptr), pre(nullptr) {
		id = facenum++;
	}
	~Face();
	void AddInnerLoop(Loop* &lp);
};

class Solid :public Singleton<Solid> {
public:
	int id;
	Face* face;
	Edge *edge;
	static int solidnum;
	void PrintSolid();
	Solid() :face(nullptr), edge(nullptr) {
		id = solidnum++;
	}
	static Solid* Instance() {
		return Singleton<Solid>::GetSingletonPtr();
	}
};

class Coordinate {
public:
	float x, y, z;
	Coordinate() {
		x = 1.0;
		y = 0;
		z = 0;
	}
	Coordinate(float xm, float ym, float zm) {
		x = xm;
		y = ym;
		z = zm;
	}
	static	Coordinate* CrossProduct(Coordinate *a, Coordinate *b);
	static	Coordinate* Normalised(Coordinate *c);
	static	Coordinate* AddCoordinate(Coordinate* a, Coordinate* b);
	static	Coordinate* SubCoordinate(Coordinate* a, Coordinate* b);
	static QVector3D ToQVec3d(Coordinate* coor);

	QVector3D operator+ (Coordinate*a);
	QVector3D operator- (Coordinate*a);
};

class Matrix4 {
public:
	Matrix4();
	double val[4][4];
	Matrix4(QVector3D axis, double angle);
	QVector3D dotProduct(QVector3D axis);
};