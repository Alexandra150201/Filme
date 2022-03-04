#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC
#include "MyGUI.h"
#include"rep_memory.h"
#include "service.h"
#include"Repo_abstract.h"
#include"validare.h"
#include"utils.h"
#include "cos.h"
#include"undo.h"
#include"teste.h"
int main(int argc, char *argv[])
{
    teste();
    QApplication a(argc, argv);
    Validator val;
    FilmeRepoFile rep{ "filme.txt" };
    Cos c{ rep };
    Service srv{ rep,val,c };
    MyGUI* gui = new MyGUI{ srv };
    gui->show();
    _CrtDumpMemoryLeaks();
    return a.exec();
   
}
