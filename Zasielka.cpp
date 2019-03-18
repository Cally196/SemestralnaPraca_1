#include "Zasielka.h"
#include "structures/heap_monitor.h"


int Zasielka::getCisloObjednavky()
{
	return cisloObjednavky_;
}

int Zasielka::getMinutyNaLokPrekladisko()
{
	return minutyNaLokPrekladisko_;
}

Zasielka::Zasielka(int cisloObjednavky, int minutyNaLokPrekladisko):
	cisloObjednavky_(cisloObjednavky),
	minutyNaLokPrekladisko_(minutyNaLokPrekladisko),
	vyzdvihnuta_(false),
	lokPrekladisko_(false),
	cenSklad_(false),
	lokprekladisko2_(false),
	dorucena_(false)
{
}


Zasielka::~Zasielka()
{
}
