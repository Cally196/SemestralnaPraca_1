#pragma once
#include "structures/heap_monitor.h"
#include "Datum.h"
#include <string>

class Zasielka
{
private:
	bool vyzdvihnuta_, lokPrekladisko_, cenSklad_, lokprekladisko2_, dorucena_;
	int minutyNaLokPrekladisko_;
	int cisloObjednavky_, casNaDobitie_;
	Datum datumNaLokPrekladisko_;
	std::string regionAdresata_;
	double hmotnost_;


public:
	double getHmotnost();
	std::string getRegionAdresata();
	Datum getDatumNaLokPrekladisko();
	int getCasNaDobitie();
	void setCasNaDobitie(int casNaDobitie);
	int getCisloObjednavky();
	int getMinutyNaLokPrekladisko();
	Zasielka(int cisloObjednavky, int minutyNaLokPrekladisko, Datum datumNaLokPrekladisko, std::string regionAdresata, double hmotnost);
	~Zasielka();
};

