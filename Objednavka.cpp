#include "Objednavka.h"
#include "structures/heap_monitor.h"



Objednavka::Objednavka(double hmotnost, std::string reg1, double vzdia1, std::string reg2, double vzdia2):
	hmotnostZasielky_(hmotnost),
	odosielatelRegion_(reg1),
	vzdialenostOdosielatela_(vzdia1),
	adresatRegion_(reg2),
	vzdialenostAdresata_(vzdia2)
{
}


Objednavka::~Objednavka()
{
}
