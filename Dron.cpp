#include "Dron.h"
#include "structures/heap_monitor.h"
#include <iostream>
#include <iomanip>

using namespace std;

string Dron::getInfoNaZapis()
{
	string retazec;

	retazec += to_string(typ_) + " ";
	retazec += serioveCislo_ + " ";
	retazec += to_string(nalietaneMinuty_) + " ";
	retazec += to_string(pocetPrepravenychZasielok_) + " ";
	retazec += to_string(kapacitaBaterie_);
	retazec += " ";
	retazec += to_string(zasielky_->size()) + " ";

	for (Zasielka *zasielka : *zasielky_)
	{
		retazec += to_string(zasielka->getCisloObjednavky()) + " ";
		retazec += to_string(zasielka->getMinutyNaLokPrekladisko()) + " ";
	}

	return retazec;
}

void Dron::pridajZasielku(Zasielka * zasielka)
{
	zasielky_->add(zasielka);
	casVolny_ = Datum::pridajMinuty(casVolny_, zasielka->getMinutyNaLokPrekladisko() * 2);

}

Datum Dron::getCasVolny()
{
	return casVolny_;
}

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

Dron::Dron(int typ, std::string serioveCislo, Datum datum, int nalietaneMinuty, int pocetPrepravenychZasielok, double kapacitaBaterie, structures::LinkedList<Zasielka*> *zasielky):
	typ_(typ),
	serioveCislo_(serioveCislo),
	pocetPrepravenychZasielok_(pocetPrepravenychZasielok),
	nalietaneMinuty_(nalietaneMinuty),
	datumZaradenia_(datum),
	casVolny_(datum),
	kapacitaBaterie_(kapacitaBaterie),
	zasielky_(zasielky)
{
}

Dron::Dron(int typ, string serioveCislo, Datum datum):
	typ_(typ),
	serioveCislo_(serioveCislo), 
	pocetPrepravenychZasielok_(0),
	nalietaneMinuty_(0),
	datumZaradenia_(datum),
	casVolny_(datum),
	zasielky_(new structures::LinkedList<Zasielka*>),
	kapacitaBaterie_(1)
{
}


Dron::~Dron()
{
	for (Zasielka *zasielka : *zasielky_)
	{
		delete zasielka;
	}
	delete zasielky_;
}
