#include "structures/heap_monitor.h"
#include "Prekladisko.h"
#include <iostream>
#include <iomanip>



int Prekladisko::getTopDron()
{
	int typ = 0;
	for (Dron *dron : *drony_)
	{
		if (dron->getTyp() > typ)
		{
			typ = dron->getTyp();
		}

		if (typ == 2) return typ;
	}
	return typ;
}

void Prekladisko::VypisDrony()
{

	if (drony_->isEmpty())
	{
		cout << "\nV zadanom prekladisku sa nenachadzaju ziadne drony.\n";
	}
	else
	{
		cout << endl;
		cout << setw(12) << left << "Typ";
		cout << setw(30) << left << "Pocet nalietanych hodin";
		cout << setw(30) << left << "Pocet prepravenych zasielok";
		cout << setw(30) << left << "Datum zaradenia do evidencie" << endl;
		for (Dron *dron : *drony_)
		{
			dron->vypisInfo();
		}
	}
}

void Prekladisko::pridajDron(Dron * dron)
{
	drony_->add(dron);
}

string Prekladisko::getOkres()
{
	return okres_;
}

Prekladisko::Prekladisko(string okres):
	okres_(okres),
	drony_(new ArrayList<Dron*>())
{
}


Prekladisko::~Prekladisko()
{
	for (Dron *dron : *drony_)
	{
		delete dron;
	}
	delete drony_;
}
