#pragma once
#include<QtWidgets/qwidget.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qslider.h>
#include<QtWidgets/qcheckbox.h>
#include<QtWidgets/qbuttongroup.h>
#include<QtWidgets/qtableview.h>
#include<QtWidgets/qlistview.h>
#include<QtWidgets/qlineedit.h>
#include<qpainter.h>
#include "service.h"
#include "observer.h"
#include "modelView.h"

class MyGUI : public QWidget
{
private:
	Service& srv;


	QPushButton* btnAdauga = new QPushButton{ "Adauga film" };
	QPushButton* btnSterge = new QPushButton{ "Sterge film" };
	QPushButton* btnModifica = new QPushButton{ "Modifica film" };
	QPushButton* btnCauta = new QPushButton{ "Cauta film" };
	QPushButton* btnGolestecampuri = new QPushButton{ "Goleste campuri" };
	QPushButton* btn1 = new QPushButton{ "CosCRUDGui" };
	QPushButton* btn2 = new QPushButton{ "CosReadOnlyGui" };

	QCheckBox* btnSortaret = new QCheckBox{ "Sortare filme dupa titlu" };
	QCheckBox* btnSortareAct = new QCheckBox{ "Sortare filme dupa actorul principal" };
	QCheckBox* btnSortareAn = new QCheckBox{ "Sortare filme dupa an si gen" };
	QPushButton* btnfiltraret = new QPushButton{ "Filtrare filme dupa prima litera din titlu" };
	QPushButton* btnfiltrarean = new QPushButton{ "Filtrare filme dupa an" };
	QPushButton* butonRaport = new QPushButton{ "Raport" };
	QPushButton* butonUndo = new QPushButton{ "Undo" };

	QListView* lstfilme = new QListView;

	QTableView* tabel = new QTableView();
	TableModel* model = new TableModel(srv.getAll());

	QLineEdit* editTitlu = new QLineEdit;
	QLineEdit* editAn = new QLineEdit;
	QLineEdit* editGen = new QLineEdit;
	QLineEdit* editActor = new QLineEdit;

	QLineEdit* editInput = new QLineEdit;
	QPushButton* butonAdaugac = new QPushButton{ "Adauga in cos" };
	QPushButton* butonGolestec = new QPushButton{ "Goleste cosul" };
	QSlider* butonGenereazac = new QSlider{ Qt::Horizontal };
	QPushButton* butonExportc = new QPushButton{ "Export" };

	void initGUICmp();
	void connectSignals();
	void setInitialGUIState();
public:
	MyGUI(Service& srv) :srv{ srv } {
		initGUICmp();
		connectSignals();
		setInitialGUIState();

	}
};

class CosCRUDGui : public QWidget, public Observer {
public:
	CosCRUDGui(Cos& cos) : cos{ cos } {
		cos.addObserver(this);
		initGUI();
		model->setFilme(cos.getAll());;
	}
	void update() override {
		model->setFilme(cos.getAll());;
	}
private:
	QLineEdit* editTitlu = new QLineEdit;
	QLineEdit* editGen = new QLineEdit;
	QPushButton* butonAdaugac = new QPushButton{ "Adauga in cos" };
	void initGUI();
	Cos& cos;
	QTableView* tabel = new QTableView();
	TableModel* model = new TableModel(cos.getAll());
	
};

class CosReadOnlyGui : public QWidget, public Observer {
public:
	CosReadOnlyGui(Cos& cos) : cos{ cos } {
		cos.addObserver(this);
		repaint();
	}
	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int t = 10;
		vector<Filme> f;
		for (const Filme& u : cos.getAll())
		{
			int ok = 0;
			for (const Filme& j : f)
				if (j.getTitlu() == u.getTitlu())
					ok = 1;
			if (ok == 0)
				f.push_back(u);
		}
		for (const Filme& u : f)
		{
			
			//p.drawEllipse(-cos.getCount(u) , -cos.getCount(u) , cos.getCount(u) * 40, cos.getCount(u) * 40);
			p.drawRect(t, 0, 20, cos.getCount(u)*20);
			t= t+ 30;
		}
	}
private:
	Cos& cos;

};


