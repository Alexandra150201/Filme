#pragma once
#include "rep_memory.h"
#include"Repo_lab.h"
#include"observer.h"
class Cos: public Observable
{
	//FilmeRepo& rep;
	Repo_abstract& rep;
	vector<Filme> cos;

public:
	/*constructor clasa cos*/
	//Cos(FilmeRepo& rep) :rep{rep}{}
	Cos(Repo_abstract& rep) :rep{ rep } {}

	/*returneaza cosul*/
	const vector<Filme>& getAll() { return cos; }

	/*goleste lista de filme inchiriate*/
	void goleste();

	/*adauga u film in cos sau arunca exceptie daca acesta nu exista*/
	void adaugaCos(const string& titlu, const string& gen);

	/*genereaza automat o lista de filme inchiriate*/
	void genereaza(const int n);

	/*exporta cosul intr un fisier primit ca parametru*/
	void exportf(const string& fname);

	int getCount(const Filme& f) const
	{
		int nr = 0;
		for (const Filme& i : cos)
			if (i.getTitlu() == f.getTitlu() && i.getGen() == f.getGen())
				nr++;
		return nr;
	}

	/*primeste string titlu,string gen
	cauta un film si l sterge din lista daca exista*/
	void sterge(const string& titlu, const string& gen) {
		if(cos.empty()==false)
			cos.erase(std::remove_if(cos.begin(), cos.end(), [titlu, gen](const Filme& f) {return f.getTitlu() == titlu && f.getGen() == gen; }), cos.end());
	};

	/*primeste string titlu,string gen,int an,string actor
	creeaza,valideaza un film si l modifica in lista daca e valid si existent*/
	void modifica(const string& titlu, const string& gen, const int an, const string& actor) {
		if (cos.empty() == false)
			for (Filme& f : cos)
				if (f.getTitlu() == titlu && f.getGen() == gen){
					f.setAn(an);
				    f.setActor(actor);}
	};
};

