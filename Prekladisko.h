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

public:
	int getTopDron(); //vrati aky najlespi dron je v prekladisku
	void VypisDrony();
	void pridajDron(Dron *dron);
	string getOkres();
	Prekladisko(string okres);
	~Prekladisko();
};

