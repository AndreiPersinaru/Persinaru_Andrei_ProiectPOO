//Domeniu - papetarie
#include <iostream>
#include <fstream>

using namespace std;

class Produs {
public:
	virtual void produs() = 0;
};

class InstrumentDeScris {
public:
	virtual void instrumentScris() = 0;
};

class Hartie :public Produs {
protected:
	const int idProdus;
	static string magazin;
	int nrMarciInStoc;
	float* pretProdus;
	float lungime;
	float latime;

public:
//Get-eri si Set-eri
	int getIdProdus() {
		return idProdus;
	}

	static void setMagazin(string magazin) {
		Hartie::magazin = magazin;
	}
	string getMagazin() {
		return magazin;
	}

	void setNrMarciSiPret(int nrMarciInStoc, float* pretProdus) {
		if (nrMarciInStoc > 0) {
			this->nrMarciInStoc = nrMarciInStoc;
			if (this->pretProdus != NULL) {
				delete[]this->pretProdus;
			}
			this->pretProdus = new float[this->nrMarciInStoc];
			for (int i = 0; i < this->nrMarciInStoc; i++) {
				this->pretProdus[i] = pretProdus[i];
			}
		}
	}
	int getNrMarciInStoc() {
		return nrMarciInStoc;
	}

	void setPretProdus(float* pretProdus) {
		for (int i = 0; i < nrMarciInStoc; i++) {
			this->pretProdus[i] = pretProdus[i];
		}
	}
	float* getPretProdus() {
		return pretProdus;
	}

	void setLungime(float lungime) {
		this->lungime = lungime;
	}
	float getLungime() {
		return lungime;
	}

