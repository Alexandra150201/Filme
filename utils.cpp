#include"utils.h"

const bool funcTit(const Filme& i, const Filme& j) { return (i.getTitlu() < j.getTitlu()); };

const bool funcAct(const Filme& i, const Filme& j) { return (i.getActor() < j.getActor()); };

const bool funcAngen(const Filme& i, const Filme& j) {
	if (i.getAn() < j.getAn()) return true; else if (i.getAn() == j.getAn() && i.getGen() < j.getGen()) return true; else return false;
};