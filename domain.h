#pragma once
#include<iostream>
#include<string>
using std::string;
class Filme
{
private:
	string titlu;
	string gen;
	int an;
	string actor;
public:
	/*returneaza anul filmului*/
	int getAn() const noexcept;

	/*modifica anul filmului*/
	void setAn(int an) noexcept;

	/*returneaza titlul filmului*/
	string getTitlu() const;

	/*returneaza genul filmului*/
	string getGen() const;

	/*returneaza actorul filmului*/
	string getActor() const;

	/*modifica actorul filmului*/
	void setActor(const string& actor);

	/*creeaza un obiect de tip film*/
	Filme() :an{ 0 } {};
	Filme(const string& titlu, const string& gen, int an, const string& actor) :titlu{ titlu }, gen{ gen }, an{ an }, actor{ actor }{};
	Filme(const Filme& ot) :titlu{ ot.titlu }, gen{ ot.gen }, an{ ot.an }, actor{ ot.actor }{std::cout << "copy construct called\n"; };

};

class DTO
{
private:
	int an;
	int count;
public:
	DTO() : an{ 0 }, count{ 0 }{};
	DTO(int an) :an{ an }, count{ 1 }{};
	void counter() { count++; };
	int getAn() { return an; };
	int getCount() { return count; };
};