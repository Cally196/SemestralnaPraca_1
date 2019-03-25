#include "Dron.h"
#include "structures/heap_monitor.h"
#include <iostream>
#include <iomanip>

using namespace structures;
using namespace std;

int Dron::casNaDobitie(int minutyNaPrekladisko)
{
	int casNaNabitie = 0;

	if (typ_ == 1)
	{
		casNaNabitie = (minutyNaPrekladisko * 2) / 4 * 3;
		if (minutyNaPrekladisko % 4 != 0) casNaNabitie += 3;
		kapacitaBaterie_ -= (minutyNaPrekladisko * 2) / 40;
	}
	else
	{
		casNaNabitie = (minutyNaPrekladisko * 2) / 6 * 5;
		if (minutyNaPrekladisko % 6 != 0) casNaNabitie += 5;
		kapacitaBaterie_ -= (minutyNaPrekladisko * 2) / 60;
	}
	casVolny_ = Datum::pridajMinuty(casVolny_, minutyNaPrekladisko * 2);


	//nalietaneMinuty_ += 2 * minutyNaPrekladisko;
	return casNaNabitie;
}

double Dron::getNalietaneHodiny()
{
	return nalietaneMinuty_ / (double)60;
}

structures::LinkedList<Zasielka*>* Dron::dorucZasielky(Datum datum)
{
	LinkedList<Zasielka*> *zasielky = new LinkedList<Zasielka*>;

	for (Zasielka *zasielka : *zasielky_)
	{
		if (zasielka->getDatumAdresat() < datum && zasielka->Vyzdvihnuta())
		{
			zasielky->add(zasielka);
			zasielky_->tryRemove(zasielka);
			//delete zasielka;
		}
		if (zasielky_->size() == 0) break;
	}
	return zasielky;
}

void Dron::setKapacitaBaterie(double kapacitaBaterie)
{
	kapacitaBaterie_ = kapacitaBaterie;
}

void Dron::setCasVolnyPoDobiti(int minuty)
{
	casVolny_ = Datum::pridajMinuty(casVolny_, minuty);
}

structures::LinkedList<Zasielka*> *Dron::vylozZasielky(Datum datum)
{
	LinkedList<Zasielka*> *zasielky = new LinkedList<Zasielka*>;

	
	for (Zasielka *zasielka : *zasielky_)
	{
		if (zasielka->getDatumNaLokPrekladisko() < datum && !zasielka->Vyzdvihnuta())
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
	retazec += to_string(nalietaneMinuty_) + " ";
	retazec += to_string(pocetPrepravenychZasielok_) + " ";
	retazec += datumZaradenia_.naZapis() + " ";
	retazec += casVolny_.naZapis() + " ";
	retazec += serioveCislo_ + " ";
	retazec += to_string(kapacitaBaterie_);
	retazec += " ";
	retazec += to_string(zasielky_->size()) + " ";

	for (Zasielka *zasielka : *zasielky_)
	{
		retazec += zasielka->getZasielkaZapis();
	}

	return retazec;
}

void Dron::pridajZasielku(Zasielka * zasielka, int casNaPrekladisko)
{
	zasielky_->add(zasielka);
	
	int casNaNabitie = casNaDobitie(casNaPrekladisko);;

	zasielka->setCasNaDobitie(casNaNabitie);

	nalietaneMinuty_ += 2 * casNaPrekladisko;
}

Datum Dron::getCasVolny()
{
	int minutyNaDobitie = 0;	
	for (Zasielka *zasielka : *zasielky_)
	{
		minutyNaDobitie += zasielka->getCasNaDobitie();
	}
	if (typ_ == 1) minutyNaDobitie -= (int)kapacitaBaterie_ * 40;
	else minutyNaDobitie -= (int)kapacitaBaterie_ * 60;
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

Dron::Dron(int typ, int nalietaneMinuty, int pocetPrepravenychZasielok, Datum datumZaradenia, Datum casVolny, std::string serioveCislo, double kapacitaBaterie, structures::LinkedList<Zasielka*> *zasielky) :
	typ_(typ),
	nalietaneMinuty_(nalietaneMinuty),
	pocetPrepravenychZasielok_(pocetPrepravenychZasielok),
	datumZaradenia_(datumZaradenia),
	casVolny_(casVolny),
	serioveCislo_(serioveCislo),	
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
