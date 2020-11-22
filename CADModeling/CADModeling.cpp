#include "CADModeling.h"

CADModeling::CADModeling(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	glw = new GLWidget(ui.centralWidget->findChild<QOpenGLWidget*>("openGLWidget"));
	option = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QWidget*>("option");
	btn_mvfs = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QPushButton*>("mvfs");
	btn_semv = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QPushButton*>("semv");
	btn_mef = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QPushButton*>("mef");

	btn_mev = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QPushButton*>("mev");
	btn_clear = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QPushButton*>("clear");
	btn_sweep = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QPushButton*>("sweep");

	btn_kemr = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QPushButton*>("kemr");
	btn_kfmrh = ui.centralWidget->findChild<QWidget*>("widget")->findChild<QPushButton*>("kfmrh");

	dsb1 = option->findChild<QDoubleSpinBox*>("dsb1");
	dsb2 = option->findChild<QDoubleSpinBox*>("dsb2");
	dsb3 = option->findChild<QDoubleSpinBox*>("dsb3");
	loopid = option->findChild<QSpinBox*>("loopid");
	vertexid = option->findChild<QSpinBox*>("vertexid");
	vertexid2 = option->findChild<QSpinBox*>("vertexid_2");
	faceid = option->findChild<QSpinBox*>("faceid");
	faceid2 = option->findChild<QSpinBox*>("faceid_2");

	connect(btn_mvfs, &QPushButton::clicked, this, &CADModeling::Btn_mvfs);
	connect(btn_semv, &QPushButton::clicked, this, &CADModeling::Btn_semv);
	connect(btn_mef, &QPushButton::clicked, this, &CADModeling::Btn_mef);

	connect(btn_mev, &QPushButton::clicked, this, &CADModeling::Btn_mev);
	connect(btn_clear, &QPushButton::clicked, this, &CADModeling::Btn_clear);
	connect(btn_kemr, &QPushButton::clicked, this, &CADModeling::Btn_kemr);

	connect(btn_kfmrh, &QPushButton::clicked, this, &CADModeling::Btn_kfmrh);
	connect(btn_sweep, &QPushButton::clicked, this, &CADModeling::Btn_sweep);

	btn_mvfs->setEnabled(true);
	btn_semv->setEnabled(false);
	btn_mef->setEnabled(false);

	btn_mev->setEnabled(false);
	btn_clear->setEnabled(true);

	btn_sweep->setEnabled(false);
	btn_kemr->setEnabled(false);
	btn_kfmrh->setEnabled(false);

}

void CADModeling::Btn_mvfs()
{
	Model::Instance()->mvfs(&Coordinate(0, 0, 0));
	btn_mvfs->setEnabled(false);
	btn_mev->setEnabled(true);
	UpdateGUI();
}

void CADModeling::Btn_mef()
{
	Vertex *sv; Vertex* ev; Loop* lp;
	for (int i = 0; i < Loop::looparr.size(); i++) {
		if (Loop::looparr[i]->id == loopid->value()) {
			lp = Loop::looparr[i];
			break;
		}
	}
	for (int i = 0; i < Vertex::vertexarr.size(); i++) {
		if (Vertex::vertexarr[i]->id == vertexid->value()) {
			sv = Vertex::vertexarr[i];
			break;
		}
	}
	for (int i = 0; i < Vertex::vertexarr.size(); i++) {
		if (Vertex::vertexarr[i]->id == vertexid2->value()) {
			ev = Vertex::vertexarr[i];
			break;
		}
	}
	btn_sweep->setEnabled(true);
	btn_kfmrh->setEnabled(true);
	Model::Instance()->mef(sv, ev, lp);
	UpdateGUI();
}

