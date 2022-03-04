#include"service.h"
#include<iterator>
#include<algorithm>
void Service::undo()
{
	if (undoActions.empty()) { throw ValidateException("Nu mai exista operatii\n"); }
	undoActions.back()->doUndo();
	undoActions.pop_back();
}
void Service::add(const string& titlu, const string& gen,const int an,const string& actor) {
Filme f{ titlu, gen, an, actor };
valid.validate_film(f);
rep.inchirieri(f);
undoActions.push_back(std::make_unique<UndoAdauga>(rep, f));
}

void Service::sterge(const string& titlu,const string& gen)
{
	auto& i = rep.cauta(titlu, gen);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, i));
	rep.sterge(i);
	cos.sterge(titlu, gen);
}

void Service::modifica(const string& titlu, const string& gen, const int an, const string& actor)
{
	Filme f{ titlu, gen, an, actor };
	valid.validate_film(f);
	auto& i = rep.cauta(titlu, gen);
	undoActions.push_back(std::make_unique<UndoModifica>(rep, i, f));
	rep.modifica(f);
	cos.modifica(titlu, gen, an, actor);
}

const vector<Filme>& Service::getAll() noexcept {
	return rep.getAll();}

const Filme& Service::cauta(const string& titlu, const string& gen)
{
	return rep.cauta(titlu, gen);
}

 const vector<Filme> Service::filtreaza_titlu(char l)
{
	 vector<Filme> rez;
	 std::copy_if(rep.getAll().begin(), rep.getAll().end(), std::back_inserter(rez), [l](const Filme& f) {return f.getTitlu()[0] == l; });
	 return rez;
}
 const vector<Filme> Service::filtreaza_an(int an)
{
	 vector<Filme> rez;
	 std::copy_if(rep.getAll().begin(), rep.getAll().end(), std::back_inserter(rez), [an](const Filme& f) {return f.getAn() == an; });
	 return rez;
}

 void Service::goleste()
 {
	 cos.goleste();
 }

 void Service::adaugaCos(const string& titlu, const string& gen)
 {
	 cos.adaugaCos(titlu, gen);
 }

 void Service::genereaza(const int n)
 {
	 cos.genereaza(n);
 }

 void Service::exportf(const string& fname)
 {
	 cos.exportf(fname);
 }

 const vector<Filme>& Service::CgetAll() noexcept
 {
	 return cos.getAll();
 }

 void Service::sortare(SortFunc fct)
 {
	 rep.sortare(fct);
 }

 const std::map<int, DTO> Service::raport()
 {
	 std::map<int, DTO> rapor;
	 for (const Filme& f : rep.getAll())
	 {
		 if (rapor.find(f.getAn()) == rapor.end())
			 rapor[f.getAn()] = DTO(f.getAn());
		 else {
			 rapor[f.getAn()].counter();
		 }
		 
	 }
	 return rapor;

 }
