#ifndef UTILS_H_
#define UTILS_H_

#include"domain.h"
typedef const bool SortFunc(const Filme& i, const Filme& j);
/*functie ce compara titlul a doua filme si returneaza true sau false*/
const bool funcTit(const Filme& i, const Filme& j);
/*functie ce compara actorii a doua filme si returneaza true sau false*/
const bool funcAct(const Filme& i, const Filme& j);
/*functie ce compara anii si genul a doua filme si returneaza true sau false*/
const bool funcAngen(const Filme& i, const Filme& j);

#endif