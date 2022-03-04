#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Filme.h"

class Filme : public QMainWindow
{
    Q_OBJECT

public:
    Filme(QWidget *parent = Q_NULLPTR);

private:
    Ui::FilmeClass ui;
};
