#pragma once
#include"BClass.h"
#include"Singleton.h"
#include<iostream>
#include<QDebug>
using namespace std;

class Model :public Singleton<Model>
{
public:
	Model();
	static Model * GetModel() {
		return Singleton<Model>::GetSingletonPtr();
	}
	//ŷ����ʽ
	//v-e+f=2(s-h)+r
	/*
	v  e  f  h  r  s       s������ h���� r�ڻ�
	1  1  0  0  0  0  mev
	0  1  1  0  0  0  mef
	1  0  1  0  0  1  mvfs
	0 -1  0  0  1  0  kemr
	0  0 -1  1  1  0  kfmrh
	*/
	Solid* mvfs(Coordinate* coordinate);//����һ���� һ���� һ���⻷ һ����
	Vertex* mev(Vertex *sv, Loop* lp, Coordinate *coordinate);//����һ���µ� ͬʱ����һ�������µ�����һ������ıߣ���ߣ�
	void mef(Vertex* sv, Vertex *ev, Loop *loop);//���������㣬�����±� �»� ����
	void kemr(Edge* e, Loop *loop);//��ȥ����һ���� ����һ���ڻ�
	void kfmrh(Face *faceToDelete, Face *outerface);//ɾ��һ���� ���䶨��Ϊһ���ڻ� ���������й���һ������ ���߽���������ϲ�
	void semv(Edge* e, Coordinate *coordinate);//�������Ϲ���һ���µ㣬ͬʱ���߷���Ϊ������
	void sweep(Coordinate *oritation, Loop *loop);//ɨ�ɲ���
	void clear();
	void updateGUI();
	~Model();

private:
	HalfEdge* GetHfEdgeByVertex(Loop* lp, Vertex* v);
	inline void AddEdge(Edge* edge);
	inline void AddFace(Face* face);
	inline void DeleteEdge(Edge *edge);
	inline void DeleteFace(Face *face);
};

