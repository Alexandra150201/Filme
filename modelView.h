#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qboxlayout.h>
#include <qfilesystemmodel.h>
#include"domain.h"
#include<vector>
using std::vector;
class TableModel :public QAbstractTableModel{
private:	
	vector<Filme> lista;

public:
	TableModel(const vector<Filme>& filme) : lista{ filme }{}
	int rowCount(const QModelIndex&  = QModelIndex()) const override {
		return static_cast<int>(lista.size());
	}
	int columnCount(const QModelIndex& = QModelIndex()) const override {
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			qDebug() << "row:" << index.row() << " col:" << index.column();
			Filme f = lista[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(f.getTitlu());
			}
			if (index.column() == 1) {
				return QString::fromStdString(f.getGen());
			}
			if (index.column() == 2) {
				return QString::number(f.getAn());
			}
			if (index.column() == 3) {
				return QString::fromStdString(f.getActor());
			}

		}

		if (role == Qt::BackgroundRole) {
			if (index.row() % 2 == 0) {
				return QBrush(Qt::red);
			}
			else {
				return QBrush(Qt::yellow);
			}

		}
		return QVariant{};
	}
	void setFilme( const vector<Filme> filme)
	{
		this->lista = filme;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		emit layoutChanged();

	}
};
