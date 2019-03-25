#include "structures/heap_monitor.h"
#include <iostream>
#include "Spolocnost.h"
#include "Datum.h"
#include <ctime>

using namespace std;

int main()
{
	initHeapMonitor();

	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	
	int minuty = ltm.tm_min;
	int hodiny = ltm.tm_hour;
	int den = ltm.tm_yday;
	Datum datum_(hodiny, minuty, den);

	Spolocnost *spol = new Spolocnost(datum_);
	spol->vyber();
	delete spol;

	return 0;
}