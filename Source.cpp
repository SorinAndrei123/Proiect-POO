#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
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
	//citire de la tastatura produs
	friend istream& operator >>(istream& in, Produs& produs) {
		delete[]produs.numeProdus;
		char aux[100];
		cout << "Nume produs: "; in >> aux; cout << endl;
		produs.numeProdus = new char[strlen(aux) + 1];
		strcpy(produs.numeProdus, aux);
		cout << "Pret: "; in >> produs.pret; cout << endl;
		cout << "Cantitate disponibila in magazin: "; cin >> produs.cantitateDisponibila; cout << endl;
		cout << "Descriere: ";
		in.ignore();
		getline(in, produs.descriere); cout << endl;
		cout << "Nr cautari produs in ultimele 24h: "; cin >> produs.nrCautariProdusInUltimele24h; cout << endl;
		return in;


	}

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
	//citire din fisier binar a produselor
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
	//scriere in fisier text a produselor
	void scriereInFisierText(ofstream& fisierText) {
		fisierText << numeProdus << endl
			<< pret << endl << cantitateDisponibila << endl
			<< descriere << endl << nrCautariProdusInUltimele24h << endl;

	}
	//citire din fisier text a produselor
	void citireDinFisierText(ifstream& fisierText) {
		if (numeProdus != nullptr) {
			delete[]this->numeProdus;
		}
		char aux[100];
		fisierText.getline(aux, 100);
		numeProdus = new char[strlen(aux) + 1];
		strcpy(numeProdus, aux);
		fisierText >> pret;
		fisierText.ignore();
		fisierText >> cantitateDisponibila;
		fisierText.ignore();
		getline(fisierText, descriere);
		fisierText >> nrCautariProdusInUltimele24h;
	

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
	//scriere client in fisier binar
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
	//citire client in fisier binar
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
	//scriere client in fisier txt
	void scriereInFisierText(ofstream& fisierText) {
		fisierText << nume << endl << prenume << endl << adresa << email << endl;
	}
	//citire client din fisier text
	void citireDinFisierText(ifstream& fisietText) {
		getline(fisietText, nume);
		getline(fisietText, prenume);
		getline(fisietText, adresa);
		getline(fisietText, email);
	}

};
//clasa cos de cumparaturi,mostenire de tip has a client si un vector de produse
class CosDeCumparaturi  {
protected:
	Client client;
	Produs* produse;
	int nrProduseInCos;
	//am luat acest vector pentru a sti din fiecare produs din cos cate bucati a comandat
	int* nrProduseComandateDinFiecareTip;
public:
	//constructor default 
	CosDeCumparaturi() {
		this->nrProduseInCos = 0;
	}
	//constructor cu parametrii
	CosDeCumparaturi(Client client, int nrProduseInCos, Produs* produse,int* nrProduseComandateDinFiecareTip) {
		this->client = client;
		if (nrProduseInCos > 0) {
			this->nrProduseInCos = nrProduseInCos;
		}
			this->produse = new Produs[nrProduseInCos];
			for (int i = 0; i < nrProduseInCos; i++) {
				this->produse[i] = produse[i];
			}
			if (nrProduseComandateDinFiecareTip != nullptr) {
				this->nrProduseComandateDinFiecareTip = new int[nrProduseInCos];
				for (int i = 0; i < nrProduseInCos; i++) {
					this->nrProduseComandateDinFiecareTip[i] = nrProduseComandateDinFiecareTip[i];
				}
			}
		
	}
	//constructor de copiere
	CosDeCumparaturi(const CosDeCumparaturi& c) {
		this->client = c.client;
		this->nrProduseInCos = c.nrProduseInCos;
		this->produse = new Produs[c.nrProduseInCos];
		for (int i = 0; i < c.nrProduseInCos; i++) {
			this->produse[i] = c.produse[i];
		}
		this->nrProduseComandateDinFiecareTip = new int[c.nrProduseInCos];
		for (int i = 0; i < c.nrProduseInCos; i++) {
			this->nrProduseComandateDinFiecareTip[i] = c.nrProduseComandateDinFiecareTip[i];
		}

		

	}
	//destructor
	~CosDeCumparaturi() {
		if (this->produse != nullptr) {
			delete[]this->produse;
		}
		if (this->nrProduseComandateDinFiecareTip != nullptr) {
			delete[]this->nrProduseComandateDinFiecareTip;
		}
	}
	//supraincarcare operator =
	CosDeCumparaturi& operator =(const CosDeCumparaturi& c) {
		if (this != &c) {
			delete[]this->produse;
			delete[]this->nrProduseComandateDinFiecareTip;
			this->client = c.client;
			this->nrProduseInCos = c.nrProduseInCos;
			this->produse = new Produs[c.nrProduseInCos];
			for (int i = 0; i < c.nrProduseInCos; i++) {
				this->produse[i] = c.produse[i];
			}
			this->nrProduseComandateDinFiecareTip = new int[c.nrProduseInCos];
			for (int i = 0; i < c.nrProduseInCos; i++) {
				this->nrProduseComandateDinFiecareTip[i] = c.nrProduseComandateDinFiecareTip[i];
			}


		}
		return*this;
	}
	Client getClient() {
		return this->client;
	}
	void setClient(Client clientNou) {
		this->client = clientNou;
	}
	int getNrProduseInCos() {
		return this->nrProduseInCos;
	}
	Produs* getProduse() {
		return this->produse;
	}
	void setProduse(Produs* produseNoi,int nrProduseNou) {
		if (produseNoi != nullptr) {
			delete[]this->produse;
			this->nrProduseInCos = nrProduseNou;
			this->produse = new Produs[nrProduseNou];
			for (int i = 0; i < nrProduseNou; i++) {
				this->produse[i] = produseNoi[i];
			}
		}
	}
	int* getNrProduseComandateDinFiecareTip() {
		return this->nrProduseComandateDinFiecareTip;
	}
	void setNrProduseComandateDinFiecareTip(int* vectorNou) {
		if (vectorNou != nullptr) {
			delete[]this->nrProduseComandateDinFiecareTip;
		}
		this->nrProduseComandateDinFiecareTip = new int[nrProduseInCos];
		for (int i = 0; i < nrProduseInCos; i++) {
			this->nrProduseComandateDinFiecareTip[i] = vectorNou[i];
		}
	}

