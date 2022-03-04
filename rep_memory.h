#pragma once
#include"repository.h"
#include"Repo_abstract.h"

class FilmeRepoFile :public FilmeRepo {
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();
public:
	FilmeRepoFile(std::string fName) :FilmeRepo(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}
	void inchirieri(const Filme& p) override {
		FilmeRepo::inchirieri(p);//apelam metoda din clasa de baza
		writeToFile();
	}
	void sterge(const Filme& p) override {
		FilmeRepo::sterge(p);//apelam metoda din clasa de baza
		writeToFile();
	}
	void modifica(const Filme& p) override {
		FilmeRepo::modifica(p);//apelam metoda din clasa de baza
		writeToFile();
	}
};

