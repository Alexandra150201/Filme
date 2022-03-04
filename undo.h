#pragma once
#include"domain.h"
#include "repository.h"
class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	//destrucorul e virtual pentru a ne asigura ca la delete se apeleaza destructorul
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Filme fAdaugat;
	//FilmeRepo& rep;
	Repo_abstract& rep;
public:
	//UndoAdauga(FilmeRepo& rep, const Filme& f) :rep{ rep }, fAdaugat{f} {}
	UndoAdauga(Repo_abstract& rep, const Filme& f) :rep{ rep }, fAdaugat{ f } {}
	void doUndo() override {
		rep.sterge(fAdaugat);
	}
};

class UndoSterge : public ActiuneUndo {
	Filme fSters;
	//FilmeRepo& rep;
	Repo_abstract& rep;
public:
	//UndoSterge(FilmeRepo& rep, const Filme& f) :rep{ rep }, fSters{ f } {}
	UndoSterge(Repo_abstract& rep, const Filme& f) :rep{ rep }, fSters{ f } {}
	void doUndo() override {
		rep.inchirieri(fSters);
	}
};

class UndoModifica : public ActiuneUndo {
	Filme fModificat;
	Filme fNemodificat;
	//FilmeRepo& rep;
	Repo_abstract& rep;
public:
	//UndoModifica(FilmeRepo& rep, const Filme& i, const Filme& f) :rep{ rep }, fNemodificat{ i }, fModificat{ f } {}
	UndoModifica(Repo_abstract& rep, const Filme& i, const Filme& f) :rep{ rep }, fNemodificat{ i }, fModificat{ f } {}
	void doUndo() override {
		rep.sterge(fModificat);
		rep.inchirieri(fNemodificat);
	}
};