#include "Zasielka.h"
#include "structures/heap_monitor.h"


std::string Zasielka::getRegionAdresata()
{
	return regionAdresata_;
}

Datum Zasielka::getDatumNaLokPrekladisko()
{
	return datumNaLokPrekladisko_;
}

int Zasielka::getCasNaDobitie()
{
	return casNaDobitie_;
}

void Zasielka::setCasNaDobitie(int casNaDobitie)
{
	casNaDobitie_ = casNaDobitie;
}

int Zasielka::getCisloObjednavky()
{
	return cisloObjednavky_;
}

int Zasielka::getMinutyNaLokPrekladisko()
{
	return minutyNaLokPrekladisko_;
}

Zasielka::Zasielka(int cisloObjednavky, int minutyNaLokPrekladisko, Datum datumNaLokPrekladisko, std::string regionAdresata):
	cisloObjednavky_(cisloObjednavky),
	minutyNaLokPrekladisko_(minutyNaLokPrekladisko),
	vyzdvihnuta_(false),
	lokPrekladisko_(false),
	cenSklad_(false),
	lokprekladisko2_(false),
	dorucena_(false),
	casNaDobitie_(0),
	datumNaLokPrekladisko_(datumNaLokPrekladisko),
	regionAdresata_(regionAdresata)
{
}


Zasielka::~Zasielka()
{
}
