#include "Vozidlo.h"
#include "structures/heap_monitor.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

void Vozidlo::vypisInfo()
{
	cout << setw(20) << left << spz_;
	cout << setw(20) << left << to_string(nosnost_);
	cout << setw(20) << left << to_string(naklady_);
	cout << setw(20) << left << datum_.toString();
	cout << endl;
}

Vozidlo::Vozidlo(string spz, double nosnost, double naklady, Datum datum):
	spz_(spz),
	nosnost_(nosnost),
	naklady_(naklady),
	celkoveNaklady_(0),
	datum_(datum)
{
}


Vozidlo::~Vozidlo()
{
	nosnost_ = 0;
	naklady_ = 0;
	celkoveNaklady_ = 0;

}
