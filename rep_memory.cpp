#include "rep_memory.h"
#include <fstream>
void FilmeRepoFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) {
		//verify if the stream is opened
		throw RepoExceptions("Error open:" + fName + "\n");
	}
	while (!in.eof()) {
		string titlu;
		string gen;
		int an;
		string actor;
		in >> titlu;
		in >> gen;
		in >> an;
		in >> actor;
		Filme f{ titlu,gen,an,actor };
		FilmeRepo::inchirieri(f);
	}
	in.close();
}
void FilmeRepoFile::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) {
		throw RepoExceptions("Error open file\n");
	}
	for (auto& f : getAll()) {
		out << "\n" << f.getTitlu() << " " << f.getGen() << " " << f.getAn() << " " << f.getActor();
	}
	out.close();
}