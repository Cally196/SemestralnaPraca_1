#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "Datum.h"

using namespace std;

class Vozidlo
{
private:
	std::string spz_;
	double nosnost_;
	double naklady_;
	double celkoveNaklady_;
	Datum datum_;
	
public:
	void vypisInfo();
	Vozidlo(string spz, double nosnost, double naklady, Datum datum);
	~Vozidlo();
};

