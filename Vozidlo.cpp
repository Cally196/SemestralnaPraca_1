#include "Vozidlo.h"
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


string Vozidlo::getZasielkyZapis()
{
	string trasa;

	for (Zasielka *zasielka : *zasielky_)
	{
		trasa += zasielka->getZasielkaZapis();
	}
	trasa += " ";
	return trasa;	
}

Datum Vozidlo::getDatumPridania()
{
	return datum_;
}

double Vozidlo::getCelkoveNaklady()
{
	return celkoveNaklady_;
}

void Vozidlo::setAktualnaHmotnost(double hmotnost)
{
	aktualnaHmotnost_ = hmotnost;
}

double Vozidlo::getAktualnaHmotnost()
{
	return aktualnaHmotnost_;
}

structures::LinkedList<Zasielka*>* Vozidlo::getZasielky()
{
	return zasielky_;
}

void Vozidlo::setCelkoveNaklady(int pocetPrekldisk)
{
	celkoveNaklady_ += 2 * pocetPrekldisk * naklady_;
}

void Vozidlo::pridajZasielkuNaRozvoz(Zasielka * zasielka)
{
	zasielky_->add(zasielka);
}

void Vozidlo::setHmotnostRozvoz(double hmotnost)
{
	hmotnostRozvoz_ += hmotnost;
}

void Vozidlo::setHmotnostZvoz(double hmotnost)
{
	hmotnostZvoz_ += hmotnost;
}

int Vozidlo::getDlzkaTrasy()
{
	return trasa_->size();
}

string Vozidlo::getTrasa()
{
	string trasa;

	for (string okres : *trasa_)
	{
		trasa += " ";
		trasa += okres;
	}
	trasa += " ";
	return trasa;
}

double Vozidlo::getNaklady()
{
	return naklady_;
}

string Vozidlo::getSpz()
{
	return spz_;
}

double Vozidlo::getNosnost()
{
	return nosnost_;
}

double Vozidlo::getHmotnostZvoz()
{
	return hmotnostZvoz_;
}

double Vozidlo::getHmotnostRozvoz()
{
	return hmotnostRozvoz_;
}

bool Vozidlo::patriRegionu(string region)
{
	for (int i = 0; i < trasa_->size(); i++)
	{
		if ((*trasa_)[i] == region) return true;
	}
	return false;
}

void Vozidlo::vypisInfo()
{
	cout << setw(20) << left << spz_;
	cout << setw(20) << left << to_string(nosnost_);
	cout << setw(20) << left << to_string(celkoveNaklady_);
	cout << setw(20) << left << datum_.toString();
	cout << endl;
}

Vozidlo::Vozidlo(string spz, double nosnost, double naklady, double celkoveNaklady, Datum datum, double hmotnostZvoz, double hmotnostRozvoz, double aktualnaHmotnost, structures::LinkedList<string>* trasa, structures::LinkedList<Zasielka*>* zasielky):
	spz_(spz),
	nosnost_(nosnost),
	naklady_(naklady),
	celkoveNaklady_(celkoveNaklady),
	datum_(datum),
	hmotnostRozvoz_(hmotnostRozvoz),
	hmotnostZvoz_(hmotnostZvoz),
	trasa_(trasa),
	zasielky_(zasielky),
	aktualnaHmotnost_(aktualnaHmotnost)
{
}

Vozidlo::Vozidlo(string spz, double nosnost, double naklady, Datum datum, structures::LinkedList<string> *trasa):
	spz_(spz),
	nosnost_(nosnost),
	naklady_(naklady),
	celkoveNaklady_(0),
	datum_(datum),
	hmotnostRozvoz_(0),
	hmotnostZvoz_(0),
	trasa_(trasa),
	zasielky_(new structures::LinkedList<Zasielka*>()),
	aktualnaHmotnost_(0)
{
}


Vozidlo::~Vozidlo()
{
	nosnost_ = 0;
	naklady_ = 0;
	celkoveNaklady_ = 0;
	delete trasa_;
	trasa_ = nullptr;
	for (Zasielka *zasielka : *zasielky_)
	{
		delete zasielka;
	}
	delete zasielky_;
}
