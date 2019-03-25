#pragma once
#include <string>
#include "structures/heap_monitor.h"

using namespace std;

class Datum
{
private:
	int minuta_, hodina_, den_;

public:
	string naZapis();
	int getHodina();
	static Datum pridajMinuty(Datum &datum, int minuty);
	static Datum posunOHodinu(Datum &datum);
	bool operator<(Datum &datum);
	bool operator==(Datum & datum);
	string toString();
	Datum(int hodina, int minuta, int den);
	~Datum();
};

