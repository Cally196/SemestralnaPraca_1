#include "structures/heap_monitor.h"
#include <iostream>
#include "Spolocnost.h"
#include "Datum.h"

using namespace std;

int main()
{
	initHeapMonitor();
	Datum datum_(13, 33, 1);

	Spolocnost *spol = new Spolocnost(datum_);
	spol->vyber();
	delete spol;

	return 0;
}