	//supraincarcare operator index pentru a obtine un produs la alegere din vector
	Produs& operator [](int index) {
		if (index >= 0 && index < nrProduseInCos) {
			return produse[index];
		}
	}
	//afisare in consola a cosului de cumparaturi
	void afisareCosDeCumparaturi() {
		client.afisareClient();
		cout << "are urmatoarele produse in cosul de cumparaturi :" << endl;
			for (int i = 0; i < nrProduseInCos; i++) {
				cout << produse[i] << "si a bagat in cos " << nrProduseComandateDinFiecareTip[i] << " produse." << endl;
			
				
			}
			
			
	}
	//supraincarcare operator << pentru a scrie in fisier binar cosul de cumparaturi
	friend ofstream& operator <<(ofstream& fisierBinar, CosDeCumparaturi& cos) {
		fisierBinar << cos.client;
		fisierBinar.write((char*)&cos.nrProduseInCos, sizeof(int));
		for (int i = 0; i < cos.nrProduseInCos; i++) {
			cos.produse[i].salvareInFisierBinar(fisierBinar);
			fisierBinar.write((char*)cos.nrProduseComandateDinFiecareTip, sizeof(int) * cos.nrProduseInCos);
		}
		
	}
	//supraincarcare operator>> pentru a citi cosul de cumparaturi din fisier binar
	friend ifstream& operator >>(ifstream& fisierBinar, CosDeCumparaturi& cos) {
		delete[]cos.produse;
		fisierBinar >> cos.client;
		fisierBinar.read((char*)&cos.nrProduseInCos, sizeof(int));
		cos.produse = new Produs[cos.nrProduseInCos];
		for (int i = 0; i < cos.nrProduseInCos; i++) {
			cos.produse[i].citireDinFisierBinar(fisierBinar);
			fisierBinar.read((char*)cos.nrProduseComandateDinFiecareTip, sizeof(int) * cos.nrProduseInCos);
		}
	}

