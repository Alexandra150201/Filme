#pragma once
#include<assert.h>
#include"teste.h"
#include"repository.h"
#include"Repo_abstract.h"
#include"Repo_lab.h"
#include"service.h"
#include"cos.h"
#include<fstream>

void testeDomain() {
	FilmeRepo rep;
	Filme fo;
	Filme f{ "nume","gen",1,"actor" };
	assert(f.getTitlu() == "nume");
	assert(f.getGen() == "gen");
	assert(f.getAn() == 1);
	assert(f.getActor() == "actor");
}

void testeService(){
	FilmeRepo rep;
	//Repo_lab rep{ 0.0f };
	Validator valid;
	Cos c{ rep };
	Service serv{ rep,valid,c };
	serv.add("nume1", "gen1", 1002, "actor");
	serv.undo();
	const auto& f0 = serv.getAll();
	assert(f0.size() == 0);

	serv.add("nume", "gen", 1000, "actor");
	const auto& f=serv.getAll();
	assert(f.size() == 1);
	try {serv.add("", "", 1, "");
		assert(false);}
	catch (ValidateException& e) {
		assert(e.get_message() == "Titlu invalid\nGen invalid\nAn invalid\nActor invalid\n");
	}

	serv.add("nume1","gen1",1002,"actor");
	const auto& f1 = serv.getAll();
	assert(f1.size() == 2);

	serv.add("nume11", "gen11", 1002, "actor");
	const std::map<int, DTO> r = serv.raport();
	assert(r.begin()->first == 1000);
	serv.sterge("nume11", "gen11");
	DTO e = r.begin()->second;
	assert(e.getCount()==1);

	const Filme& fc = serv.cauta("nume1", "gen1");
	assert(fc.getAn() == 1002);
	try {serv.cauta("nume1", "gen");
		assert(false);}
	catch (RepoExceptions& e) {
		assert(e.getMessage() == "Film inexistent\n");
	}
	serv.add("nume2", "gen2", 1004, "actor");

	serv.sterge("nume1", "gen1");
	serv.undo();
	const auto& filmee2 = serv.getAll();
	assert(filmee2.size() == 3);

	serv.sterge("nume1", "gen1");
	serv.sterge("nume2", "gen2");
	const auto& filme2 = serv.getAll();
	assert(filme2.size() == 1);

	serv.modifica("nume", "gen", 2002, "actornou");
	const vector<Filme>& filme3 = serv.getAll();
	assert(filme3[0].getAn() == 2002);
	assert(filme3[0].getActor() == "actornou");

	serv.undo();
	const vector<Filme>& filme31 = serv.getAll();
	assert(filme31[0].getAn() == 1000);
	serv.modifica("nume", "gen", 2002, "actornou");

	auto filmef = serv.filtreaza_titlu('n');
	assert(filmef.size() == 1);
	auto filmef1 = serv.filtreaza_titlu('t');
	assert(filmef1.size() == 0);
	auto filmef2= serv.filtreaza_an(2002);
	assert(filmef2.size() == 1);
	auto filmef3 = serv.filtreaza_an(2000);
	assert(filmef3.size() == 0);

	serv.add("nume2", "gen2", 1000, "actor");
	serv.add("asd", "generic", 1008, "bert");
	serv.add("zax", "romantic", 2002, "cert");
	const auto& filmes = serv.getAll();
	assert(filmes.size() == 4);
	serv.sortare(funcTit);
	const auto& filmes1 = serv.getAll();
	assert(filmes1[0].getTitlu() == "asd");
	serv.sortare(funcAct);
	const auto& filmes2 = serv.getAll();
	assert(filmes2[0].getTitlu() == "nume2");
	serv.sortare(funcAngen);
	const auto& filmes3 = serv.getAll();
	assert(filmes3[0].getTitlu() == "nume2");
	

}



void testeRepo() {
	FilmeRepo rep;
	//Repo_lab rep{ 0.0f };
	Filme f{ "nume","gen",1001,"actor" };
	rep.inchirieri(f);
	const auto& filme = rep.getAll();
	assert(filme.size() == 1);

	try {rep.inchirieri(f);
		assert(false);}
	catch (RepoExceptions& e) {
		assert(e.getMessage()=="Film deja in lista\n");
	}

	Filme f1{ "nume1","gen1",1002,"actor" };
	rep.inchirieri(f1);
	const auto& filme1 = rep.getAll();
	assert(filme1.size() == 2);
	const Filme& fc=rep.cauta("nume1", "gen1");
	assert(fc.getAn() == 1002);
	try {rep.cauta("nume1", "gen");
		assert(false);}
	catch (RepoExceptions& e) {
		assert(e.getMessage() == "Film inexistent\n");
	}

	rep.sterge(f1);
	const auto& filme2 = rep.getAll();
	assert(filme2.size() == 1);

	Filme f2{ "nume","gen",2002,"actornou" };
	rep.modifica(f2);
	const auto& filme3 = rep.getAll();
	assert(filme3[0].getAn() == 2002);
	assert(filme3[0].getActor() == "actornou");
	
}
void TesteCos() {
	FilmeRepo rep;
	//Repo_lab rep{ 0.0f };
	Validator valid;
	Cos c{ rep };
	Service serv{ rep,valid,c };
	Filme f{ "nume","gen",1001,"actor" };
	Filme f2{ "nume","gen2",2002,"actornou" };
	Filme f3{ "nume","gen2",2000,"actornou" };
	rep.inchirieri(f2);
	rep.inchirieri(f);
	serv.genereaza(4);
	const auto& cosulet= serv.CgetAll();
	assert(cosulet.size() == 4);
	serv.goleste();
	const auto& cosule = serv.CgetAll();
	assert(cosule.size() == 0);
	serv.adaugaCos("nume", "gen");
	serv.adaugaCos("nume", "gen2");
	serv.modifica("nume", "gen2", 2000, "actornou");
	serv.sterge("nume", "gen2");
	const auto& cos = serv.CgetAll();
	assert(cos.size() == 1);
	serv.exportf("test.csv");
}

