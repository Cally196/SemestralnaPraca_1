#pragma once
#include "structures/heap_monitor.h"
#include "Datum.h"
#include <string>

class Zasielka
{
private:
	bool vyzdvihnuta_;
	int minutyNaLokPrekladisko_;
	int cisloObjednavky_, casNaDobitie_;
	Datum datumNaLokPrekladisko_, datumAdresat_;
	std::string regionAdresata_;
	double hmotnost_;
	double vzdialenostAdresata_;

public:
	string getZasielkaZapis();
	Datum getDatumAdresat();
	void setDatumAdresat(Datum datum);
	int getVzdialenostAdresata();
	void setVyzdvihnuta();
	bool Vyzdvihnuta();
	double getHmotnost();
	std::string getRegionAdresata();
	Datum getDatumNaLokPrekladisko();
	int getCasNaDobitie();
	void setCasNaDobitie(int casNaDobitie);
	int getCisloObjednavky();
	int getMinutyNaLokPrekladisko();
	Zasielka(bool vyzdvihnuta, int minutyNaLokPrekladisko, int cisloObjednavky, int casNaDobitie, Datum datNaLokPrekladisko, Datum datumAdresat, std::string regionAdresata, double hmotnost, double vzdialenostAdresata);
	Zasielka(int cisloObjednavky, int minutyNaLokPrekladisko, Datum datumNaLokPrekladisko, std::string regionAdresata, double hmotnost, double vzdialenostAdresata);
	~Zasielka();
};

