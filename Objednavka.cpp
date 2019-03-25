#include "Objednavka.h"
#include "structures/heap_monitor.h"



int Objednavka::getCisloObjednavky()
{
	return cisloObjednavky_;
}

string Objednavka::getRegionOdosielatela()
{
	return odosielatelRegion_;
}

Datum Objednavka::getDatum()
{
	return datumVytvorenia_;
}

string Objednavka::getObjednavkaZapis()
{
	string retazec = " ";

	retazec += to_string(hmotnostZasielky_);
	retazec += " ";

	retazec += odosielatelRegion_;
	retazec += " ";

	retazec += adresatRegion_;
	retazec += " ";

	retazec += to_string(vzdialenostOdosielatela_);
	retazec += " ";

	retazec += to_string(vzdialenostAdresata_);
	retazec += " ";

	retazec += to_string(cisloObjednavky_);
	retazec += " ";

	retazec += to_string(kod_);
	retazec += " ";

	retazec += datumVytvorenia_.naZapis();
	retazec += " ";

	return retazec;
}

int Objednavka::getKod()
{
	return kod_;
}

Objednavka::Objednavka(double hmotnost, std::string reg1, double vzdia1, std::string reg2, double vzdia2, int cisloObjednavky, int kod, Datum datum):
	hmotnostZasielky_(hmotnost),
	odosielatelRegion_(reg1),
	vzdialenostOdosielatela_(vzdia1),
	adresatRegion_(reg2),
	vzdialenostAdresata_(vzdia2),
	cisloObjednavky_(cisloObjednavky),
	kod_(kod),
	datumVytvorenia_(datum)
{
}


Objednavka::~Objednavka()
{
}