void TesteFisier() {
	FilmeRepoFile rep{ "test.txt" };

	Filme f{ "nume","gen",1001,"actor" };
	Filme f2{ "nume","gen2",2002,"actornou" };
	Filme f3{ "nume","gen2",2000,"actornou" };
	const auto& filme = rep.getAll();
	try {
		FilmeRepoFile rep2{ "inexistent.txt" };
		assert(false);}
	catch (RepoExceptions& e) {
		assert(e.getMessage() == "Error open:inexistent.txt\n");
	}

	assert(filme.size() == 1);
	rep.inchirieri(f2);
	rep.inchirieri(f);
	const auto& filme1 = rep.getAll();
	assert(filme1.size() == 3);
	rep.modifica(f3);
	assert(f3.getAn() == 2000);
	rep.sterge(f);
	rep.sterge(f3);
	const auto& filme2 = rep.getAll();
	assert(filme2.size() == 1);

}

void testeRepolab() {
	Filme f{ "nume","gen",1001,"actor" };
	Filme f2{ "nume2","gen2",2002,"actornou" };
	Filme f3{ "nume","gen",2000,"acto" };
	Filme f4{ "fp", "obl", 1200, "vasile" };
	Repo_lab repo{ 0 };
	// add + get_all
		assert(repo.getAll().size() == 0);
		repo.inchirieri(f);
		assert(repo.getAll().size() == 1);
		try {
			repo.inchirieri(f3);
			assert(false);}
		catch (RepoExceptions& ex) {
			assert(ex.getMessage() == "0.000000");
		}
		repo.inchirieri(f2);
		const vector<Filme>& list = repo.getAll();
		assert(list[0].getTitlu() == "nume");
		assert(list[1].getTitlu() == "nume2");

		// find
		const Filme& s = repo.cauta("nume","gen");
		assert(s.getAn() == 1001);
		assert(s.getActor() == "actor");
		try {
			repo.cauta("cv","dfg");
			assert(false);}
		catch (RepoExceptions& ex) {
			assert(ex.getMessage() == "0.000000");
		}

		// update
		repo.modifica(f3);
		const Filme& s1 = repo.cauta("nume","gen");
		assert(s1.getAn() == 2000);
		assert(s1.getActor() == "acto");
		try {
			repo.modifica(f4);
			assert(false);}
		catch (RepoExceptions& ex) {
			assert(ex.getMessage() == "0.000000");
		}

		// delete
		assert(repo.getAll().size() == 2);
		repo.sterge(f);
		assert(repo.getAll().size() == 1);
		try {
			repo.sterge(f4);
			assert(false);}
		catch (RepoExceptions& ex) {
			assert(ex.getMessage() == "0.000000");
		}
		// sort
		repo.sortare(funcAct);
		assert(repo.getAll().size() == 1);

	Repo_lab rep{ 1 };
	// add + get_all
	try {
		assert(rep.getAll().size() == 0);
		rep.inchirieri(f);}
	catch (RepoExceptions& ex) {
		assert(ex.getMessage() < "1.0000" || ex.getMessage() == "1.000000");
		assert(true);
	}
	try {
		assert(rep.getAll().size() == 0);
		rep.sterge(f);}
	catch (RepoExceptions& ex) {
		assert(ex.getMessage() < "1.0000" || ex.getMessage() == "1.000000");
		assert(true);
	}
	try {
		assert(rep.getAll().size() == 0);
		rep.modifica(f);}
	catch (RepoExceptions& ex) {
		assert(ex.getMessage() < "1.0000" || ex.getMessage() == "1.000000");
		assert(true);
	}
	try {
		assert(rep.getAll().size() == 0);
		rep.cauta("nume","gen");}
	catch (RepoExceptions& ex) {
		assert(ex.getMessage() < "1.0000" || ex.getMessage() == "1.000000");
		assert(true);
	}
	
}
void teste() {
	testeService();
	testeRepo();
	testeRepolab();
	testeDomain();
	TesteCos();
	TesteFisier();
}
