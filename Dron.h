#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "Datum.h"

class Dron
{
private:
	int typ_, nalietaneMinuty_, pocetPrepravenychZasielok_;
	Datum datumZaradenia_;
	std::string serioveCislo_;
	

public:
	int getTyp();
	void vypisInfo();
	Dron(int typ, std::string serioveCislo, Datum datum);
	~Dron();
};

