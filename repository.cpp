#include "repository.h"
#include<algorithm>

void FilmeRepo::inchirieri(const Filme& film) {
	for (const Filme& f : filme) {
		if (f.getTitlu() == film.getTitlu() && f.getGen() == film.getGen())
			throw RepoExceptions("Film deja in lista\n");}
	filme.push_back(film);}

void FilmeRepo::sterge(const Filme& film)
{
	filme.erase(std::remove_if(filme.begin(),filme.end(), [film](const Filme& f) {return f.getTitlu() == film.getTitlu() && f.getGen() == film.getGen(); }),filme.end());
}

void FilmeRepo::modifica(const Filme& film)
{
	for ( Filme& f : filme)
		if (f.getTitlu() == film.getTitlu() && f.getGen() == film.getGen())
		{
			f.setAn(film.getAn());
			f.setActor(film.getActor());
		}

}

const vector<Filme>& FilmeRepo::getAll() noexcept {
		return filme;}

const Filme& FilmeRepo::cauta(const string& titlu, const string& gen)
{
	vector<Filme>::iterator i = std::find_if(filme.begin(), filme.end(), [titlu, gen](const Filme& film) 
		{return film.getTitlu() == titlu && film.getGen() == gen; });
	if (i == filme.end())
		throw RepoExceptions("Film inexistent\n");
	else return *i;}

void FilmeRepo::sortare(SortFunc fct)
{
	sort(filme.begin(), filme.end(), fct);
}