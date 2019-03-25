#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "Datum.h"


class Objednavka
{
private:
	double hmotnostZasielky_;
	std::string odosielatelRegion_, adresatRegion_;
	double vzdialenostOdosielatela_, vzdialenostAdresata_;
	int cisloObjednavky_, kod_;
	Datum datumVytvorenia_;

public:
	int getKod();
	Objednavka(double hmotnost, std::string reg1, double vzdia1, std::string reg2, double vzdia2, int cisloObjednavky, int kod_, Datum datum);
	~Objednavka();
};

