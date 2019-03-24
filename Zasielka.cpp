#include "Zasielka.h"
#include "structures/heap_monitor.h"
#include "Datum.h"


Datum Zasielka::getDatumAdresat()
{
	return datumAdresat_;
}

void Zasielka::setDatumAdresat(Datum datum)
{
	datumAdresat_ = datum;
}

int Zasielka::getVzdialenostAdresata()
{
	return vzdialenostAdresata_;
}

void Zasielka::setVyzdvihnuta()
{
	vyzdvihnuta_ = true;
}

bool Zasielka::Vyzdvihnuta()
{
	return vyzdvihnuta_;
}

double Zasielka::getHmotnost()
{
	return hmotnost_;
}

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

Zasielka::Zasielka(int cisloObjednavky, int minutyNaLokPrekladisko, Datum datumNaLokPrekladisko, std::string regionAdresata, double hmotnost, double vzdialenostAdresata):
	cisloObjednavky_(cisloObjednavky),
	minutyNaLokPrekladisko_(minutyNaLokPrekladisko),
	vyzdvihnuta_(false),
	lokPrekladisko_(false),
	cenSklad_(false),
	lokprekladisko2_(false),
	dorucena_(false),
	casNaDobitie_(0),
	datumNaLokPrekladisko_(datumNaLokPrekladisko),
	regionAdresata_(regionAdresata),
	hmotnost_(hmotnost),
	vzdialenostAdresata_(vzdialenostAdresata),
	datumAdresat_(Datum(1, 1, 1))
{
}


Zasielka::~Zasielka()
{
}
