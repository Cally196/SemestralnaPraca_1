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
			"8. Vypis statistiky\n"
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
	switch (topDron)
	{
	case 1:
		if (vzdialenost <= (40 * 1.33) / 2) return true;
		else return false;
		break;

	case 2:
		if (vzdialenost <= (60 * 0.66) / 2) return true;
		else return false;
		break;
	default:
		return false;
		break;
	}
	//return false;
}

bool Spolocnost::overNosnost(int topDron, double hmotnost)
{

	switch (topDron)
	{
	case 1:
		if (hmotnost <= 2) return true;
		else return false;
		break;

	case 2:
		if (hmotnost <= 5) return true;
		else return false;
		break;
	default:
		return false;
		break;
	}
	return false;
}

Vozidlo* Spolocnost::overNosnostAutaZvoz(string okres, double hmotnost)
{
	Vozidlo *vhodneVozidlo = nullptr;
	
	for (Vozidlo *vozidlo : *vozidla_  )
	{
		if (vozidlo->patriRegionu(okres) && vozidlo->getHmotnostZvoz() + (hmotnost/1000) <= vozidlo->getNosnost())
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

Dron * Spolocnost::getDostupnyDron(double hmotnost, Prekladisko *prekladisko, double vzdialenost)
{
	//Prekladisko *prekladisko = nullptr;
	Dron *dostupnyDron = nullptr;
	//prekladisko = getPrekladisko(okres);
	dostupnyDron = prekladisko->getDron(hmotnost, &datum_, vzdialenost);
	   
	return dostupnyDron;
}

Dron * Spolocnost::getDostupnyDron(double hmotnost, Prekladisko *prekladisko, Dron *dron, double vzdialenost)
{
	//Prekladisko *prekladisko = nullptr;
	Dron *dostupnyDron = nullptr;
	//prekladisko = getPrekladisko(okres);
	dostupnyDron = prekladisko->getDron(hmotnost, &datum_, dron, vzdialenost);

	return dostupnyDron;
}

void Spolocnost::pridajVozidlo()
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

	do                                                                       //cyklus pre pridavanie regionov do trasy vozidla
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
}

void Spolocnost::vypisVozidla()
{
	cout << endl;
	cout << setw(20) << left << "SPZ";
	cout << setw(20) << left << "Nosnost";
	cout << setw(20) << left << "Celkove naklady";
	cout << setw(20) << left << "Datum zaradenia do evidencie" << endl;
	for (Vozidlo *voz : *vozidla_)
	{
		voz->vypisInfo();
	}
}

void Spolocnost::pridajDronDoPrekladiska()
{
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
	cout << "Dron bol pridany do prekladiska " << okres << endl;
}

void Spolocnost::vypisDronyVPrekladisku()
{
	string okres;
	Prekladisko *prekladisko = nullptr;
	do
	{
		cout << "\nZadajte okres\n>>";
		cin >> okres;
		prekladisko = getPrekladisko(okres);

	} while (prekladisko == nullptr);

	prekladisko->VypisDrony();
}

void Spolocnost::pridajObjednavku(int cisloObjednavky)
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
	vozidloZvoz = overNosnostAutaZvoz(regionOdosielatela, hmotnost); //ak existuje vozidlo schopne previezt zasielku tak sa priradi inak nullptr
	vozidloOdvoz = overNosnostAutaRozvoz(regionAdresata, hmotnost);

	Dron *dostupnyDron = getDostupnyDron(hmotnost, prekladiskoOdosielatela, vzdialenostOodosielatela); //konkretny najlepsi dron na prepravu zasielky od odosielatela
	if (dostupnyDron != nullptr) topDronZvoz = dostupnyDron->getTyp();
	else topDronZvoz = 3;
	
	Dron *dostupnyDronAdresat = getDostupnyDron(hmotnost, prekladiskoAdresata, vzdialenostAdresata);
	if (dostupnyDronAdresat != nullptr) topDronRozvoz = dostupnyDronAdresat->getTyp();
	else topDronRozvoz = 3;


	if (overDolet(topDronZvoz, vzdialenostOodosielatela) && overDolet(topDronRozvoz, vzdialenostAdresata)) //overenie doletu dronov v regione adresata a odosielatela
	{
		if (overNosnost(topDronZvoz, hmotnost) && overNosnost(topDronRozvoz, hmotnost))  //overenie nosnosti dronov v prekladiskach
		{
			if (vozidloZvoz != nullptr && vozidloOdvoz != nullptr) //overenie ci mame k dispozicii vozidla na prepravu 
			{
				Datum datumVyzdvihnutia = dostupnyDron->getCasVolny();
				if (dostupnyDron->getTyp() == 1)
				{
					minutyNaLokPrekladisko = (int)(0.75 * vzdialenostOodosielatela + 1);
					minutyNaDobitie = (minutyNaLokPrekladisko * 2) / 4 * 3;
					if (minutyNaLokPrekladisko % 4 != 0) minutyNaDobitie += 3;
				}
				else {
					minutyNaLokPrekladisko = (int)(1.5 * vzdialenostOodosielatela + 1);
					minutyNaDobitie = (minutyNaLokPrekladisko * 2) / 6 * 5;
					if (minutyNaLokPrekladisko % 4 != 0) minutyNaDobitie += 5;
				}
				datumVyzdvihnutia = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko); //cas kedy moze dostupny dron vyzdvihnut zasielku


				if (regionAdresata == regionOdosielatela) // overenie ci sa zasielka stihne dorucit do 18 hodiny ak sa regiony rovnaju
				{
					Datum datLokPrekladisko = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko + minutyNaDobitie); //cas kedy ten isty dron bude ready na odvezenie zasielky k adresatovi
					Dron *alternativnyDron = getDostupnyDron(hmotnost, prekladiskoAdresata, dostupnyDron, vzdialenostAdresata); //druhy najvhodnejsi dron 
					if (alternativnyDron->getCasVolny() < datLokPrekladisko)  //podmienka ci alternativny dron dokaze dorucit zasielku skor ako sa prvy dron nabije
					{
						if (alternativnyDron->getTyp() == 1)
						{
							minutyAdresat = (int)(0.75 * vzdialenostAdresata + 1);
						}
						else {
							minutyAdresat = (int)(1.5 * vzdialenostAdresata + 1);
						}
						Datum dorucenie = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko + minutyAdresat);
						if (dorucenie.getHodina() >= 18) flag = true;  //kontrola ci sa zasielka stihne dorucit do 18 hodiny
						else dostupnyDron = alternativnyDron;
					}
					else
					{
						if (dostupnyDron->getTyp() == 1)
						{
							minutyAdresat = (int)(0.75 * vzdialenostAdresata + 1);
						}
						else {
							minutyAdresat = (int)(1.5 * vzdialenostAdresata + 1);
						}
						Datum dorucenie = Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko + minutyAdresat + minutyNaDobitie);
						if (dorucenie.getHodina() >= 18) flag = true;
					}
				}

				if (datumVyzdvihnutia.getHodina() >= 20) flag = true; //ak sa zasielka moze vyzdvihnut az po 20 hodine objednavka sa zrusi 



				if (!flag)
				{
					Datum pomDatum = Datum::posunOHodinu(datum_);  //datum na kontrolu ci sa stihne zasielka vyzdvihnut do 1 hodiny
					if (pomDatum < datumVyzdvihnutia)
					{
						potvrdObjednavku = true;
					}
					else {
						cout << "Cas na vyzdvihnutie je viac ako hodina. Prajete si objednavku zrusit? [A/N]\n";
						string moznost;
						cin >> moznost;
						if (moznost == "A") potvrdObjednavku = false;
					}

					if (potvrdObjednavku) //ak vsetky podmienky platia objednavka sa akceptuje
					{
						Objednavka *objednavka = new Objednavka(hmotnost, regionOdosielatela, vzdialenostOodosielatela, regionAdresata, vzdialenostAdresata, cisloObjednavky, 0, datum_);
						Zasielka *zasielka = new Zasielka(cisloObjednavky, minutyNaLokPrekladisko, Datum::pridajMinuty(datumVyzdvihnutia, minutyNaLokPrekladisko), regionAdresata, hmotnost, vzdialenostAdresata);						
						objednavky_->add(objednavka);
						dostupnyDron->pridajZasielku(zasielka, minutyNaLokPrekladisko);
						vozidloZvoz->setHmotnostZvoz(hmotnost);
						vozidloOdvoz->setHmotnostRozvoz(hmotnost);
						cout << "\nObjednavka bola prijata\n";

					}
					else
					{
						Objednavka *objednavka = new Objednavka(hmotnost, regionOdosielatela, vzdialenostOodosielatela, regionAdresata, vzdialenostAdresata, cisloObjednavky, 5, datum_);
						objednavky_->add(objednavka);
						cout << "Objednavka bola zrusena.\n";
					}
				}
				else
				{
					Objednavka *objednavka = new Objednavka(hmotnost, regionOdosielatela, vzdialenostOodosielatela, regionAdresata, vzdialenostAdresata, cisloObjednavky, 4, datum_);
					objednavky_->add(objednavka);
					cout << "\nObjednavka bola zamietnuta z dovodu neskoreho casu vyzdvihnutia.\n";
				}
			}
			else
			{
				Objednavka *objednavka = new Objednavka(hmotnost, regionOdosielatela, vzdialenostOodosielatela, regionAdresata, vzdialenostAdresata, cisloObjednavky, 3, datum_);
				objednavky_->add(objednavka);
				cout << "\nObjednavka bola zamietnuta pretoze nalozenie zasielky do auta by prekrocilo jeho nosnost.\n";
			}
		
		}
		else
		{
			Objednavka *objednavka = new Objednavka(hmotnost, regionOdosielatela, vzdialenostOodosielatela, regionAdresata, vzdialenostAdresata, cisloObjednavky, 2, datum_);
			objednavky_->add(objednavka);
			cout << "\nObjednavka bola zamietnuta pretoze jej hmotnost je prilis vysoka.\n";
		}
	}
	else
	{
		Objednavka *objednavka = new Objednavka(hmotnost, regionOdosielatela, vzdialenostOodosielatela, regionAdresata, vzdialenostAdresata, cisloObjednavky, 1, datum_);
		objednavky_->add(objednavka);
		cout << "\nObjednavka bola zamietnuta pretoze je mimo akcny radius dronov.\n";
	}
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
	for (Prekladisko *prekladisko : *prekladiska_) //vsetky prekladiska
	{
		LinkedList<Zasielka*> *zasielky = prekladisko->getZasielkyNaOdvoz();

		if (!zasielky->isEmpty())
		{
			for (Vozidlo *vozidlo : *vozidla_) //najdenie vozidiel operujuceho v danom regione
			{				
				if (vozidlo->patriRegionu(prekladisko->getOkres()))
				{					
					vozidlo->setCelkoveNaklady(1); //pridanie nakladov za operovanie v danom prekladisku
					for (Zasielka *zasielka : *zasielky) //vsetky zasielky v prekladisku ktore sa nalozia do zvoleneho vozidla
					{						
						if (vozidlo->getNosnost() >= (vozidlo->getAktualnaHmotnost() + (zasielka->getHmotnost() / 1000))) //pomienka ci sa zmesti dalsia zasielka do vozidla
						{
							vozidlo->pridajZasielkuNaRozvoz(zasielka);
							vozidlo->setAktualnaHmotnost(vozidlo->getAktualnaHmotnost() + (zasielka->getHmotnost() / 1000));							
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

	Prekladisko *centralknePrekladisko = (*prekladiska_)[0];

	/*for (Prekladisko *prekladisko : *prekladiska_)
	{
		if (prekladisko->getOkres() == "ZA")
		{
			centralknePrekladisko = prekladisko;
			break;
		}			
	}*/

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
	Prekladisko *centralknePrekladisko = (*prekladiska_)[0];

	//for (Prekladisko *prekladisko : *prekladiska_)
	//{
	//	if (prekladisko->getOkres() == "ZA")
	//	{
	//		centralknePrekladisko = prekladisko;
	//		break;
	//	}
	//}

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
		vozidlo->VynulujHmotnosti();
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
			Dron *dostupnyDron = getDostupnyDron(zasielka->getHmotnost(), prekladisko, zasielka->getVzdialenostAdresata());

			if (dostupnyDron->getTyp() == 1)
			{
				minutyNaPrekladisko = (int)(0.75 * zasielka->getVzdialenostAdresata() + 1);

			}
			else {
				minutyNaPrekladisko = (int)(1.5 * zasielka->getVzdialenostAdresata() + 1);

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

void Spolocnost::vypisStatistiky()
{
	int minuty, hodiny, dni, pocetZrusenychObjednavok = 0;
	string region;

	cout << "\nZadaj zaciatok sledovaneho obdobia v tvare MM HH DD\n";
	cin >> minuty >> hodiny >> dni;
	Datum zacDatum = Datum(hodiny, minuty, dni);

	cout << "\nZadaj koniec sledovaneho obdobia v tvare MM HH DD\n";
	cin >> minuty >> hodiny >> dni;
	Datum konDatum = Datum(hodiny, minuty, dni);

	cout << "Zadajte sledovany region:\n";
	cin >> region;

	Prekladisko *maxDorucenych = (*prekladiska_)[0];
	Prekladisko *maxOdoslanych = (*prekladiska_)[0];
	int celkovyPocetDorucenychObjednavok = 0;
	double pocetNajazdenychKilometrov = 0;	

	for (Vozidlo *vozidlo : *vozidla_)
	{
		pocetNajazdenychKilometrov += (vozidlo->getCelkoveNaklady() / vozidlo->getNaklady()) / 2;
	}

	cout << "\n\nNalietane hodiny dronov podla typu v prekladiskach:" << endl << endl;
	cout << setw(20) << left << "Prekladisko";
	cout << setw(20) << left << "Drony typu 1";
	cout << setw(20) << left << "Drony typu 2" << endl;

	for (Prekladisko *prekladisko : *prekladiska_)
	{
		double pocetHodin1 = 0;
		double pocetHodin2 = 0;

		celkovyPocetDorucenychObjednavok += prekladisko->getPocetDorucenych();
		if (maxDorucenych->getPocetDorucenych() < prekladisko->getPocetDorucenych()) maxDorucenych = prekladisko;
		if (maxOdoslanych->getPocetOdoslanych() < prekladisko->getPocetOdoslanych()) maxOdoslanych = prekladisko;

		for (Dron *dron : *prekladisko->getZoznamDronov())
		{
			if (dron->getTyp() == 1) pocetHodin1 += dron->getNalietaneHodiny();
			else pocetHodin2 += dron->getNalietaneHodiny();
		}
		cout << setw(20) << left << prekladisko->getOkres();
		cout << setw(20) << left << pocetHodin1;
		cout << setw(20) << left << pocetHodin2 << endl;

	}

	cout << "\nNajviac dorucenych zasielok bolo do regionu: " << maxDorucenych->getOkres() << " (" << maxDorucenych->getPocetDorucenych() << ")\n";
	cout << "\nNajviac odoslanych zasielok bolo z regionu: " << maxOdoslanych->getOkres() << " (" << maxOdoslanych->getPocetOdoslanych() << ")\n";
	cout << "\nCelkovy pocet dorucenych zasielok: " << celkovyPocetDorucenychObjednavok << endl;
	cout << "\nCelkovy pocet najazdenych kilometrov vozidiel: " << pocetNajazdenychKilometrov * 50 << endl;

	cout << "\nObjednavku ktore boli v zadanom casovom obdobi zamietnute:\n";

	cout << setw(20) << left << "Cislo objednavky";
	cout << setw(20) << left << "Dovod zamietnutia" << endl;

	for (Objednavka *objednavka : *objednavky_)
	{
		if (objednavka->getDatum() < konDatum && zacDatum < objednavka->getDatum() && objednavka->getRegionOdosielatela() == region)
		{
			if (objednavka->getKod() == 5) pocetZrusenychObjednavok++;
			if (objednavka->getKod() > 0 && objednavka->getKod() < 5)
			{
				switch (objednavka->getKod())
				{
				case 1:
					cout << setw(20) << left << objednavka->getCisloObjednavky();
					cout << setw(20) << left << "Objednavka bola zamietnuta pretoze je mimo akcny radius dronov." << endl;
					break;

				case 2:
					cout << setw(20) << left << objednavka->getCisloObjednavky();
					cout << setw(20) << left << "Objednavka bola zamietnuta pretoze jej hmotnost je prilis vysoka." << endl;
					break;

				case 3:
					cout << setw(20) << left << objednavka->getCisloObjednavky();
					cout << setw(20) << left << "Objednavka bola zamietnuta pretoze nalozenie zasielky do auta by prekrocilo jeho nosnost." << endl;
					break;

				case 4:
					cout << setw(20) << left << objednavka->getCisloObjednavky();
					cout << setw(20) << left << "Objednavka bola zamietnuta z dovodu neskoreho casu vyzdvihnutia." << endl;
					break;
				}
			}
		}
		//else cout << "\nV zadanom okrese alebo casovom obdobi sa nenasli ziadne zamietnute zasielky.\n";
	}

	cout << "\nPocet zrusenych objednavok v regione " << region << " za zadane casove obdobie je: " << pocetZrusenychObjednavok << ".\n";
}

void Spolocnost::zapisDoSuboru()
{
	ofstream zapis;
	zapis.open("save.txt");

	if (zapis.is_open())
	{
		zapis << cisloObjednavky_ << endl;
		zapis << datum_.naZapis() << endl; //datum

		//zapis vozidiel
		zapis << vozidla_->size() << endl;
		for (Vozidlo *vozidlo : * vozidla_ )
		{
			zapis << vozidlo->getSpz() << " " << vozidlo->getNosnost() << " " <<
				vozidlo->getNaklady() << " " << vozidlo->getCelkoveNaklady() << " " << vozidlo->getDatumPridania().naZapis() << " " <<
				vozidlo->getHmotnostZvoz() << " " << vozidlo->getHmotnostRozvoz() << " " << vozidlo->getAktualnaHmotnost() << " " <<
				vozidlo->getDlzkaTrasy() << " " << vozidlo->getTrasa() << " " <<
				vozidlo->getZasielky()->size() << " " << vozidlo->getZasielkyZapis() << " ";
		}
		zapis << endl;



		//zapis prekladisk
		zapis << prekladiska_->size() << " ";

		for (Prekladisko *prekladisko : *prekladiska_)
		{
			zapis << prekladisko->getOkres() << " " << prekladisko->getMaxHmotnost() << " " <<
				prekladisko->getPocetDorucenych() << " " << prekladisko->getPocetOdoslanych() << " " <<
				prekladisko->getZoznamDronov()->size() << " ";
			for (Dron *dron : *prekladisko->getZoznamDronov())
			{
				zapis << dron->getInfoNaZapis();
			}

			zapis << prekladisko->getZasielkyNaOdvoz()->size() << endl;

			for (Zasielka *zasielka : *prekladisko->getZasielkyNaOdvoz())
			{
				zapis << zasielka->getZasielkaZapis();
			}

			zapis << prekladisko->getZasielkyNaRozvoz()->size() << endl;

			for (Zasielka *zasielka : *prekladisko->getZasielkyNaRozvoz())
			{
				zapis << zasielka->getZasielkaZapis();
			}
		}

		//objednavky

		zapis << objednavky_->size() << endl;

		for (Objednavka *objednavka : *objednavky_)
		{
			zapis << objednavka->getObjednavkaZapis();
		}
	}
}

void Spolocnost::nacitajZoSuboru()
{
	ifstream citac;
	citac.open("save.txt");
	int vozidla, dlzkaTrasy, prekladiska, drony, typ, nalietaneMinuty, pocPrepravenychZasielok, pocetZasielok;
	string spz, okres, serioveCislo, regionAdresata;
	double nosnost, naklady, celkoveNaklady, maxHmotnost, kapacitaBaterie, hmotnostZvoz, hmotnostRozvoz, aktualnaHmotnost, hmotnost, vzdialenostAdresata;
	int minuty, hodiny, dni, minutyNaLokPrekladisko, cisloObjednavky, casNaDobitie, pomBool, pocetDorucenychZasielok, pocetOdoslanychZasielok;
	
	bool vyzdvihnuta;

	citac >> cisloObjednavky_;

	//datum
	citac >> minuty >> hodiny >> dni;
	datum_ = Datum(hodiny, minuty, dni);

	//vozidla
	citac >> vozidla;
	for (int i = 0; i < vozidla; i++)
	{
		citac >> spz >> nosnost >> naklady >> celkoveNaklady >> minuty >> hodiny >> dni >> hmotnostZvoz >> hmotnostRozvoz >> aktualnaHmotnost;
		Datum datumVozidlo = Datum(hodiny, minuty, dni);
		citac >> dlzkaTrasy;
		LinkedList<string> *trasa = new LinkedList<string>;
		for (int j = 0; j < dlzkaTrasy; j++)
		{
			citac >> okres;
			trasa->add(okres);
		}

		LinkedList<Zasielka*> *zasielky = new LinkedList<Zasielka*>;
		citac >> pocetZasielok;
		for (int j = 0; j < pocetZasielok; j++)
		{
			citac >> pomBool;
			if (pomBool == 1) vyzdvihnuta = true;
			else vyzdvihnuta = false;

			citac >> minutyNaLokPrekladisko >> cisloObjednavky >> casNaDobitie >> minuty >> hodiny >> dni;
			Datum datLokPrekladisko = Datum(hodiny, minuty, dni);
			citac >> minuty >> hodiny >> dni >> regionAdresata >> hmotnost >> vzdialenostAdresata;
			Datum datumAdresat = Datum(hodiny, minuty, dni);
			Zasielka *zasielka = new Zasielka(vyzdvihnuta, minutyNaLokPrekladisko, cisloObjednavky, casNaDobitie, datLokPrekladisko, datumAdresat, regionAdresata, hmotnost, vzdialenostAdresata);
			zasielky->add(zasielka);
		}

		Vozidlo *vozidlo = new Vozidlo(spz, nosnost, naklady, celkoveNaklady, datumVozidlo, hmotnostZvoz, hmotnostRozvoz, aktualnaHmotnost, trasa, zasielky);
		vozidla_->add(vozidlo);
	}


	//prekladiska	
	for (Prekladisko *prekladisko : *prekladiska_)
	{
		delete prekladisko;
	}
	prekladiska_->clear();


	citac >> prekladiska;
	for (int i = 0; i < prekladiska; i++)
	{
		citac >> okres >> maxHmotnost >> pocetDorucenychZasielok >> pocetOdoslanychZasielok >> drony;
		ArrayList<Dron*> *drony_ = new ArrayList<Dron*>();
		LinkedList<Zasielka*> *zasielkyNaOdvoz = new LinkedList<Zasielka*>();
		LinkedList<Zasielka*> *zasielkyNaRozvoz = new LinkedList<Zasielka*>();	
		for (int j = 0; j < drony; j++)
		{
			citac >> typ >> nalietaneMinuty >> pocPrepravenychZasielok >> minuty >> hodiny >> dni;
			Datum datumZaradenia = Datum(hodiny, minuty, dni);
			citac >> minuty >> hodiny >> dni >> serioveCislo >> kapacitaBaterie >> pocetZasielok;
			Datum casVolny = Datum(hodiny, minuty, dni);

			LinkedList<Zasielka*> *zasielky_ = new LinkedList<Zasielka*>();			
			for (int k = 0; k < pocetZasielok; k++)
			{
				citac >> pomBool;
				if (pomBool == 1) vyzdvihnuta = true;
				else vyzdvihnuta = false;

				citac >> minutyNaLokPrekladisko >> cisloObjednavky >> casNaDobitie >> minuty >> hodiny >> dni;
				Datum datLokPrekladisko = Datum(hodiny, minuty, dni);
				citac >> minuty >> hodiny >> dni >> regionAdresata >> hmotnost >> vzdialenostAdresata;
				Datum datumAdresat = Datum(hodiny, minuty, dni);
				Zasielka *zasielka = new Zasielka(vyzdvihnuta, minutyNaLokPrekladisko, cisloObjednavky, casNaDobitie, datLokPrekladisko, datumAdresat, regionAdresata, hmotnost, vzdialenostAdresata);
				zasielky_->add(zasielka);
			}
			Dron *dron = new Dron(typ, nalietaneMinuty, pocPrepravenychZasielok, datumZaradenia, casVolny, serioveCislo, kapacitaBaterie, zasielky_);
			drony_->add(dron);
		}
			
			citac >> pocetZasielok;

			for (int k = 0; k < pocetZasielok; k++)
			{
				citac >> pomBool;
				if (pomBool == 1) vyzdvihnuta = true;
				else vyzdvihnuta = false;

				citac >> minutyNaLokPrekladisko >> cisloObjednavky >> casNaDobitie >> minuty >> hodiny >> dni;
				Datum datLokPrekladisko = Datum(hodiny, minuty, dni);
				citac >> minuty >> hodiny >> dni >> regionAdresata >> hmotnost >> vzdialenostAdresata;
				Datum datumAdresat = Datum(hodiny, minuty, dni);
				Zasielka *zasielka = new Zasielka(vyzdvihnuta, minutyNaLokPrekladisko, cisloObjednavky, casNaDobitie, datLokPrekladisko, datumAdresat, regionAdresata, hmotnost, vzdialenostAdresata);
				zasielkyNaOdvoz->add(zasielka);
			}
			
			citac >> pocetZasielok;

			for (int k = 0; k < pocetZasielok; k++)
			{
				citac >> pomBool;
				if (pomBool == 1) vyzdvihnuta = true;
				else vyzdvihnuta = false;

				citac >> minutyNaLokPrekladisko >> cisloObjednavky >> casNaDobitie >> minuty >> hodiny >> dni;
				Datum datLokPrekladisko = Datum(hodiny, minuty, dni);
				citac >> minuty >> hodiny >> dni >> regionAdresata >> hmotnost >> vzdialenostAdresata;
				Datum datumAdresat = Datum(hodiny, minuty, dni);
				Zasielka *zasielka = new Zasielka(vyzdvihnuta, minutyNaLokPrekladisko, cisloObjednavky, casNaDobitie, datLokPrekladisko, datumAdresat, regionAdresata, hmotnost, vzdialenostAdresata);
				zasielkyNaRozvoz->add(zasielka);
			}
		
	
		Prekladisko *prekladisko_ = new Prekladisko(okres, maxHmotnost, pocetDorucenychZasielok, pocetOdoslanychZasielok, drony_, zasielkyNaOdvoz, zasielkyNaRozvoz);
		prekladiska_->add(prekladisko_);
	}


	//objednavky

	int pocetObjednavok, kod;
	string odosielatelRegion, adresatRegion;
	double hmotnostZasielky, vzdialenostOdosielatela;

	citac >> pocetObjednavok;

	for (int i = 0; i < pocetObjednavok; i++)
	{
		citac >> hmotnostZasielky >> odosielatelRegion >> adresatRegion >> vzdialenostOdosielatela >>
			vzdialenostAdresata >> cisloObjednavky >> kod >> minuty >> hodiny >> dni;
		Datum datumVytvorenia = Datum(hodiny, minuty, dni);
		Objednavka *objednavka = new Objednavka(hmotnostZasielky, odosielatelRegion, vzdialenostOdosielatela, adresatRegion, vzdialenostAdresata, cisloObjednavky, kod, datumVytvorenia);
		objednavky_->add(objednavka);
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

		case 2:
		{
			datum_ = Datum::posunOHodinu(datum_);
			vylozDrony();
			if (datum_.getHodina() == 7)
			{
				navratVozidielDoCentralnehoSkladu();
				nalozenieVozidielVCentralnomSklade();
				transportZasielokDoLokalnychPrekladisk();
			}
			naplanujRozvozZasielok();
			dorucZasielky();
			break;
		}

		case 3:		
			pridajVozidlo(); 
			break;		

		case 4: 
			vypisVozidla();
			break;

		case 5: 			
			pridajDronDoPrekladiska();
			break;

		case 6: 		
			vypisDronyVPrekladisku();
			break;

		case 7:
			pridajObjednavku(cisloObjednavky_);
			cisloObjednavky_++;
			break;		

		case 8:
			vypisStatistiky();
			break;

		case 9:
			vypisMenu();
			break;

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
		//cout << okres;
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
