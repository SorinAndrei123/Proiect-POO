#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

 enum Categorie{tehnologie,igienaPersonala,bacanie,fashion,sport,birotica,jucarii,necunoscut};
class Produs {
	const int idProdus;
	static int contor;
	char* numeProdus;
	float pret;
	double cantitateDisponibila;
	string descriere;
	Categorie categorie;
	int nrCautariProdusInUltimele24h;
public:
	
	//constructor default
	Produs() :idProdus(1) {
		this->numeProdus = new char[strlen("Necunoscut") + 1];
		strcpy(this->numeProdus, "Necunoscut");
		this->pret = 0;
		this->cantitateDisponibila = 0;
		this->descriere = "Nu cunoastem acest produs.Este prea nou...";
		this->categorie = Categorie::necunoscut;
		this->nrCautariProdusInUltimele24h = 0;

	}
	//constructor cu toti parametrii
	Produs(const char*numeProdus,float pret,double cantitateDisponibila,string descriere,Categorie categorie,int nrCautariProdusInUltimele24h) :idProdus(contor++) {
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
	
		if (categorie == Categorie::bacanie || categorie == Categorie::birotica || categorie == Categorie::fashion || categorie == Categorie::igienaPersonala || categorie == Categorie::jucarii
			|| categorie == Categorie::sport || categorie == Categorie::tehnologie) {
			this->categorie = categorie;

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
		this->categorie = p.categorie;
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
			this->categorie = p.categorie;
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
	void setCategorie(Categorie categorieNoua) {

		if (categorieNoua == Categorie::bacanie || categorieNoua == Categorie::birotica || categorieNoua == Categorie::fashion || categorieNoua == Categorie::igienaPersonala || categorieNoua == Categorie::jucarii
			|| categorieNoua == Categorie::sport || categorieNoua == Categorie::tehnologie) {
			this->categorie = categorieNoua;
		}
	}

	//getter pentru a obtine in char categoria, nu cifra
	  const char* obtinereCategorie() {
		switch (this->categorie) {
		case Categorie::bacanie:
			return "bacanie";
			break;
		case Categorie::birotica:
			return "birotica";
			break;
		case Categorie::fashion:
			return "fashion";
			break;
		case Categorie::igienaPersonala:
			return "igiena personala";
			break;
		case Categorie::jucarii:
			return "jucarii";
			break;
		case Categorie::sport:
			return "articole sportive";
			break;
		case Categorie::tehnologie:
			return "tehnologie";
			break;
		default:
			return "necunoscut";
			break;
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


	
};
int Produs::contor = 1;
ostream& operator <<(ostream& out, Produs& produs) {
	out << "nume produs: " << produs.numeProdus << endl
		<< "pret: " << produs.pret <<" lei"<<endl
		<< "cantitate disponibila: " << produs.cantitateDisponibila << endl
		<< "descriere: " << produs.descriere << endl
		<< "categorie: " << produs.obtinereCategorie() << endl
		<< "nr cautari in ultimele 24 ore: " << produs.nrCautariProdusInUltimele24h << " ori." << endl;
	return out;
		
}








void main() {
	Produs p1("pasta de dinti", 10, 100, "este foarte mentolata", Categorie::igienaPersonala, 100);
	cout << p1;


}


