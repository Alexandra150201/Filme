#include "MyGUI.h"
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qmessagebox.h>
#include<QtWidgets/qformlayout.h>

vector<string> genuri;
void MyGUI::initGUICmp()
{
	QHBoxLayout* lyMain = new QHBoxLayout;
	setLayout(lyMain);

	QVBoxLayout* ly = new QVBoxLayout;
	lyMain->addLayout(ly);
	ly->addWidget(lstfilme);
	lstfilme->setUniformItemSizes(true);
	lstfilme->setModel(model);
	tabel->setModel(model);
	ly->addWidget(tabel);
	ly->addWidget(btnSortaret);
	ly->addWidget(btnSortareAct);
	ly->addWidget(btnSortareAn);

	QHBoxLayout* ly2 = new QHBoxLayout;
	ly->addLayout(ly2);
	ly2->addWidget(btnfiltraret);
	ly2->addWidget(btnfiltrarean);

	QFormLayout* lyForm = new QFormLayout;
	lyForm->addRow("Titlu", editTitlu);
	lyForm->addRow("Gen", editGen);
	lyForm->addRow("An", editAn);
	lyForm->addRow("Actor", editActor);
	lyForm->addRow("Introduceti:", editInput);
	lyForm->addWidget(btnAdauga);
	lyForm->addWidget(btnSterge);
	lyForm->addWidget(btnModifica);
	lyForm->addWidget(btnCauta);
	lyForm->addWidget(btnGolestecampuri);
	lyForm->addWidget(butonRaport);
	lyForm->addWidget(butonUndo);
	lyForm->addWidget(butonAdaugac);
	lyForm->addWidget(butonGolestec);
	lyForm->addWidget(butonGenereazac);
	lyForm->addWidget(butonExportc);
	lyForm->addWidget(btn1);
	lyForm->addWidget(btn2);
	lyMain->addLayout(lyForm);

	
}


