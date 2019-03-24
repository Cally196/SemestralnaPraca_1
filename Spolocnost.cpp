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

bool Spolocnost::overDolet(int topDron, double vzdialenost)
{
	int typ = 0;		
	
	switch (topDron)
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

bool Spolocnost::overNosnost(int topDron, double hmotnost)
{

	switch (topDron)
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

Vozidlo* Spolocnost::overNosnostAutaZvoz(string okres, double hmotnost)
{
	Vozidlo *vhodneVozidlo = nullptr;
	
	for (Vozidlo *vozidlo : *vozidla_  )
	{
		if (vozidlo->patriRegionu(okres) && (vozidlo->getHmotnostZvoz() + hmotnost)/1000 <= vozidlo->getNosnost())
		{
			vhodneVozidlo = vozidlo;
		}
	}

	return vhodneVozidlo;
}

Vozidlo* Spolocnost::overNosnostAutaRozvoz(string okres, double hmotnost)
{
	Vozidlo *vhodneVozidlo = nullptr;

	for (Vozidlo *vozidlo : *vozidla_)
	{
		if (vozidlo->patriRegionu(okres) && (vozidlo->getHmotnostRozvoz() + hmotnost)/1000 <= vozidlo->getNosnost())
		{
			vhodneVozidlo = vozidlo;
		}
	}
	return vhodneVozidlo;
}

Dron * Spolocnost::getDostupnyDron(double hmotnost, Prekladisko *prekladisko)
{
	//Prekladisko *prekladisko = nullptr;
	Dron *dostupnyDron = nullptr;
	//prekladisko = getPrekladisko(okres);
	dostupnyDron = prekladisko->getDron(hmotnost, &datum_);
	   
	return dostupnyDron;
}

Dron * Spolocnost::getDostupnyDron(double hmotnost, Prekladisko *prekladisko, Dron *dron)
{
	//Prekladisko *prekladisko = nullptr;
	Dron *dostupnyDron = nullptr;
	//prekladisko = getPrekladisko(okres);
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

void Spolocnost::navratVozidielDoCentralnehoSkladu()
{
	for (Prekladisko *prekladisko : *prekladiska_)
	{
		LinkedList<Zasielka*> *zasielky = prekladisko->getZasielkyNaOdvoz();

		if (!zasielky->isEmpty())
		{
			for (Vozidlo *vozidlo : *vozidla_)
			{
				//int pocetObsluzenychPrekladisk = 0;
				if (vozidlo->patriRegionu(prekladisko->getOkres()))
				{
					//double hmotnost = 0;
					vozidlo->setCelkoveNaklady(1);
					for (Zasielka *zasielka : *zasielky)
					{						
						if (vozidlo->getNosnost() >= (vozidlo->getAktualnaHmotnost() + (zasielka->getHmotnost() / 1000)))
						{
							vozidlo->pridajZasielkuNaRozvoz(zasielka);
							vozidlo->setAktualnaHmotnost(vozidlo->getAktualnaHmotnost() + (zasielka->getHmotnost() / 1000));
							//hmotnost += zasielka->getHmotnost() / 1000;
							zasielky->tryRemove(zasielka);
							if (zasielky->isEmpty()) break;
						}
						else break;
					}
					if (zasielky->isEmpty()) break;
				}
			}
		}
	}

	Prekladisko *centralknePrekladisko = nullptr;

	for (Prekladisko *prekladisko : *prekladiska_)
	{
		if (prekladisko->getOkres() == "ZA")
		{
			centralknePrekladisko = prekladisko;
			break;
		}			
	}

	for (Vozidlo *vozidlo : *vozidla_)
	{
		vozidlo->setAktualnaHmotnost(0);
		LinkedList<Zasielka*> *zasielky = vozidlo->getZasielky();

		for (Zasielka *zasielka : *zasielky)
		{
			centralknePrekladisko->getZasielkyNaOdvoz()->add(zasielka);
			zasielky->tryRemove(zasielka);
			if (zasielky->isEmpty()) break;
		}
	}


}

void Spolocnost::nalozenieVozidielVCentralnomSklade()
{
	Prekladisko *centralknePrekladisko = nullptr;

	for (Prekladisko *prekladisko : *prekladiska_)
	{
		if (prekladisko->getOkres() == "ZA")
		{
			centralknePrekladisko = prekladisko;
			break;
		}
	}
	LinkedList<Zasielka*> *zasielky = centralknePrekladisko->getZasielkyNaOdvoz();

	for (Zasielka *zasielka : *zasielky)
	{
		if (zasielka->getRegionAdresata() == "ZA")
		{
			centralknePrekladisko->getZasielkyNaRozvoz()->add(zasielka);
		}
		else
		{
			for (Vozidlo *vozdilo : *vozidla_)
			{
				if (vozdilo->patriRegionu(zasielka->getRegionAdresata()))
				{
					if (vozdilo->getNosnost() >= (vozdilo->getAktualnaHmotnost() + (zasielka->getHmotnost() / 1000)))
					{
						vozdilo->pridajZasielkuNaRozvoz(zasielka);
						zasielky->tryRemove(zasielka);
						vozdilo->setAktualnaHmotnost(vozdilo->getAktualnaHmotnost() + (zasielka->getHmotnost() / 1000));
					}
				}
				if (zasielky->isEmpty()) break;
			}
		}
		if (zasielky->isEmpty()) break;
	}


}

void Spolocnost::transportZasielokDoLokalnychPrekladisk()
{
	for (Vozidlo *vozidlo : *vozidla_)
	{
		if (!vozidlo->getZasielky()->isEmpty())
		{
			for (Zasielka *zasielka : *vozidlo->getZasielky())
			{
				for (Prekladisko *prekladisko : *prekladiska_)
				{
					if (prekladisko->getOkres() == zasielka->getRegionAdresata())
					{
						prekladisko->getZasielkyNaRozvoz()->add(zasielka);
						vozidlo->getZasielky()->tryRemove(zasielka);
						break;
					}

				}
				if (vozidlo->getZasielky()->isEmpty()) break;
			}
		}
	}

}

void Spolocnost::naplanujRozvozZasielok()
{
	
	int minutyNaPrekladisko = 0;

	for (Prekladisko *prekladisko : *prekladiska_)
	{
		for (Zasielka *zasielka : *prekladisko->getZasielkyNaRozvoz())
		{
			Dron *dostupnyDron = getDostupnyDron(zasielka->getHmotnost(), prekladisko);

			if (dostupnyDron->getTyp() == 1)
			{
				minutyNaPrekladisko = 0.75 * zasielka->getVzdialenostAdresata() + 1;

			}
			else {
				minutyNaPrekladisko = 1.5 * zasielka->getVzdialenostAdresata() + 1;

			}

			zasielka->setDatumAdresat(Datum::pridajMinuty(datum_, minutyNaPrekladisko));

			dostupnyDron->pridajZasielku(zasielka, minutyNaPrekladisko);

			prekladisko->getZasielkyNaRozvoz()->tryRemove(zasielka);

			if (prekladisko->getZasielkyNaRozvoz()->isEmpty()) break;
		}
	}
}

void Spolocnost::dorucZasielky()
{
	for (Prekladisko *prekladisko : *prekladiska_)
	{
		prekladisko->dorucZasielky(datum_);
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
				Zasielka *zasielka = new Zasielka(cisloOnjednavky, minNaLokPrekladisko, datum_, okres, 5, 0); // TODO
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
			if (datum_.getHodina() == 7)
			{
				navratVozidielDoCentralnehoSkladu();
				nalozenieVozidielVCentralnomSklade();
				transportZasielokDoLokalnychPrekladisk();
				naplanujRozvozZasielok();
			}
			if (datum_.getHodina() == 8)
			{
				dorucZasielky();

			}
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
			Vozidlo *vozidloZvoz = nullptr;
			Vozidlo *vozidloOdvoz = nullptr;
			int topDronZvoz = 0;
			int topDronRozvoz = 0;

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
			vzdialenostOodosielatela = skontrolujInt();

			do
			{
				cout << "Zadajte okres adresata\n";
				cin >> regionAdresata;
				prekladiskoAdresata = getPrekladisko(regionAdresata);
				if (prekladiskoAdresata != nullptr) break;
				cout << "Zadali ste chybny okres\n";

			} while (true);

			cout << "Zadajte vzdialenost adresata od prekladiska[km]\n";
			vzdialenostAdresata = skontrolujInt();

			int minutyNaLokPrekladisko = 0;
			int minutyNaDobitie = 0;
			int minutyAdresat = 0;
			bool flag = false;
			vozidloZvoz = overNosnostAutaZvoz(regionOdosielatela, hmotnost);
			vozidloOdvoz = overNosnostAutaRozvoz(regionAdresata, hmotnost);

			topDronZvoz = prekladiskoOdosielatela->getTopDron();
			topDronRozvoz = prekladiskoAdresata->getTopDron();

			if (overDolet(topDronZvoz, vzdialenostOodosielatela) && overDolet(topDronRozvoz, vzdialenostAdresata))
			{
				if (overNosnost(topDronZvoz, hmotnost) && overNosnost(topDronRozvoz, hmotnost))
				{
					if (vozidloZvoz != nullptr && vozidloOdvoz != nullptr)
					{



						Dron *dostupnyDron = getDostupnyDron(hmotnost, prekladiskoOdosielatela);
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
						datumVyzdvihnutia = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko); //cas kedy moze dostupny dron vyzdvihnut zasielku





						if (regionAdresata == regionOdosielatela) // overenie ci sa zasielka stihne dorucit do 18 hodiny ak sa regiony rovnaju
						{
							Datum datLokPrekladisko = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko + minutyNaDobitie); //cas kedy ten isty dron bude ready na odvezenie zasielky
							Dron *alternativnyDron = getDostupnyDron(hmotnost, prekladiskoAdresata, dostupnyDron);
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
								else dostupnyDron = alternativnyDron;
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
								Zasielka *zasielka = new Zasielka(cisloObjednavky, minutyNaLokPrekladisko, Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko), regionAdresata, hmotnost, vzdialenostAdresata);
								cisloObjednavky++;
								objednavky_->add(objednavka);
								dostupnyDron->pridajZasielku(zasielka, minutyNaLokPrekladisko);
								vozidloZvoz->setHmotnostZvoz(hmotnost);
								vozidloOdvoz->setHmotnostRozvoz(hmotnost);
								cout << "\nObjednavka bola prijata\n";

							}
							else cout << "Objednavka bola zrusena.\n";
						}
						else
						{
							cout << "\nObjednavka bola zamietnuta z dovodu neskoreho casu vyzdvihnutia.\n";
						}
					}
					else
					{
						cout << "\nObjednavka bola zamietnuta pretoze nalozenie zasielky do auta by prekrocilo jeho nosnost.\n";
					}
				}
				else
				{
					cout << "\nObjednavka bola zamietnuta pretoze jej hmotnost je prilis vysoka.\n";
				}
			}
			else
			{
				cout << "\nObjednavka bola zamietnuta pretoze je mimo akcnz radius dronov.\n";
			}
				
				/*flag = true;

			if (flag) cout << "\nObjednavka bola zamietanuta zo strany AoE\n";		*/
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
