#include "CADModeling.h"

CADModeling::CADModeling(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	glw = new GLWidget(ui.centralWidget->findChild<QOpenGLWidget*>("openGLWidget"));
}

void CADModeling::Btn_example()
{
}

void CADModeling::Btn_mvfs()
{
}

void CADModeling::Btn_mef()
{
}

void CADModeling::Btn_mev()
{
}

void CADModeling::Btn_kfmrh()
{
}

void CADModeling::Btn_kemr()
{
}

void CADModeling::Btn_semv()
{
}

void CADModeling::Btn_sweep()
{
}

void CADModeling::Btn_clear()
{
}
