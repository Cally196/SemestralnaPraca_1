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
			"2. Posun cas o hodinu\n"
			"3. Pridaj nove vozidlo\n"
			"4. Vypis zoznam vozidiel\n"
			"5. Pridaj novy dron\n"
			"6. Vypis vsetky drony v danom prekladisku\n"
			"7. Vytvor objednavku\n"
			"15. Zapis do suboru\n"
			"16. Nacitaj zo suboru\n"
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
	Prekladisko *prekladisko_ = nullptr;
	for (Prekladisko *prekladisko : *prekladiska_)
	{
		if (prekladisko->getOkres() == okres) return prekladisko;
	}
	return prekladisko_;
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

bool Spolocnost::overNosnostAutaZvoz(string okres, double hmotnost)
{
	for (Vozidlo *vozidlo : *vozidla_  )
	{
		if (vozidlo->patriRegionu(okres) && (vozidlo->getHmotnostZvoz() + hmotnost)/1000 <= vozidlo->getNosnost())
		{
			return true;
		}
	}

	return false;
}

bool Spolocnost::overNosnostAutaRozvoz(string okres, double hmotnost)
{
	for (Vozidlo *vozidlo : *vozidla_)
	{
		if (vozidlo->patriRegionu(okres) && (vozidlo->getHmotnostRozvoz() + hmotnost)/1000 <= vozidlo->getNosnost())
		{
			return true;
		}
	}
	return false;
}

Dron * Spolocnost::getDostupnyDron(double hmotnost, string okres)
{
	Prekladisko *prekladisko = nullptr;
	Dron *dostupnyDron = nullptr;
	prekladisko = getPrekladisko(okres);
	dostupnyDron = prekladisko->getDron(hmotnost, &datum_);
	   
	return dostupnyDron;
}

Dron * Spolocnost::getDostupnyDron(double hmotnost, string okres, Dron * dron)
{
	Prekladisko *prekladisko = nullptr;
	Dron *dostupnyDron = nullptr;
	prekladisko = getPrekladisko(okres);
	dostupnyDron = prekladisko->getDron(hmotnost, &datum_, dron);

	return dostupnyDron;
}

void Spolocnost::vylozDrony()
{
	for (Prekladisko *prekladisko : *prekladiska_)
	{
		prekladisko->vylozDrony(datum_);
	}
}

void Spolocnost::zapisDoSuboru()
{
	ofstream zapis;
	zapis.open("save.txt");

	if (zapis.is_open())
	{
		zapis << vozidla_->size() << endl;
		for (Vozidlo *vozidlo : * vozidla_ )
		{
			zapis << vozidlo->getSpz() << " " << vozidlo->getNosnost() << " " <<
				vozidlo->getNaklady() << " " << vozidlo->getDlzkaTrasy() << " " << vozidlo->getTrasa() << " ";
		}
		zapis << endl;

		zapis << prekladiska_->size() << " ";

		for (Prekladisko *prekladisko : *prekladiska_)
		{
			zapis << prekladisko->getOkres() << " " << prekladisko->getMaxHmotnost() << " " <<
				prekladisko->getZoznamDronov()->size() << " ";
			for (Dron *dron : *prekladisko->getZoznamDronov())
			{
				zapis << dron->getInfoNaZapis();
			}
		}



	}
}

void Spolocnost::nacitajZoSuboru()
{
	ifstream citac;
	citac.open("save.txt");
	int vozidla, dlzkaTrasy, prekladiska, drony, typ, nalietaneMinuty, pocPrepravenychZasielok, zasielky, cisloOnjednavky, minNaLokPrekladisko;
	string spz, okres, serioveCislo;
	double nosnost, naklady, maxHmotnost, kapacitaBaterie;
	
	citac >> vozidla;
	for (int i = 0; i < vozidla; i++)
	{
		citac >> spz >> nosnost >> naklady;
		citac >> dlzkaTrasy;
		LinkedList<string> *trasa = new LinkedList<string>;
		for (int j = 0; j < dlzkaTrasy; j++)
		{
			citac >> okres;
			trasa->add(okres);
		}
		Vozidlo *vozidlo = new Vozidlo(spz, nosnost, naklady, datum_, trasa);
		vozidla_->add(vozidlo);
	}

	for (Prekladisko *prekladisko : *prekladiska_)
	{
		delete prekladisko;
	}
	prekladiska_->clear();
	citac >> prekladiska;
	for (int i = 0; i < prekladiska; i++)
	{
		citac >> okres >> maxHmotnost >> drony;
		ArrayList<Dron*> *drony_ = new ArrayList<Dron*>();
		for (int j = 0; j < drony; j++)
		{
			citac >> typ >> serioveCislo >> nalietaneMinuty >> pocPrepravenychZasielok >> kapacitaBaterie >> zasielky;
			LinkedList<Zasielka*> *zasielky_ = new LinkedList<Zasielka*>();	
			for (int k = 0; k < zasielky; k++)
			{
				citac >> cisloOnjednavky >> minNaLokPrekladisko;
				Zasielka *zasielka = new Zasielka(cisloOnjednavky, minNaLokPrekladisko, datum_, okres);
				zasielky_->add(zasielka);
			}			
			Dron *dron = new Dron(typ, serioveCislo, datum_, nalietaneMinuty, pocPrepravenychZasielok, kapacitaBaterie, zasielky_);
			drony_->add(dron);
		}
	
		Prekladisko *prekladisko_ = new Prekladisko(okres, maxHmotnost, drony_);
		prekladiska_->add(prekladisko_);

	}
}

