#pragma once
#include<map>
#include<algorithm>
#include"Repo_abstract.h"
#include"repository.h"
using std::map;
using std::to_string;

class Repo_lab: public Repo_abstract
{
private:
	map<string,Filme> elems;
	vector<Filme> elems2;
	float prob;
	float generate_float() {
		float random = ((float)rand()) / (float)RAND_MAX;
		return random;
	}
public:
	Repo_lab() = default;
	Repo_lab(float p) :prob{ p } {};
	Repo_lab(const Repo_lab & ot) = delete;
	~Repo_lab() = default;

	void inchirieri(const Filme& film) override {
		float eroare = generate_float();
		if (eroare < prob) {
			throw RepoExceptions(to_string(eroare));
		}
		for (const auto& s : elems) {
			if (s.second.getTitlu() ==film.getTitlu()) {
				throw RepoExceptions(to_string(prob));
			}
		}
		elems[film.getTitlu()] = film;
	}

	const vector<Filme>& getAll() noexcept override {
		elems2.clear();
		for (const auto& el : elems) {
			elems2.push_back(el.second);
		}
		return elems2;
	}

	void sterge(const Filme& film) override {
		float eroare = generate_float();
		if (eroare < prob) {
			throw RepoExceptions(to_string(eroare));
		}
		for (const auto& el : elems) {
			if (el.first == film.getTitlu()) {
				elems.erase(el.first);
				return;
			}
		}
		throw RepoExceptions(to_string(prob));
	}

	const Filme& cauta(const string& titlu, const string& gen) override {
		float eroare = generate_float();
		if (eroare < prob) {
			throw RepoExceptions(to_string(eroare));
		}
		for (const auto& el : elems) {
			if (el.first == titlu && el.second.getGen() == gen) {
				return el.second;
			}
		}
		throw RepoExceptions(to_string(prob));
	}

	void modifica(const Filme& film) override {
		float eroare = generate_float();
		if (eroare < prob) {
			throw RepoExceptions(to_string(eroare));
		}
		for (const auto& el : elems) {
			if (el.first == film.getTitlu()) {
				elems[el.first] = film;
				return;
			}
		}
		throw RepoExceptions(to_string(prob));
	}

	void sortare(SortFunc fct) override {
		sort(elems2.begin(), elems2.end(), fct);
	}

};

