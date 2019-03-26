#include "structures/heap_monitor.h"
#include "Prekladisko.h"
#include <iostream>
#include <iomanip>



int Prekladisko::getPocetDorucenych()
{
	return pocetDorucenychZasielok_;
}

int Prekladisko::getPocetOdoslanych()
{
	return pocetOdoslanychZasielok_;
}

void Prekladisko::dorucZasielky(Datum datum)
{
	for (Dron *dron : *drony_)
	{
		LinkedList<Zasielka*> *zasielky = dron->dorucZasielky(datum);
		if (!zasielky->isEmpty())
		{
			for (Zasielka *zasielka : *zasielky)
			{			
				dron->setCasVolnyPoDobiti(zasielka->getCasNaDobitie());
				pocetDorucenychZasielok_++;

				zasielky->tryRemove(zasielka);
				delete zasielka;
				if (zasielky->size() == 0)
				{
					delete zasielky;
					break;
				}
			}
		}
		else delete zasielky;
	}
}

LinkedList<Zasielka*>* Prekladisko::getZasielkyNaRozvoz()
{
	return zasielkyNaRozvoz_;
}

LinkedList<Zasielka*>* Prekladisko::getZasielkyNaOdvoz()
{
	return zasielkyNaOdvoz_;
}

void Prekladisko::vylozDrony(Datum datum)
{
	for (Dron *dron : *drony_)
	{		
		LinkedList<Zasielka*> *zasielky = dron->vylozZasielky(datum);

		for (Zasielka *zasielka : *zasielky)
		{
			//if (!zasielka->Vyzdvihnuta())
			//{
			zasielka->setVyzdvihnuta();
			pocetOdoslanychZasielok_++;

			if (zasielka->getRegionAdresata() == okres_) zasielkyNaRozvoz_->add(zasielka);
			else zasielkyNaOdvoz_->add(zasielka);

			dron->setCasVolnyPoDobiti(zasielka->getCasNaDobitie());

			zasielky->tryRemove(zasielka);
			if (zasielky->size() == 0) break;
			//}
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

Dron * Prekladisko::getDron(double hmotnost, Datum *datum, double vzdialenost)
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
		else if (vzdialenost > 20)
		{
			if (dron->getTyp() == 1)
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

Dron * Prekladisko::getDron(double hmotnost, Datum *datum, Dron * dron_, double vzdialenost)
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
						if (dron->getKapacitaBaterie() > pickDron->getKapacitaBaterie()) if (dron != dron_) pickDron = dron;
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
		else if (vzdialenost >= 20)
		{
			if (dron->getTyp() == 1)
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

int Prekladisko::getTopDron(int pouzitie)
{
	int typ = 0;

	if (pouzitie == 1)
	{
		typ = 3;
		for (Dron *dron : *drony_)
		{
			if (dron->getTyp() < typ)
			{
				typ = dron->getTyp();
			}

			if (typ == 1) return typ;
		}
	}
	else
	{
		for (Dron *dron : *drony_)
		{
			if (dron->getTyp() > typ)
			{
				typ = dron->getTyp();
			}

			if (typ == 2) return typ;
		}
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

Prekladisko::Prekladisko(string okres, double maxHmotnost, int pocetDorucenychZasielok, int pocetOdoslanychZasielok, ArrayList<Dron*> *drony, LinkedList<Zasielka*> *zasielkyNaOdvoz, LinkedList<Zasielka*> *zasielkyNaRozvoz) :
	okres_(okres),
	maxHmotnost_(maxHmotnost),
	pocetDorucenychZasielok_(pocetDorucenychZasielok),
	pocetOdoslanychZasielok_(pocetOdoslanychZasielok),
	drony_(drony),
	zasielkyNaOdvoz_(zasielkyNaOdvoz),
	zasielkyNaRozvoz_(zasielkyNaRozvoz)
{
}

Prekladisko::Prekladisko(string okres) :
	okres_(okres),
	drony_(new ArrayList<Dron*>()),
	maxHmotnost_(0),
	zasielkyNaOdvoz_(new LinkedList<Zasielka*>()),
	zasielkyNaRozvoz_(new LinkedList<Zasielka*>()),
	pocetDorucenychZasielok_(0),
	pocetOdoslanychZasielok_(0)
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
