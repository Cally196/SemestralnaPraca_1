#pragma once
#include "structures/heap_monitor.h"
#include "Datum.h"
#include "Vozidlo.h"
#include "Prekladisko.h"
#include "Objednavka.h"
#include "structures/list/array_list.h"

using namespace std;
using namespace structures;

class Spolocnost
{
private:
	Datum datum_;
	bool run_;
	ArrayList<Vozidlo*> *vozidla_;
	ArrayList<Prekladisko*> *prekladiska_;
	ArrayList<Objednavka*> *objednavky_;
	void vypisMenu();
	int skontrolujInt();
	Prekladisko* getPrekladisko(string okres);
	bool overDolet(string okres, double vzdialenost);
	bool overNosnost(string okres, double hmotnost);
	bool overNosnostAutaZvoz(string okres, double hmotnost);
	bool overNosnostAutaRozvoz(string okres, double hmotnost);
	Dron* getDostupnyDron(double hmotnost, string okres);
	void zapisDoSuboru();
	void nacitajZoSuboru();

public:
	void vyber();
	Spolocnost(Datum datum);
	~Spolocnost();
};

