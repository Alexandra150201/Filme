#include "domain.h"
#include<vector>
using std::vector;

int Filme::getAn() const noexcept {
	return an; }
void Filme::setAn(int a) noexcept
{
	this->an = a;
}
string Filme::getTitlu() const {
	return titlu; }
string Filme::getGen() const {
	return gen; }
string Filme::getActor() const {
	return actor; }

void Filme::setActor(const string& actorm)
{
	this->actor = actorm;
}

