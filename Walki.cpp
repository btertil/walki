/*
 * walki.cpp
 *
 *  Created on:
 *  Author: Bondiev
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

class kmiot {

protected:
	static int iloscInstancji; // pole statyczne

public:
	float hp, exp, wyt, atak, obrona;
	string name, klasa;

	kmiot() {
		iloscInstancji++;
		hp = 100;
		exp = 20;
		wyt = 100;
		atak = 25;
		obrona = 25;
		klasa = "kmiot";
	}

	virtual ~kmiot() {
		iloscInstancji--;
	}

	static int IloscInstancji() {
		return iloscInstancji;
	}

	float atakuje();
	float broni(float);

};

int kmiot::iloscInstancji = 0;

float kmiot::atakuje() {

	float zadaje, random1, random_kr;

	if (hp > 0) {
		random1 = rand() % 100;
		random_kr = rand() % 100;

		//if ((random1 > 50) && ((random_kr + exp)/2) > 80) //premia za exp i tylko lepsze ciosy

		if (random_kr > 80 && random1 > 33) {
			zadaje = 3
					* (atak * (sqrt(hp) / 10) * (sqrt(exp) / 10)
							* (random1 / 100));
			cout << name << " zadaje " << zadaje
					<< " obrażeń  => trafienie krytyczne ***\n";
		} else {
			zadaje = atak * (sqrt(hp) / 10) * (sqrt(exp) / 10)
					* (random1 / 100);
			cout << name << " zadaje " << zadaje << " obrażeń\n";
		}
	}

	else
		zadaje = 0;
	return zadaje;

}

float kmiot::broni(float atak) {

	float broni, newhp;
	float random2;

	newhp = hp;

	if (hp > 0) {

		random2 = rand() % 100;
		broni = obrona * (sqrt(hp) / 10) * (sqrt(exp) / 10) * (random2 / 100);
		cout << name << " broni " << broni << " obrażeń\n";

		if ((atak > broni) && (atak > 0)) {
			newhp = hp - (atak - broni);
			cout << name << " ma jeszcze " << newhp << " życia\n";
		}

		else
			cout << name << " ma jeszcze " << newhp << " życia\n";

	}

	return newhp;
}

class SzkolonyBandzior: public kmiot {
public:

	SzkolonyBandzior() {
		iloscInstancji++;
		hp = 100;
		exp = 30;
		wyt = 100;
		atak = 30;
		obrona = 25;
		klasa = "Szkolony bandzior";
	}
};

class StrazZamkowa: public kmiot {
public:

	StrazZamkowa() {
		iloscInstancji++;
		hp = 100;
		exp = 45;
		wyt = 100;
		atak = 35;
		obrona = 40;
		klasa = "Strażnik zamkowy";
	}
};

class Miecznik: public kmiot {
public:

	Miecznik() {
		iloscInstancji++;
		hp = 100;
		exp = 45;
		wyt = 100;
		atak = 50;
		obrona = 45;
		klasa = "Miecznik";
	}
};

class Topornik: public kmiot {
public:

	Topornik() {
		iloscInstancji++;
		hp = 100;
		exp = 45;
		wyt = 100;
		atak = 65;
		obrona = 30;
		klasa = "Topornik";
	}
};

class Rycerz: public kmiot {
public:

	Rycerz() {
		iloscInstancji++;
		hp = 100;
		exp = 65;
		wyt = 100;
		atak = 55;
		obrona = 60;
		klasa = "Rycerz";
	}
};

class Mistrz: public kmiot {
public:

	Mistrz() {
		iloscInstancji++;
		hp = 100;
		exp = 85;
		wyt = 100;
		atak = 65;
		obrona = 70;
		klasa = "Mistrz";
	}
};

void walka(kmiot *w1, kmiot *w2) {

	static int tura = 0;

	while (w1->hp > 0 && w2->hp > 0) {
		w1->hp = w1->broni(w2->atakuje());
		w2->hp = w2->broni(w1->atakuje());
		cout << endl;
		tura++;
	}

	if (w1->hp <= 0 && w2->hp <= 0) {
		cout << w1->name << " padł\n";
		cout << w2->name << " padł\n";
	}

	if (w1->hp <= 0 && w2->hp > 0) {
		cout << w1->klasa << " " << w1->name << " padł po " << tura
				<< " ciosach \n";
		cout << w2->klasa << " " << w2->name << " wygrał i ma jeszcze "
				<< w2->hp << " hp\n";
	}

	if (w1->hp > 0 && w2->hp <= 0) {
		cout << w1->klasa << " " << w1->name << " wygrał i ma jeszcze "
				<< w1->hp << " hp\n";
		cout << w2->klasa << " " << w2->name << " padł po " << tura
				<< " ciosach \n";
	}

	return;
}

void losowanie(int *d1, int *d2) {
	*d1 = rand() % 7 + 1;
	*d2 = rand() % 7 + 1;
}

void wybierz(int *d1, int *d2, string tabname[2][7]) //UWAGA argument przesłany to tablica bez nawiasów klamrowych jako wskaźnik
		{

	int *ztab[2] = { d1, d2 }; // tablica ze wskaźnikami żeby w pętli

	cout << "Walki Kmiotów v0.3.1\n";

	for (int k = 1; k < 3; k++) {
		cout << "\nWybierz zawodnika: " << k << "\n";
		for (int i = 1; i <= 7; i++) {
			cout << "   " << i << ": " << tabname[k - 1][i - 1] << endl;
		}
		do {
			cout << "Podaj liczbę 1-7, lub 8 żeby wylosować obu zawodników: ";
			cin >> *ztab[k - 1];
			if (*ztab[k - 1] == 8) {
				losowanie(d1, d2);
				goto exit;
			}
		} while ((*ztab[k - 1] < 1) || (*ztab[k - 1] > 8));

	}

	exit:

	return;
}

int main() {

// Deklaracje
// Dwa wskaźniki dla walczących, zamiast deklaracji pozostałych => new w warunku!! :)
// Muszą być zadeklarowane w main bo w ifie zasięg tylko wewnątrz ifa.

	kmiot *wk1, *wk2;
	int zawodnik1, zawodnik2, kol;

	string tab_name[2][7] = { { "Leszek", "Felicjan", "Wiesław", "Sobiesław",
			"Marnota", "Zbysław", "Bondkovitz" }, { "Otroka", "Mruk", "Biedroń",
			"Wacław", "Yarpen", "Bolesław", "Władysław" } };

	srand (time(NULL)); // reset dla seeda wartości losowej

wybierz	(&zawodnik1, &zawodnik2, tab_name); // do menu wystarczy tak przekazać tablicę z nazwami bez bo to i tak jest wskaźnik!!!

	/*	przekazanie wskaźnika jako argumentu funkcji efektywniejsze niż całej klasy i można elastycznie
	 *  zarządzać pamięcią. Żeby nie tworzyć wielu deklaracji (w if'ie zasięg lokalny) - operator new warunkowo.
	 *  Tak będą tylko 2 instancje a nie 26 !  */

	if (zawodnik1 == 1)
		wk1 = new kmiot;
	if (zawodnik1 == 2)
		wk1 = new SzkolonyBandzior;
	if (zawodnik1 == 3)
		wk1 = new StrazZamkowa;
	if (zawodnik1 == 4)
		wk1 = new Miecznik;
	if (zawodnik1 == 5)
		wk1 = new Topornik;
	if (zawodnik1 == 6)
		wk1 = new Rycerz;
	if (zawodnik1 == 7)
		wk1 = new Mistrz;

	if (zawodnik2 == 1)
		wk2 = new kmiot;
	if (zawodnik2 == 2)
		wk2 = new SzkolonyBandzior;
	if (zawodnik2 == 3)
		wk2 = new StrazZamkowa;
	if (zawodnik2 == 4)
		wk2 = new Miecznik;
	if (zawodnik2 == 5)
		wk2 = new Topornik;
	if (zawodnik2 == 6)
		wk2 = new Rycerz;
	if (zawodnik2 == 7)
		wk2 = new Mistrz;

	wk1->name = tab_name[0][zawodnik1 - 1]; // bo w tablicy element 1 to tab_name[0] i imiona będą przesunięte
	wk2->name = tab_name[1][zawodnik2 - 1];

	cout << "\nPierwszy zawodnik to " << wk1->klasa << " " << wk1->name << "\n";
	cout << "Drugi zawodnik to " << wk2->klasa << " " << wk2->name << "\n\n";

//getch();

	kol = rand() % 2 + 1; //ustawienie losowej kolejnoci zadawania ciosów

	if (kol > 1)
		walka(wk1, wk2); // uwaga, funkacja przekazuje wskaźniki do klas!
	else
		walka(wk2, wk1);

	delete wk1;
	delete wk2;

	return 0;
}