	void setLatime(float latime) {
		this->latime = latime;
	}
	float getLatime() {
		return latime;
	}

//Constructori si destructor
	Hartie() :idProdus(100) {
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
	Hartie(const Hartie& hartie):idProdus(hartie.idProdus) {
		nrMarciInStoc = hartie.nrMarciInStoc;
		lungime = hartie.lungime;
		latime = hartie.latime;
		if (pretProdus != NULL) {
			delete[]pretProdus;
		}
		pretProdus = new float[hartie.nrMarciInStoc];
		for (int i = 0; i < hartie.nrMarciInStoc; i++) {
			pretProdus[i] = hartie.pretProdus[i];
		}
	}
	~Hartie() {
		if (pretProdus != NULL) {
			delete[] pretProdus;
		}
	}

//Supraincarcare
	const Hartie& operator=(const Hartie& hartie) {
		nrMarciInStoc = hartie.nrMarciInStoc;
		lungime = hartie.lungime;
		latime = hartie.latime;
		if (pretProdus != NULL) {
			delete[]pretProdus;
		}
		pretProdus = new float[hartie.nrMarciInStoc];
		for (int i = 0; i < hartie.nrMarciInStoc; i++) {
			pretProdus[i] = hartie.pretProdus[i];
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Hartie& hartie) {
		out << "In " << magazin << " se afla hartie (ID:" << hartie.idProdus << ") de lungime " << hartie.lungime << " si latime " << hartie.latime << ". Avem " << hartie.nrMarciInStoc << " marci diferite la preturile de: ";
		if (hartie.nrMarciInStoc != 0) {
			for (int i = 0; i < hartie.nrMarciInStoc; i++) {
				out << hartie.pretProdus[i] << "RON ";
			}
			out << endl;
		}
		else out << "- " << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Hartie& hartie) {
		cout << "Introdu lungime hartiei: ";
		in >> hartie.lungime;
		cout << "Introdu latimea hartiei: ";
		in >> hartie.latime;
		cout << "Introdu numarul de marci in stoc: ";
		in >> hartie.nrMarciInStoc;
		if (hartie.pretProdus != NULL) {
			delete[]hartie.pretProdus;
		}
		if (hartie.nrMarciInStoc > 0){
			hartie.pretProdus = new float[hartie.nrMarciInStoc];
			cout << "Introdu preturile pentru hartie: ";
			for (int i = 0; i < hartie.nrMarciInStoc; i++) {
				in >> hartie.pretProdus[i];
			}
		}

		return in;
	}
	float& operator[](int index) {
		if (index >= 0 && index < this->nrMarciInStoc) {
			return this->pretProdus[index];
		}
	}
	Hartie& operator++() {
		for (int i = 0; i < this->nrMarciInStoc; i++) {
			this->pretProdus[i] += 1;
		}
		return *this;
	}
	friend ofstream& operator<<(ofstream& out, const Hartie& hartie) {
		out.write((char*)&hartie.lungime, sizeof(float));
		out.write((char*)&hartie.latime, sizeof(float));
		out.write((char*)&hartie.nrMarciInStoc, sizeof(int));
		if (hartie.nrMarciInStoc > 0) {
			for (int i = 0; i < hartie.nrMarciInStoc; i++) {
				out.write((char*)&hartie.pretProdus[i], sizeof(float));
			}
		}

		return out;
	}
	friend ifstream& operator>>(ifstream& in, Hartie& hartie) {
		in.read((char*)&hartie.lungime, sizeof(float));
		in.read((char*)&hartie.latime, sizeof(float));
		in.read((char*)&hartie.nrMarciInStoc, sizeof(int));
		if (hartie.pretProdus != NULL) {
			delete[] hartie.pretProdus;
		}
		if (hartie.nrMarciInStoc > 0) {
			hartie.pretProdus = new float[hartie.nrMarciInStoc];
			for (int i = 0; i < hartie.nrMarciInStoc; i++) {
				in.read((char*)&hartie.pretProdus[i], sizeof(float));
			}
		}

		return in;
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
	friend float pretMediuHartie(const Hartie& hartie);

//Virtual
	void produs() {
		cout << "Produs: Hartie" << endl;
	}
};

class Pix :public Produs, public InstrumentDeScris{
private:
	const int idProdus;
	static string magazin;
	int nrMarciInStoc;
	float* pretProdus;
	bool pixCuGel;
	string culoare;

public:
//Get-eri si Set-eri
	int getIdProdus() {
		return idProdus;
	}

	static void setMagazin(string magazin) {
		Pix::magazin = magazin;
	}
	string getMagazin() {
		return magazin;
	}

	void setNrMarciSiPret(int nrMarciInStoc, float* pretProdus) {
		if (nrMarciInStoc > 0) {
			this->nrMarciInStoc = nrMarciInStoc;
			if (this->pretProdus != NULL) {
				delete[]this->pretProdus;
			}
			this->pretProdus = new float[this->nrMarciInStoc];
			for (int i = 0; i < this->nrMarciInStoc; i++) {
				this->pretProdus[i] = pretProdus[i];
			}
		}
	}
	int getNrMarciInStoc() {
		return nrMarciInStoc;
	}

	void setPretProdus(float* pretProdus) {
		for (int i = 0; i < nrMarciInStoc; i++) {
			this->pretProdus[i] = pretProdus[i];
		}
	}
	float* getPretProdus() {
		return pretProdus;
	}

	void setPixCuGel(bool pixCuGel) {
		this->pixCuGel = pixCuGel;
	}
	bool getPixCuGel() {
		return pixCuGel;
	}

	void setCuloare(string culoare) {
		this->culoare = culoare;
	}
	string getCuloare() {
		return culoare;
	}

//Constructori si destructor
	Pix() :idProdus(200) {
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
	Pix(const Pix& pix) :idProdus(pix.idProdus) {
		nrMarciInStoc = pix.nrMarciInStoc;
		pixCuGel = pix.pixCuGel;
		culoare = pix.culoare;
		if (pretProdus != NULL) {
			delete[]pretProdus;
		}
		pretProdus = new float[pix.nrMarciInStoc];
		for (int i = 0; i < pix.nrMarciInStoc; i++) {
			pretProdus[i] = pix.pretProdus[i];
		}
	}
	~Pix() {
		if (pretProdus != NULL) {
			delete[] pretProdus;
		}
	}

//Supraincarcare
	const Pix& operator=(const Pix& pix) {
		nrMarciInStoc = pix.nrMarciInStoc;
		pixCuGel = pix.pixCuGel;
		culoare = pix.culoare;
		if (pretProdus != NULL) {
			delete[]pretProdus;
		}
		pretProdus = new float[pix.nrMarciInStoc];
		for (int i = 0; i < pix.nrMarciInStoc; i++) {
			pretProdus[i] = pix.pretProdus[i];
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Pix& pix) {
		cout << "In " << magazin << " se afla pixuri (ID:" << pix.idProdus << ") de culoarea " << pix.culoare;
		if (pix.pixCuGel) {
			cout << ", cu gel. ";
		}
		else cout << ", fara gel. ";
		cout << "Avem " << pix.nrMarciInStoc << " marci diferite la preturile de: ";
		if (pix.nrMarciInStoc != 0) {
			for (int i = 0; i < pix.nrMarciInStoc; i++) {
				cout << pix.pretProdus[i] << "RON ";
			}
			cout << endl;
		}
		else cout << "-" << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Pix& pix) {
		cout << "Este pixul cu gel? (1 = true / 0 = false): ";
		in >> pix.pixCuGel;
		cout << "Introdu culoarea: ";
		in >> pix.culoare;
		cout << "Introdu numarul de marci in stoc: ";
		in >> pix.nrMarciInStoc;
		if (pix.pretProdus != NULL) {
			delete[]pix.pretProdus;
		}
		if (pix.nrMarciInStoc > 0) {
			pix.pretProdus = new float[pix.nrMarciInStoc];
			cout << "Introdu preturile pentru pixuri: ";
			for (int i = 0; i < pix.nrMarciInStoc; i++) {
				in >> pix.pretProdus[i];
			}
		}		
		return in;
	}
	bool operator==(const Pix& pix) {
		bool ok = true;
		if (this->idProdus != pix.idProdus || this->nrMarciInStoc != pix.nrMarciInStoc || this->pixCuGel != pix.pixCuGel || this->culoare != pix.culoare) {
			ok = false;
		}
		for (int i = 0; i < this->nrMarciInStoc; i++) {
			if (this->pretProdus[i] != pix.pretProdus[i]) {
				ok = false;
			}
		}
		return ok;
	}
	Pix operator++(int) {
		Pix aux = *this;
		for (int i = 0; i < this->nrMarciInStoc; i++) {
			this->pretProdus[i]++;
		}
		return aux;
	}

//Metode care lucreaza cu fisiere txt
	void scriereInFisierTxt(string numeFisier) {
		ofstream f(numeFisier, ios::out);
		f << nrMarciInStoc << endl << pixCuGel << endl << culoare << endl;
		for (int i = 0; i < nrMarciInStoc; i++) {
			f << pretProdus[i] << " ";
		}
		f.close();
	}
	void copiereDinFisierTxt(string numeFisier) {
		ifstream f(numeFisier, ios::in);
		f >> nrMarciInStoc;
		f >> pixCuGel;
		f >> culoare;
		if (pretProdus != NULL) {
			delete[] pretProdus;
		}
		pretProdus = new float[nrMarciInStoc];
		for (int i = 0; i < nrMarciInStoc; i++) {
			f >> pretProdus[i];
		}
		f.close();
	}

//Virtual
	void produs() {
		cout << "Produs: Pix" << endl;
	}
	void instrumentScris() {
		cout << "Pixul este un instrument de scris." << endl;
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
	friend void generareFactura(const Pix& pix, int cantitateCumparata, int indexProdus);
};

class Caiet:public Produs {
private:
	const int idProdus;
	static string magazin;
	int nrMarciInStoc;
	float* pretProdus;
	int nrFile;
	string tipCaiet;
	
public:
//Get-eri si Set-eri
	int getIdProdus() {
		return idProdus;
	}

	static void setMagazin(string magazin) {
		Caiet::magazin = magazin;
	}
	string getMagazin() {
		return magazin;
	}

	void setNrMarciSiPret(int nrMarciInStoc, float* pretProdus) {
		if (nrMarciInStoc > 0) {
			this->nrMarciInStoc = nrMarciInStoc;
			if (this->pretProdus != NULL) {
				delete[]this->pretProdus;
			}
			this->pretProdus = new float[this->nrMarciInStoc];
			for (int i = 0; i < this->nrMarciInStoc; i++) {
				this->pretProdus[i] = pretProdus[i];
			}
		}
	}
	int getNrMarciInStoc() {
		return nrMarciInStoc;
	}

	void setPretProdus(float* pretProdus) {
		for (int i = 0; i < nrMarciInStoc; i++) {
			this->pretProdus[i] = pretProdus[i];
		}
	}
	float* getPretProdus() {
		return pretProdus;
	}

	void setNrFile(int nrFile) {
		this->nrFile = nrFile;
	}
	int getNrFile() {
		return nrFile;
	}

	void setTipCaiet(string tipCaiet) {
		this->tipCaiet = tipCaiet;
	}
	string getTipCaiet() {
		return tipCaiet;
	}

//Constructori si destructor
	Caiet():idProdus(300){
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
	Caiet(const Caiet& caiet):idProdus(caiet.idProdus) {
		nrMarciInStoc = caiet.nrMarciInStoc;
		nrFile = caiet.nrFile;
		tipCaiet = caiet.tipCaiet;
		if (pretProdus != NULL) {
			delete[]pretProdus;
		}
		pretProdus = new float[caiet.nrMarciInStoc];
		for (int i = 0; i < caiet.nrMarciInStoc; i++) {
			pretProdus[i] = caiet.pretProdus[i];
		}
	}
	~Caiet() {
		if (pretProdus != NULL) {
			delete[] pretProdus;
		}
	}

//Supraincarcare
	void operator=(const Caiet& caiet) {
			nrMarciInStoc = caiet.nrMarciInStoc;
			nrFile = caiet.nrFile;
			tipCaiet = caiet.tipCaiet;
			if (pretProdus != NULL) {
				delete[]pretProdus;
			}
			pretProdus = new float[caiet.nrMarciInStoc];
			for (int i = 0; i < caiet.nrMarciInStoc; i++) {
				pretProdus[i] = caiet.pretProdus[i];
			}
	}
	friend ostream& operator<<(ostream& out, const Caiet& caiet) {
		out << "In " << magazin << " se afla caiete (ID:" << caiet.idProdus << ") cu " << caiet.nrFile << " de file tip " << caiet.tipCaiet << ". Avem " << caiet.nrMarciInStoc << " marci diferite la preturile de: ";
		if (caiet.nrMarciInStoc != 0) {
			for (int i = 0; i < caiet.nrMarciInStoc; i++) {
				out << caiet.pretProdus[i] << "RON ";
			}
			out << endl;
		}
		else out << "-" << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Caiet& caiet) {
		cout << "Introdu numarul de file: ";
		in >> caiet.nrFile;
		cout << "Introdu tipul de caiet: ";
		in >> caiet.tipCaiet;
		cout << "Introdu numarul de marci in stoc: ";	
		in >> caiet.nrMarciInStoc;
		if (caiet.pretProdus != NULL) {
			delete[]caiet.pretProdus;
		}
		if (caiet.nrMarciInStoc > 0) {
			caiet.pretProdus = new float[caiet.nrMarciInStoc];
			cout << "Introdu preturile pentru caiete: ";
			for (int i = 0; i < caiet.nrMarciInStoc; i++) {
				in >> caiet.pretProdus[i];
			}
		}

		return in;
	}
	bool operator!=(const Caiet& caiet) {
		bool ok = false;
		if (this->idProdus != caiet.idProdus || this->nrMarciInStoc != caiet.nrMarciInStoc || this->nrFile != caiet.nrFile || this->tipCaiet != caiet.tipCaiet) {
			ok = true;
		}
		for (int i = 0; i < this->nrMarciInStoc; i++) {
			if (this->pretProdus[i] != caiet.pretProdus[i]) {
				ok = true;
			}
		}
		return ok;
	}
	Caiet& operator--() {
		for (int i = 0; i < this->nrMarciInStoc; i++) {
			this->pretProdus[i]--;
		}
		return *this;
	}
	friend ofstream& operator<<(ofstream& out, const Caiet& caiet) {
		out << caiet.nrFile << endl << caiet.tipCaiet << endl << caiet.nrMarciInStoc << endl;
		if (caiet.nrMarciInStoc != 0) {
			for (int i = 0; i < caiet.nrMarciInStoc; i++) {
				out << caiet.pretProdus[i] << " ";
			}
			out << endl;
		}
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Caiet& caiet) {
		in >> caiet.nrFile;
		in >> caiet.tipCaiet;
		in >> caiet.nrMarciInStoc;
		if (caiet.pretProdus != NULL) {
			delete[]caiet.pretProdus;
		}
		if (caiet.nrMarciInStoc > 0) {
			caiet.pretProdus = new float[caiet.nrMarciInStoc];
			for (int i = 0; i < caiet.nrMarciInStoc; i++) {
				in >> caiet.pretProdus[i];
			}
		}

		return in;
	}

//Virtual
	void produs() {
		cout << "Produs: Caiet" << endl;
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

class Comanda {
private:
	Hartie* produs;
	const int idComanda;
	static int numarComenzi;
	string adresaLivrare;
	int cantitate;
	bool expediat;

public:
//Get-eri si Set-eri
	int getIdComanda() {
		return idComanda;
	}

	static int getNumarComenzi() {
		return numarComenzi;
	}

	void setProdus(Hartie* produs) {
		this->produs = produs;
	}
	Hartie* getProdus() {
		return produs;
	}

	void setAdresaLivrare(string adresaLivrare) {
		this->adresaLivrare = adresaLivrare;
	}
	string getAdresaLivrare() {
		return adresaLivrare;
	}

	void setCantitate(int cantitate) {
		this->cantitate = cantitate;
	}
	int getCantitate() {
		return cantitate;
	}

	void setExpediat(bool expediat) {
		this->expediat = expediat;
	}
	bool getExpediat() {
		return expediat;
	}

//Constructori
	Comanda() : idComanda(++numarComenzi){
		if (this->produs != NULL) {
			delete this->produs;
		}
		this->produs = new Hartie();
		this->adresaLivrare = "-"; 
		this->cantitate = 0;
		this->expediat = false;
	}
	Comanda(Hartie* produs, string adresaLivrare, int cantitate, bool expediat): idComanda(++numarComenzi){
		this->produs = produs;
		this->adresaLivrare = adresaLivrare;
		this->cantitate = cantitate;
		this->expediat = expediat;
	}

//Supraincarcare
	Comanda& operator=(const Comanda& comanda) {
		produs = comanda.produs;
		adresaLivrare = comanda.adresaLivrare;
		cantitate = comanda.cantitate;
		expediat = comanda.expediat;
		return *this;
	}
	bool operator==(const Comanda& comanda) {
		return idComanda == comanda.idComanda && produs == comanda.produs && adresaLivrare == comanda.adresaLivrare && cantitate == comanda.cantitate && expediat == comanda.expediat;
	}
	Comanda& operator++() {
		expediat = true;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Comanda& comanda) {
		out << "Comanda nr. " << comanda.idComanda << " - Detalii:" << endl;
		if (comanda.produs != NULL) {
			out << "Produs comandat: Hartie " << endl;
		}
		else {
			out << "Produs comandat: - " << endl;
		}
		out << "Adresa livrare: " << comanda.adresaLivrare << endl;
		out << "Cantitate comandata: " << comanda.cantitate << endl;
		out << "Status expediere: " << (comanda.expediat ? "Expediat" : "Neexpediat") << endl << endl;
		return out;
	}

//Metode care lucreaza cu fisier binare
	void scriereInFisierBinar(string numeFisier) {
		ofstream f(numeFisier, ios::binary | ios::out);
		f << *produs;
		f.write((char*)&cantitate, sizeof(int));
		f.write((char*)&expediat, sizeof(bool));
		int lungime = adresaLivrare.length() + 1;
		f.write((char*)&lungime, sizeof(int));
		f.write((char*)adresaLivrare.c_str(), lungime);
		f.close();
	}
	void copiereDinFisierBinar(string numeFisier) {
		ifstream f(numeFisier, ios::binary | ios::in);
		f >> *produs;
		f.read((char*)&cantitate, sizeof(int));
		f.read((char*)&expediat, sizeof(bool));
		int lungimeTemp;
		f.read((char*)&lungimeTemp, sizeof(int));
		char* temp = new char[lungimeTemp];
		f.read((char*)temp, lungimeTemp);
		adresaLivrare = temp;
		f.close();
		delete[]temp;
	}

	void afisare() {
		cout << "Comanda nr. " << idComanda << " - Detalii:" << endl;
		if (produs != NULL) {
			cout << "Produs comandat: Hartie " << endl;
		}
		else {
			cout << "Produs comandat: - " << endl;
		}
		cout << "Adresa livrare: " << adresaLivrare << endl;
		cout << "Cantitate comandata: " << cantitate << endl;
		cout << "Status expediere: " << (expediat ? "Expediat" : "Neexpediat") << endl << endl;
	}
};

class HartieCreponata :public Hartie{
private:
	int densitate;
	string culoare;

public:
//Get-eri si Set-eri
	void setDensitate(int densitate) {
		this->densitate = densitate;
	}
	int getDensitate() {
		return densitate;
	}

	void setCuloare(string culoare) {
		this->culoare = culoare;
	}
	string getCuloare() {
		return culoare;
	}


//Constructori
	HartieCreponata() :Hartie(110) {
		densitate = 0;
		culoare = "necunoscuta";
	}
	HartieCreponata(int densitate, string culoare) :Hartie(110, 0, NULL, 29.7, 21) {
		this->densitate = densitate;
		this->culoare = culoare;
	}
	HartieCreponata(int densitate, string culoare, int idProdus, int nrMarciInStoc, float* pretProdus, float lungime, float latime) : Hartie(idProdus, nrMarciInStoc, pretProdus, lungime, latime) {
		this->densitate = densitate;
		this->culoare = culoare;
	}
	HartieCreponata(const HartieCreponata& hartieCreponata) : Hartie(hartieCreponata) {
		this->densitate = hartieCreponata.densitate;
		this->culoare = hartieCreponata.culoare;
	}

	//Supraincarcare operatori
	friend ostream& operator<<(ostream& out, const HartieCreponata& hartieCreponata) {
		out << "In " << magazin << " se afla hartie creponata (ID:" << hartieCreponata.idProdus << ") de lungime " << hartieCreponata.lungime << " si latime " << hartieCreponata.latime << ". Poti gasi hartie creponata cu densitatea de " << hartieCreponata.densitate << " g/m^2 de culoarea " << hartieCreponata.culoare << ". Avem " << hartieCreponata.nrMarciInStoc << " marci diferite la preturile de : ";
		if (hartieCreponata.nrMarciInStoc != 0) {
			for (int i = 0; i < hartieCreponata.nrMarciInStoc; i++) {
				out << hartieCreponata.pretProdus[i] << "RON ";
			}
			out << endl;
		}
		else out << "- " << endl;
		return out;
	}
	friend istream& operator>>(istream& in, HartieCreponata& hartieCreponata) {
		cout << "Introdu lungime hartiei creponate: ";
		in >> hartieCreponata.lungime;
		cout << "Introdu latimea hartiei creponate: ";
		in >> hartieCreponata.latime;
		cout << "Introdu densitatea hartiei creponate: ";
		in >> hartieCreponata.densitate;
		cout << "Introdu culoarea hartiei creponate: ";
		in >> hartieCreponata.culoare;
		cout << "Introdu numarul de marci in stoc: ";
		in >> hartieCreponata.nrMarciInStoc;
		if (hartieCreponata.pretProdus != NULL) {
			delete[]hartieCreponata.pretProdus;
		}
		if (hartieCreponata.nrMarciInStoc > 0) {
			hartieCreponata.pretProdus = new float[hartieCreponata.nrMarciInStoc];
			cout << "Introdu preturile pentru hartia creponata: ";
			for (int i = 0; i < hartieCreponata.nrMarciInStoc; i++) {
				in >> hartieCreponata.pretProdus[i];
			}
		}
		return in;
	}
};

class HartieGlasata :public Hartie {
private:
	int nrColiPerTop;
	string culoare;

public:
//Get-eri si Set-eri
	void setNrColiPerTop(int nrColiPerTop) {
		this->nrColiPerTop = nrColiPerTop;
	}
	int getNrColiPerTop() {
		return nrColiPerTop;
	}

	void setCuloare(string culoare) {
		this->culoare = culoare;
	}
	string getCuloare() {
		return culoare;
	}


//Constructori
	HartieGlasata() :Hartie(120) {
		nrColiPerTop = 0;
		culoare = "necunoscuta";
	}
	HartieGlasata(int nrColiPerTop, string culoare) :Hartie(120, 0, NULL, 29.7, 21) {
		this->nrColiPerTop = nrColiPerTop;
		this->culoare = culoare;
	}
	HartieGlasata(int nrColiPerTop, string culoare, int idProdus, int nrMarciInStoc, float* pretProdus, float lungime, float latime) : Hartie(idProdus, nrMarciInStoc, pretProdus, lungime, latime) {
		this->nrColiPerTop = nrColiPerTop;
		this->culoare = culoare;
	}
	HartieGlasata(const HartieGlasata& hartieGlasata) : Hartie(hartieGlasata) {
		this->nrColiPerTop = hartieGlasata.nrColiPerTop;
		this->culoare = hartieGlasata.culoare;
	}

//Supraincarcare operatori
	friend ostream& operator<<(ostream& out, const HartieGlasata& hartieGlasata) {
		out << "In " << magazin << " se afla hartie glasata (ID:" << hartieGlasata.idProdus << ") de lungime " << hartieGlasata.lungime << " si latime " << hartieGlasata.latime << ". Poti gasi topuri cu " << hartieGlasata.nrColiPerTop << " de coli de culoarea " << hartieGlasata.culoare << ". Avem " << hartieGlasata.nrMarciInStoc << " marci diferite la preturile de : ";
		if (hartieGlasata.nrMarciInStoc != 0) {
			for (int i = 0; i < hartieGlasata.nrMarciInStoc; i++) {
				out << hartieGlasata.pretProdus[i] << "RON ";
			}
			out << endl;
		}
		else out << "- " << endl;
		return out;
	}
	friend istream& operator>>(istream& in, HartieGlasata& hartieGlasata) {
		cout << "Introdu lungime hartiei glasante: ";
		in >> hartieGlasata.lungime;
		cout << "Introdu latimea hartiei glasante: ";
		in >> hartieGlasata.latime;
		cout << "Introdu numarul de coli per top: ";
		in >> hartieGlasata.nrColiPerTop;
		cout << "Introdu culoarea hartiei glasante: ";
		in >> hartieGlasata.culoare;
		cout << "Introdu numarul de marci in stoc: ";
		in >> hartieGlasata.nrMarciInStoc;
		if (hartieGlasata.pretProdus != NULL) {
			delete[]hartieGlasata.pretProdus;
		}
		if (hartieGlasata.nrMarciInStoc > 0) {
			hartieGlasata.pretProdus = new float[hartieGlasata.nrMarciInStoc];
			cout << "Introdu preturile pentru hartia glasanta: ";
			for (int i = 0; i < hartieGlasata.nrMarciInStoc; i++) {
				in >> hartieGlasata.pretProdus[i];
			}
		}
		return in;
	}
};

float pretMediuHartie(const Hartie& hartie) {
	if (hartie.nrMarciInStoc > 0) {
		float suma = 0;
		for (int i = 0; i < hartie.nrMarciInStoc; i++) {
			suma += hartie.pretProdus[i];
		}
		return (suma / hartie.nrMarciInStoc);
	}
	else return 0;
}

void generareFactura(const Pix& pix, int cantitateCumparata, int indexProdus) {
	if (cantitateCumparata > 0 && indexProdus > 0 && indexProdus < pix.nrMarciInStoc) {
		float total = pix.pretProdus[indexProdus] * cantitateCumparata;
		string pixuri = (cantitateCumparata == 1) ? " pix " : " pixuri ";
		cout << "Factura:" << endl << "Ati achizitionat " << cantitateCumparata << pixuri << "la pret de " << pix.pretProdus[indexProdus] << "RON. " << "Totalul este de: " << total << "RON." << endl;
	}
}

string Hartie::magazin = "Papetarie S.R.L.";
string Pix::magazin = "Papetarie S.R.L.";
string Caiet::magazin = "Papetarie S.R.L.";
int Comanda::numarComenzi = 0;

void main() {
//HARTIE - Initializarea obiectelor
	float* pretHartie = new float[3] {13.99, 14.99, 19.99};
	Hartie hartie1;
	Hartie hartie2(100);
	Hartie hartie3(100, 3, pretHartie, 29.7, 21);
	Hartie hartie4(hartie2);
//Afisare
	hartie1.afisare();
	hartie2.afisare();
	hartie3.afisare();
	hartie3.setMagazin("magazinul Papetarie S.R.L.");
	hartie3.afisare();
	hartie4.afisare();
//Set-eri
	hartie4.setNrMarciSiPret(3, pretHartie);
	hartie4.setPretProdus(pretHartie);
	hartie4.setLungime(29.7);
	hartie4.setLatime(21);
//Get-eri
	cout << "Get-er ID: " << hartie4.getIdProdus() << endl;
	cout << "Get-er magazin: " << hartie4.getMagazin() << endl;
	cout << "Get-er numar marci in stoc: " << hartie4.getNrMarciInStoc() << endl;
	cout << "Get-er preturi produs: ";
	for (int i = 0; i < hartie4.getNrMarciInStoc(); i++) {
		cout << hartie4.getPretProdus()[i] << " ";
	}
	cout << endl;
	cout << "Get-er lungime: " << hartie4.getLungime() << endl;
	cout << "Get-er latime: " << hartie4.getLatime() << endl;
//Functie globala friend
	cout << "Pretul mediu pentru hartie este de: " << pretMediuHartie(hartie4) << "RON" << endl;
//Utilizare operatori
	hartie1 = hartie4;
	cout << hartie1;
	cout << "Pretul pentru acest produs este de " << hartie1[2] << "RON." << endl;
	cout << "Pretul pentru acest produs este de " << ++hartie1[2] << "RON." << endl;
	cout << endl;
//Vector hartie
	Hartie* pHartie = new Hartie[2];
	for (int i = 0; i < 2; i++) {
		cout << "Hartie " << i + 1 << ": " << endl;
		cin >> pHartie[i];
		cout << endl;
	}
	for (int i = 0; i < 2; i++){
		cout << pHartie[i];
	}
//Matrice
	cout << endl << "Matrice: " << endl;
	int n = 3;
	Hartie** ppHartie = new Hartie* [n];
	for (int i = 0; i < n; i++) {
		ppHartie[i] = new Hartie[2];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			cout <<	ppHartie[i][j];
		}
	}
	cout << endl;
//Fisier binar
	ofstream binHartie("Hartie.bin", ios::binary | ios::out);
	binHartie << hartie3;
	binHartie.close();
	ifstream copiereBinarHartie("Hartie.bin", ios::binary | ios::in);
	Hartie hartieFisier;
	copiereBinarHartie >> hartieFisier;
	cout << "Copiat din fisier:" << endl << hartieFisier << endl << endl;
	copiereBinarHartie.close();


//PIX - Initializarea obiectelor
	float* pretPix = new float[4] {2.99, 3.50, 4.99, 8.00};
	Pix pix1;
	Pix pix2(200);
	Pix pix3(200, 4, pretPix, true, "negru");
	Pix pix4(pix2);
//Afisare
	pix1.afisare();
	pix2.afisare();
	pix3.afisare();
	pix3.setMagazin("magazinul Papetarie S.R.L.");
	pix3.afisare();
	pix4.afisare();
//Set-eri
	pix4.setNrMarciSiPret(4, pretPix);
	pix4.setPretProdus(pretPix);
	pix4.setPixCuGel(true);
	pix4.setCuloare("negru");
//Get-eri
	cout << "Get-er ID: " << pix4.getIdProdus() << endl;
	cout << "Get-er magazin: " << pix4.getMagazin() << endl;
	cout << "Get-er numar marci in stoc: " << pix4.getNrMarciInStoc() << endl;
	cout << "Get-er preturi produs: ";
	for (int i = 0; i < pix4.getNrMarciInStoc(); i++) {
		cout << pix4.getPretProdus()[i] << " ";
	}
	cout << endl;
	cout << "Get-er pix cu gel: ";
	if (pix4.getPixCuGel()) {
		cout << "Pix cu gel" << endl;
	}
	else cout << "Pix fara gel" << endl;
	cout << "Get-er culoare: " << pix4.getCuloare() << endl;
//Functie globala friend
	generareFactura(pix4, 5, 2);
//Utilizare operatori
	pix1 = pix4;
	cout << pix1++;
	cout << pix1;
	if (pix1 == pix4) {
		cout << "Obiectele sunt la fel." << endl;
	}
	else cout << "Obiectele difera." << endl;
	cout << endl;
//Vector pix
	Pix* pPix = new Pix[2];
	for (int i = 0; i < 2; i++) {
		cout << "Pix " << i + 1 << ": " << endl;
		cin >> pPix[i];
		cout << endl;
	}
	for (int i = 0; i < 2; i++){
		cout << pPix[i];
	}
	cout << endl;
//Fisier text
	pix3.scriereInFisierTxt("Pix.txt");
	Pix pixFisier;
	pixFisier.copiereDinFisierTxt("Pix.txt");
	cout << "Copiat din fisier: " << endl << pixFisier << endl << endl;

//CAIET - Initializarea obiectelor
	float* pretCaiet = new float[2] {9.99, 17.50};
	Caiet caiet1;
	Caiet caiet2(300);
	Caiet caiet3(300, 2, pretCaiet, 80, "velin");
	Caiet caiet4(caiet2);
//Afisare
	caiet1.afisare();
	caiet2.afisare();
	caiet3.afisare();
	caiet3.setMagazin("magazinul Papetarie S.R.L.");
	caiet3.afisare();
	caiet4.afisare();
//Set-eri
	caiet4.setNrMarciSiPret(2, pretCaiet);
	caiet4.setPretProdus(pretCaiet);
	caiet4.setNrFile(80);
	caiet4.setTipCaiet("velin");
//Get-eri
	cout << "Get-er ID: " << caiet4.getIdProdus() << endl;
	cout << "Get-er magazin: " << caiet4.getMagazin() << endl;
	cout << "Get-er numar marci in stoc: " << caiet4.getNrMarciInStoc() << endl;
	cout << "Get-er preturi produs: ";
	for (int i = 0; i < caiet4.getNrMarciInStoc(); i++) {
		cout << caiet4.getPretProdus()[i] << " ";
	}
	cout << endl;
	cout << "Get-er numar file: " << caiet4.getNrFile() << endl;
	cout << "Get-er tip caiet: " << caiet4.getTipCaiet() << endl;
//Utilizare operatori
	caiet1 = caiet4;
	cout << caiet1;
	cout << --caiet1;
	if (caiet1 != caiet4) {
		cout << "Obiectele difera." << endl;
	}
	else cout << "Obiectele sunt la fel." << endl;
	cout << endl;
//Vector caiet
	Caiet* pCaiet = new Caiet[2];
	for (int i = 0; i < 2; i++) {
		cout << "Caiet " << i + 1 << ": " << endl;
		cin >> pCaiet[i];
		cout << endl;
	}
	for (int i = 0; i < 2; i++){
		cout << pCaiet[i];
	}
	cout << endl;
//Fisier txt
	ofstream txtCaiet("Caiet.txt", ios::out);
	txtCaiet << caiet3;
	txtCaiet.close();
	ifstream copiereTxtCaiet("Caiet.txt", ios::in);
	Caiet caietFisier;
	copiereTxtCaiet >> caietFisier;
	copiereTxtCaiet.close();
	cout << "Copiat din fisier: " << endl << caietFisier << endl << endl;

//COMANDA - Initializarea obiectelor
	Comanda comanda1;
	Comanda comanda2(&hartie2, "Sos. Pantelimon nr.139", 30, false);
//Afisare
	comanda1.afisare();
	comanda2.afisare();
//Set-eri
	comanda1.setAdresaLivrare("Sos. Iancului nr.58");
	comanda1.setCantitate(23);
	comanda1.setExpediat(true);
	comanda1.setProdus(&hartie3);
//Get-eri
	cout << "Get-er adresa livrare: " << comanda1.getAdresaLivrare() << endl;
	cout << "Get-er cantitate: " << comanda1.getCantitate() << endl;
	cout << "Get-er status expediere: ";
	if (comanda1.getExpediat()) {
		cout << "Produs expediat. " << endl;
	}
	else {
		cout << "Produsul nu a fost expediat. " << endl;
	}
	cout << "Get-er produs: " << *(comanda1.getProdus()) << endl;
//Utilizare operatori
	Comanda comanda3 = comanda2;
	comanda3.afisare();
	if (comanda3 == comanda2) {
		cout << "Aceeasi comanda. " << endl;
	}
	else {
		cout << "Comenzile sunt diferite" << endl;
	}
	(++comanda2).afisare();
//Fisier binar
	comanda1.scriereInFisierBinar("Comanda.bin");
	Comanda comandaFisier;
	comandaFisier.copiereDinFisierBinar("Comanda.bin");
	cout << endl << "Copiat din fisier: " << endl << comandaFisier << endl << endl;
	

//MOSTENIRE
//HARTIE CREPONATA - Initializarea obiectelor
	HartieCreponata hartieCreponata1;
	HartieCreponata hartieCreponata2(40, "rosie");
	HartieCreponata hartieCreponata3(40, "albastra", 110, 3, pretHartie, 40, 20);
	HartieCreponata hartieCreponata4(hartieCreponata3);
//Afisare
	cout << hartieCreponata1;
	cout << hartieCreponata2;
	cout << hartieCreponata3;
	cout << hartieCreponata4 << endl;
//Set-eri
	hartieCreponata1.setDensitate(40);
	hartieCreponata1.setCuloare("verde");
//Get-eri
	cout << "Densitatea hartiei creponate: " << hartieCreponata1.getDensitate() << endl;
	cout << "Culoarea hartiei creponate: " << hartieCreponata1.getCuloare() << endl << endl;
//Citire de la tastatura
	cin >> hartieCreponata1;
	cout << hartieCreponata1 << endl;

//HARTIE GLASATA - Initializarea obiectelor
	HartieGlasata hartieGlasata1;
	HartieGlasata hartieGlasata2(100, "rosie");
	HartieGlasata hartieGlasata3(100, "albastra", 120, 3, pretHartie, 29.7, 21);
	HartieGlasata hartieGlasata4(hartieGlasata3);
//Afisare
	cout << hartieGlasata1;
	cout << hartieGlasata2;
	cout << hartieGlasata3;
	cout << hartieGlasata4 << endl;
//Set-eri
	hartieGlasata1.setNrColiPerTop(100);
	hartieGlasata1.setCuloare("verde");
//Get-eri
	cout << "Densitatea hartiei glasate: " << hartieGlasata1.getNrColiPerTop() << endl;
	cout << "Culoarea hartiei glasate: " << hartieGlasata1.getCuloare() << endl << endl;
//Citire de la tastatura
	cin >> hartieGlasata1;
	cout << hartieGlasata1 << endl;

//Vectori pentru late-binding
	Produs** produse = new Produs * [5];
	produse[0] = new Hartie();
	produse[1] = new Pix();
	produse[2] = new Hartie();
	produse[3] = new Caiet();
	produse[4] = new Caiet();
	for (int i = 0; i < 5; i++) {
		produse[i]->produs();
	}
	InstrumentDeScris** instrument = new InstrumentDeScris * [5];
	instrument[0] = new Pix();
	instrument[1] = new Pix();
	instrument[2] = new Pix();
	instrument[3] = new Pix();
	instrument[4] = new Pix();
	for (int i = 0; i < 5; i++) {
		instrument[i]->instrumentScris();
	}

//Dezalocare
	delete[]pretHartie;
	delete[]pretPix;
	delete[]pretCaiet;
	delete[]pHartie;
	delete[]pPix;
	delete[]pCaiet;
	for (int i = 0; i < 2; i++){
		delete[] ppHartie[i];
	}
	delete[]ppHartie;
	for (int i = 0; i < 5; i++) {
		delete produse[i];
	}
	delete[]produse;
}
