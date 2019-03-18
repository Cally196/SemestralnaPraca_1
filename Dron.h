#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/linked_list.h"
#include <string>
#include "Datum.h"
#include "Zasielka.h"

class Dron
{
private:
	int typ_, nalietaneMinuty_, pocetPrepravenychZasielok_;
	Datum datumZaradenia_, casVolny_;
	std::string serioveCislo_;
	double kapacitaBaterie_;
	structures::LinkedList<Zasielka*> *zasielky_;
	

public:
	string getInfoNaZapis();
	void pridajZasielku(Zasielka *zasielka);
	Datum getCasVolny();
	int getTyp();
	void vypisInfo();
	Dron(int typ, std::string serioveCislo, Datum datum, int nalietaneMinuty, int pocetPrepravenychZasielok_, double kapacitaBaterie, structures::LinkedList<Zasielka*> *zasielky);
	Dron(int typ, std::string serioveCislo, Datum datum);
	~Dron();
};

