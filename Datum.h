#pragma once
#include <string>
#include "structures/heap_monitor.h"

using namespace std;

class Datum
{
private:
	int minuta_, hodina_, den_;

public:
	string toString();
	Datum(int hodina, int minuta, int den);
	~Datum();
};

