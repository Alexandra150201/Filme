#pragma once
#include<vector>
#include"domain.h"
#include"Repo_abstract.h"
//#include"VectorDinamic.h"
#include"utils.h"
using std::vector;

class RepoExceptions {
private:	
	string msg;
public:
	RepoExceptions(string mesaj) : msg{ mesaj } {}

	/*returneaza eroarea repo primita*/
	string getMessage() {
		return msg;}
};
class FilmeRepo : public Repo_abstract
{
private:
	vector<Filme> filme;
public:
	FilmeRepo() = default;
	FilmeRepo(const FilmeRepo& ot) = delete;

	/* adauga un film in lista sau ridica exceptii daca acesta exista deja*/
	void inchirieri(const Filme& film) override;

	/*primeste un film de tip Filme
	si l sterge din lista*/
	void sterge(const Filme& film) override;

	/* primeste un film de tip Filme
	modifica un film din lista */
	void modifica( const Filme& film) override;

	/* returneaza toate filmele din lista*/
	const vector<Filme>& getAll() noexcept override;

	/*primeste string titlu,string gen
	cauta in lista si returneaza daca e gasit, ridica exceptie daca nu*/
	const Filme& cauta(const string& titlu, const string& gen) override;

	/*sorteazaza toate filmele din lista dupa ofunctie de sortare primita ca parametru*/
	void sortare(SortFunc fct) override;

};
