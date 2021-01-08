#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Produs {
	const int idProdus;
	static int contor;
protected:
	char* numeProdus;
	float pret;
	double cantitateDisponibila;
	string descriere;
	int nrCautariProdusInUltimele24h;
public:

	//constructor default
	Produs() :idProdus(1) {
		this->numeProdus = new char[strlen("Necunoscut") + 1];
		strcpy(this->numeProdus, "Necunoscut");
		this->pret = 0;
		this->cantitateDisponibila = 0;
		this->descriere = "Nu cunoastem acest produs.Este prea nou...";
		this->nrCautariProdusInUltimele24h = 0;

	}
	//constructor cu toti parametrii
	Produs(const char* numeProdus, float pret, double cantitateDisponibila, string descriere, int nrCautariProdusInUltimele24h) :idProdus(contor++) {
		if (numeProdus != nullptr && strlen(numeProdus) > 2) {
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);

		}
		if (pret > 1) {
			this->pret = pret;
		}
		if (cantitateDisponibila > 0) {
			this->cantitateDisponibila = cantitateDisponibila;

		}
		if (descriere.length() > 6) {
			this->descriere = descriere;
		}


		if (nrCautariProdusInUltimele24h >= 0) {
			this->nrCautariProdusInUltimele24h = nrCautariProdusInUltimele24h;

		}

	}//constructor de copiere
	Produs(const Produs& p) :idProdus(p.idProdus) {
		this->numeProdus = new char[strlen(p.numeProdus) + 1];
		strcpy(this->numeProdus, p.numeProdus);
		this->pret = p.pret;
		this->cantitateDisponibila = p.cantitateDisponibila;
		this->descriere = p.descriere;
		this->nrCautariProdusInUltimele24h = p.nrCautariProdusInUltimele24h;
	}
	//destructor
	~Produs() {
		if (this->numeProdus != nullptr) {
			delete[]this->numeProdus;
		}
	}
	//operator =
	Produs& operator =(const Produs& p) {
		if (this != &p) {
			delete[]this->numeProdus;
			this->numeProdus = new char[strlen(p.numeProdus) + 1];
			strcpy(this->numeProdus, p.numeProdus);
			this->pret = p.pret;
			this->cantitateDisponibila = p.cantitateDisponibila;
			this->descriere = p.descriere;
			this->nrCautariProdusInUltimele24h = p.nrCautariProdusInUltimele24h;
		}
		else {
			throw new exception("nu este persima auto asignarea");
		}
		return *this;
	}

	//setteri si getteri pentru atribute
	int getIdProdus() {
		return this->idProdus;
	}
	char* getNumeProdus() {
		return this->numeProdus;
	}
	void setNumeProdus(const char* numeNou) {
		if (numeNou != nullptr && strlen(numeNou) > 2) {
			delete[]this->numeProdus;
			this->numeProdus = new char[strlen(numeNou) + 1];
			strcpy(this->numeProdus, numeNou);
		}
	}
	float getPret() {
		return this->pret;
	}
	void setPret(float pretNou) {
		if (pretNou > 1) {
			this->pret = pret;
		}
	}
	double getCantitateDisponibila() {
		return this->cantitateDisponibila;
	}
	void setCantitateDisponibila(double cantitateNoua) {
		if (cantitateNoua > 0) {
			this->cantitateDisponibila = cantitateNoua;
		}

	}
	string getDescriere() {
		return this->descriere;
	}
	void setDescriere(string descriereNoua) {
		if (descriereNoua.length() > 6) {
			this->descriere = descriereNoua;
		}
	}
	int getNrCautari() {
		return this->nrCautariProdusInUltimele24h;
	}
	void setNrCautari(int nrCautariNoi) {
		if (nrCautariNoi >= 0) {
			this->nrCautariProdusInUltimele24h = nrCautariNoi;
		}
	}



	friend ostream& operator <<(ostream& out, Produs& produs);

	//operator + pentru a scumpi un produs
	float operator +(float valoare) {
		return this->pret + valoare;
	}

	//operator - pentru a scadea pretul unui produs
	float operator -(float valoare) {
		return this->pret - valoare;
	}

	//operator cast pentru a returna numarul de cautari a produsului 
	operator int() {
		return this->nrCautariProdusInUltimele24h;
	}
	//scriere in fisier binar a produselor.M-am gandit ca ne va trebui oricum mai incolo cand vom stoca produsele magazinului
	void salvareInFisierBinar(ofstream& fisierBinar) {
		int dimensiuneNumeProdus = strlen(numeProdus) + 1;
		fisierBinar.write((char*)&dimensiuneNumeProdus, sizeof(int));
		fisierBinar.write(numeProdus, sizeof(char) * dimensiuneNumeProdus);
		fisierBinar.write((char*)&pret, sizeof(float));
		fisierBinar.write((char*)&cantitateDisponibila, sizeof(double));
		int dimensiuneDescriere = descriere.length() + 1;
		fisierBinar.write((char*)&dimensiuneDescriere, sizeof(int));
		fisierBinar.write(descriere.c_str(), sizeof(string) * dimensiuneDescriere);
		fisierBinar.write((char*)&nrCautariProdusInUltimele24h, sizeof(int));


	}
	void citireDinFisierBinar(ifstream& fisierBinar) {
		delete this->numeProdus;
		int dimensiuneNumeProdus;
		char aux[100];
		fisierBinar.read((char*)&dimensiuneNumeProdus, sizeof(int));
		fisierBinar.read(aux, sizeof(char) * dimensiuneNumeProdus);
		this->numeProdus = new char[strlen(aux) + 1];
		strcpy(this->numeProdus, aux);
		fisierBinar.read((char*)&pret, sizeof(float));
		fisierBinar.read((char*)&cantitateDisponibila, sizeof(double));
		int dimensiuneDescriere;
		fisierBinar.read((char*)&dimensiuneDescriere, sizeof(int));
		char auxiliar[100];
		fisierBinar.read(auxiliar, dimensiuneDescriere * sizeof(char));
		this->descriere = string(auxiliar);
		fisierBinar.read((char*)&nrCautariProdusInUltimele24h, sizeof(int));
	}

};
class TelefonMobil :Produs {
	string producator;
	float diagonala;
	double memorieStocare;
	int memorieRam;
public:
	//constructor default 
	TelefonMobil() :Produs() {
		this->producator = "Samsung";
		this->diagonala = 10;
		this->memorieStocare = 64;
		this->memorieRam = 8;
	}
	TelefonMobil(const char* numeProdus, float pret, double cantitateDisponibila, string descriere, int nrCautariProdusInUltimele24h
		, string producator, float diagonala, double memorieStocare, int memorieRam) :Produs(numeProdus, pret, cantitateDisponibila, descriere, nrCautariProdusInUltimele24h) {
		if (producator.empty()) {
			throw new exception("campul nu poate fi gol");
		}
		else {
			this->producator = producator;
		}
		if (diagonala > 5) {
			this->diagonala = diagonala;
		}
		if (memorieStocare > 8) {
			this->memorieStocare = memorieStocare;
		}
		if (memorieRam > 2) {
			this->memorieRam = memorieRam;
		}
	}


};
class Client {

