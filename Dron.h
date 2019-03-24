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
	int casNaDobitie(int minutyNaPrekladisko);
	

public:
	void setCasVolnyPoDobiti(int minuty);
	structures::LinkedList<Zasielka*> *vylozZasielky(Datum datum);
	double getKapacitaBaterie();
	string getInfoNaZapis();
	void pridajZasielku(Zasielka *zasielka, int casNaPrekladisko);
	Datum getCasVolny();
	int getTyp();
	void vypisInfo();
	Dron(int typ, std::string serioveCislo, Datum datum, int nalietaneMinuty, int pocetPrepravenychZasielok_, double kapacitaBaterie, structures::LinkedList<Zasielka*> *zasielky);
	Dron(int typ, std::string serioveCislo, Datum datum);
	~Dron();
};

