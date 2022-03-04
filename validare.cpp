#include "validare.h"
#include<string>
#include<exception>
using std::string;
void Validator::validate_film(const Filme& f)
{
	string msg;
	if (f.getTitlu().size() == 0) msg += "Titlu invalid\n";
	if (f.getGen().size() == 0) msg += "Gen invalid\n";
	if (f.getAn()<1000 || f.getAn()>2021) msg += "An invalid\n";
	if (f.getActor().size() == 0) msg += "Actor invalid\n";
	if (msg.size() > 0)
		throw ValidateException(msg);
}