void CADModeling::Btn_mev()
{
	Loop* lp; Vertex* vp;
	for (int i = 0; i < Loop::looparr.size(); i++) {
		if (Loop::looparr[i]->id == loopid->value()) {
			lp = Loop::looparr[i];
			break;
		}
	}
	for (int i = 0; i < Vertex::vertexarr.size(); i++) {
		if (Vertex::vertexarr[i]->id == vertexid->value()) {
			vp = Vertex::vertexarr[i];
			break;
		}
	}
	btn_mef->setEnabled(true);
	btn_kemr->setEnabled(true);

	Model::Instance()->mev(vp, lp, &Coordinate(dsb1->value(), dsb2->value(), dsb3->value()));
	vertexid->setValue(vertexid->value() + 1);
	UpdateGUI();
}

void CADModeling::Btn_kfmrh()
{
	Face *fa; Face* fb;

	Face* fit = Solid::Instance()->face;
	while (true) {
		if (fit->id == faceid->value()) {
			fa = fit;
			break;
		}
		fit = fit->next;
		if (fit == Solid::Instance()->face)
			break;
	}


	fit = Solid::Instance()->face;
	while (true) {
		if (fit->id == faceid2->value()) {
			fb = fit;
			break;
		}
		fit = fit->next;
		if (fit == Solid::Instance()->face)
			break;
	}

	Model::Instance()->kfmrh(fa, fb);
	UpdateGUI();
}

void CADModeling::Btn_kemr()
{
	Vertex *sv;
	Vertex* ev;
	Loop* lp;
	for (int i = 0; i < Loop::looparr.size(); i++) {
		if (Loop::looparr[i]->id == loopid->value()) {
			lp = Loop::looparr[i];
			break;
		}
	}
	for (unsigned int i = 0; i < Vertex::vertexarr.size(); i++) {
		if (Vertex::vertexarr[i]->id == vertexid->value()) {
			sv = Vertex::vertexarr[i];
			break;
		}
	}
	for (unsigned int i = 0; i < Vertex::vertexarr.size(); i++) {
		if (Vertex::vertexarr[i]->id == vertexid2->value()) {
			ev = Vertex::vertexarr[i];
			break;
		}
	}
	Model::Instance()->kemr(sv, ev, lp);
	UpdateGUI();
}

void CADModeling::Btn_semv()
{
	Vertex *sv;
	Vertex* ev;
	for (unsigned int i = 0; i < Vertex::vertexarr.size(); i++) {
		if (Vertex::vertexarr[i]->id == vertexid->value()) {
			sv = Vertex::vertexarr[i];
			break;
		}
	}
	for (unsigned int i = 0; i < Vertex::vertexarr.size(); i++) {
		if (Vertex::vertexarr[i]->id == vertexid2->value()) {
			ev = Vertex::vertexarr[i];
			break;
		}
	}
	Model::Instance()->semv(sv, ev, &Coordinate(dsb1->value(), dsb2->value(), dsb3->value()));
	UpdateGUI();
}

void CADModeling::Btn_sweep()
{
	Loop* lp;
	for (int i = 0; i < Loop::looparr.size(); i++) {
		if (Loop::looparr[i]->id == loopid->value()) {
			lp = Loop::looparr[i];
			break;
		}
	}
	Model::Instance()->sweep(&Coordinate(dsb1->value(), dsb2->value(), dsb3->value()), lp);
	UpdateGUI();
}

void CADModeling::Btn_clear()
{
	Face::facenum = 0;
	Edge::edgenum = 0;
	Loop::looparr.clear();
	Loop::loopnum = 0;
	Vertex::vertexarr.clear();
	Vertex::vertexnum = 0;
	Model::Instance()->clear();
	Solid::Instance()->face = nullptr;
	UpdateGUI();
	btn_mvfs->setEnabled(true);
	btn_semv->setEnabled(false);
	btn_mef->setEnabled(false);

	btn_mev->setEnabled(false);
	btn_clear->setEnabled(true);

	btn_sweep->setEnabled(false);
	btn_kemr->setEnabled(false);
	btn_kfmrh->setEnabled(false);
}

void CADModeling::UpdateGUI()
{
	if (!Loop::looparr.empty())
		Loop::looparr[Loop::looparr.size() - 1]->normal = Loop::looparr[Loop::looparr.size() - 1]->GetOritation();
	glw->update();

}
