#include "Dron.h"
#include "structures/heap_monitor.h"
#include <iostream>
#include <iomanip>

using namespace structures;
using namespace std;

structures::LinkedList<Zasielka*> *Dron::vylozZasielky(Datum datum)
{
	LinkedList<Zasielka*> *zasielky = new LinkedList<Zasielka*>;

	
	for (Zasielka *zasielka : *zasielky_)
	{
		if (zasielka->getDatumNaLokPrekladisko() < datum)
		{
			zasielky->add(zasielka);
			zasielky_->tryRemove(zasielka);
			//delete zasielka;
		}
		if (zasielky_->size() == 0) break;
	}
	
	//for (Zasielka *zasielka : *zasielky_)
	//{
	//	if (zasielka->getDatumNaLokPrekladisko() < datum)
	//	{			
	//		zasielky_->tryRemove(zasielka);
	//	}
	//}
	return zasielky;
}

double Dron::getKapacitaBaterie()
{
	return kapacitaBaterie_;
}

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
	int casNaNabitie = 0;
	if (typ_ == 1)
	{	
		casNaNabitie = (zasielka->getMinutyNaLokPrekladisko() * 2) / 4 * 3;
		if (zasielka->getMinutyNaLokPrekladisko() % 4 != 0) casNaNabitie += 3;
		kapacitaBaterie_ -= (zasielka->getMinutyNaLokPrekladisko() * 2) / 40;
	} 
	else
	{
		casNaNabitie = (zasielka->getMinutyNaLokPrekladisko() * 2) / 6 * 5;
		if (zasielka->getMinutyNaLokPrekladisko() % 6 != 0) casNaNabitie += 5;
		kapacitaBaterie_ -= (zasielka->getMinutyNaLokPrekladisko() * 2) / 60;
	}
	zasielka->setCasNaDobitie(casNaNabitie);
	casVolny_ = Datum::pridajMinuty(casVolny_, zasielka->getMinutyNaLokPrekladisko() * 2);
	

	nalietaneMinuty_ += 2 * zasielka->getMinutyNaLokPrekladisko();

}

Datum Dron::getCasVolny()
{
	int minutyNaDobitie = 0;	
	for (Zasielka *zasielka : *zasielky_)
	{
		minutyNaDobitie += zasielka->getCasNaDobitie();
	}
	if (typ_ == 1) minutyNaDobitie -= kapacitaBaterie_ * 40;
	else minutyNaDobitie -= kapacitaBaterie_ * 60;
	Datum newDatum = Datum::pridajMinuty(casVolny_, minutyNaDobitie);
	return newDatum;
}

int Dron::getTyp()
{
	return typ_;
}

void Dron::vypisInfo()
{
	double nalietaneHodiny = nalietaneMinuty_ / (double)60;
	cout << setw(12) << left << typ_;
	cout << setw(30) << left << nalietaneHodiny;
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