void MyGUI::connectSignals()
{
	QObject::connect(lstfilme->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (lstfilme->selectionModel()->selectedIndexes().isEmpty()) {
			editTitlu->setText("");
			editAn->setText("");
			editGen->setText("");
			editActor->setText("");
			return;
		}
		int selRow = lstfilme->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = lstfilme->model()->index(selRow, 0);
		auto cellValue = lstfilme->model()->data(cel0Index, Qt::DisplayRole).toString();
		editTitlu->setText(cellValue);

		auto cel1Index = lstfilme->model()->index(selRow, 1);
		auto cellValue1 = lstfilme->model()->data(cel1Index, Qt::DisplayRole).toString();
		editGen->setText(cellValue1);

		auto cel2Index = lstfilme->model()->index(selRow, 2);
		auto cellValue2 = lstfilme->model()->data(cel2Index, Qt::DisplayRole).toString();
		editAn->setText(cellValue2);

		auto cel3Index = lstfilme->model()->index(selRow, 3);
		auto cellValue3 = lstfilme->model()->data(cel3Index, Qt::DisplayRole).toString();
		editActor->setText(cellValue3);
		});
	QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tabel->selectionModel()->selectedIndexes().isEmpty()) {
			editTitlu->setText("");
			editAn->setText("");
			editGen->setText("");
			editActor->setText("");
			return;
		}
		int selRow = tabel->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tabel->model()->index(selRow, 0);
		auto cellValue = tabel->model()->data(cel0Index, Qt::DisplayRole).toString();
		editTitlu->setText(cellValue);

		auto cel1Index = tabel->model()->index(selRow, 1);
		auto cellValue1 = tabel->model()->data(cel1Index, Qt::DisplayRole).toString();
		editGen->setText(cellValue1);

		auto cel2Index = tabel->model()->index(selRow, 2);
		auto cellValue2 = tabel->model()->data(cel2Index, Qt::DisplayRole).toString();
		editAn->setText(cellValue2);

		auto cel3Index = tabel->model()->index(selRow, 3);
		auto cellValue3 = tabel->model()->data(cel3Index, Qt::DisplayRole).toString();
		editActor->setText(cellValue3);
		});
	QObject::connect(btnAdauga, &QPushButton::clicked, [this]() {
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toInt();
		string actor = editActor->text().toStdString();
		try {
			srv.add(titlu, gen, an, actor);
			model->setFilme(srv.getAll());
		}
		catch (RepoExceptions& e) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(e.getMessage()));
		}
		catch (ValidateException& e) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(e.get_message()));
		}
		});
	QObject::connect(btnSterge, &QPushButton::clicked, [this]() {
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		try {
			srv.sterge(titlu, gen);
			model->setFilme(srv.getAll());
		}
		catch (RepoExceptions& e) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(e.getMessage()));
		}
		catch (ValidateException& e) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(e.get_message()));
		}
		});
	QObject::connect(btnModifica, &QPushButton::clicked, [this]() {
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toInt();
		string actor = editActor->text().toStdString();
		try {
			srv.modifica(titlu, gen, an, actor);
			model->setFilme(srv.getAll());;
		}
		catch (RepoExceptions& e) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(e.getMessage()));
		}
		catch (ValidateException& e) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(e.get_message()));
		}
		});
	QObject::connect(btnCauta, &QPushButton::clicked, [this]() {
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		try {
			const Filme& f=srv.cauta(titlu, gen);
			QMessageBox::information(this, "Film gasit", QString::fromStdString(f.getTitlu()+" "+f.getGen()+" "+to_string(f.getAn())+" "+f.getActor()));
		}
		catch (RepoExceptions& e) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(e.getMessage()));
		}
		catch (ValidateException& e) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(e.get_message()));
		}
		});
	QObject::connect(btnGolestecampuri, &QPushButton::clicked, [this]() {
		editTitlu->setText("");
		editGen->setText("");
		editAn->setText("");
		editActor->setText("");
		});
	QObject::connect(btnSortaret, &QCheckBox::clicked, [this]() {
		try {
			srv.sortare(funcTit);
			model->setFilme(srv.getAll());
		}
		catch (RepoExceptions& e) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(e.getMessage()));
		}
		catch (ValidateException& e) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(e.get_message()));
		}
		});
	QObject::connect(btnSortareAct, &QPushButton::clicked, [this]() {
		try {
			srv.sortare(funcAct);
			model->setFilme(srv.getAll());
		}
		catch (RepoExceptions& e) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(e.getMessage()));
		}
		catch (ValidateException& e) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(e.get_message()));
		}
		});
	QObject::connect(btnSortareAn, &QPushButton::clicked, [this]() {
		try {
			srv.sortare(funcAngen);
			model->setFilme(srv.getAll());
		}
		catch (RepoExceptions& e) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(e.getMessage()));
		}
		catch (ValidateException& e) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(e.get_message()));
		}
		});
	QObject::connect(btnfiltraret, &QPushButton::clicked, [this]() {
		string titlua = editTitlu->text().toStdString();
		const vector<Filme>& f=srv.filtreaza_titlu(titlua[0]);
		model->setFilme(f);
		});
	QObject::connect(btnfiltrarean, &QPushButton::clicked, [this]() {
		int an = editAn->text().toInt();
		const vector<Filme>& f=srv.filtreaza_an(an);
		model->setFilme(f);
		});
	QObject::connect(butonRaport, &QPushButton::clicked, [=]() {
		try {
			const map <int, DTO>& repo_raport = srv.raport();
			string mesaj;
			for (const auto& el : repo_raport) {
				DTO p = el.second;
				mesaj = mesaj + to_string(el.first) + " apare de " + to_string(p.getCount() + 1) + " ori \n";
			}
			QMessageBox::information(this, "Raport", QString::fromStdString(mesaj));
		}
		catch ( RepoExceptions& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.getMessage())); }
		catch ( ValidateException& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(butonUndo, &QPushButton::clicked, [=]() {
		try {
			srv.undo();
			model->setFilme(srv.getAll());
		}
		catch (RepoExceptions& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.getMessage())); }
		catch (ValidateException& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonAdaugac, &QPushButton::clicked, [=]() {
		try {
			const string titlu = (editTitlu->text()).QString::toStdString();
			const string gen = (editGen->text()).QString::toStdString();
			srv.adaugaCos(titlu, gen);
		}
		catch (RepoExceptions& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.getMessage())); }
		catch (ValidateException& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonGolestec, &QPushButton::clicked, [=]() {
		try {
			srv.goleste();
		}
		catch (RepoExceptions& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.getMessage())); }
		catch (ValidateException& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonGenereazac, &QSlider::valueChanged, [=]() {
		try {
			const int nr = butonGenereazac->value();
			srv.genereaza(nr);
		}
		catch (RepoExceptions& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.getMessage())); }
		catch (ValidateException& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonExportc, &QPushButton::clicked, [=]() {
		try {
			const string denumire = (editInput->text()).QString::toStdString();
			srv.exportf(denumire);
		}
		catch (RepoExceptions& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.getMessage())); }
		catch (ValidateException& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(btn1, &QPushButton::clicked, [=]() {
		CosCRUDGui* gui = new CosCRUDGui{ srv.get_cos() };
		gui->show();
		});

	QObject::connect(btn2, &QPushButton::clicked, [=]() {
		CosReadOnlyGui* gui = new CosReadOnlyGui{srv.get_cos()};
		gui->show();
		});
}


void CosCRUDGui::initGUI()
{
	cos.addObserver(this);
	QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);
	tabel->setModel(model);
	mainLayout->addWidget(tabel);
	QFormLayout* lyForm = new QFormLayout;
	lyForm->addRow("Titlu", editTitlu);
	lyForm->addRow("Gen", editGen);
	lyForm->addWidget(butonAdaugac);
	mainLayout->addLayout(lyForm);

	QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tabel->selectionModel()->selectedIndexes().isEmpty()) {
			editTitlu->setText("");
			editGen->setText("");
			return;
		}
		int selRow = tabel->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tabel->model()->index(selRow, 0);
		auto cellValue = tabel->model()->data(cel0Index, Qt::DisplayRole).toString();
		editTitlu->setText(cellValue);

		auto cel1Index = tabel->model()->index(selRow, 1);
		auto cellValue1 = tabel->model()->data(cel1Index, Qt::DisplayRole).toString();
		editGen->setText(cellValue1);

		});
	QObject::connect(butonAdaugac, &QPushButton::clicked, [=]() {
		try {
			const string titlu = (editTitlu->text()).QString::toStdString();
			const string gen = (editGen->text()).QString::toStdString();
			cos.adaugaCos(titlu, gen);
			model->setFilme(cos.getAll());
			
		}
		catch (RepoExceptions& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.getMessage())); }
		catch (ValidateException& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
}

void MyGUI::setInitialGUIState()
{
	model->setFilme(srv.getAll());
}
