#pragma once
#include<string>
#include<map>
#include"domain.h"
#include"rep_memory.h"
#include"Repo_abstract.h"
#include"Repo_lab.h"
#include"validare.h"
#include"utils.h"
#include "cos.h"
#include"undo.h"
using std::string;
using std::unique_ptr;
class Service {
private:
	//FilmeRepo& rep;
	Repo_abstract& rep;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	Validator& valid;
	Cos& cos;
public:
	//Service(FilmeRepo& rep, Validator& valid, Cos& cos) noexcept : rep{ rep }, valid{ valid }, cos{ cos }{};
	Service(Repo_abstract& rep, Validator& valid, Cos& cos) noexcept : rep{ rep }, valid{ valid }, cos{ cos }{};
	Service() = default;
	Service(const Service& ot)  = delete;
	Cos& get_cos() { return cos; }

	//functia de undo la ultima operatie
	void undo();
	/*primeste string titlu,string gen,int an,string actor
	creeaza,valideaza un film si l adauga in lista daca e valid*/
	void add(const string& titlu, const string& gen,const int an, const string& actor);

	/*primeste string titlu,string gen
	cauta un film si l sterge din lista daca exista*/
	void sterge(const string& titlu, const string& gen);

	/*primeste string titlu,string gen,int an,string actor
	creeaza,valideaza un film si l modifica in lista daca e valid si existent*/
	void modifica(const string& titlu,const string& gen,const int an,const  string& actor);
	
	/*returneaza toate filmele din lista*/
	const vector<Filme>& getAll() noexcept;

	/*primeste string titlu,string gen
	cauta in lista si returneaza daca e gasit, ridica exceptie daca nu*/
	const Filme& cauta(const string& titlu, const  string& gen);

	/*returneaza toate filmele din lista care incep cu litera l nume*/
	const vector<Filme> filtreaza_titlu(char l);

	/*returneaza toate filmele din lista care au anul an*/
	const vector<Filme> filtreaza_an(int an);

	/*goleste lista de filme inchiriate*/
	void goleste();

	/*adauga u film in cos sau arunca exceptie daca acesta nu exista*/
	void adaugaCos(const string& titlu, const string& gen);

	/*genereaza automat o lista de filme inchiriate*/
	void genereaza(const int n);

	/*exporta cosul intr un fisier primit ca parametru*/
	void exportf(const string& fname);

	/*returneaza toate filmele din cos*/
	const vector<Filme>& CgetAll() noexcept;

	const int getCount(const Filme& f) { return cos.getCount(f); }
	/*sorteazaza toate filmele din lista dupa ofunctie de sortare primita ca parametru*/
    void sortare(SortFunc fct);
	/*creeaza raport pt fiecare an din filmele existente*/
	const std::map<int, DTO> raport();
};