	string nume;
	string prenume;
	string adresa;
	string email;
public:
	Client() {
		this->nume = "Tzanca";
		this->prenume = "Uraganu";
		this->adresa = "Ferentari,aleea livezilor";
		this->email = "tzancabomdardierul@manele.ro";
	}
	//am facut constructor doar cu nume si prenume pentru atunci cand intram prima oara in magazin 
	Client(string nume, string prenume) {
		if (nume.length() > 3) {
			this->nume = nume;
		}
		if (prenume.length() > 3) {
			this->prenume = prenume;
		}
	}
	Client(string nume, string prenume, string adresa, string email) {
		if (nume.length() > 3) {
			this->nume = nume;
		}
		if (prenume.length() > 3) {
			this->prenume = prenume;
		}
		if (adresa.length() > 10) {
			this->adresa = adresa;
		}
		else {
			throw new exception("adresa invalida");
		}
		if (email.length() > 5 && email.find("@")!=string::npos && (email.find(".com") != string::npos || email.find(".ro") != string::npos) ){
			this->email=email;
		}
		else {
			throw new exception("formatul emailului nu este valid");
		}
		
	}
	//constructor de copiere
	Client(const Client& c) {
		this->nume = c.nume;
		this->prenume = c.prenume;
		this->adresa = c.adresa;
		this->email = c.email;

	}
	//operatorul =
	Client& operator=(const Client& c) {
		if (this != &c) {
			this->nume = c.nume;
			this->prenume = c.prenume;
			this->adresa = c.adresa;
			this->email = c.email;
		}
		return *this;
	}
	string getNume() {
		return this->nume;
	}
	void setNume(string numeNou) {
		if (numeNou.length() > 3) {
			this->nume = numeNou;
		}
	}
	string getPrenume() {
		return this->prenume;
	}
	void setPrenume(string prenumeNou) {
		if (prenumeNou.length() > 3) {
			this->prenume = prenumeNou;
		}

	}
	string getAdresa() {
		return this->adresa;
	}
	void setAdresa(string adresaNoua) {
		if (adresaNoua.length() > 10) {
			this->adresa = adresaNoua;
		}
	}
	string getEmail() {
		return this->email;
	}
	void setEmail(string emailNou) {
		if (emailNou.length() > 5 && emailNou.find("@") != string::npos && (emailNou.find(".com") != string::npos || emailNou.find(".ro") != string::npos)) {
			this->email = emailNou;
		}
	}
	
