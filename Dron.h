#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/linked_list.h"
#include <string>
#include "Datum.h"
#include "Zasielka.h"

using namespace std;

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
	double getNalietaneHodiny();
	structures::LinkedList<Zasielka*> *dorucZasielky(Datum datum);
	void setKapacitaBaterie(double kapacitaBaterie);
	void setCasVolnyPoDobiti(int minuty);
	structures::LinkedList<Zasielka*> *vylozZasielky(Datum datum);
	double getKapacitaBaterie();
	string getInfoNaZapis();
	void pridajZasielku(Zasielka *zasielka, int casNaPrekladisko, Datum datum);
	Datum getCasVolny();
	int getTyp();
	void vypisInfo();
	Dron(int typ, int nalietaneMinuty, int pocetPrepravenychZasielok, Datum datumZaradenia, Datum casVolny, std::string serioveCislo, double kapacitaBaterie, structures::LinkedList<Zasielka*> *zasielky);
	Dron(int typ, std::string serioveCislo, Datum datum);
	~Dron();
};