	//scriere in fisier text a cosului de cumparaturi
	void scriereInFisierText(ofstream& fisierText) {
		client.scriereInFisierText(fisierText);
		cout << endl;
		fisierText << nrProduseInCos << endl;
		for (int i = 0; i < nrProduseInCos; i++) {
			produse[i].scriereInFisierText(fisierText);
			cout << endl;
		}
		for (int i = 0; i < nrProduseInCos; i++) {
			fisierText << nrProduseComandateDinFiecareTip[i] << endl;
		}
	}
	//citire din fisier text a cosului de cumparaturi
	void citireDinFisierText(ifstream& fisierText) {
		if (produse != nullptr) {
			delete[]this->produse;
		}
		if (nrProduseComandateDinFiecareTip != nullptr) {
			delete[]this->nrProduseComandateDinFiecareTip;
		}
		
		client.citireDinFisierText(fisierText);
		fisierText >> nrProduseInCos;
		fisierText.ignore();
		this->produse = new Produs[nrProduseInCos];
		for (int i = 0; i < nrProduseInCos; i++) {
			produse[i].citireDinFisierText(fisierText);
		}
		this->nrProduseComandateDinFiecareTip = new int[nrProduseInCos];
		for (int i = 0; i < nrProduseInCos; i++) {
			fisierText >> nrProduseComandateDinFiecareTip[i];
			fisierText.ignore();
		}
		
		
	}

};
class OperatiiFinanciare {
	virtual double calculPretFinal() = 0;
};
class PrelucrareComanda : public OperatiiFinanciare {
	CosDeCumparaturi cosCumparaturi;
	bool plataCard;
	string dateCard;
	string lunaExpirarii;
	int anulExpirarii;
	string codCVV;
public:
	//constructor default
	PrelucrareComanda() {
		this->plataCard = true;
	}
	//constructor cu parametrii daca metoda de plata este cu cardul
	PrelucrareComanda( CosDeCumparaturi cos,bool plataCard,string dateCard,string lunaExpirarii,int anulExpirarii,string codCVV)  {
		if (plataCard == true) {
			if (dateCard.length() == 16) {
				if (anulExpirarii > 21) {
					cout << "tranzactia a fost aprobata,datele de pe card sunt valide" << endl;
				}
				else {
					cout << "cardul dumneavoastra este expirat!!" << endl;
				}
			}
			else {
				cout << "ati introdus prea multe/prea putine cifre din datele cardului" << endl;
			}
		}
		this->cosCumparaturi = cos;
		}
	
	
	//constructor cu parametrii daca metoda de plata este cash
	PrelucrareComanda(CosDeCumparaturi cos, bool plataCard) {
		if (plataCard == false) {
			this->plataCard = plataCard;
			this->cosCumparaturi = cos;
		}
	}
	//constructor de copiere
	PrelucrareComanda(const PrelucrareComanda& comanda)  {
		this->cosCumparaturi = comanda.cosCumparaturi;
		this->plataCard = comanda.plataCard;

	}
	//operator egal
	PrelucrareComanda& operator =(const PrelucrareComanda& comanda) {
		if (this != &comanda) {
			this->cosCumparaturi = comanda.cosCumparaturi;
			this->plataCard = comanda.plataCard;
		}
		return *this;
	}
	//setter si getter pentru plataCard
	void setPlataCard(bool plataCard) {
		if (plataCard == true || plataCard == false) {
			this->plataCard = plataCard;
		}
	}
	const char* getPlataCardInString() {
		switch (plataCard) {
		case 0:
			return "plata card";
		case 1:
			return"plata ramburs la curier";
		}

	}

	virtual double calculPretFinal() {
		double sumaDePlata;
		for (int i = 0; i < cosCumparaturi.getNrProduseInCos(); i++) {
			sumaDePlata+= cosCumparaturi.getProduse()[i] * cosCumparaturi.getNrProduseComandateDinFiecareTip()[i] * cosCumparaturi.getProduse()[i].getPret();
		}
		return sumaDePlata;
	}
	void afisareLaEcran() {
		cosCumparaturi.afisareCosDeCumparaturi();
		cout << "metoda aleasa de plata este: " << getPlataCardInString() << endl;

	}
	//m-am blocat aici
	void scriereInFisierTextRaport(ostream& fisierText) {


	}
};



