#include "Vozidlo.h"
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

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
	cout << setw(20) << left << to_string(naklady_);
	cout << setw(20) << left << datum_.toString();
	cout << endl;
}

Vozidlo::Vozidlo(string spz, double nosnost, double naklady, Datum datum, structures::Array<string> *trasa):
	spz_(spz),
	nosnost_(nosnost),
	naklady_(naklady),
	celkoveNaklady_(0),
	datum_(datum),
	hmotnostRozvoz_(0),
	hmotnostZvoz_(0),
	trasa_(trasa)
{
}


Vozidlo::~Vozidlo()
{
	nosnost_ = 0;
	naklady_ = 0;
	celkoveNaklady_ = 0;
	delete trasa_;
	trasa_ = nullptr;
}
