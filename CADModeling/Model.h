#pragma once
#include"BClass.h"
#include"Singleton.h"
#include<iostream>
#include<QDebug>
using namespace std;

class Model :public Singleton<Model>
{
public:
	Model() = default;
	static Model * Instance() {
		return Singleton<Model>::GetSingletonPtr();
	}
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
	void  mvfs(Coordinate* coordinate);//构造一个体 一个面 一个外环 一个点
	Vertex* mev(Vertex *sv, Loop* lp, Coordinate *coordinate);//生成一个新点 同时构造一条连接新点与另一给定点的边（半边）
	void mef(Vertex* sv, Vertex *ev, Loop *loop);//给定两个点，构造新边 新环 新面
	void kemr(Edge* e, Loop *loop);//消去环中一条边 构造一个内环
	void kfmrh(Face *faceToDelete, Face *outerface);//删除一个面 将其定义为一个内环 进而在体中构建一个亏格 或者将两个物体合并
	void semv(Edge* e, Coordinate *coordinate);//给定边上构造一个新点，同时将边分离为两条边
	void sweep(Coordinate *oritation, Loop *loop);//扫成操作
	void kemr(Vertex*sv, Vertex* ev, Loop *loop);//消去环中一条边 构造一个内环
	void semv(Vertex*sv, Vertex* ev, Coordinate *coordinate);//给定边上构造一个新点，同时将边分离为两条边

	void clear();
	void updateGUI();
	~Model();

private:
	HalfEdge* GetHfEdge(Loop* lp, Vertex* v);
	Edge* GetEdge(Vertex*sv, Vertex*ev);
	inline void AddEdge(Edge* edge);
	inline void AddFace(Face* face);
	inline void DeleteEdge(Edge *edge);
	inline void DeleteFace(Face *face);
};

