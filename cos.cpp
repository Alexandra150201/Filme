#include "cos.h"
#include<fstream>
#include<algorithm>
#include<random>
#include<chrono> 
using std::ofstream;

void Cos::goleste()
{
	cos.erase(cos.begin(),cos.end());
	notify();
}

void Cos::adaugaCos(const string& titlu, const string& gen)
{
	cos.push_back(rep.cauta(titlu, gen));
	notify();
}

void Cos::genereaza(const int n)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, 3);
	
	vector<Filme> filme = { Filme("marea_neagra","doc",1267,"mathew"),Filme("visul","Horror",1967,"marta"),Filme("nota_10","romantic",2007,"serge"),Filme("Discussion","aventura",2017,"albertino") ,Filme("Inside","drama",1897,"Pamela") };
	for (const Filme& f : filme)
	{
		try { rep.inchirieri(f); }
		catch (RepoExceptions) {}
	}
	for (const Filme& f : rep.getAll())
		filme.push_back(f);
	
	
	int i = 0;
	while (i != n)
	{
		const auto seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(filme.begin(), filme.end(), std::default_random_engine(seed)); //amesteca lista de filme
		int r = dist(mt);// numar aleator intre [0,3]
		if (i + r <= n) {
			i = i + r;
			while (r > 0)
			{
				cos.push_back(filme[0]);
				r--;
			}

		}
	}

	notify();
}

void Cos::exportf(const string& fname)
{
	ofstream out{ fname };
	for (const Filme& f : cos) {
		out << f.getTitlu() << "," << f.getGen() << "," << f.getAn() << "," << f.getActor() <<"\n";
	}

	notify();
}
