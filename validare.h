#pragma once
#include"domain.h"
class ValidateException
{
private:
	string msg;
public:
	/*constructor for validateException*/
	ValidateException(string message):msg{message}{}

	/*returneaza mesajul*/
	string get_message() { return msg; }

};

class Validator {

public:
	Validator() = default;

	/*valideaza daca titlul genul sauactorul au stringuri gole sau daca anul aparitiei e mai mic ca 1000 sau mai mare ca 2021*/
	void validate_film(const Filme& f);

};