void Spolocnost::vyber()
{
	int volba_, cisloObjednavky = 100;
	

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

		case 2:
		{
			datum_ = Datum::posunOHodinu(datum_);
			vylozDrony();
			break;
		}

		case 3:
		{
			string spz, okres;
			double nosnost;
			double naklady;
			LinkedList<string> *trasa = new LinkedList<string>;		
			cout << "\nZadajte SPZ:\n";
			cin >> spz;
			cout << "Zadajte nosnost(v tonach):\n";
			cin >> nosnost;
			cout << "Zadajte prevadzkove naklady:\n";
			cin >> naklady;

			do
			{
				cout << "\nZadaj okres do trasy. Pre ukoncenie zadaj 'koniec'\n";
				cin >> okres;
				if (okres == "koniec")
				{
					break;
				}
				else {
					if (getPrekladisko(okres) != nullptr)
					{
						trasa->add(okres);					
					}
				}
			} while (true);


			Vozidlo *vozidlo = new Vozidlo(spz, nosnost, naklady, datum_, trasa);
			vozidla_->add(vozidlo);			
			cout << "Vozidlo bolo pridane do databazy.\n";
			break;
		}

		case 4: {
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

		case 5: {
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

		case 6: 
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

		case 7:
		{
			bool potvrdObjednavku = true;
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

			int minutyNaLokPrekladisko = 0;
			int minutyNaDobitie = 0;
			int minutyAdresat = 0;
			bool flag = false;

			if (overDolet(regionOdosielatela, vzdialenostOodosielatela) && overDolet(regionAdresata, vzdialenostAdresata) && overNosnost(regionOdosielatela, hmotnost) &&
				overNosnost(regionAdresata, hmotnost) && overNosnostAutaZvoz(regionOdosielatela, hmotnost) && overNosnostAutaRozvoz(regionAdresata, hmotnost))
			{
				Dron *dostupnyDron = getDostupnyDron(hmotnost, regionOdosielatela);
				Datum datumVyzdvihnutia = dostupnyDron->getCasVolny();
				if (dostupnyDron->getTyp() == 1)
				{
					minutyNaLokPrekladisko = 0.75 * vzdialenostOodosielatela + 1;
					minutyNaDobitie = (minutyNaLokPrekladisko * 2) / 4 * 3;
					if (minutyNaLokPrekladisko % 4 != 0) minutyNaDobitie += 3;					
				}
				else {
					minutyNaLokPrekladisko = 1.5 * vzdialenostOodosielatela + 1;
					minutyNaDobitie = (minutyNaLokPrekladisko * 2) / 6 * 5;
					if (minutyNaLokPrekladisko % 4 != 0) minutyNaDobitie += 5;
				}
				datumVyzdvihnutia = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko); //zas kedy moze dostupny dron vyzdvihnut zasielku





				if (regionAdresata == regionOdosielatela) // overenie ci sa zasielka stihne dorucit do 18 hodiny ak sa regiony rovnaju
				{
					Datum datLokPrekladisko = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko + minutyNaDobitie); //cas kedy ten isty dron bude ready na odvezenie zasielky
					Dron *alternativnyDron = getDostupnyDron(hmotnost, regionOdosielatela, dostupnyDron);
					if (alternativnyDron->getCasVolny() < datLokPrekladisko)
					{
						if (alternativnyDron->getTyp() == 1)
						{
							minutyAdresat = 0.75 * vzdialenostAdresata + 1;							
						}
						else {
							minutyAdresat = 1.5 * vzdialenostAdresata + 1;						
						}
						Datum dorucenie = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko + minutyAdresat);
						if (dorucenie.getHodina() >= 18) flag = true;
						dostupnyDron = alternativnyDron;
					}
					else
					{
						if (dostupnyDron->getTyp() == 1)
						{
							minutyAdresat = 0.75 * vzdialenostAdresata + 1;
						}
						else {
							minutyAdresat = 1.5 * vzdialenostAdresata + 1;
						}
						Datum dorucenie = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko + minutyAdresat + minutyNaDobitie);
						if (dorucenie.getHodina() >= 18) flag = true;
					}
				}

				if (datumVyzdvihnutia.getHodina() >= 20) flag = true; //ak sa zasielka moze vyzdvihnut az po 20 hodine objednavka sa zrusi 
				if (!flag)
				{
					Datum pomDatum = Datum::posunOHodinu(datum_);  //datum na kontrolu ci sa stihne zasielka vyzdvihnut do 1 hodiny
					if (datumVyzdvihnutia < pomDatum)
					{
						potvrdObjednavku = true;
					}
					else {
						cout << "Cas na vyzdvihnutie je viac ako hodina. Prajete si objednavku zrusit? [A/N]\n";
						string moznost;
						cin >> moznost;
						if (moznost == "A") potvrdObjednavku = false;
					}

					if (potvrdObjednavku)
					{
						Objednavka *objednavka = new Objednavka(hmotnost, regionOdosielatela, vzdialenostOodosielatela, regionAdresata, vzdialenostAdresata, cisloObjednavky);
						Zasielka *zasielka = new Zasielka(cisloObjednavky, minutyNaLokPrekladisko, Datum::pridajMinuty(datum_, minutyNaLokPrekladisko*2), regionAdresata);
						cisloObjednavky++;
						objednavky_->add(objednavka);
						dostupnyDron->pridajZasielku(zasielka);
						cout << "\nObjednavka bola prijata\n";

					}
					else cout << "Objednavka bola zrusena.\n";
				}
				else
				{
					cout << "Objednavka bola zrusena.\n";
				}
			}
			else flag = true;

			if (flag) cout << "\nObjednavka bola zamietanuta zo strany AoE\n";		
			break;
		}

		case 15:		
			zapisDoSuboru();
			break;

		case 16:
			nacitajZoSuboru();
			break;

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
