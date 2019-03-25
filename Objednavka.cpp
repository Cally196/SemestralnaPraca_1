#include "Objednavka.h"
#include "structures/heap_monitor.h"



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
