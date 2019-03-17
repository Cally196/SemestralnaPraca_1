#include "Spolocnost.h"
#include "structures/heap_monitor.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "structures/list/array_list.h"
#include "Vozidlo.h"
#include "Dron.h"
#include "Objednavka.h"

using namespace std;
using namespace structures;


void Spolocnost::vypisMenu()
{
	cout << "\n_____________________________";
	cout << "\nAge of Express" << endl;
	cout << "\nVyber moznost:\n"
			"0. Ukonci aplikaciu\n"
			"1. Vypis aktuapny cas\n"
			"2. Pridaj nove vozidlo\n"
			"3. Vypis zoznam vozidiel\n"
			"4. Pridaj novy dron\n"
			"5. Vypis vsetky drony v danom prekladisku\n"
			"6. Vytvor objednavku\n"
			">>";
}

int Spolocnost::skontrolujInt()
{
	int vstup;
	bool pod = false;
	do
	{
		cin >> vstup;
		pod = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (pod == true)
		{
			cout << "\nZly vstup. Zadaj znovu:\n>>";
		}
	} while (pod == true);

	return vstup;
}

Prekladisko* Spolocnost::getPrekladisko(string okres)
{
	Prekladisko *prekladisko = nullptr;
	for (Prekladisko *prekladisko : *prekladiska_)
	{
		if (prekladisko->getOkres() == okres) return prekladisko;
	}
	return prekladisko;
}

bool Spolocnost::overDolet(string okres, double vzdialenost)
{
	int typ = 0;
	Prekladisko *prekladisko = getPrekladisko(okres);
	typ = prekladisko->getTopDron();
	
	switch (typ)
	{
	case 1:
		if (vzdialenost <= (40 / 0.75)/2) return true;
		break;

	case 2:
		if (vzdialenost <= (60 / 1.5) / 2) return true;
		break;
	default:
		return false;
		break;
	}
}

bool Spolocnost::overNosnost(string okres, double hmotnost)
{
	int typ = 0;
	Prekladisko *prekladisko = getPrekladisko(okres);
	typ = prekladisko->getTopDron();

	switch (typ)
	{
	case 1:
		if (hmotnost <= 2) return true;
		break;

	case 2:
		if (hmotnost <= 5) return true;
		break;
	default:
		return false;
		break;
	}
}

void Spolocnost::vyber()
{
	int volba_;

	while (run_)
	{
		Spolocnost::vypisMenu();

		volba_ = skontrolujInt();

		switch (volba_)
		{
		case 0:
			run_ = false;
			break;

		case 1:
			cout << "\nAktualny datum: " + datum_.toString() + "\n";
			break;

		case 2: {
			string spz;
			double nosnost;
			double naklady;
			cout << "\nZadajte SPZ:\n";
			cin >> spz;
			cout << "Zadajte nosnost(v tonach):\n";
			cin >> nosnost;
			cout << "Zadajte prevadzkove naklady:\n";
			cin >> naklady;
			Vozidlo *vozidlo = new Vozidlo(spz, nosnost, naklady, datum_);
			vozidla_->add(vozidlo);			
			cout << "Vozidlo bolo pridane do databazy.\n";
			break;
		}

		case 3: {
			cout << endl;
			cout << setw(20) << left << "SPZ";
			cout << setw(20) << left << "Nosnost";
			cout << setw(20) << left << "Celkove naklady";
			cout << setw(20) << left << "Datum zaradenia do evidencie" << endl;
			for (Vozidlo *voz : *vozidla_)
			{
				voz->vypisInfo();
			}
			break;
		}

		case 4: {
			int typ;
			string serioveCislo, okres;
			bool flag = true;
			Prekladisko *prekladisko = nullptr;
			cout << "\nZadajte seriove cislo dronu\n>>";
			cin >> serioveCislo;

			do
			{
				cout << "\nZadajte typ dronu(1 alebo 2)\n>>";
				typ = skontrolujInt();
				if (typ == 1 || typ == 2) flag = false;

			} while (flag);
			
			do
			{
				cout << "\nZadajte okres prekladiska pre priradenie dronu\n>>";
				cin >> okres;
				prekladisko = getPrekladisko(okres);
			} while (prekladisko == nullptr);

			Dron *dron = new Dron(typ, serioveCislo, datum_);
			prekladisko->pridajDron(dron);

			break;
		}

		case 5: 
		{
			string okres;
			Prekladisko *prekladisko = nullptr;
			do
			{
				cout << "\nZadajte okres/n>>";
				cin >> okres;
				prekladisko = getPrekladisko(okres);

			} while (prekladisko == nullptr);

			prekladisko->VypisDrony();


			break;
		}

		case 6:
		{
			double hmotnost; 
			string regionOdosielatela, regionAdresata;
			double vzdialenostOodosielatela, vzdialenostAdresata;
			Prekladisko *prekladiskoOdosielatela = nullptr;
			Prekladisko *prekladiskoAdresata = nullptr;

			cout << "\nZadajte hmotnost zasielky\n";
			cin >> hmotnost;
			do
			{
				cout << "Zadajte okres odosielatela\n";
				cin >> regionOdosielatela;
				prekladiskoOdosielatela = getPrekladisko(regionOdosielatela);
				if (prekladiskoOdosielatela != nullptr) break;
				cout << "Zadali ste chybny okres\n";

			} while (true);

			cout << "Zadajtie vzdialenot odosielatela od prekladiska[km]\n";
			cin >> vzdialenostOodosielatela;

			do
			{
				cout << "Zadajte okres adresata\n";
				cin >> regionAdresata;
				prekladiskoAdresata = getPrekladisko(regionAdresata);
				if (prekladiskoAdresata != nullptr) break;
				cout << "Zadali ste chybny okres\n";

			} while (true);

			cout << "Zadajte vzdialenost adresata od prekladiska[km]\n";
			cin >> vzdialenostAdresata;

			if (overDolet(regionOdosielatela, vzdialenostOodosielatela) && overDolet(regionAdresata, vzdialenostAdresata) && overNosnost(regionOdosielatela, hmotnost) &&
				overNosnost(regionAdresata, hmotnost))
			{
				Objednavka *objednavka = new Objednavka(hmotnost, regionOdosielatela, vzdialenostOodosielatela, regionAdresata, vzdialenostAdresata);
				objednavky_->add(objednavka);
				cout << "\nObjednavka bola prijata\n";
			}
			else
			{
				cout << "\nObjednavka bola zamietanuta zo strany AoE\n";
			}



			break;
		}
		default:
			cout << "\nZly vstup. Zadaj znovu:\n";
			break;
		}
	}
}

Spolocnost::Spolocnost(Datum datum):
	datum_(datum), 
	vozidla_(new ArrayList<Vozidlo*>()),
	prekladiska_(new ArrayList<Prekladisko*>()),
	objednavky_(new ArrayList<Objednavka*>()),
	run_(true)
{
	ifstream citac;
	citac.open("regiony.txt");
	string okres;

	while (true)
	{
		citac >> okres;
		cout << okres;
		Prekladisko *prekladisko = new Prekladisko(okres);
		prekladiska_->add(prekladisko);
		if (citac.eof()) break;
	}
}


Spolocnost::~Spolocnost()
{
	for (Vozidlo *vozidlo : *vozidla_)
	{
		delete vozidlo;
	}
	delete vozidla_;
	for (Prekladisko *prekladisko : *prekladiska_)
	{
		delete prekladisko;
	}
	delete prekladiska_;
	for (Objednavka *objednavka : *objednavky_)
	{
		delete objednavka;
	}
	delete objednavky_;
}
