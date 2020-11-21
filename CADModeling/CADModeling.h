#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CADModeling.h"
#include"GLWidget.h"
class CADModeling : public QMainWindow
{
    Q_OBJECT

public:
    CADModeling(QWidget *parent = Q_NULLPTR);

private:
	//�������
	void Btn_mvfs();
	void Btn_mef();
	void Btn_mev();
	void Btn_kfmrh();
	void Btn_kemr();
	void Btn_semv();
	void Btn_sweep();
	void Btn_clear();
	void Btn_example();
	//����
    Ui::CADModelingClass ui;
	GLWidget* glw;
};