int Produs::contor = 1;
ostream& operator <<(ostream& out, Produs& produs) {
	out << "nume produs: " << produs.numeProdus << endl
		<<"cod produs: "<<produs.idProdus<<endl
		<< "pret: " << produs.pret << " lei" << endl
		<< "descriere: " << produs.descriere << endl
		<< "nr cautari in ultimele 24 ore: " << produs.nrCautariProdusInUltimele24h << " ori." << endl;
	return out;

}








void main() {
	Produs p1("pasta de dinti", 10, 100, "este foarte mentolata", 100);
	Produs p2("bulion", 10, 100, "este foarte gustos", 100);
	Produs p3("casti gaming", 250, 999, "sunt foarte bune in jocuri precum call of duty si csgo", 10000);
	Produs p4("salam", 15, 400, "este un salam facut in casa de bunica mea", 999);
	vector<Produs>vectorProduse;
	vectorProduse.push_back(p1);
	vectorProduse.push_back(p2);
	vectorProduse.push_back(p3);
	vectorProduse.push_back(p4);
	vector<Produs*>::iterator iteratorProdus;
	ofstream fisierText("fisierTextProduseVector.txt");

	//salvare in fisier binar a produselor deja existente in magazin
	ofstream fisierBinar("fisierBinarProduse.bin", ios::binary | ios::out);
//de completat parcurgere

	///verificare functie de iteratie
	//deci imi itereaza bine, afiseaza id 1 ,2 3, dar nu inteleg dc atunci cand fac sa verific .

	
	//cout << "-------AFISARE ITERATIE VECTOR PERSOANE-------" << endl;

	Client c1("preda", "sorin", "aleea salaj nr.10", "sorinpreda045@gmail.com");
	Produs vector[] = { p1,p2 };
	int nrProduse[] = { 2,4 };
	CosDeCumparaturi cosdecumparaturi1(c1, 2, vector, nrProduse);
	cout << "-----------------AFISARE COS DE CUMPARATURI-------------------" << endl;
	cosdecumparaturi1.afisareCosDeCumparaturi();

	bool boolGlobal = true;
	while (boolGlobal) {
		cout << "------Meniu principal--------" << endl
			<< "Alegeti optiunea dorita: " << endl
			<< "1.Meniu client" << endl
			<< "2.Meniu magazin" << endl;
		int optiuneAleasa;
		cin >> optiuneAleasa;
		if (optiuneAleasa == 1) {
			bool verificareLopp = true;
			while (verificareLopp) {
				cout << "Bine ati venit in interfata client.Va rugam alegeti optiunea dorita:" << endl;
				cout << "1.Vizualizare produse din magazin" << endl
					<< "2.Adaugare produse in cosul de cumparaturi" << endl;
				int optiuneAleasaClient;
				cin >> optiuneAleasaClient;
				if (optiuneAleasaClient == 1) {
					for (int i = 0; i < vectorProduse.size(); i++) {
						cout << vectorProduse[i] << endl;
					}
				

				}
				else if (optiuneAleasaClient == 2) {
					cout << "Inainte de a putea baga produse in cos va rugam sa va scrieti numele si prenumele dumneavostra" << endl;
					string nume;
					string prenume;
					cout << "Nume:";
					cin >> nume; cout << endl <<
						"prenume: "; cin >> prenume;
					cout << "Va rugam sa specificati codul produsului dorit ,precum si cantitatea dorita din fiecare produs in parte" << endl;
					bool pragPunereInCos=true;
					while (pragPunereInCos) {
						int idProdus;
						string raspunsClient;
						bool esteIdValid = false;
						int controNrElementeVector = 0;
						cout << "id produs: "; cin >> idProdus; cout << endl;
						for (int i = 0; i < vectorProduse.size(); i++) {
							if (idProdus==vectorProduse[i].getIdProdus()) {
								esteIdValid = true;
								controNrElementeVector++;
								cout << "id este valid.Acum specificati cate bucati doriti din acest produs:" << endl;
								int nrProduseDorite;
								cin >> nrProduseDorite;
								cout << "este ok." << endl;
								cout << "Mai doriti alte produse?" << endl;
								cin >> raspunsClient;
								if (raspunsClient.compare("da") == 0) {
									break;
								}
								else {
									pragPunereInCos = false;
								}

								break;
							
							}
							if (esteIdValid == false) {
								cout << "Id nu este valid ,incercati din nou" << endl;
								break;
							}
					
						}

					}


				}
				else {
					cout << "Nu ati ales bine optiunea .Incercati din nou." << endl;
				}

			}


		}
		else if (optiuneAleasa == 2) {
			cout << "Bine ati venit in interfata magazin.Va rugam selectati optiunea dorita: " << endl
				<< "1.Adaugare de produse noi in magazin " << endl
				<< "2.Editare de produse din magazin " << endl
				<< "3.Stergere de produse din magazin " << endl
				<< "4.Preluare comenzi de la clienti " << endl
				<< "5.Realizare raport cu privire la comenzile primite" << endl;
			int optiuneAleasaMagazin;
			cin >> optiuneAleasaMagazin;
			if (optiuneAleasaMagazin == 1) {
				Produs p5;
				cin >> p5;
				cout << "Toate datele sunt corecte ? " << endl;
				cout << p5 << endl;
				vectorProduse.push_back(p5);
				
			}
			else if (optiuneAleasaMagazin == 2) {
				cout << "Precizati id-ul produsului pe care doriti sa il modificati." << endl;
				int idProdusDeModificat;
				Produs p100;
				int indexProdusDeModificat = -1;
				cin >> idProdusDeModificat;
				for (int i = 0; i < vectorProduse.size(); i++) {
					if (idProdusDeModificat == vectorProduse[i].getIdProdus()) {
						indexProdusDeModificat = i;
						p100 = vectorProduse[i];
						break;
					}
				}
				if (indexProdusDeModificat != -1) {
					cout << "Precizati atributul pe care doriti sa il modificati" << endl;
					cout << "1.Nume produs" << endl
						<< "2.Pret" << endl << "3.Cantitate disponibila" << endl
						<< "4.Descriere" << endl << "5.Nr cautari ale produsului in ultimele 24h" << endl;
					int atributDeModificat;
					cin >> atributDeModificat;
					switch (atributDeModificat) {
					case 1:
					{char numeNou[100];
					cout << "Precizati noul nume pentru produs:" << endl;
					cin >> numeNou;
					p100.setNumeProdus(numeNou); }
						
						break;
					case 2:
					{float pretNou;
					cout << "Precizati noul pret pentru produs: " << endl;
					cin >> pretNou;
					p100.setPret(pretNou); 
					}
						
						break;
					case 3: {

						double cantitateDisponibilaNoua;
						cout << "Precizati noua cantitate disponibila a produsului:" << endl;
						cin >> cantitateDisponibilaNoua;
						p100.setCantitateDisponibila(cantitateDisponibilaNoua);

					}
						break;
					case 4: {
						string descriereNoua;
						cout << "Precizati noua descriere a produsului: " << endl;
						cin >> descriereNoua;
						p100.setDescriere(descriereNoua);
					}
						
						break;
					case 5:
					{
						int nrCautariNou;
						cout << "Precizati noul numar de cautari al produsului" << endl;
						cin >> nrCautariNou;
						p100.setNrCautari(nrCautariNou);
					}
						
						break;
					default:
						cout << "Nu ati introdus un id corect." << endl;
					


					}
					vectorProduse[indexProdusDeModificat] = p100;
					cout << "Modificarea a fost realizata cu succes" << endl;
					if (fisierText.is_open()) {
						for (int i = 0; i < vectorProduse.size(); i++) {
							vectorProduse[i].scriereInFisierText(fisierText);
							
						}
						fisierText.close();
					}
					else {
						cout << "Fisierul text nu a putut fi deschis" << endl;
					}
					cout << "Salvarea in fisier text a fost realizata cu succes" << endl;
				

				}
				else {
					cout << "Ati introdus un id invalid" << endl;
					
				}
				

			}

		}
		else {
			cout << "nu ati ales bine optiunea .Incercati din nou" << endl;
		}

	}
	

}
