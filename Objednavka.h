#pragma once
#include "structures/heap_monitor.h"
#include <string>


class Objednavka
{
private:
	double hmotnostZasielky_;
	std::string odosielatelRegion_, adresatRegion_;
	double vzdialenostOdosielatela_, vzdialenostAdresata_;
	int cisloObjednavky_;

public:
	int getCisloObjednavky();
	Objednavka(double hmotnost, std::string reg1, double vzdia1, std::string reg2, double vzdia2, int cisloObjednavky);
	~Objednavka();
};

