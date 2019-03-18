#pragma once
#include "structures/heap_monitor.h"

class Zasielka
{
private:
	bool vyzdvihnuta_, lokPrekladisko_, cenSklad_, lokprekladisko2_, dorucena_;
	int minutyNaLokPrekladisko_;
	int cisloObjednavky_;


public:
	int getCisloObjednavky();
	int getMinutyNaLokPrekladisko();
	Zasielka(int cisloObjednavky, int minutyNaLokPrekladisko);
	~Zasielka();
};

