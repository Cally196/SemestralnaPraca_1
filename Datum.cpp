#include "Datum.h"
#include "structures/heap_monitor.h"

using namespace std;


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
