#include "structures/heap_monitor.h"
#include "Prekladisko.h"
#include <iostream>
#include <iomanip>



void Prekladisko::vylozDrony(Datum datum)
{
	for (Dron *dron : *drony_)
	{
		LinkedList<Zasielka*> *zasielky = dron->vylozZasielky(datum);

		for (Zasielka *zasielka : *zasielky)
		{
			if (zasielka->getRegionAdresata() == okres_) zasielkyNaOdvoz_->add(zasielka);
			else zasielkyNaRozvoz_->add(zasielka);
			
			zasielky->tryRemove(zasielka);
			if (zasielky->size() == 0) break;
		}
		delete zasielky;
	}
}

ArrayList<Dron*>* Prekladisko::getZoznamDronov()
{
	return drony_;
}

double Prekladisko::getMaxHmotnost()
{
	return maxHmotnost_;
}

Dron * Prekladisko::getDron(double hmotnost, Datum *datum)
{
	Dron *pickDron = (*drony_)[0];
	
	for (Dron *dron : *drony_)
	{	
		if (hmotnost > 2)
		{
			if (dron->getTyp() == 2)
			{
				if (dron->getCasVolny() < *datum)
				{
					if (pickDron->getCasVolny() < *datum)
					{
						if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) pickDron = dron;
					}
					else pickDron = dron;
				}
				else if (dron->getCasVolny() < pickDron->getCasVolny())
				{
					pickDron = dron;
				}
				else if (dron->getCasVolny() == pickDron->getCasVolny())
				{
					if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) pickDron = dron;
				}
			}
		}
		else
		{
			if (dron->getCasVolny() < *datum)
			{
				if (pickDron->getCasVolny() < *datum)
				{
					if (dron->getTyp() < pickDron->getTyp()) pickDron = dron;
					else if (dron->getTyp() == pickDron->getTyp())
					{
						if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) pickDron = dron;
					}
				}
				else pickDron = dron;
			}
			else if (dron->getCasVolny() < pickDron->getCasVolny())
			{
				pickDron = dron;
			}
			else if (dron->getCasVolny() == pickDron->getCasVolny())
			{
				if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) pickDron = dron;
			}
		}
	}
	return pickDron;
}

Dron * Prekladisko::getDron(double hmotnost, Datum *datum, Dron * dron_)
{
	Dron *pickDron = (*drony_)[0];

	for (Dron *dron : *drony_)
	{
		if (hmotnost > 2)
		{
			if (dron->getTyp() == 2)
			{
				if (dron->getCasVolny() < *datum)
				{
					if (pickDron->getCasVolny() < *datum)
					{
						if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) if(dron != dron_) pickDron = dron;
					}
					else if (dron != dron_) pickDron = dron;
				}
				else if (dron->getCasVolny() < pickDron->getCasVolny())
				{
					if (dron != dron_) pickDron = dron;
				}
				else if (dron->getCasVolny() == pickDron->getCasVolny())
				{
					if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) if (dron != dron_) pickDron = dron;
				}
			}
		}
		else
		{
			if (dron->getCasVolny() < *datum)
			{
				if (pickDron->getCasVolny() < *datum)
				{
					if (dron->getTyp() < pickDron->getTyp()) if (dron != dron_) pickDron = dron;
					else if (dron->getTyp() == pickDron->getTyp())
					{
						if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) if (dron != dron_) pickDron = dron;
					}
				}
				else if (dron != dron_) pickDron = dron;
			}
			else if (dron->getCasVolny() < pickDron->getCasVolny())
			{
				if (dron != dron_) pickDron = dron;
			}
			else if (dron->getCasVolny() == pickDron->getCasVolny())
			{
				if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) if (dron != dron_) pickDron = dron;
			}
		}
	}
	return pickDron;
}

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

Prekladisko::Prekladisko(string okres, double maxHmotnost, ArrayList<Dron*> *drony):
	okres_(okres),
	drony_(drony), 
	maxHmotnost_(maxHmotnost),
	zasielkyNaOdvoz_(new LinkedList<Zasielka*>()),
	zasielkyNaRozvoz_(new LinkedList<Zasielka*>())
{
}

Prekladisko::Prekladisko(string okres):
	okres_(okres),
	drony_(new ArrayList<Dron*>()),
	maxHmotnost_(0),
	zasielkyNaOdvoz_(new LinkedList<Zasielka*>()),
	zasielkyNaRozvoz_(new LinkedList<Zasielka*>())
{
}


Prekladisko::~Prekladisko()
{
	for (Dron *dron : *drony_)
	{
		delete dron;
	}
	delete drony_;

	for (Zasielka *zasielka : *zasielkyNaOdvoz_)
	{
		delete zasielka;
	}
	delete zasielkyNaOdvoz_;

	for (Zasielka *zasielka : *zasielkyNaRozvoz_)
	{
		delete zasielka;
	}
	delete zasielkyNaRozvoz_;
}
