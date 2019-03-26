#pragma once
#include "structures/heap_monitor.h"
#include "structures/list/linked_list.h"
#include <string>
#include "Datum.h"
#include "Zasielka.h"

using namespace std;

class Vozidlo
{
private:
	std::string spz_;
	double nosnost_;
	double naklady_;
	double celkoveNaklady_;
	Datum datum_;
	double hmotnostZvoz_, hmotnostRozvoz_, aktualnaHmotnost_;

	structures::LinkedList<string> *trasa_;
	structures::LinkedList<Zasielka*> *zasielky_;

	
public:
	void VynulujHmotnosti();
	string getZasielkyZapis();
	Datum getDatumPridania();
	double getCelkoveNaklady();
	void setAktualnaHmotnost(double hmotnost);
	double getAktualnaHmotnost();
	structures::LinkedList<Zasielka*>* getZasielky();
	void setCelkoveNaklady(int pocetPrekldisk);
	void pridajZasielkuNaRozvoz(Zasielka *zasielka);
	void setHmotnostRozvoz(double hmotnost);
	void setHmotnostZvoz(double hmotnost);
	int getDlzkaTrasy();
	string getTrasa();
	double getNaklady();
	string getSpz();
	double getNosnost();
	double getHmotnostZvoz();
	double getHmotnostRozvoz();
	bool patriRegionu(string region);
	void vypisInfo();
	Vozidlo(string spz, double nosnost, double naklady, double celkoveNaklady, Datum datum, double hmotnostZvoz, double hmotnostRozvoz, double aktualnaHmotnost, structures::LinkedList<string> *trasa, structures::LinkedList<Zasielka*> *zasielky);
	Vozidlo(string spz, double nosnost, double naklady, Datum datum, structures::LinkedList<string> *trasa);
	~Vozidlo();
};

