#include "Zasielka.h"
#include "structures/heap_monitor.h"
#include "Datum.h"


string Zasielka::getZasielkaZapis()
{
	string retazec = " ";

	if (vyzdvihnuta_) retazec += to_string(1);
	else retazec += to_string(0);

	retazec += " ";
	retazec += to_string(minutyNaLokPrekladisko_);

	retazec += " ";
	retazec += to_string(cisloObjednavky_);

	retazec += " ";
	retazec += to_string(casNaDobitie_);

	retazec += " ";
	retazec += datumNaLokPrekladisko_.naZapis();

	retazec += " ";
	retazec += datumAdresat_.naZapis();

	retazec += " ";
	retazec += regionAdresata_;

	retazec += " ";
	retazec += to_string(hmotnost_);

	retazec += " ";
	retazec += to_string(vzdialenostAdresata_);
	retazec += " ";

	return retazec;
}

Datum Zasielka::getDatumAdresat()
{
	return datumAdresat_;
}

void Zasielka::setDatumAdresat(Datum datum)
{
	datumAdresat_ = datum;
}

double Zasielka::getVzdialenostAdresata()
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

Zasielka::Zasielka(bool vyzdvihnuta, int minutyNaLokPrekladisko, int cisloObjednavky, int casNaDobitie, Datum datNaLokPrekladisko, Datum datumAdresat, std::string regionAdresata, double hmotnost, double vzdialenostAdresata):
	vyzdvihnuta_(vyzdvihnuta),
	minutyNaLokPrekladisko_(minutyNaLokPrekladisko),
	cisloObjednavky_(cisloObjednavky),
	casNaDobitie_(casNaDobitie),
	datumNaLokPrekladisko_(datNaLokPrekladisko),
	datumAdresat_(datumAdresat),
	regionAdresata_(regionAdresata),
	hmotnost_(hmotnost),
	vzdialenostAdresata_(vzdialenostAdresata)
{
		
}

Zasielka::Zasielka(int cisloObjednavky, int minutyNaLokPrekladisko, Datum datumNaLokPrekladisko, std::string regionAdresata, double hmotnost, double vzdialenostAdresata):
	cisloObjednavky_(cisloObjednavky),
	minutyNaLokPrekladisko_(minutyNaLokPrekladisko),
	vyzdvihnuta_(false),
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