	void afisareClient() {
		cout << "nume client: " << nume << " ,prenume client: " << prenume << ",adresa: " << adresa << ", adresa de email: " << email << endl;


	}
	friend ofstream& operator <<(ofstream& fisierBinar,Client&c) {
		int dimensiuneNume = c.nume.length() + 1;
		fisierBinar.write((char*)&dimensiuneNume, sizeof(int));
		fisierBinar.write(c.nume.c_str(), sizeof(string) * dimensiuneNume);
		int dimensiunePrenume = c.prenume.length() + 1;
		fisierBinar.write((char*)&dimensiunePrenume, sizeof(int));
		fisierBinar.write(c.prenume.c_str(), sizeof(string) * dimensiunePrenume);
		int dimensiuneAdresa = c.adresa.length() + 1;
		fisierBinar.write((char*)&dimensiuneAdresa, sizeof(int));
		fisierBinar.write(c.adresa.c_str(), sizeof(string) * dimensiuneAdresa);
		int dimensiuneEmail = c.email.length() + 1;
		fisierBinar.write((char*)&dimensiuneEmail, sizeof(int));
		fisierBinar.write(c.email.c_str(), sizeof(string) * dimensiuneEmail);

	
	}
	friend istream& operator>>(ifstream& fisierBinar, Client& c) {
		int dimensiuneNume, dimensiunePrenume, dimensiuneAdresa, dimensiuneEmail;
		fisierBinar.read((char*)&dimensiuneNume, sizeof(int));
		char aux1[100];
		fisierBinar.read(aux1, sizeof(char) * dimensiuneNume);
		c.nume = (string)aux1;
		fisierBinar.read((char*)&dimensiunePrenume, sizeof(int));
		char aux2[100];
		fisierBinar.read(aux2, sizeof(char) * dimensiunePrenume);
		c.prenume = (string)aux2;
		fisierBinar.read((char*)&dimensiuneAdresa, sizeof(int));
		char aux3[100];
		fisierBinar.read(aux3, sizeof(char) * dimensiuneAdresa);
		c.adresa = (string)aux3;
		fisierBinar.read((char*)&dimensiuneEmail, sizeof(int));
		char aux4[100];
		fisierBinar.read(aux4, sizeof(char) * dimensiuneEmail);
		c.email = (string)aux4;
	}

};

int Produs::contor = 1;
ostream& operator <<(ostream& out, Produs& produs) {
	out << "nume produs: " << produs.numeProdus << endl
		<< "pret: " << produs.pret << " lei" << endl
		<< "cantitate disponibila: " << produs.cantitateDisponibila << endl
		<< "descriere: " << produs.descriere << endl
		<< "nr cautari in ultimele 24 ore: " << produs.nrCautariProdusInUltimele24h << " ori." << endl;
	return out;

}








void main() {
	Produs p1("pasta de dinti", 10, 100, "este foarte mentolata", 100);
	cout << p1;
	cout << "-------------" << endl;
	Produs p2;
	ofstream fisier("fisier.dat", ios::binary | ios::out);
	if (fisier.is_open()) {
		p1.salvareInFisierBinar(fisier);
		fisier.close();

	}
	else {
		cout << "fisierul nu a putut fi deschis" << endl;
	}

	ifstream fisierIntrare("fisier.dat", ios::binary | ios::in);
	if (fisierIntrare.is_open()) {
		p2.citireDinFisierBinar(fisierIntrare);
		fisierIntrare.close();

	}
	else {
		cout << "fisieurl nu a putut fi deschis" << endl;
	}
	cout << p2;
	Client c1("preda", "sorin", "aleea salaj nr.10", "sorinpreda045@gmail.com");
	
	
}
