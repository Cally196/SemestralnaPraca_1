#include "Datum.h"
#include "structures/heap_monitor.h"
#include <iostream>
using namespace std;


string Datum::naZapis()
{
	string trasa;
	
	trasa += " ";
	trasa += to_string(minuta_);
	trasa += " ";
	trasa += to_string(hodina_);
	trasa += " ";
	trasa += to_string(den_);
	
	trasa += " ";
	return trasa;

}

int Datum::getHodina()
{
	return hodina_;
}

Datum Datum::pridajMinuty(Datum & datum, int minuty)
{
	int cas = minuty;
	int hodiny_, dni_;
	Datum novyDatum = datum;
	dni_ = cas / 1440;	
	cas -= dni_ * 1440;
	hodiny_ = cas / 60;
	cas -= hodiny_ * 60; 

	if (novyDatum.minuta_ + cas >= 60)
	{
		novyDatum.minuta_ += cas - 60;
		hodiny_++;
	}
	else
	{
		novyDatum.minuta_ += cas;
	}
	

	if (novyDatum.hodina_ + hodiny_ >= 24)
	{
		novyDatum.hodina_ += hodiny_ - 24;
		dni_++;
	}
	else
	{
		novyDatum.hodina_ += hodiny_;
	}

	novyDatum.den_ += dni_;

	return novyDatum;
}

Datum Datum::posunOHodinu(Datum &datum)
{
	Datum novyDatum = datum;
	novyDatum.hodina_++;

	if (novyDatum.hodina_ >= 21)
	{
		novyDatum.hodina_ = 7;
		novyDatum.minuta_ = 0;
		novyDatum.den_++;
	}

	return novyDatum;
}

bool Datum::operator<(Datum datum)
{
	if (den_ < datum.den_) return true;
	else if (den_ == datum.den_ && hodina_ < datum.hodina_) return true;
	else if (den_ == datum.den_ && hodina_ == datum.hodina_ && minuta_ < datum.minuta_) return true;
	else return false;
}

bool Datum::operator==(Datum datum)
{
	return (den_ == datum.den_ && hodina_ == datum.hodina_ && minuta_ == datum.minuta_);
}

string Datum::toString()
{
	return (to_string(hodina_) + ":" + to_string(minuta_) + "  Den:" + to_string(den_));
}

Datum::Datum(int hodina, int minuta, int den):
	hodina_(hodina),
	minuta_(minuta),
	den_(den)
{
}


Datum::~Datum()
{
}
