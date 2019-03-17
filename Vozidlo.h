#pragma once
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include <string>
#include "Datum.h"

using namespace std;

class Vozidlo
{
private:
	structures::Array<string> *trasa_;
	std::string spz_;
	double nosnost_;
	double naklady_;
	double celkoveNaklady_;
	Datum datum_;
	double hmotnostZvoz_, hmotnostRozvoz_;

	
public:
	double getNosnost();
	double getHmotnostZvoz();
	double getHmotnostRozvoz();
	bool patriRegionu(string region);
	void vypisInfo();
	Vozidlo(string spz, double nosnost, double naklady, Datum datum, structures::Array<string> *trasa);
	~Vozidlo();
};

