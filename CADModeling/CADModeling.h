#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CADModeling.h"
#include"GLWidget.h"
#include<QPushButton>
#include"Model.h"
#include"Singleton.h"
#include<QDoubleSpinBox>
#include<QSpinBox>
class CADModeling : public QMainWindow
{
	Q_OBJECT

public:
	CADModeling(QWidget *parent = Q_NULLPTR);

private:
	//点击函数
	void Btn_mvfs();
	void Btn_mef();
	void Btn_mev();
	void Btn_kfmrh();
	void Btn_kemr();
	void Btn_semv();
	void Btn_sweep();
	void Btn_clear();
	//变量
	Ui::CADModelingClass ui;
	GLWidget* glw;
	QWidget* option;
	QWidget* info;

	QPushButton* btn_mvfs;
	QPushButton* btn_mef;
	QPushButton* btn_mev;

	QPushButton* btn_clear;
	QPushButton* btn_semv;

	QPushButton* btn_kfmrh;
	QPushButton* btn_sweep;
	QPushButton* btn_kemr;

	QDoubleSpinBox* dsb1, *dsb2, *dsb3;
	QSpinBox* loopid, *vertexid,*vertexid2,*faceid,*faceid2;
	//工具函数
	void UpdateGUI();
};
