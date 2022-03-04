#pragma once
#include<vector>
#include"domain.h"
#include"utils.h"
using std::vector;
class Repo_abstract
{
public:
	void virtual inchirieri(const Filme& film) = 0;
	void virtual sterge(const Filme& film) = 0;
	void virtual modifica(const Filme& film) = 0;
	virtual const vector<Filme>& getAll() noexcept = 0;
	virtual const Filme& cauta(const string& titlu, const string& gen) = 0;
	virtual void sortare(SortFunc fct) = 0;

};

