#include "Dron.h"
#include "structures/heap_monitor.h"
#include <iostream>
#include <iomanip>

using namespace std;

int Dron::getTyp()
{
	return typ_;
}

void Dron::vypisInfo()
{
	cout << setw(12) << left << typ_;
	cout << setw(30) << left << nalietaneMinuty_/60;
	cout << setw(30) << left << pocetPrepravenychZasielok_;
	cout << setw(30) << left << datumZaradenia_.toString();
	cout << endl;
}

Dron::Dron(int typ, string serioveCislo, Datum datum):
	typ_(typ),
	serioveCislo_(serioveCislo), 
	pocetPrepravenychZasielok_(0),
	nalietaneMinuty_(0),
	datumZaradenia_(datum)
{
}


Dron::~Dron()
{
}
