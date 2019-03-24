#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"
#include <string>
#include "Dron.h"
#include "Datum.h"


using namespace std;
using namespace structures;

class Prekladisko
{
private:
	string okres_;
	ArrayList<Dron*> *drony_;
	double maxHmotnost_;
	LinkedList<Zasielka*> *zasielkyNaOdvoz_;
	LinkedList<Zasielka*> *zasielkyNaRozvoz_;

public:
	void dorucZasielky(Datum datum);
	LinkedList<Zasielka*>* getZasielkyNaRozvoz();
	LinkedList<Zasielka*>* getZasielkyNaOdvoz();
	void vylozDrony(Datum datum);
	ArrayList<Dron*>* getZoznamDronov();
	double getMaxHmotnost();
	Dron* getDron(double hmotnost, Datum *datum);
	Dron* getDron(double hmotnost, Datum *datum, Dron *dron_);
	int getTopDron(); //vrati aky najlespi dron je v prekladisku
	void VypisDrony();
	void pridajDron(Dron *dron);
	string getOkres();
	Prekladisko(string okres, double maxHmotnost, ArrayList<Dron*> *drony);
	Prekladisko(string okres);
	~Prekladisko();
};

