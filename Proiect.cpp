//Domeiu - papetarie
#include <iostream>

using namespace std;

class Hartie {
public:
	const int idProdus;
	static string magazin;
	int nrMarciInStoc;
	float* pretProdus;
	float lungime;
	float latime;

	Hartie() :idProdus(1) {
		this->nrMarciInStoc = 0;
		this->pretProdus = NULL;
		this->lungime = 0;
		this->latime = 0;
	}
	Hartie(int idProdus) :idProdus(idProdus) {
		this->nrMarciInStoc = 0;
		this->pretProdus = NULL;
		this->lungime = 0;
		this->latime = 0;
	}
	Hartie(int idProdus, int nrMarciInStoc, float* pretProdus, float lungime, float latime) :idProdus(idProdus) {
		this->nrMarciInStoc = nrMarciInStoc;
		this->lungime = lungime;
		this->latime = latime;
		this->pretProdus = new float[nrMarciInStoc];
		for (int i = 0; i < nrMarciInStoc; i++) {
			this->pretProdus[i] = pretProdus[i];
		}
	}

	static void setMagazin(string magazin) {
		Hartie::magazin = magazin;
	}

	void afisare() {
		cout << "In " << magazin << " se afla hartie (ID:" << idProdus << ") de lungime " << lungime << " si latime " << latime << ". Avem " << nrMarciInStoc << " marci diferite la preturile de: ";
		if (nrMarciInStoc != 0) {
			for (int i = 0; i < nrMarciInStoc; i++) {
				cout << pretProdus[i] << "RON ";
			}
			cout << endl;
		}
		else cout << "-" << endl;
	}

};

class Pix {
public:
	const int idProdus;
	static string magazin;
	int nrMarciInStoc;
	float* pretProdus;
	bool pixCuGel;
	string culoare;

	Pix() :idProdus(2) {
		this->nrMarciInStoc = 0;
		this->pretProdus = NULL;
		this->pixCuGel = false;
		this->culoare = "necunoscuta";
	}
	Pix(int idProdus) :idProdus(idProdus) {
		this->nrMarciInStoc = 0;
		this->pretProdus = NULL;
		this->pixCuGel = false;
		this->culoare = "necunoscuta";
	}
	Pix(int idProdus, int nrMarciInStoc, float* pretProdus, bool pixCuGel, string culoare) :idProdus(idProdus) {
		this->nrMarciInStoc = nrMarciInStoc;
		this->pixCuGel = pixCuGel;
		this->culoare = culoare;
		this->pretProdus = new float[nrMarciInStoc];
		for (int i = 0; i < nrMarciInStoc; i++) {
			this->pretProdus[i] = pretProdus[i];
		}
	}

	static void setMagazin(string magazin) {
		Pix::magazin = magazin;
	}

	void afisare() {
		cout << "In " << magazin << " se afla pixuri (ID:" << idProdus << ") de culoarea " << culoare;
		if (pixCuGel) {
			cout << ", cu gel. ";
		}
		else cout << ", fara gel. ";
		cout<<"Avem " << nrMarciInStoc << " marci diferite la preturile de: ";
		if (nrMarciInStoc != 0) {
			for (int i = 0; i < nrMarciInStoc; i++) {
				cout << pretProdus[i] << "RON ";
			}
			cout << endl;
		}
		else cout << "-" << endl;
	}

};

class Caiet {
public:
	const int idProdus;
	static string magazin;
	int nrMarciInStoc;
	float* pretProdus;
	int nrFile;
	string tipCaiet;

	Caiet():idProdus(3){
		this->nrMarciInStoc = 0;
		this->pretProdus = NULL;
		this->nrFile = 0;
		this->tipCaiet = "necunoscut";
	}
	Caiet(int idProdus) :idProdus(idProdus) {
		this->nrMarciInStoc = 0;
		this->pretProdus = NULL;
		this->nrFile = 0;
		this->tipCaiet = "necunoscut";
	}
	Caiet(int idProdus, int nrMarciInStoc, float* pretProdus, int nrFile, string tipCaiet) :idProdus(idProdus) {
		this->nrMarciInStoc = nrMarciInStoc;
		this->nrFile = nrFile;
		this->tipCaiet = tipCaiet;
		this->pretProdus = new float[nrMarciInStoc];
		if (nrMarciInStoc != 0) {
			for (int i = 0; i < nrMarciInStoc; i++) {
				this->pretProdus[i] = pretProdus[i];
			}
		}
	}

	static void setMagazin(string magazin) {
		Caiet::magazin = magazin;
	}

	void afisare() {
		cout << "In " << magazin << " se afla caiete (ID:" << idProdus << ") cu " << nrFile << " de file tip " << tipCaiet << ". Avem " << nrMarciInStoc << " marci diferite la preturile de: ";
		if (nrMarciInStoc != 0) {
			for (int i = 0; i < nrMarciInStoc; i++) {
				cout << pretProdus[i] << "RON ";
			}
			cout << endl;
		}
		else cout << "-" << endl;
	}

};

string Hartie::magazin = "Papetarie S.R.L.";
string Pix::magazin = "Papetarie S.R.L.";
string Caiet::magazin = "Papetarie S.R.L.";

void main() {
//HARTIE - Initializarea obiectelor
	float* pretHartie=new float[3];
	pretHartie[0] = 13.99;
	pretHartie[1] = 14.99;
	pretHartie[2] = 19.99;
	Hartie hartie1;
	Hartie hartie2(100);
	Hartie hartie3(100, 3, pretHartie, 29.7, 21);
//Afisare
	hartie1.afisare();
	hartie2.afisare();
	hartie3.afisare();
	hartie3.setMagazin("magazinul Papetarie S.R.L.");
	hartie3.afisare();
	cout << endl;

//PIX - Initializarea obiectelor
	float* pretPix = new float[4];
	pretPix[0] = 2.99;
	pretPix[1] = 3.50;
	pretPix[2] = 4.99;
	pretPix[3] = 8.00;
	Pix pix1;
	Pix pix2(200);
	Pix pix3(200, 4, pretPix, true, "negru");
//Afisare
	pix1.afisare();
	pix2.afisare();
	pix3.afisare();
	pix3.setMagazin("magazinul Papetarie S.R.L.");
	pix3.afisare();
	cout << endl;

//CAIET - Initializarea obiectelor
	float* pretCaiet = new float[2];
	pretCaiet[0] = 9.99;
	pretCaiet[1] = 17.50;
	Caiet caiet1;
	Caiet caiet2(300);
	Caiet caiet3(300, 2, pretCaiet, 80, "velin");
//Afisare
	caiet1.afisare();
	caiet2.afisare();
	caiet3.afisare();
	caiet3.setMagazin("magazinul Papetarie S.R.L.");
	caiet3.afisare();
}