#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

class Exceptie {
private:
	string mesaj;
public:
	Exceptie(string mesaj) :mesaj(mesaj) {}
	string getMesaj() {
		return this->mesaj;
	}
};

enum UnitateDeMasura {
	GRAM = 1, MILILITRU = 2, LITRU = 3
};

class MateriePrima {
private:
	char* denumire = nullptr;
	float cantitateDisponibila = 0;
	UnitateDeMasura unitate = UnitateDeMasura::GRAM;
	float pretPerUnitate = 0;
protected:
	friend class Produs;
	friend class Trattorie;
	void operator>>(istream& in) {
		delete[] this->denumire;
		this->denumire = nullptr;

		string buffer;
		cout << "Denumire materie prima: ";
		cin.get();
		getline(cin, buffer);
		if (buffer.length() > 0) {
			this->denumire = new char[buffer.length() + 1];
			strcpy(this->denumire, buffer.data());
		}
		else throw new Exceptie("Denumirea materiei prime nu poate fi nula!");
		cout << "Cantitate disponibila: ";
		in >> this->cantitateDisponibila;
		cout << "Unitate (1 pt gram, 2 pt ml, 3 pl L): ";
		cin.get();
		getline(cin, buffer);
		if (buffer == "1") this->unitate = UnitateDeMasura::GRAM;
		else if (buffer == "2") this->unitate = UnitateDeMasura::MILILITRU;
		else if (buffer == "3") this->unitate = UnitateDeMasura::LITRU;
		cout << "Pret per unitate: ";
		in >> this->pretPerUnitate;
	}
public:
	MateriePrima() {}
	MateriePrima(const char* denumire, float cantitateDisponibila, UnitateDeMasura unitate, float pretPerUnitate) {
		if (denumire != nullptr && strlen(denumire) > 0) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else
			throw new Exceptie("Denumirea materiei prime trebuie sa nu fie nula!");
		if (cantitateDisponibila >= 0)
			this->cantitateDisponibila = cantitateDisponibila;
		else
			throw new Exceptie("Cantitatea disponibila a materiei prime trebuie sa fie nenegativa!");
		this->unitate = unitate;
		if (pretPerUnitate >= 0)
			this->pretPerUnitate = pretPerUnitate;
		else throw new Exceptie("Pretul per unitate trebuie sa aiba o valoare nenegativa!");
	}
	MateriePrima(const char* denumire, UnitateDeMasura unitate) {
		if (denumire != nullptr && strlen(denumire) > 0) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else
			throw new Exceptie("Denumirea materiei prime trebuie sa nu fie nula!");
		this->unitate = unitate;
	}
	MateriePrima(const MateriePrima& m) {
		if (m.denumire != nullptr && strlen(m.denumire) > 0) {
			this->denumire = new char[strlen(m.denumire) + 1];
			strcpy(this->denumire, m.denumire);
		}
		else
			throw new Exceptie("Denumirea materiei prime trebuie sa nu fie nula!");
		if (m.cantitateDisponibila >= 0)
			this->cantitateDisponibila = m.cantitateDisponibila;
		else
			throw new Exceptie("Cantitatea disponibila a materiei prime trebuie sa fie nenegativa!");
		this->unitate = m.unitate;
		if (m.pretPerUnitate >= 0)
			this->pretPerUnitate = m.pretPerUnitate;
		else throw new Exceptie("Pretul per unitate trebuie sa aiba o valoare nenegativa!");
	}
	~MateriePrima() {
		delete[] this->denumire;
		this->denumire = nullptr;
	}
	MateriePrima& operator=(const MateriePrima& m) {
		if (this != &m) {
			delete[] this->denumire;
			this->denumire = nullptr;

			if (m.denumire != nullptr && strlen(m.denumire) > 0) {
				this->denumire = new char[strlen(m.denumire) + 1];
				strcpy(this->denumire, m.denumire);
			}
			else
				throw new Exceptie("Denumirea materiei prime trebuie sa nu fie nula!");
			if (m.cantitateDisponibila >= 0)
				this->cantitateDisponibila = m.cantitateDisponibila;
			else
				throw new Exceptie("Cantitatea disponibila a materiei prime trebuie sa fie nenegativa!");
			this->unitate = m.unitate;
			if (m.pretPerUnitate >= 0)
				this->pretPerUnitate = m.pretPerUnitate;
			else throw new Exceptie("Pretul per unitate trebuie sa aiba o valoare nenegativa!");
		}
		return *this;
	}
	const char* getDenumire() {
		return this->denumire;
	}
	void setDenumire(const char* denumire) {
		if (denumire != nullptr && strlen(denumire) > 0) {
			delete[] this->denumire;
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else throw new Exceptie("Denumirea materiei prime trebuie sa nu fie nula!");
	}
	float getCantitateDisponibila() {
		return this->cantitateDisponibila;
	}
	void setCantitateDisponibila(float cantitate) {
		if (cantitate >= 0)
			this->cantitateDisponibila = cantitate;
		else throw new Exceptie("Cantitatea disponibila a materiei prime trebuie sa fie nenegativa!");
	}
	UnitateDeMasura getUnitate() {
		return this->unitate;
	}
	void setUnitate(UnitateDeMasura unitate) {
		this->unitate = unitate;
	}
	float getPretPerUnitate() {
		return this->pretPerUnitate;
	}
	void setPretPerUnitate(float pretPerUnitate) {
		if (pretPerUnitate >= 0)
			this->pretPerUnitate = pretPerUnitate;
		else throw new Exceptie("Pretul per unitate trebuie sa aiba o valoare nenegativa!");
	}
	void convertireUnitate(UnitateDeMasura unitate) {
		if (this->unitate != unitate) {
			switch (unitate) {
			case 1: {
				if (this->unitate == 2) {
					this->unitate = unitate;
				}
				else if (this->unitate == 3) {
					this->unitate = unitate;
					this->cantitateDisponibila *= 1000;
				}
			}; break;
			case 2: {
				if (this->unitate == 1) {
					this->unitate = unitate;
				}
				else if (this->unitate == 3) {
					this->unitate = unitate;
					this->cantitateDisponibila *= 1000;
				}
			}; break;
			case 3: {
				if (this->unitate == 1) {
					this->unitate = unitate;
					this->cantitateDisponibila /= 1000;
				}
				if (this->unitate == 2) {
					this->unitate = unitate;
					this->cantitateDisponibila /= 1000;
				}
			}; break;
			}
		}
	}
	float returnCantitateInGrame() {
		if (this->unitate != UnitateDeMasura::GRAM) {
			if (this->unitate == UnitateDeMasura::MILILITRU)
				return this->cantitateDisponibila;
			if (this->unitate == UnitateDeMasura::LITRU)
				return this->cantitateDisponibila * 1000;
		}
		return this->cantitateDisponibila;
	}
	static float transformare(UnitateDeMasura unitate1, UnitateDeMasura unitate2, float cantitate) {
		if (unitate1 != unitate2) {
			switch (unitate2) {
			case 1: {
				if (unitate1 == 2) {
					return cantitate;
				}
				else if (unitate1 == 3) {
					return cantitate / 1000;
				}
			}; break;
			case 2: {
				if (unitate1 == 1) {
					return cantitate;
				}
				else if (unitate1 == 3) {
					return cantitate / 1000;
				}
			}; break;
			case 3: {
				if (unitate1 == 1) {
					return cantitate * 1000;
				}
				if (unitate1 == 2) {
					return cantitate * 1000;
				}
			}; break;
			}
		}
		return cantitate;
	}
	string enumUnitate() {
		switch (this->unitate) {
		case 1: return "G";
		case 2: return "mL";
		case 3: return "L";
		}
		return "-";
	}
	friend ostream& operator<<(ostream& out, const MateriePrima& m) {
		out << "Denumire: ";
		if (m.denumire != nullptr)
			out << m.denumire << " ";
		else
			out << "N/A ";
		out << "| Cantitate disponibila: ";
		out << m.cantitateDisponibila << " ";
		out << "| Unitate de masura: ";
		switch (m.unitate) {
		case 1: out << "gram "; break;
		case 2: out << "mililitru "; break;
		case 3: out << "litru "; break;
		}
		out << "| Pret per unitate: ";
		out << m.pretPerUnitate;
		return out;
	}
	bool operator[](UnitateDeMasura index) {
		if (index == 1 || index == 2 || index == 3)
			switch (index) {
			case 1: { if (this->unitate == UnitateDeMasura::GRAM) return true; else return false; }
			case 2: { if (this->unitate == UnitateDeMasura::MILILITRU) return true; else return false; }
			case 3: { if (this->unitate == UnitateDeMasura::LITRU) return true; else return false; }
			}
		else throw new Exceptie("Nu exista unitate de masura corespunzatoare indexului dat!");
	}
	MateriePrima operator+(float cantitate) {
		if (cantitate >= 0) {
			MateriePrima rez = *this;
			rez.cantitateDisponibila += cantitate;
			return rez;
		}
		else throw new Exceptie("Cantitatea adaugata trebuie sa fie nenegativa!");
	}
	MateriePrima operator-(float cantitate) {
		if (cantitate >= 0) {
			MateriePrima rez = *this;
			if (rez.cantitateDisponibila - cantitate >= 0)
				rez.cantitateDisponibila -= cantitate;
			else throw new Exceptie("Cantitatea rezultata trebuie sa fie nenegativa!");
			return rez;
		}
		else throw new Exceptie("Cantitatea eliminata trebuie sa fie nenegativa!");
	}
	MateriePrima operator*(float cantitate) {
		if (cantitate >= 0) {
			MateriePrima rez = *this;
			rez.cantitateDisponibila *= cantitate;
			return rez;
		}
		else throw new Exceptie("Cantitatea de inmultit trebuie sa fie nenegativa!");
	}
	MateriePrima operator/(float cantitate) {
		if (cantitate > 0) {
			MateriePrima rez = *this;
			rez.cantitateDisponibila /= cantitate;
			return rez;
		}
		else throw new Exceptie("Cantitatea de impartit trebuie sa fie pozitiva!");
	}
	MateriePrima& operator++() {
		this->pretPerUnitate++;
		return *this;
	}
	MateriePrima operator++(int) {
		MateriePrima copie = *this;
		this->pretPerUnitate++;
		return copie;
	}
	MateriePrima& operator--() {
		if (this->pretPerUnitate - 1 >= 0) {
			this->pretPerUnitate--;
			return *this;
		}
		else throw new Exceptie("Pretul nu poate fi negativ!");
	}
	MateriePrima operator--(int) {
		if (this->pretPerUnitate - 1 >= 0) {
			MateriePrima copie = *this;
			this->pretPerUnitate--;
			return copie;
		}
		else throw new Exceptie("Pretul nu poate fi negativ!");
	}
	explicit operator float() {
		return this->cantitateDisponibila;
	}
	bool operator!() {
		if (cantitateDisponibila) return false;
		return true;
	}
	bool operator<(const MateriePrima& m) {
		if (this != &m) {
			if (this->cantitateDisponibila < m.cantitateDisponibila) return true;
			else return false;
		}
		return false;
	}
	bool operator<=(const MateriePrima& m) {
		if (this != &m) {
			if (this->cantitateDisponibila <= m.cantitateDisponibila) return true;
			else return false;
		}
		return true;
	}
	bool operator>(const MateriePrima& m) {
		if (this != &m) {
			if (this->cantitateDisponibila > m.cantitateDisponibila) return true;
			else return false;
		}
		return false;
	}
	bool operator>=(const MateriePrima& m) {
		if (this != &m) {
			if (this->cantitateDisponibila >= m.cantitateDisponibila) return true;
			else return false;
		}
		return true;
	}
	bool operator==(const MateriePrima& m) {
		if (this != &m) {
			if (strcmp(this->denumire, m.denumire) != 0) return false;
			if (this->cantitateDisponibila != m.cantitateDisponibila) return false;
			if (this->unitate != m.unitate) return false;
			if (this->pretPerUnitate != m.pretPerUnitate) return false;
			return true;
		}
		return true;
	}
};

class Produs {
private:
	static int* listaIDuri;
	static int nrIDuri;
	const int id;
	string denumire = "N/A";
	int nrMateriiPrime = 0;
	MateriePrima** retetar = nullptr;
	float* cantitatiNecesare = nullptr;
	float adaos = 0;
protected:
	friend class Client;
	friend class Trattorie;
	friend class DateClient;
	void operator>>(istream& in) {
		delete[] this->retetar;
		this->retetar = nullptr;
		delete[] this->cantitatiNecesare;
		this->cantitatiNecesare = nullptr;
		string buffer;
		cout << "Denumire produs: ";
		cin.get();
		getline(cin, buffer);
		if (buffer.length() > 0)
			this->denumire = buffer;
		else throw new Exceptie("Denumirea produsului nu poate sa fie nula!");
		cout << "Nr materii prime: ";
		in >> this->nrMateriiPrime;
		if (this->nrMateriiPrime) {
			this->retetar = new MateriePrima * [this->nrMateriiPrime];
			this->cantitatiNecesare = new float[this->nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++) {
				this->retetar[i] = new MateriePrima;
				cout << "MATERIA PRIMA " << i << " :\n";
				*this->retetar[i] >> in;
				cout << "CANTITATE NECESARA DIN MATERIA PRIMA " << i << " : ";
				in >> this->cantitatiNecesare[i];
			}
		}
		cout << "Adaos (in procente): ";
		in >> this->adaos;
	}
public:
	/*static void distrugeListaIDuri() {
		delete[] Produs::listaIDuri;
		Produs::listaIDuri = nullptr;
	}*/
	void adaugaID(int id) {
		if (Produs::nrIDuri == 0 && Produs::listaIDuri == nullptr) {
			Produs::nrIDuri++;
			Produs::listaIDuri = new int[Produs::nrIDuri];
			Produs::listaIDuri[0] = id;
		}
		else if (Produs::nrIDuri > 0 && Produs::listaIDuri != nullptr) {
			int* copieLista = new int[Produs::nrIDuri];
			for (int i = 0; i < Produs::nrIDuri; i++)
				copieLista[i] = Produs::listaIDuri[i];
			Produs::nrIDuri++;
			delete[] Produs::listaIDuri;
			Produs::listaIDuri = new int[Produs::nrIDuri];
			for (int i = 0; i < Produs::nrIDuri - 1; i++)
				Produs::listaIDuri[i] = copieLista[i];
			Produs::listaIDuri[Produs::nrIDuri - 1] = id;
			delete[] copieLista;
			copieLista = nullptr;
		}
	}
	void stergeID(int id) {
		if (Produs::nrIDuri == 1) {
			Produs::nrIDuri--;
			delete[] Produs::listaIDuri;
			Produs::listaIDuri = nullptr;
		}
		else if (Produs::nrIDuri >= 2) {
			int* copieLista = new int[Produs::nrIDuri];
			for (int i = 0; i < Produs::nrIDuri; i++)
				copieLista[i] = Produs::listaIDuri[i];
			int index = -1;
			for (int i = 0; i < Produs::nrIDuri && index < 0; i++)
				if (copieLista[i] == id) index = i;
			for (int i = index; i < Produs::nrIDuri - 1; i++)
				copieLista[i] = copieLista[i + 1];
			Produs::nrIDuri--;
			delete[] Produs::listaIDuri;
			Produs::listaIDuri = new int[Produs::nrIDuri];
			for (int i = 0; i < Produs::nrIDuri; i++)
				Produs::listaIDuri[i] = copieLista[i];
			delete[] copieLista;
			copieLista = nullptr;
		}
		else throw new Exceptie("Lista ID-urilor este corupta!");
	}
	int verificaID(int id) {
		if (id < 0) id *= -1;
		if (Produs::nrIDuri == 0 && Produs::listaIDuri == nullptr) {
			Produs::adaugaID(id);
			return id;
		}
		else if (Produs::nrIDuri > 0 && Produs::listaIDuri != nullptr) {
			bool ok = true;
			do {
				ok = true;
				for (int i = 0; i < Produs::nrIDuri && ok; i++)
					if (id == Produs::listaIDuri[i]) ok = false;
				if (ok) {
					Produs::adaugaID(id);
					return id;
				}
				else id++;
			} while (!ok);
		}
		throw new Exceptie("Lista ID-urilor este corupta!");
	}
	Produs() :id(Produs::verificaID(0)) {}
	Produs(int id, string denumire, int nrMateriiPrime, MateriePrima** retetar, float* cantitatiNecesare, float adaos) :id(Produs::verificaID(id)) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		else
			throw new Exceptie("Denumirea produsului nu poate sa fie nula!");
		if (nrMateriiPrime > 0) {
			this->nrMateriiPrime = nrMateriiPrime;
			if (retetar != nullptr) {
				this->retetar = new MateriePrima * [this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++) {
					this->retetar[i] = retetar[i];
				}
			}
			else throw new Exceptie("Retetarul nu poate sa fie nul!");
			if (cantitatiNecesare != nullptr) {
				this->cantitatiNecesare = new float[this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++) {
					if (cantitatiNecesare[i] > 0)
						this->cantitatiNecesare[i] = cantitatiNecesare[i];
					else
						throw new Exceptie("Cantitatea necesara nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor necesare nu poate fi nula!");
		}
		else throw new Exceptie("Numarul de materii prime necesare produsului trebuie sa fie pozitiv!");
		if (adaos >= 0)
			this->adaos = adaos;
		else throw new Exceptie("Adaosul comercial nu poate fi negativ!");
	}
	Produs(string denumire) :id(Produs::verificaID(0)) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		else
			throw new Exceptie("Denumirea produsului nu poate sa fie nula!");
	}
	Produs(const Produs& p) :id(Produs::verificaID(p.id + 1)) {
		if (p.denumire.length() > 0)
			this->denumire = p.denumire;
		else
			throw new Exceptie("Denumirea produsului nu poate sa fie nula!");
		if (p.nrMateriiPrime > 0) {
			this->nrMateriiPrime = p.nrMateriiPrime;
			if (p.retetar != nullptr) {
				this->retetar = new MateriePrima * [this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++) {
					this->retetar[i] = p.retetar[i];
				}
			}
			else throw new Exceptie("Retetarul nu poate sa fie nul!");
			if (p.cantitatiNecesare != nullptr) {
				this->cantitatiNecesare = new float[this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++) {
					if (p.cantitatiNecesare[i] > 0)
						this->cantitatiNecesare[i] = p.cantitatiNecesare[i];
					else
						throw new Exceptie("Cantitatea necesara nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor necesare nu poate fi nula!");
		}
		else throw new Exceptie("Numarul de materii prime necesare produsului trebuie sa fie pozitiv!");
		if (p.adaos >= 0)
			this->adaos = p.adaos;
		else throw new Exceptie("Adaosul comercial nu poate fi negativ!");
	}
	~Produs() {
		Produs::stergeID(this->id);
		delete[] this->retetar;
		this->retetar = nullptr;
		delete[] this->cantitatiNecesare;
		this->cantitatiNecesare = nullptr;
	}
	Produs& operator=(const Produs& p) {
		if (this != &p) {
			delete[] this->retetar;
			this->retetar = nullptr;
			delete[] this->cantitatiNecesare;
			this->cantitatiNecesare = nullptr;

			if (p.denumire.length() > 0)
				this->denumire = p.denumire;
			else
				throw new Exceptie("Denumirea produsului nu poate sa fie nula!");
			if (p.nrMateriiPrime > 0) {
				this->nrMateriiPrime = p.nrMateriiPrime;
				if (p.retetar != nullptr) {
					this->retetar = new MateriePrima * [this->nrMateriiPrime];
					for (int i = 0; i < this->nrMateriiPrime; i++) {
						this->retetar[i] = p.retetar[i];
					}
				}
				else throw new Exceptie("Retetarul nu poate sa fie nul!");
				if (p.cantitatiNecesare != nullptr) {
					this->cantitatiNecesare = new float[this->nrMateriiPrime];
					for (int i = 0; i < this->nrMateriiPrime; i++) {
						if (p.cantitatiNecesare[i] > 0)
							this->cantitatiNecesare[i] = p.cantitatiNecesare[i];
						else
							throw new Exceptie("Cantitatea necesara nu poate fi negativa sau zero!");
					}
				}
				else throw new Exceptie("Lista cantitatilor necesare nu poate fi nula!");
			}
			else throw new Exceptie("Numarul de materii prime necesare produsului trebuie sa fie pozitiv!");
			if (p.adaos >= 0)
				this->adaos = p.adaos;
			else throw new Exceptie("Adaosul comercial nu poate fi negativ!");
		}
		return *this;
	}
	const static int* getListaIDuri() {
		return Produs::listaIDuri;
	}
	static int getNrIDuri() {
		return Produs::nrIDuri;
	}
	/*static void setListaIDuri(int nrIDuri, int* listaIDuri) {
		if (nrIDuri > 0) {
			Produs::nrIDuri = nrIDuri;
			if (listaIDuri != nullptr) {
				delete[] Produs::listaIDuri;
				Produs::listaIDuri = new int[Produs::nrIDuri];
				for (int i = 0; i < Produs::nrIDuri; i++)
					Produs::listaIDuri[i] = listaIDuri[i];
			}
			else throw new Exceptie("Lista ID-urilor adaugate nu poate fi nula!");
		}
		else throw new Exceptie("Numarul de ID-uri adaugate trebuie sa fie pozitiv!");
	}*/
	const int getID() {
		return this->id;
	}
	string getDenumire() {
		return this->denumire;
	}
	void setDenumire(string denumire) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		else throw new Exceptie("Denumirea produsului nu poate sa fie nula!");
	}
	int getNrMateriiPrime() {
		return this->nrMateriiPrime;
	}
	MateriePrima** getRetetar() {
		return this->retetar;
	}
	const float* getCantitatiNecesare() {
		return this->cantitatiNecesare;
	}
	void setRetetarSiCantitati(int nrMateriiPrime, MateriePrima** retetar, float* cantitatiNecesare) {
		if (nrMateriiPrime > 0) {
			this->nrMateriiPrime = nrMateriiPrime;
			if (retetar != nullptr) {
				delete[] this->retetar;
				this->retetar = new MateriePrima * [this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++) {
					this->retetar[i] = retetar[i];
				}
			}
			else throw new Exceptie("Retetarul nu poate sa fie nul!");
			if (cantitatiNecesare != nullptr) {
				delete[] this->cantitatiNecesare;
				this->cantitatiNecesare = new float[this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++) {
					if (cantitatiNecesare[i] > 0)
						this->cantitatiNecesare[i] = cantitatiNecesare[i];
					else
						throw new Exceptie("Cantitatea necesara nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor necesare nu poate fi nula!");
		}
		else throw new Exceptie("Numarul de materii prime necesare produsului trebuie sa fie pozitiv!");
	}
	void setRetetar(int nrMateriiPrime, MateriePrima** retetar) {
		if (nrMateriiPrime > 0) {
			this->nrMateriiPrime = nrMateriiPrime;
			if (retetar != nullptr) {
				delete[] this->retetar;
				this->retetar = new MateriePrima * [this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++) {
					this->retetar[i] = retetar[i];
				}
			}
			else throw new Exceptie("Retetarul nu poate sa fie nul!");
		}
		else throw new Exceptie("Numarul de materii prime necesare produsului trebuie sa fie pozitiv!");
	}
	void setCantitati(float* cantitatiNecesare) {
		if (this->nrMateriiPrime > 0) {
			if (cantitatiNecesare != nullptr) {
				delete[] this->cantitatiNecesare;
				this->cantitatiNecesare = new float[this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++) {
					if (cantitatiNecesare[i] > 0)
						this->cantitatiNecesare[i] = cantitatiNecesare[i];
					else
						throw new Exceptie("Cantitatea necesara nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor necesare nu poate fi nula!");
		}
		else throw new Exceptie("Numarul de materii prime necesare produsului nu este pozitiv!");
	}
	float getAdaos() {
		return this->adaos;
	}
	void setAdaos(float adaos) {
		if (adaos >= 0)
			this->adaos = adaos;
		else throw new Exceptie("Adaosul comercial nu poate fi negativ!");
	}
	float uniformizareCantitate(int index) {
		if (index >= 0 && index < this->nrMateriiPrime && this->nrMateriiPrime > 0 && this->retetar != nullptr) {
			if (this->retetar[index]->getUnitate() != UnitateDeMasura::GRAM) {
				switch (this->retetar[index]->getUnitate()) {
				case 2: return this->cantitatiNecesare[index];
				case 3: return this->cantitatiNecesare[index] * 1000;
				}
			}
			return this->cantitatiNecesare[index];
		}
		else throw new Exceptie("Nu exista cantitate la indexul dat!");
	}
	float calculPret() {
		float pret = 0;
		for (int i = 0; i < this->nrMateriiPrime; i++) {
			pret += this->cantitatiNecesare[i] * (this->retetar[i]->getPretPerUnitate());
		}
		pret *= (1 + this->adaos / 100);
		return pret;
	}
	float calculCantitate() {
		float cantitate = 0;
		for (int i = 0; i < this->nrMateriiPrime; i++) {
			cantitate += this->uniformizareCantitate(i);
		}
		return cantitate;
	}
	void afisareProdus() {
		cout << "[" << this->id << "]  ";
		cout << this->denumire;
		printf("  %.2fG  |  %.2fRON", this->calculCantitate(), this->calculPret());
	}
	void majorareAdaos(float puncteProcentuale) {
		if (puncteProcentuale > 0)
			this->adaos += puncteProcentuale;
		else throw new Exceptie("Numarul de puncte procentuale trebuie sa fie pozitiv!");
	}
	void micsorareAdaos(float puncteProcentuale) {
		if (puncteProcentuale > 0)
			this->adaos -= puncteProcentuale;
		else throw new Exceptie("Numarul de puncte procentuale trebuie sa fie pozitiv!");
	}
	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "ID: " << p.id << " ";
		out << "| Denumire: " << p.denumire << " ";
		out << "| Nr materii prime: " << p.nrMateriiPrime << "\n";
		if (p.nrMateriiPrime > 0 && p.retetar != nullptr && p.cantitatiNecesare != nullptr) {
			out << "RETETAR:\n";
			for (int i = 0; i < p.nrMateriiPrime; i++)
				out << "  " << *p.retetar[i] << " [CANTITATE NECESARA: " << p.cantitatiNecesare[i] << p.retetar[i]->enumUnitate() << " ]\n";
		}
		out << "Adaos: " << p.adaos << "%";
		return out;
	}
	float operator[](int index) {
		if (index >= 0 && index < this->nrMateriiPrime && this->cantitatiNecesare != nullptr)
			return this->cantitatiNecesare[index];
		else throw new Exceptie("Nu exista cantitate necesara la indexul dat!");
	}
	Produs operator+(float adaos) {
		if (adaos >= 0) {
			Produs rez = *this;
			rez.adaos += adaos;
			return rez;
		}
		else throw new Exceptie("Adaosul adaugat trebuie sa fie nenegativ!");
	}
	Produs operator-(float adaos) {
		if (adaos >= 0 && adaos < 100) {
			Produs rez = *this;
			rez.adaos -= adaos;
			return rez;
		}
		else throw new Exceptie("Discount-ul trebuie sa fie nenegativ si mai mic ca 100!");
	}
	Produs operator*(float adaos) {
		if (adaos >= 0) {
			Produs rez = *this;
			rez.adaos *= adaos;
			return rez;
		}
		else throw new Exceptie("Adaosul de inmultit trebuie sa fie nenegativ!");
	}
	Produs operator/(float adaos) {
		if (adaos > 0) {
			Produs rez = *this;
			rez.adaos /= adaos;
			return rez;
		}
		else throw new Exceptie("Adaosul de impartit trebuie sa fie pozitiv!");
	}
	Produs& operator++() {
		this->adaos++;
		return *this;
	}
	Produs operator++(int) {
		Produs copie = *this;
		this->adaos++;
		return copie;
	}
	Produs& operator--() {
		if (this->adaos - 1 > -100) {
			this->adaos--;
			return *this;
		}
		else throw new Exceptie("Discount-ul nu poate fi mai pare procentual decat pretul final!");
	}
	Produs operator--(int) {
		if (this->adaos - 1 > -100) {
			Produs copie = *this;
			this->adaos--;
			return copie;
		}
		else throw new Exceptie("Discount-ul nu poate fi mai pare procentual decat pretul final!");
	}
	explicit operator float() {
		return this->adaos;
	}
	bool operator!() {
		if (this->adaos) return false;
		return true;
	}
	bool operator<(const Produs& p) {
		if (this != &p) {
			if (this->adaos < p.adaos) return true;
			return false;
		}
		return false;
	}
	bool operator<=(const Produs& p) {
		if (this != &p) {
			if (this->adaos <= p.adaos) return true;
			return false;
		}
		return true;
	}
	bool operator>(const Produs& p) {
		if (this != &p) {
			if (this->adaos > p.adaos) return true;
			return false;
		}
		return false;
	}
	bool operator>=(const Produs& p) {
		if (this != &p) {
			if (this->adaos >= p.adaos) return true;
			return false;
		}
		return true;
	}
	bool operator==(const Produs& p) {
		if (this != &p) {
			if (this->denumire != p.denumire) return false;
			if (this->nrMateriiPrime != p.nrMateriiPrime) return false;
			if (this->retetar == nullptr && p.retetar != nullptr) return false;
			if (this->retetar != nullptr && p.retetar == nullptr) return false;
			if (this->cantitatiNecesare == nullptr && p.cantitatiNecesare != nullptr) return false;
			if (this->cantitatiNecesare != nullptr && p.cantitatiNecesare == nullptr) return false;
			if (this->retetar != nullptr && p.retetar != nullptr)
				for (int i = 0; i < this->nrMateriiPrime; i++)
					if (!(*this->retetar[i] == *p.retetar[i])) return false;
			if (this->cantitatiNecesare != nullptr && p.cantitatiNecesare != nullptr)
				for (int i = 0; i < this->nrMateriiPrime; i++)
					if (this->cantitatiNecesare[i] != p.cantitatiNecesare[i]) return false;
			if (this->adaos != p.adaos) return false;
			return true;
		}
		return true;
	}
	friend bool operator<(const Produs& p1, const Produs& p2) {
		return p1.adaos < p2.adaos;
	}
};

enum TipBlat {
	SUBTIRE = 1, NORMAL = 2, PUFOS = 3
};

class Pizza : public Produs {
private:
	int nrOptiuniBlat = 0;
	TipBlat* optiuniBlat = nullptr;
	int marime = 0;
protected:
	friend class Client;
	friend class Trattorie;
	friend class DateClient;
	void operator>>(istream& in) {
		delete[] this->optiuniBlat;
		this->optiuniBlat = nullptr;
		this->Produs::operator>>(in);
		cout << "Nr optiuni blat: ";
		in >> this->nrOptiuniBlat;
		string buffer;
		if (this->nrOptiuniBlat > 0) {
			this->optiuniBlat = new TipBlat[this->nrOptiuniBlat];
			cin.get();
			for (int i = 0; i < this->nrOptiuniBlat; i++) {
				cout << "Optiunea blat " << i << " (1 pt subtire, 2 pt normal, 3 pt pufos) : ";
				getline(cin, buffer);
				if (buffer == "1") this->optiuniBlat[i] = TipBlat::SUBTIRE;
				else if (buffer == "2") this->optiuniBlat[i] = TipBlat::NORMAL;
				else if (buffer == "3") this->optiuniBlat[i] = TipBlat::PUFOS;
			}
		}
		cout << "Marime pizza: ";
		in >> this->marime;
	}
public:
	Pizza() : Produs() {}
	Pizza(int id, string denumire, int nrMateriiPrime, MateriePrima** retetar, float* cantitatiNecesare, float adaos, int nrOptiuniBlat, TipBlat* optiuniBlat, int marime)
		:Produs(id, denumire, nrMateriiPrime, retetar, cantitatiNecesare, adaos) {
		if (nrOptiuniBlat > 0) {
			this->nrOptiuniBlat = nrOptiuniBlat;
			if (optiuniBlat != nullptr) {
				this->optiuniBlat = new TipBlat[this->nrOptiuniBlat];
				for (int i = 0; i < this->nrOptiuniBlat; i++)
					this->optiuniBlat[i] = optiuniBlat[i];
			}
			else throw new Exceptie("Lista optiunilor de blat nu poate fi nula!");
		}
		else throw new Exceptie("Numarul de optiuni ale blatului trebuie sa fie pozitiv!");
		if (marime > 0)
			this->marime = marime;
		else
			throw new Exceptie("Marimea pizzei trebuie sa fie pozitiva!");
	}
	Pizza(string denumire, int marime)
		:Produs(denumire) {
		if (marime > 0)
			this->marime = marime;
		else
			throw new Exceptie("Marimea pizzei trebuie sa fie pozitiva!");
	}
	Pizza(const Pizza& p) :Produs(p) {
		if (p.nrOptiuniBlat > 0) {
			this->nrOptiuniBlat = p.nrOptiuniBlat;
			if (p.optiuniBlat != nullptr) {
				this->optiuniBlat = new TipBlat[this->nrOptiuniBlat];
				for (int i = 0; i < this->nrOptiuniBlat; i++)
					this->optiuniBlat[i] = p.optiuniBlat[i];
			}
			else throw new Exceptie("Lista optiunilor de blat nu poate fi nula!");
		}
		else throw new Exceptie("Numarul de optiuni ale blatului trebuie sa fie pozitiv!");
		if (p.marime > 0)
			this->marime = p.marime;
		else
			throw new Exceptie("Marimea pizzei trebuie sa fie pozitiva!");
	}
	~Pizza() {
		delete[] this->optiuniBlat;
		this->optiuniBlat = nullptr;
	}
	Pizza& operator=(const Pizza& p) {
		if (this != &p) {
			delete[] this->optiuniBlat;
			this->optiuniBlat = nullptr;

			this->Produs::operator=(p);
			if (p.nrOptiuniBlat > 0) {
				this->nrOptiuniBlat = p.nrOptiuniBlat;
				if (p.optiuniBlat != nullptr) {
					this->optiuniBlat = new TipBlat[this->nrOptiuniBlat];
					for (int i = 0; i < this->nrOptiuniBlat; i++)
						this->optiuniBlat[i] = p.optiuniBlat[i];
				}
				else throw new Exceptie("Lista optiunilor de blat nu poate fi nula!");
			}
			else throw new Exceptie("Numarul de optiuni ale blatului trebuie sa fie pozitiv!");
			if (p.marime > 0)
				this->marime = p.marime;
			else
				throw new Exceptie("Marimea pizzei trebuie sa fie pozitiva!");
		}
		return *this;
	}
	int getNrOptiuniBlat() {
		return this->nrOptiuniBlat;
	}
	const TipBlat* getOptiuniBlat() {
		return this->optiuniBlat;
	}
	void setOptiuniBlat(int nrOptiuniBlat, TipBlat* optiuniBlat) {
		if (nrOptiuniBlat > 0) {
			this->nrOptiuniBlat = nrOptiuniBlat;
			if (optiuniBlat != nullptr) {
				this->optiuniBlat = new TipBlat[this->nrOptiuniBlat];
				for (int i = 0; i < this->nrOptiuniBlat; i++)
					this->optiuniBlat[i] = optiuniBlat[i];
			}
			else throw new Exceptie("Lista optiunilor de blat nu poate fi nula!");
		}
		else throw new Exceptie("Numarul de optiuni ale blatului trebuie sa fie pozitiv!");
	}
	int getMarime() {
		return this->marime;
	}
	void setMarime(int marime) {
		if (marime > 0)
			this->marime = marime;
		else
			throw new Exceptie("Marimea pizzei trebuie sa fie pozitiva!");
	}
	float uniformizareCantitate(int index) {
		if (index >= 0 && index < this->getNrMateriiPrime() && this->getNrMateriiPrime() > 0 && this->getRetetar() != nullptr) {
			if (this->getRetetar()[index]->getUnitate() != UnitateDeMasura::GRAM) {
				switch (this->getRetetar()[index]->getUnitate()) {
				case 2: return this->getCantitatiNecesare()[index];
				case 3: return this->getCantitatiNecesare()[index] * 1000;
				}
			}
			return this->getCantitatiNecesare()[index];
		}
		else throw new Exceptie("Nu exista cantitate la indexul dat!");
	}
	float calculPret() {
		float pret = 0;
		for (int i = 0; i < this->getNrMateriiPrime(); i++) {
			pret += this->getCantitatiNecesare()[i] * (this->getRetetar()[i]->getPretPerUnitate());
		}
		pret *= (1 + ((float)this->marime / 100) / 4);
		pret *= (1 + this->getAdaos() / 100);
		return pret;
	}
	float calculCantitate() {
		float cantitate = 0;
		for (int i = 0; i < this->getNrMateriiPrime(); i++) {
			cantitate += this->uniformizareCantitate(i);
		}
		return cantitate;
	}
	string enumOptiuniBlat(int index, TipBlat* optiuniBlat) {
		if (index >= 0 && index < this->nrOptiuniBlat && optiuniBlat != nullptr && this->nrOptiuniBlat > 0 && this->optiuniBlat != nullptr) {
			switch (optiuniBlat[index]) {
			case 1: return "Blat subtire";
			case 2: return "Blat normal";
			case 3: return "Blat pufos";
			}
		}
		else throw new Exceptie("Nu exista tip de blat la indexul dat!");
		return "";
	}
	void afisareProdus() {
		cout << "[" << this->getID() << "]  ";
		cout << this->getDenumire();
		printf("  %.2fG  ", this->calculCantitate());

		if (this->nrOptiuniBlat > 0) {
			if (this->optiuniBlat != nullptr) {
				TipBlat* copieOptiuni = new TipBlat[this->nrOptiuniBlat];
				for (int i = 0; i < this->nrOptiuniBlat; i++)
					copieOptiuni[i] = this->optiuniBlat[i];
				int inv = 0;
				do {
					inv = 0;
					for (int i = 0; i < this->nrOptiuniBlat - 1; i++)
						if (copieOptiuni[i] > copieOptiuni[i + 1]) {
							TipBlat aux = copieOptiuni[i];
							copieOptiuni[i] = copieOptiuni[i + 1];
							copieOptiuni[i + 1] = aux;
							inv = 1;
						}
				} while (inv);

				cout << "|  ";
				for (int i = 0; i < this->nrOptiuniBlat - 1; i++) {
					printf("%.2fRON - ", this->calculPret() * (1 + (float)copieOptiuni[i] / 10 - (float)1 / 10));
					cout << this->enumOptiuniBlat(i, copieOptiuni) << " | ";
				}
				printf("%.2fRON - ", this->calculPret() * (1 + (float)copieOptiuni[this->nrOptiuniBlat - 1] / 10 - (float)1 / 10));
				cout << this->enumOptiuniBlat(this->nrOptiuniBlat - 1, copieOptiuni);
				delete[] copieOptiuni;
				copieOptiuni = nullptr;
			}
			else {
				printf("%.2fRON", this->calculPret());
				cout << "|  ";
			}
		}
		else {
			cout << "|  ";
			printf("%.2fRON", this->calculPret());
		}
	}
	void majorareAdaos(float puncteProcentuale) {
		if (puncteProcentuale > 0)
			this->setAdaos(this->getAdaos() + puncteProcentuale);
		else throw new Exceptie("Numarul de puncte procentuale trebuie sa fie pozitiv!");
	}
	void micsorareAdaos(float puncteProcentuale) {
		if (puncteProcentuale > 0)
			this->setAdaos(this->getAdaos() - puncteProcentuale);
		else throw new Exceptie("Numarul de puncte procentuale trebuie sa fie pozitiv!");
	}
	void modificareMarime(int valoare) {
		this->marime += valoare;
	}
	friend ostream& operator<<(ostream& out, const Pizza& p) {
		out << (Produs&)p;
		out << "\nNr optiuni blat: " << p.nrOptiuniBlat;
		if (p.nrOptiuniBlat > 0 && p.optiuniBlat != nullptr) {
			out << " -> ";
			for (int i = 0; i < p.nrOptiuniBlat; i++) {
				switch (p.optiuniBlat[i]) {
				case 1: out << "SUBTIRE  "; break;
				case 2: out << "NORMAL  "; break;
				case 3: out << "PUFOS  "; break;
				}
			}
		}
		out << "\nMarime pizza: " << p.marime << "cm";
		return out;
	}
	TipBlat operator[](int index) {
		if (index >= 0 && index < this->nrOptiuniBlat && this->optiuniBlat != nullptr)
			return this->optiuniBlat[index];
		else throw new Exceptie("Nu exista tip de blat la indexul dat!");
	}
	Pizza operator+(int marime) {
		if (marime >= 0) {
			Pizza rez = *this;
			rez.marime += marime;
			return rez;
		}
		else throw new Exceptie("Marimea adaugata trebuie sa fie nenegativa!");
	}
	Pizza operator-(int marime) {
		if (marime >= 0) {
			Pizza rez = *this;
			if (rez.marime - marime > 0)
				rez.marime -= marime;
			else throw new Exceptie("Marimea rezultata trebuie sa fie pozitiva!");
			return rez;
		}
		else throw new Exceptie("Marimea scazuta trebuie sa fie nenegativa!");
	}
	Pizza operator*(int marime) {
		if (marime >= 0) {
			Pizza rez = *this;
			rez.marime *= marime;
			return rez;
		}
		else throw new Exceptie("Marimea de inmultit trebuie sa fie nenegativa!");
	}
	Pizza operator/(int marime) {
		if (marime > 0) {
			Pizza rez = *this;
			rez.marime /= marime;
			return rez;
		}
		else throw new Exceptie("Marimea de impartit trebuie sa fie pozitiva!");
	}
	Pizza& operator++() {
		this->marime++;
		return *this;
	}
	Pizza operator++(int) {
		Pizza copie = *this;
		this->marime++;
		return copie;
	}
	Pizza& operator--() {
		if (this->marime - 1 > 0) {
			this->marime--;
			return *this;
		}
		else throw new Exceptie("Marimea pizzei trebuie sa fie pozitiva!");
	}
	Pizza operator--(int) {
		if (this->marime - 1 > 0) {
			Pizza copie = *this;
			this->marime--;
			return copie;
		}
		else throw new Exceptie("Marimea pizzei trebuie sa fie pozitiva!");
	}
	explicit operator int() {
		return this->marime;
	}
	bool operator!() {
		if (this->marime) return false;
		return true;
	}
	bool operator<(const Pizza& p) {
		if (this != &p) {
			if (this->marime < p.marime) return true;
			return false;
		}
		return false;
	}
	bool operator<=(const Pizza& p) {
		if (this != &p) {
			if (this->marime <= p.marime) return true;
			return false;
		}
		return true;
	}
	bool operator>(const Pizza& p) {
		if (this != &p) {
			if (this->marime > p.marime) return true;
			return false;
		}
		return false;
	}
	bool operator>=(const Pizza& p) {
		if (this != &p) {
			if (this->marime >= p.marime) return true;
			return false;
		}
		return true;
	}
	bool operator==(const Pizza& p) {
		if (this != &p) {
			if (this->Produs::operator==(p) == false) return false;
			if (this->nrOptiuniBlat != p.nrOptiuniBlat) return false;
			if (this->optiuniBlat == nullptr && p.optiuniBlat != nullptr) return false;
			if (this->optiuniBlat != nullptr && p.optiuniBlat == nullptr) return false;
			if (this->optiuniBlat != nullptr && p.optiuniBlat != nullptr) {
				for (int i = 0; i < this->nrOptiuniBlat; i++)
					if (this->optiuniBlat[i] != p.optiuniBlat[i]) return false;
			}
			if (this->marime != p.marime) return false;
			return true;
		}
		return true;
	}
	friend bool operator<(const Pizza& p1, const Pizza& p2) {
		return p1.marime < p2.marime;
	}
};

class Trattorie;
class DateTrattorie;

class Client {
private:
	string nume = "N/A";
	string sex = "N/A";
	string telefon = "N/A";
	int varsta = 0;
	static float procentMinimBacsis;
	int nrProduse = 0;
	Produs** comandaProduse = nullptr;
	float* cantitatiCeruteProduse = nullptr;
	int nrPizza = 0;
	Pizza** comandaPizza = nullptr;
	float* cantitatiCerutePizza = nullptr;
	TipBlat* tipuri = nullptr;
	float buget = 0;
	Trattorie* restaurant = nullptr;
public:
	friend class Trattorie;
	friend class DateTrattorie;
	Client() {}
	Client(string nume, string sex, string telefon, int varsta, int nrProduse, Produs** comandaProduse, float* cantitatiCeruteProduse, int nrPizza, Pizza** comandaPizza, float* cantitatiCerutePizza, TipBlat* tipuri, float buget, Trattorie* restaurant) {
		if (nume.length() > 0)
			this->nume = nume;
		else
			throw new Exceptie("Numele clientului nu poate sa fie nul!");
		if (sex.length() > 0)
			this->sex = sex;
		else
			throw new Exceptie("Sexul clientului nu poate fi nul!");
		if (telefon.length() > 0)
			this->telefon = telefon;
		else
			throw new Exceptie("Telefonul clientului nu poate fi nul!");
		if (varsta >= 0)
			this->varsta = varsta;
		else
			throw new Exceptie("Varsta clientului trebuie sa fie nenegativa!");
		if (nrProduse >= 0) {
			if (nrProduse > 0) {
				this->nrProduse = nrProduse;
				if (comandaProduse != nullptr) {
					this->comandaProduse = new Produs * [this->nrProduse];
					for (int i = 0; i < this->nrProduse; i++)
						this->comandaProduse[i] = comandaProduse[i];
				}
				else
					throw new Exceptie("Comanda de produse nu poate sa fie nula pentru un numar de produse comandate pozitiv!");
				if (cantitatiCeruteProduse != nullptr) {
					this->cantitatiCeruteProduse = new float[this->nrProduse];
					for (int i = 0; i < this->nrProduse; i++) {
						if (cantitatiCeruteProduse[i] > 0)
							this->cantitatiCeruteProduse[i] = cantitatiCeruteProduse[i];
						else
							throw new Exceptie("Cantitatea ceruta de un produs nu poate fi negativa!");
					}
				}
				else throw new Exceptie("Lista cantitatilor cerute de produse nu poate fi nula pentru un numar de produse comandate pozitiv!");
			}
		}
		else throw new Exceptie("Numarul de produse comandate nu poate fi negativ!");
		if (nrPizza >= 0) {
			if (nrPizza > 0) {
				this->nrPizza = nrPizza;
				if (comandaPizza != nullptr) {
					this->comandaPizza = new Pizza * [this->nrPizza];
					for (int i = 0; i < this->nrPizza; i++)
						this->comandaPizza[i] = comandaPizza[i];
				}
				else
					throw new Exceptie("Comanda de pizza nu poate sa fie nula pentru un numar de produse comandate pozitiv!");
				if (cantitatiCerutePizza != nullptr) {
					this->cantitatiCerutePizza = new float[this->nrPizza];
					for (int i = 0; i < this->nrPizza; i++) {
						if (cantitatiCerutePizza[i] > 0)
							this->cantitatiCerutePizza[i] = cantitatiCerutePizza[i];
						else
							throw new Exceptie("Cantitatea ceruta de o pizza nu poate fi negativa!");
					}
				}
				else throw new Exceptie("Lista cantitatilor cerute de pizza nu poate fi nula pentru un numar de pizza comandate pozitiv!");
				if (tipuri != nullptr) {
					this->tipuri = new TipBlat[this->nrPizza];
					for (int i = 0; i < this->nrPizza; i++)
						this->tipuri[i] = tipuri[i];
				}
			}
		}
		else throw new Exceptie("Numarul de pizza comandate nu poate fi negativ!");
		if (buget >= 0)
			this->buget = buget;
		else throw new Exceptie("Bugetul clientului trebuie sa fie nenegativ!");
		this->restaurant = restaurant;
	}
	Client(float buget) {
		if (buget >= 0)
			this->buget = buget;
		else throw new Exceptie("Bugetul clientului trebuie sa fie nenegativ!");
	}
	Client(const Client& c) {
		if (c.nume.length() > 0)
			this->nume = c.nume;
		else
			throw new Exceptie("Numele clientului nu poate sa fie nul!");
		if (c.sex.length() > 0)
			this->sex = c.sex;
		else
			throw new Exceptie("Sexul clientului nu poate fi nul!");
		if (c.telefon.length() > 0)
			this->telefon = c.telefon;
		else
			throw new Exceptie("Telefonul clientului nu poate fi nul!");
		if (c.varsta >= 0)
			this->varsta = c.varsta;
		else
			throw new Exceptie("Varsta clientului trebuie sa fie nenegativa!");
		if (c.nrProduse >= 0) {
			if (c.nrProduse > 0) {
				this->nrProduse = c.nrProduse;
				if (c.comandaProduse != nullptr) {
					this->comandaProduse = new Produs * [this->nrProduse];
					for (int i = 0; i < this->nrProduse; i++)
						this->comandaProduse[i] = c.comandaProduse[i];
				}
				else
					throw new Exceptie("Comanda de produse nu poate sa fie nula pentru un numar de produse comandate pozitiv!");
				if (c.cantitatiCeruteProduse != nullptr) {
					this->cantitatiCeruteProduse = new float[this->nrProduse];
					for (int i = 0; i < this->nrProduse; i++) {
						if (c.cantitatiCeruteProduse[i] > 0)
							this->cantitatiCeruteProduse[i] = c.cantitatiCeruteProduse[i];
						else
							throw new Exceptie("Cantitatea ceruta de un produs nu poate fi negativa!");
					}
				}
				else throw new Exceptie("Lista cantitatilor cerute de produse nu poate fi nula pentru un numar de produse comandate pozitiv!");
			}
		}
		else throw new Exceptie("Numarul de produse comandate nu poate fi negativ!");
		if (c.nrPizza >= 0) {
			if (c.nrPizza > 0) {
				this->nrPizza = c.nrPizza;
				if (c.comandaPizza != nullptr) {
					this->comandaPizza = new Pizza * [this->nrPizza];
					for (int i = 0; i < this->nrPizza; i++)
						this->comandaPizza[i] = c.comandaPizza[i];
				}
				else
					throw new Exceptie("Comanda de pizza nu poate sa fie nula pentru un numar de produse comandate pozitiv!");
				if (c.cantitatiCerutePizza != nullptr) {
					this->cantitatiCerutePizza = new float[this->nrPizza];
					for (int i = 0; i < this->nrPizza; i++) {
						if (c.cantitatiCerutePizza[i] > 0)
							this->cantitatiCerutePizza[i] = c.cantitatiCerutePizza[i];
						else
							throw new Exceptie("Cantitatea ceruta de o pizza nu poate fi negativa!");
					}
				}
				else throw new Exceptie("Lista cantitatilor cerute de pizza nu poate fi nula pentru un numar de pizza comandate pozitiv!");
				if (c.tipuri != nullptr) {
					this->tipuri = new TipBlat[this->nrPizza];
					for (int i = 0; i < this->nrPizza; i++)
						this->tipuri[i] = c.tipuri[i];
				}
			}
		}
		else throw new Exceptie("Numarul de pizza comandate nu poate fi negativ!");
		if (c.buget >= 0)
			this->buget = c.buget;
		else throw new Exceptie("Bugetul clientului trebuie sa fie nenegativ!");
		this->restaurant = c.restaurant;
	}
	~Client() {
		delete[] this->comandaProduse;
		this->comandaProduse = nullptr;
		delete[] this->cantitatiCeruteProduse;
		this->cantitatiCeruteProduse = nullptr;
		delete[] this->comandaPizza;
		this->comandaPizza = nullptr;
		delete[] this->cantitatiCerutePizza;
		this->cantitatiCerutePizza = nullptr;
		delete[] this->tipuri;
		this->tipuri = nullptr;
		this->restaurant = nullptr;
	}
	Client& operator=(const Client& c) {
		if (this != &c) {
			delete[] this->comandaProduse;
			this->comandaProduse = nullptr;
			delete[] this->cantitatiCeruteProduse;
			this->cantitatiCeruteProduse = nullptr;
			delete[] this->comandaPizza;
			this->comandaPizza = nullptr;
			delete[] this->cantitatiCerutePizza;
			this->cantitatiCerutePizza = nullptr;
			delete[] this->tipuri;
			this->tipuri = nullptr;
			this->restaurant = nullptr;

			if (c.nume.length() > 0)
				this->nume = c.nume;
			else
				throw new Exceptie("Numele clientului nu poate sa fie nul!");
			if (c.sex.length() > 0)
				this->sex = c.sex;
			else
				throw new Exceptie("Sexul clientului nu poate fi nul!");
			if (c.telefon.length() > 0)
				this->telefon = c.telefon;
			else
				throw new Exceptie("Telefonul clientului nu poate fi nul!");
			if (c.varsta >= 0)
				this->varsta = c.varsta;
			else
				throw new Exceptie("Varsta clientului trebuie sa fie nenegativa!");
			if (c.nrProduse >= 0) {
				if (c.nrProduse > 0) {
					this->nrProduse = c.nrProduse;
					if (c.comandaProduse != nullptr) {
						this->comandaProduse = new Produs * [this->nrProduse];
						for (int i = 0; i < this->nrProduse; i++)
							this->comandaProduse[i] = c.comandaProduse[i];
					}
					else
						throw new Exceptie("Comanda de produse nu poate sa fie nula pentru un numar de produse comandate pozitiv!");
					if (c.cantitatiCeruteProduse != nullptr) {
						this->cantitatiCeruteProduse = new float[this->nrProduse];
						for (int i = 0; i < this->nrProduse; i++) {
							if (c.cantitatiCeruteProduse[i] > 0)
								this->cantitatiCeruteProduse[i] = c.cantitatiCeruteProduse[i];
							else
								throw new Exceptie("Cantitatea ceruta de un produs nu poate fi negativa!");
						}
					}
					else throw new Exceptie("Lista cantitatilor cerute de produse nu poate fi nula pentru un numar de produse comandate pozitiv!");
				}
			}
			else throw new Exceptie("Numarul de produse comandate nu poate fi negativ!");
			if (c.nrPizza >= 0) {
				if (c.nrPizza > 0) {
					this->nrPizza = c.nrPizza;
					if (c.comandaPizza != nullptr) {
						this->comandaPizza = new Pizza * [this->nrPizza];
						for (int i = 0; i < this->nrPizza; i++)
							this->comandaPizza[i] = c.comandaPizza[i];
					}
					else
						throw new Exceptie("Comanda de pizza nu poate sa fie nula pentru un numar de produse comandate pozitiv!");
					if (c.cantitatiCerutePizza != nullptr) {
						this->cantitatiCerutePizza = new float[this->nrPizza];
						for (int i = 0; i < this->nrPizza; i++) {
							if (c.cantitatiCerutePizza[i] > 0)
								this->cantitatiCerutePizza[i] = c.cantitatiCerutePizza[i];
							else
								throw new Exceptie("Cantitatea ceruta de o pizza nu poate fi negativa!");
						}
					}
					else throw new Exceptie("Lista cantitatilor cerute de pizza nu poate fi nula pentru un numar de pizza comandate pozitiv!");
					if (c.tipuri != nullptr) {
						this->tipuri = new TipBlat[this->nrPizza];
						for (int i = 0; i < this->nrPizza; i++)
							this->tipuri[i] = c.tipuri[i];
					}
				}
			}
			else throw new Exceptie("Numarul de pizza comandate nu poate fi negativ!");
			if (c.buget >= 0)
				this->buget = c.buget;
			else throw new Exceptie("Bugetul clientului trebuie sa fie nenegativ!");
			this->restaurant = c.restaurant;
		}
		return *this;
	}
	string getNume() {
		return this->nume;
	}
	void setNume(string nume) {
		if (nume.length() > 0)
			this->nume = nume;
		else
			throw new Exceptie("Numele clientului nu poate sa fie nul!");
	}
	string getSex() {
		return this->sex;
	}
	void setSex(string sex) {
		if (sex.length() > 0)
			this->sex = sex;
		else
			throw new Exceptie("Sexul clientului nu poate fi nul!");
	}
	string getTelefon() {
		return this->telefon;
	}
	void setTelefon(string telefon) {
		if (telefon.length() > 0)
			this->telefon = telefon;
		else
			throw new Exceptie("Telefonul clientului nu poate fi nul!");
	}
	int getVarsta() {
		return this->varsta;
	}
	void setVarsta(int varsta) {
		if (varsta >= 0)
			this->varsta = varsta;
		else
			throw new Exceptie("Varsta clientului trebuie sa fie nenegativa!");
	}
	static float getProcentMinimBacsis() {
		return Client::procentMinimBacsis;
	}
	static void setProcentMinimBacsis(float procent) {
		if (procent >= 0 && procent <= 50)
			Client::procentMinimBacsis = procent;
		else throw new Exceptie("Procentul minim de bacsis trebuie sa fie cuprins intre 0 si 50 (%) !");
	}
	int getNrProduse() {
		return this->nrProduse;
	}
	Produs** getComandaProduse() {
		return this->comandaProduse;
	}
	const float* getCantitatiCeruteProduse() {
		return this->cantitatiCeruteProduse;
	}
	void setComandaSiCantitatiProduse(int nrProduse, Produs** comandaProduse, float* cantitatiCeruteProduse) {
		if (nrProduse > 0) {
			this->nrProduse = nrProduse;
			if (comandaProduse != nullptr) {
				delete[] this->comandaProduse;
				this->comandaProduse = new Produs * [this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->comandaProduse[i] = comandaProduse[i];
			}
			else
				throw new Exceptie("Comanda nu poate sa fie nula pentru un numar de produse comandate pozitiv!");
			if (cantitatiCeruteProduse != nullptr) {
				delete[] this->cantitatiCeruteProduse;
				this->cantitatiCeruteProduse = new float[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++) {
					if (cantitatiCeruteProduse[i] > 0)
						this->cantitatiCeruteProduse[i] = cantitatiCeruteProduse[i];
					else
						throw new Exceptie("Cantitatea ceruta nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor cerute nu poate fi nula pentru un numar de produse comandate pozitiv!");
		}
		else if (nrProduse == 0) {
			this->nrProduse = 0;
			delete[] this->comandaProduse;
			this->comandaProduse = nullptr;
			delete[] this->cantitatiCeruteProduse;
			this->cantitatiCeruteProduse = nullptr;
		}
		else throw new Exceptie("Numarul de produse comandate trebuie sa fie nenegativ!");
	}
	void setComandaProduse(int nrProduse, Produs** comandaProduse) {
		if (nrProduse > 0) {
			this->nrProduse = nrProduse;
			if (comandaProduse != nullptr) {
				delete[] this->comandaProduse;
				this->comandaProduse = new Produs * [this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->comandaProduse[i] = comandaProduse[i];
			}
			else
				throw new Exceptie("Comanda nu poate sa fie nula pentru un numar de produse comandate pozitiv!");
		}
		else if (nrProduse == 0) {
			this->nrProduse = 0;
			delete[] this->comandaProduse;
			this->comandaProduse = nullptr;
			delete[] this->cantitatiCeruteProduse;
			this->cantitatiCeruteProduse = nullptr;
		}
		else throw new Exceptie("Numarul de produse comandate trebuie sa fie nenegativ!");
	}
	void setCantitatiProduse(float* cantitatiCeruteProduse) {
		if (nrProduse > 0) {
			if (cantitatiCeruteProduse != nullptr) {
				delete[] this->cantitatiCeruteProduse;
				this->cantitatiCeruteProduse = new float[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++) {
					if (cantitatiCeruteProduse[i] > 0)
						this->cantitatiCeruteProduse[i] = cantitatiCeruteProduse[i];
					else
						throw new Exceptie("Cantitatea ceruta nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor cerute nu poate fi nula pentru un numar de produse comandate pozitiv!");
		}
		else throw new Exceptie("Numarul de produse comandate nu este pozitiv!");
	}
	int getNrPizza() {
		return this->nrPizza;
	}
	Pizza** getComandaPizza() {
		return this->comandaPizza;
	}
	const float* getCantitatiCerutePizza() {
		return this->cantitatiCerutePizza;
	}
	const TipBlat* getTipuri() {
		return this->tipuri; //vezi daca e cu const
	}
	void setComandaPizzaComplet(int nrPizza, Pizza** comandaPizza, float* cantitatiCerutePizza, TipBlat* tipuri) {
		if (nrPizza > 0) {
			this->nrPizza = nrPizza;
			if (comandaPizza != nullptr) {
				delete[] this->comandaPizza;
				this->comandaPizza = new Pizza * [this->nrPizza];
				for (int i = 0; i < this->nrPizza; i++)
					this->comandaPizza[i] = comandaPizza[i];
			}
			else
				throw new Exceptie("Comanda nu poate sa fie nula pentru un numar de pizza comandate pozitiv!");
			if (cantitatiCerutePizza != nullptr) {
				delete[] this->cantitatiCerutePizza;
				this->cantitatiCerutePizza = new float[this->nrPizza];
				for (int i = 0; i < this->nrPizza; i++) {
					if (cantitatiCerutePizza[i] > 0)
						this->cantitatiCerutePizza[i] = cantitatiCerutePizza[i];
					else
						throw new Exceptie("Cantitatea ceruta nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor cerute nu poate fi nula pentru un numar de pizza comandate pozitiv!");
			if (tipuri != nullptr) {
				delete[] this->tipuri;
				this->tipuri = new TipBlat[this->nrPizza];
				for (int i = 0; i < this->nrPizza; i++)
					this->tipuri[i] = tipuri[i];
			}
		}
		else if (nrPizza == 0) {
			this->nrPizza = 0;
			delete[] this->comandaPizza;
			this->comandaPizza = nullptr;
			delete[] this->cantitatiCerutePizza;
			this->cantitatiCerutePizza = nullptr;
			delete[] this->tipuri;
			this->tipuri = nullptr;
		}
		else throw new Exceptie("Numarul de pizza comandate trebuie sa fie nenegativ!");
	}
	void setComandaPizza(int nrPizza, Pizza** comandaPizza) {
		if (nrPizza > 0) {
			this->nrPizza = nrPizza;
			if (comandaPizza != nullptr) {
				delete[] this->comandaPizza;
				this->comandaPizza = new Pizza * [this->nrPizza];
				for (int i = 0; i < this->nrPizza; i++)
					this->comandaPizza[i] = comandaPizza[i];
			}
			else
				throw new Exceptie("Comanda nu poate sa fie nula pentru un numar de pizza comandate pozitiv!");
		}
		else if (nrPizza == 0) {
			this->nrPizza = 0;
			delete[] this->comandaPizza;
			this->comandaPizza = nullptr;
			delete[] this->cantitatiCerutePizza;
			this->cantitatiCerutePizza = nullptr;
			delete[] this->tipuri;
			this->tipuri = nullptr;
		}
		else throw new Exceptie("Numarul de pizza comandate trebuie sa fie nenegativ!");
	}
	void setCantitatiSiTipuri(float* cantitatiCerutePizza, TipBlat* tipuri) {
		if (nrPizza > 0) {
			if (cantitatiCerutePizza != nullptr) {
				delete[] this->cantitatiCerutePizza;
				this->cantitatiCerutePizza = new float[this->nrPizza];
				for (int i = 0; i < this->nrPizza; i++) {
					if (cantitatiCerutePizza[i] > 0)
						this->cantitatiCerutePizza[i] = cantitatiCerutePizza[i];
					else
						throw new Exceptie("Cantitatea ceruta nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor cerute nu poate fi nula pentru un numar de pizza comandate pozitiv!");
			if (tipuri != nullptr) {
				delete[] this->tipuri;
				this->tipuri = new TipBlat[this->nrPizza];
				for (int i = 0; i < this->nrPizza; i++)
					this->tipuri[i] = tipuri[i];
			}
			else throw new Exceptie("Lista tipurilor de pizza nu poate fi nula pentru un numar de pizza comandate pozitiv!");
		}
		else throw new Exceptie("Numarul de pizza comandate nu este pozitiv!");
	}
	void setCantitatiPizza(float* cantitatiCerutePizza) {
		if (nrPizza > 0) {
			if (cantitatiCerutePizza != nullptr) {
				delete[] this->cantitatiCerutePizza;
				this->cantitatiCerutePizza = new float[this->nrPizza];
				for (int i = 0; i < this->nrPizza; i++) {
					if (cantitatiCerutePizza[i] > 0)
						this->cantitatiCerutePizza[i] = cantitatiCerutePizza[i];
					else
						throw new Exceptie("Cantitatea ceruta nu poate fi negativa sau zero!");
				}
			}
			else throw new Exceptie("Lista cantitatilor cerute nu poate fi nula pentru un numar de pizza comandate pozitiv!");
		}
		else throw new Exceptie("Numarul de pizza comandate nu este pozitiv!");
	}
	void setTipuriPizza(TipBlat* tipuri) {
		if (nrPizza > 0) {
			if (tipuri != nullptr) {
				delete[] this->tipuri;
				this->tipuri = new TipBlat[this->nrPizza];
				for (int i = 0; i < this->nrPizza; i++)
					this->tipuri[i] = tipuri[i];
			}
			else throw new Exceptie("Lista tipurilor de pizza nu poate fi nula pentru un numar de pizza comandate pozitiv!");
		}
		else throw new Exceptie("Numarul de pizza comandate nu este pozitiv!");
	}
	float getBuget() {
		return this->buget;
	}
	void setBuget(float buget) {
		if (buget >= 0)
			this->buget = buget;
		else throw new Exceptie("Bugetul clientului trebuie sa fie nenegativ!");
	}
	const Trattorie* getRestaurant() {
		return this->restaurant;
	}
	void setRestaurant(Trattorie* restaurant) {
		this->restaurant = restaurant;
	}
	string pizzaSauProdusMENIU(int id);
	string pizzaSauProdusCOMANDA(int id);
	void adaugaProdus(int id, float cantitateCeruta);
	void eliminaProdus(int id, int cantitateEliminata);
	void adaugaPizza(int id, float cantitateCeruta, TipBlat tip);
	void eliminaPizza(int id, int cantitateEliminata);
	bool calculDisponibilitate();
	float calculSubpretComanda() {
		float pret = 0;
		if (this->nrProduse > 0 && this->comandaProduse != nullptr && this->cantitatiCeruteProduse != nullptr)
			for (int i = 0; i < this->nrProduse; i++)
				pret += this->cantitatiCeruteProduse[i] * this->comandaProduse[i]->calculPret();
		if (this->nrPizza > 0 && this->comandaPizza != nullptr && this->cantitatiCerutePizza != nullptr && this->tipuri != nullptr)
			for (int i = 0; i < this->nrPizza; i++)
				pret += this->cantitatiCerutePizza[i] * (this->comandaPizza[i]->calculPret() * (1 + (float)this->tipuri[i] / 10 - (float)1 / 10));
		return pret;
	}
	float calculPretComanda() {
		float pret = this->calculSubpretComanda();
		pret += pret * (Client::procentMinimBacsis / 100);
		return pret;
	}
	bool areComanda() {
		if (this->nrProduse > 0 && this->comandaProduse != nullptr && this->cantitatiCeruteProduse != nullptr) return true;
		if (this->nrPizza > 0 && this->comandaPizza != nullptr && this->cantitatiCerutePizza != nullptr && this->tipuri != nullptr) return true;
		return false;
	}
	void afiseazaComanda() {
		cout << "Comanda - " << this->nume << "\n";
		cout << "-------------------------------------------------------------------\n";
		if (this->areComanda() == false) cout << "[ COMANDA GOALA ]\n";
		else {
			if (this->nrPizza > 0 && this->comandaPizza != nullptr && this->cantitatiCerutePizza != nullptr) {
				for (int i = 0; i < this->nrPizza; i++) {
					cout << "[" << this->comandaPizza[i]->getID() << "]  ";
					cout << this->comandaPizza[i]->getDenumire();
					printf("  %.2fG  ", this->comandaPizza[i]->calculCantitate());
					cout << "|  ";
					if (this->tipuri != nullptr) {
						printf("%.2fRON - ", this->comandaPizza[i]->calculPret() * (1 + (float)this->tipuri[i] / 10 - (float)1 / 10));
						switch (this->tipuri[i]) {
						case 1: cout << "Blat subtire"; break;
						case 2: cout << "Blat normal"; break;
						case 3: cout << "Blat pufos"; break;
						}
					}
					else cout << "Blat subtire";
					cout << "   (CANTITATE: " << this->cantitatiCerutePizza[i] << ")";
					cout << "\n";
				}
			}
			if (this->nrProduse > 0 && this->comandaProduse != nullptr && this->cantitatiCeruteProduse != nullptr) {
				for (int i = 0; i < this->nrProduse; i++) {
					this->comandaProduse[i]->afisareProdus();
					cout << "   (CANTITATE: " << this->cantitatiCeruteProduse[i] << ")";
					cout << "\n";
				}
			}
		}
		cout << "-------------------------------------------------------------------\n";
		printf("[ SUBTOTAL: %.2fRON ]\n", this->calculSubpretComanda());
		printf("[ PROCENT MINIM BACSIS: %.2f%% ]\n", Client::procentMinimBacsis);
		printf("[ TOTAL: %.2fRON ]", this->calculPretComanda());
	}
	friend ostream& operator<<(ostream& out, const Client& c) {
		out << "Nume: " << c.nume << " ";
		out << "| Sex: " << c.sex << " ";
		out << "| Telefon: " << c.telefon << " ";
		out << "| Varsta: " << c.varsta;
		out << "\nNR PIZZA COMANDATE: " << c.nrPizza;
		if (c.nrPizza > 0 && c.comandaPizza != nullptr && c.cantitatiCerutePizza != nullptr) {
			for (int i = 0; i < c.nrPizza; i++) {
				out << "\n" << "  " << *c.comandaPizza[i];
				out << "\n  [ CANTITATE CERUTA: " << c.cantitatiCerutePizza[i] << " ]  ";
				if (c.tipuri[i])
					switch (c.tipuri[i]) {
					case 1: out << "[ BLAT CERUT: SUBTIRE ]"; break;
					case 2: out << "[ BLAT CERUT: NORMAL ]"; break;
					case 3: out << "[ BLAT CERUT: PUFOS ]"; break;
					}
			}
		}
		out << "\nNR PRODUSE COMANDATE: " << c.nrProduse;
		if (c.nrProduse > 0 && c.comandaProduse != nullptr && c.cantitatiCeruteProduse != nullptr) {
			for (int i = 0; i < c.nrProduse; i++) {
				out << "\n" << "  " << *c.comandaProduse[i];
				out << "\n  [ CANTITATE CERUTA: " << c.cantitatiCeruteProduse[i] << " ]";
			}
		}
		out << "\nBUGET: " << c.buget;
		if (c.restaurant != nullptr) {
			out << "\nPROCENT MINIM BACSIS COMANDA: " << Client::procentMinimBacsis << "%";
		}
		return out;
	}
	friend istream& operator>>(istream& in, Client& c);
	void stergeComanda() {
		this->nrProduse = 0;
		this->nrPizza = 0;
		delete[] this->comandaProduse;
		this->comandaProduse = nullptr;
		delete[] this->cantitatiCeruteProduse;
		this->cantitatiCeruteProduse = nullptr;
		delete[] this->comandaPizza;
		this->comandaPizza = nullptr;
		delete[] this->cantitatiCerutePizza;
		this->cantitatiCerutePizza = nullptr;
		delete[] this->tipuri;
		this->tipuri = nullptr;
	}
	TipBlat operator[](int index) {
		if (index >= 0 && index < this->nrPizza && this->tipuri != nullptr)
			return this->tipuri[index];
		else throw new Exceptie("Nu exista tip de blat la indexul dat");
	}
	Client operator+(float buget) {
		if (buget >= 0) {
			Client rez = *this;
			rez.buget += buget;
			return rez;
		}
		else throw new Exceptie("Bugetul de adaugat trebuie sa fie nenegativ!");
	}
	Client operator-(float buget) {
		if (buget >= 0) {
			Client rez = *this;
			if (rez.buget - buget >= 0)
				rez.buget -= buget;
			else throw new Exceptie("Bugetul rezultat trebuie sa fie nenegativ!");
			return rez;
		}
		else throw new Exceptie("Bugetul de scazut trebuie sa fie nenegativ!");
	}
	Client operator*(float buget) {
		if (buget >= 0) {
			Client rez = *this;
			rez.buget *= buget;
			return rez;
		}
		else throw new Exceptie("Bugetul de inmultit trebuie sa fie nenegativ!");
	}
	Client operator/(float buget) {
		if (buget > 0) {
			Client rez = *this;
			rez.buget /= buget;
			return rez;
		}
		else throw new Exceptie("Bugetul de adaugat trebuie sa fie pozitiv!");
	}
	Client& operator++() {
		this->buget++;
		return *this;
	}
	Client operator++(int) {
		Client copie = *this;
		this->buget++;
		return copie;
	}
	Client& operator--() {
		if (this->buget - 1 >= 0) {
			this->buget--;
			return *this;
		}
		else throw new Exceptie("Bugetul nu poate fi negativ!");
	}
	Client operator--(int) {
		if (this->buget - 1 >= 0) {
			Client copie = *this;
			this->buget--;
			return copie;
		}
		else throw new Exceptie("Bugetul nu poate fi negativ!");
	}
	explicit operator float() {
		return this->buget;
	}
	bool operator!() {
		if (this->buget) return false;
		return true;
	}
	bool operator<(const Client& c) {
		if (this != &c) {
			if (this->buget < c.buget) return true;
			return false;
		}
		return false;
	}
	bool operator<=(const Client& c) {
		if (this != &c) {
			if (this->buget <= c.buget) return true;
			return false;
		}
		return true;
	}
	bool operator>(const Client& c) {
		if (this != &c) {
			if (this->buget > c.buget) return true;
			return false;
		}
		return false;
	}
	bool operator>=(const Client& c) {
		if (this != &c) {
			if (this->buget >= c.buget) return true;
			return false;
		}
		return true;
	}
	bool operator==(const Client& c) {
		if (this != &c) {
			if (this->nume != c.nume) return false;
			if (this->sex != c.sex) return false;
			if (this->telefon != c.telefon) return false;
			if (this->varsta != c.varsta) return false;
			if (this->nrProduse != c.nrProduse) return false;
			if (this->comandaProduse == nullptr && c.comandaProduse != nullptr) return false;
			if (this->comandaProduse != nullptr && c.comandaProduse == nullptr) return false;
			if (this->cantitatiCeruteProduse != nullptr && c.cantitatiCeruteProduse == nullptr) return false;
			if (this->cantitatiCeruteProduse == nullptr && c.cantitatiCeruteProduse != nullptr) return false;
			if (this->comandaProduse != nullptr && c.comandaProduse != nullptr)
				for (int i = 0; i < this->nrProduse; i++)
					if (!(*this->comandaProduse[i] == *c.comandaProduse[i])) return false;
			if (this->cantitatiCeruteProduse != nullptr && c.cantitatiCeruteProduse != nullptr)
				for (int i = 0; i < this->nrProduse; i++)
					if (this->cantitatiCeruteProduse[i] != c.cantitatiCeruteProduse[i]) return false;
			if (this->nrPizza != c.nrPizza) return false;
			if (this->comandaPizza != nullptr && c.comandaPizza == nullptr) return false;
			if (this->comandaPizza == nullptr && c.comandaPizza != nullptr) return false;
			if (this->cantitatiCerutePizza != nullptr && c.cantitatiCerutePizza == nullptr) return false;
			if (this->cantitatiCerutePizza == nullptr && c.cantitatiCerutePizza != nullptr) return false;
			if (this->tipuri != nullptr && c.tipuri == nullptr) return false;
			if (this->tipuri == nullptr && c.tipuri != nullptr) return false;
			if (this->comandaPizza != nullptr && c.comandaPizza != nullptr)
				for (int i = 0; i < this->nrPizza; i++)
					if (!(*this->comandaPizza[i] == *c.comandaPizza[i])) return false;
			if (this->cantitatiCerutePizza != nullptr && c.cantitatiCerutePizza != nullptr)
				for (int i = 0; i < this->nrPizza; i++)
					if (this->cantitatiCerutePizza[i] != c.cantitatiCerutePizza[i]) return false;
			if (this->tipuri != nullptr && c.tipuri != nullptr)
				for (int i = 0; i < this->nrPizza; i++)
					if (this->tipuri[i] != c.tipuri[i]) return false;
			if (this->buget != c.buget) return false;
			if (this->restaurant != c.restaurant) return false;
			return true;
		}
		return true;
	}
};

class Trattorie {
private:
	string denumire = "N/A";
	string administrator = "N/A";
	string adresa = "N/A";
	char* telefon = nullptr;
	char* mail = nullptr;
	int oraIncepereProgram = 12;
	int oraTerminareProgram = 24;
	float rating = 0;
	MateriePrima** stoc = nullptr;
	int dimStoc = 0;
	Produs** meniuDeBaza = nullptr;
	int dimMeniuDeBaza = 0;
	Pizza** meniuPizza = nullptr;
	int dimMeniuPizza = 0;
	Client** clienti = nullptr;
	int dimClienti = 0;
	//int nrMese = 0;
public:
	Trattorie() {}
	Trattorie(string denumire, string administrator, string adresa, const char* telefon, const char* mail, int oraIncepereProgram, int oraTerminareProgram, float rating,
		MateriePrima** stoc, int dimStoc, Produs** meniuDeBaza, int dimMeniuDeBaza, Pizza** meniuPizza, int dimMeniuPizza, Client** clienti, int dimClienti) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		else throw new Exceptie("Denumirea trattoriei nu poate sa fie nula!");
		if (administrator.length() > 0)
			this->administrator = administrator;
		else throw new Exceptie("Numele administratorului trattoriei nu poate sa fie nul!");
		if (adresa.length() > 0)
			this->adresa = adresa;
		else throw new Exceptie("Adresa trattoriei nu poate sa fie nula!");
		if (telefon != nullptr && strlen(telefon) > 0) {
			this->telefon = new char[strlen(telefon) + 1];
			strcpy(this->telefon, telefon);
		}
		else
			throw new Exceptie("Telefonul de contact al trattoriei nu poate sa fie nul!");
		if (mail != nullptr && strlen(mail) > 0) {
			this->mail = new char[strlen(mail) + 1];
			strcpy(this->mail, mail);
		}
		else
			throw new Exceptie("Mail-ul al trattoriei nu poate sa fie nul!");
		if (oraIncepereProgram >= 0 && oraIncepereProgram <= 24)
			this->oraIncepereProgram = oraIncepereProgram;
		else throw new Exceptie("Ora de incepere a programului trattoriei trebuie sa fie intre 0 si 24!");
		if (oraTerminareProgram >= 0 && oraTerminareProgram <= 24)
			this->oraTerminareProgram = oraTerminareProgram;
		else throw new Exceptie("Ora de terminare a programului trattoriei trebuie sa fie intre 0 si 24!");
		if (rating >= 0.0f && rating <= 5.0f)
			this->rating = rating;
		else throw new Exceptie("Rating-ul trattoriei trebuie sa fie cuprins intre 0 si 5 stele!");
		if (dimStoc > 0) {
			this->dimStoc = dimStoc;
			if (stoc != nullptr) {
				this->stoc = new MateriePrima * [this->dimStoc];
				for (int i = 0; i < this->dimStoc; i++)
					this->stoc[i] = stoc[i];
			}
			else throw new Exceptie("Lista materiilor prime ale trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Dimensiunea stocului trattoriei trebuie sa fie pozitiva!");
		if (dimMeniuDeBaza > 0) {
			this->dimMeniuDeBaza = dimMeniuDeBaza;
			if (meniuDeBaza != nullptr) {
				this->meniuDeBaza = new Produs * [this->dimMeniuDeBaza];
				for (int i = 0; i < this->dimMeniuDeBaza; i++)
					this->meniuDeBaza[i] = meniuDeBaza[i];
			}
			else throw new Exceptie("Lista produselor trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Numarul produselor trattoriei trebuie sa fie pozitiv!");
		if (dimMeniuPizza > 0) {
			this->dimMeniuPizza = dimMeniuPizza;
			if (meniuPizza != nullptr) {
				this->meniuPizza = new Pizza * [this->dimMeniuPizza];
				for (int i = 0; i < this->dimMeniuPizza; i++)
					this->meniuPizza[i] = meniuPizza[i];
			}
			else throw new Exceptie("Lista pizzelor trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Numarul pizzelor trattoriei trebuie sa fie pozitiv!");
		if (dimClienti >= 0) {
			if (dimClienti > 0 && clienti != nullptr) {
				this->dimClienti = dimClienti;
				this->clienti = new Client * [this->dimClienti];
				for (int i = 0; i < this->dimClienti; i++)
					this->clienti[i] = clienti[i];
			}
			else if (dimClienti > 0 && clienti == nullptr) throw new Exceptie("Lista clientilor trattoriei nu poate sa fie nula pentru un numar de clienti pozitiv!");
		}
		else throw new Exceptie("Numarul clientilor trattoriei trebuie sa fie nenegativ!");
	}
	Trattorie(string denumire, string administrator, string adresa) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		else throw new Exceptie("Denumirea trattoriei nu poate sa fie nula!");
		if (administrator.length() > 0)
			this->administrator = administrator;
		else throw new Exceptie("Numele administratorului trattoriei nu poate sa fie nul!");
		if (adresa.length() > 0)
			this->adresa = adresa;
		else throw new Exceptie("Adresa trattoriei nu poate sa fie nula!");
	}
	Trattorie(const Trattorie& t) {
		if (t.denumire.length() > 0)
			this->denumire = t.denumire;
		else throw new Exceptie("Denumirea trattoriei nu poate sa fie nula!");
		if (t.administrator.length() > 0)
			this->administrator = t.administrator;
		else throw new Exceptie("Numele administratorului trattoriei nu poate sa fie nul!");
		if (t.adresa.length() > 0)
			this->adresa = t.adresa;
		else throw new Exceptie("Adresa trattoriei nu poate sa fie nula!");
		if (t.telefon != nullptr && strlen(t.telefon) > 0) {
			this->telefon = new char[strlen(t.telefon) + 1];
			strcpy(this->telefon, t.telefon);
		}
		else
			throw new Exceptie("Telefonul de contact al trattoriei nu poate sa fie nul!");
		if (t.mail != nullptr && strlen(t.mail) > 0) {
			this->mail = new char[strlen(t.mail) + 1];
			strcpy(this->mail, t.mail);
		}
		else
			throw new Exceptie("Mail-ul al trattoriei nu poate sa fie nul!");
		if (t.oraIncepereProgram >= 0 && t.oraIncepereProgram <= 24)
			this->oraIncepereProgram = t.oraIncepereProgram;
		else throw new Exceptie("Ora de incepere a programului trattoriei trebuie sa fie intre 0 si 24!");
		if (t.oraTerminareProgram >= 0 && t.oraTerminareProgram <= 24)
			this->oraTerminareProgram = t.oraTerminareProgram;
		else throw new Exceptie("Ora de terminare a programului trattoriei trebuie sa fie intre 0 si 24!");
		if (t.rating >= 0.0f && t.rating <= 5.0f)
			this->rating = t.rating;
		else throw new Exceptie("Rating-ul trattoriei trebuie sa fie cuprins intre 0 si 5 stele!");
		if (t.dimStoc > 0) {
			this->dimStoc = t.dimStoc;
			if (t.stoc != nullptr) {
				this->stoc = new MateriePrima * [this->dimStoc];
				for (int i = 0; i < this->dimStoc; i++)
					this->stoc[i] = t.stoc[i];
			}
			else throw new Exceptie("Lista materiilor prime ale trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Dimensiunea stocului trattoriei trebuie sa fie pozitiva!");
		if (t.dimMeniuDeBaza > 0) {
			this->dimMeniuDeBaza = t.dimMeniuDeBaza;
			if (t.meniuDeBaza != nullptr) {
				this->meniuDeBaza = new Produs * [this->dimMeniuDeBaza];
				for (int i = 0; i < this->dimMeniuDeBaza; i++)
					this->meniuDeBaza[i] = t.meniuDeBaza[i];
			}
			else throw new Exceptie("Lista produselor trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Numarul produselor trattoriei trebuie sa fie pozitiv!");
		if (t.dimMeniuPizza > 0) {
			this->dimMeniuPizza = t.dimMeniuPizza;
			if (t.meniuPizza != nullptr) {
				this->meniuPizza = new Pizza * [this->dimMeniuPizza];
				for (int i = 0; i < this->dimMeniuPizza; i++)
					this->meniuPizza[i] = t.meniuPizza[i];
			}
			else throw new Exceptie("Lista pizzelor trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Numarul pizzelor trattoriei trebuie sa fie pozitiv!");
		if (t.dimClienti >= 0) {
			if (t.dimClienti > 0 && t.clienti != nullptr) {
				this->dimClienti = t.dimClienti;
				this->clienti = new Client * [this->dimClienti];
				for (int i = 0; i < this->dimClienti; i++)
					this->clienti[i] = t.clienti[i];
			}
			else if (t.dimClienti > 0 && t.clienti == nullptr) throw new Exceptie("Lista clientilor trattoriei nu poate sa fie nula pentru un numar de clienti pozitiv!");
		}
		else throw new Exceptie("Numarul clientilor trattoriei trebuie sa fie nenegativ!");
	}
	~Trattorie() {
		delete[] this->telefon;
		this->telefon = nullptr;
		delete[] this->mail;
		this->mail = nullptr;
		delete[] this->stoc;
		this->stoc = nullptr;
		delete[] this->meniuDeBaza;
		this->meniuDeBaza = nullptr;
		delete[] this->meniuPizza;
		this->meniuPizza = nullptr;
		delete[] this->clienti;
		this->clienti = nullptr;
	}
	Trattorie& operator=(const Trattorie& t) {
		if (this != &t) {
			delete[] this->telefon;
			this->telefon = nullptr;
			delete[] this->mail;
			this->mail = nullptr;
			delete[] this->stoc;
			this->stoc = nullptr;
			delete[] this->meniuDeBaza;
			this->meniuDeBaza = nullptr;
			delete[] this->meniuPizza;
			this->meniuPizza = nullptr;
			delete[] this->clienti;
			this->clienti = nullptr;

			if (t.denumire.length() > 0)
				this->denumire = t.denumire;
			else throw new Exceptie("Denumirea trattoriei nu poate sa fie nula!");
			if (t.administrator.length() > 0)
				this->administrator = t.administrator;
			else throw new Exceptie("Numele administratorului trattoriei nu poate sa fie nul!");
			if (t.adresa.length() > 0)
				this->adresa = t.adresa;
			else throw new Exceptie("Adresa trattoriei nu poate sa fie nula!");
			if (t.telefon != nullptr && strlen(t.telefon) > 0) {
				this->telefon = new char[strlen(t.telefon) + 1];
				strcpy(this->telefon, t.telefon);
			}
			else
				throw new Exceptie("Telefonul de contact al trattoriei nu poate sa fie nul!");
			if (t.mail != nullptr && strlen(t.mail) > 0) {
				this->mail = new char[strlen(t.mail) + 1];
				strcpy(this->mail, t.mail);
			}
			else
				throw new Exceptie("Mail-ul al trattoriei nu poate sa fie nul!");
			if (t.oraIncepereProgram >= 0 && t.oraIncepereProgram <= 24)
				this->oraIncepereProgram = t.oraIncepereProgram;
			else throw new Exceptie("Ora de incepere a programului trattoriei trebuie sa fie intre 0 si 24!");
			if (t.oraTerminareProgram >= 0 && t.oraTerminareProgram <= 24)
				this->oraTerminareProgram = t.oraTerminareProgram;
			else throw new Exceptie("Ora de terminare a programului trattoriei trebuie sa fie intre 0 si 24!");
			if (t.rating >= 0.0f && t.rating <= 5.0f)
				this->rating = t.rating;
			else throw new Exceptie("Rating-ul trattoriei trebuie sa fie cuprins intre 0 si 5 stele!");
			if (t.dimStoc > 0) {
				this->dimStoc = t.dimStoc;
				if (t.stoc != nullptr) {
					this->stoc = new MateriePrima * [this->dimStoc];
					for (int i = 0; i < this->dimStoc; i++)
						this->stoc[i] = t.stoc[i];
				}
				else throw new Exceptie("Lista materiilor prime ale trattoriei nu poate sa fie nula!");
			}
			else throw new Exceptie("Dimensiunea stocului trattoriei trebuie sa fie pozitiva!");
			if (t.dimMeniuDeBaza > 0) {
				this->dimMeniuDeBaza = t.dimMeniuDeBaza;
				if (t.meniuDeBaza != nullptr) {
					this->meniuDeBaza = new Produs * [this->dimMeniuDeBaza];
					for (int i = 0; i < this->dimMeniuDeBaza; i++)
						this->meniuDeBaza[i] = t.meniuDeBaza[i];
				}
				else throw new Exceptie("Lista produselor trattoriei nu poate sa fie nula!");
			}
			else throw new Exceptie("Numarul produselor trattoriei trebuie sa fie pozitiv!");
			if (t.dimMeniuPizza > 0) {
				this->dimMeniuPizza = t.dimMeniuPizza;
				if (t.meniuPizza != nullptr) {
					this->meniuPizza = new Pizza * [this->dimMeniuPizza];
					for (int i = 0; i < this->dimMeniuPizza; i++)
						this->meniuPizza[i] = t.meniuPizza[i];
				}
				else throw new Exceptie("Lista pizzelor trattoriei nu poate sa fie nula!");
			}
			else throw new Exceptie("Numarul pizzelor trattoriei trebuie sa fie pozitiv!");
			if (t.dimClienti >= 0) {
				this->dimClienti = t.dimClienti;
				if (this->dimClienti > 0 && t.clienti != nullptr) {
					this->clienti = new Client * [this->dimClienti];
					for (int i = 0; i < this->dimClienti; i++)
						this->clienti[i] = t.clienti[i];
				}
				else if (this->dimClienti > 0 && t.clienti == nullptr) throw new Exceptie("Lista clientilor trattoriei nu poate sa fie nula pentru un numar de clienti pozitiv!");
			}
			else throw new Exceptie("Numarul clientilor trattoriei trebuie sa fie nenegativ!");
		}
		return *this;
	}
	string getDenumire() {
		return this->denumire;
	}
	void setDenumire(string denumire) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		else throw new Exceptie("Denumirea trattoriei nu poate sa fie nula!");
	}
	string getAdministrator() {
		return this->administrator;
	}
	void setAdministrator(string administrator) {
		if (administrator.length() > 0)
			this->administrator = administrator;
		else throw new Exceptie("Numele administratorului trattoriei nu poate sa fie nul!");
	}
	string getAdresa() {
		return this->adresa;
	}
	void setAdresa(string adresa) {
		if (adresa.length() > 0)
			this->adresa = adresa;
		else throw new Exceptie("Adresa trattoriei nu poate sa fie nula!");
	}
	const char* getTelefon() {
		return this->telefon;
	}
	void setTelefon(const char* telefon) {
		if (telefon != nullptr && strlen(telefon) > 0) {
			delete[] this->telefon;
			this->telefon = new char[strlen(telefon) + 1];
			strcpy(this->telefon, telefon);
		}
		else
			throw new Exceptie("Telefonul de contact al trattoriei nu poate sa fie nul!");
	}
	const char* getMail() {
		return this->mail;
	}
	void setMail(const char* mail) {
		if (mail != nullptr && strlen(mail) > 0) {
			delete[] this->mail;
			this->mail = new char[strlen(mail) + 1];
			strcpy(this->mail, mail);
		}
		else
			throw new Exceptie("Mail-ul al trattoriei nu poate sa fie nul!");
	}
	int getOraIncepereProgram() {
		return this->oraIncepereProgram;
	}
	void setOraIncepereProgram(int oraIncepereProgram) {
		if (oraIncepereProgram >= 0 && oraIncepereProgram <= 24)
			this->oraIncepereProgram = oraIncepereProgram;
		else throw new Exceptie("Ora de incepere a programului trattoriei trebuie sa fie intre 0 si 24!");
	}
	int getOraTerminareProgram() {
		return this->oraTerminareProgram;
	}
	void setOraTerminareProgram(int oraTerminareProgram) {
		if (oraTerminareProgram >= 0 && oraTerminareProgram <= 24)
			this->oraTerminareProgram = oraTerminareProgram;
		else throw new Exceptie("Ora de terminare a programului trattoriei trebuie sa fie intre 0 si 24!");
	}
	float getRating() {
		return this->rating;
	}
	void setRating(float rating) {
		if (rating >= 0.0f && rating <= 5.0f)
			this->rating = rating;
		else throw new Exceptie("Rating-ul trattoriei trebuie sa fie cuprins intre 0 si 5 stele!");
	}
	MateriePrima** getStoc() {
		return this->stoc;
	}
	int getDimStoc() {
		return this->dimStoc;
	}
	void setStoc(int dimStoc, MateriePrima** stoc) {
		if (dimStoc > 0) {
			this->dimStoc = dimStoc;
			if (stoc != nullptr) {
				delete[] this->stoc;
				this->stoc = new MateriePrima * [this->dimStoc];
				for (int i = 0; i < this->dimStoc; i++)
					this->stoc[i] = stoc[i];
			}
			else throw new Exceptie("Lista materiilor prime ale trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Dimensiunea stocului trattoriei trebuie sa fie pozitiva!");
	}
	Produs** getMeniuDeBaza() {
		return this->meniuDeBaza;
	}
	int getDimMeniuDeBaza() {
		return this->dimMeniuDeBaza;
	}
	void setMeniuDeBaza(int dimMeniuDeBaza, Produs** meniuDeBaza) {
		if (dimMeniuDeBaza > 0) {
			this->dimMeniuDeBaza = dimMeniuDeBaza;
			if (meniuDeBaza != nullptr) {
				delete[] this->meniuDeBaza;
				this->meniuDeBaza = new Produs * [this->dimMeniuDeBaza];
				for (int i = 0; i < this->dimMeniuDeBaza; i++)
					this->meniuDeBaza[i] = meniuDeBaza[i];
			}
			else throw new Exceptie("Lista produselor trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Numarul produselor trattoriei trebuie sa fie pozitiv!");
	}
	Pizza** getMeniuPizza() {
		return this->meniuPizza;
	}
	int getDimMeniuPizza() {
		return this->dimMeniuPizza;
	}
	void setMeniuPizza(int dimMeniuPizza, Pizza** meniuPizza) {
		if (dimMeniuPizza > 0) {
			this->dimMeniuPizza = dimMeniuPizza;
			if (meniuPizza != nullptr) {
				delete[] this->meniuPizza;
				this->meniuPizza = new Pizza * [this->dimMeniuPizza];
				for (int i = 0; i < this->dimMeniuPizza; i++)
					this->meniuPizza[i] = meniuPizza[i];
			}
			else throw new Exceptie("Lista pizzelor trattoriei nu poate sa fie nula!");
		}
		else throw new Exceptie("Numarul pizzelor trattoriei trebuie sa fie pozitiv!");
	}
	Client** getClienti() {
		return this->clienti;
	}
	int getDimClienti() {
		return this->dimClienti;
	}
	void setClienti(int dimClienti, Client** clienti) {
		if (dimClienti >= 0) {
			this->dimClienti = dimClienti;
			delete[] this->clienti;
			this->clienti = nullptr;
			if (this->dimClienti > 0 && clienti != nullptr) {
				this->clienti = new Client * [this->dimClienti];
				for (int i = 0; i < this->dimClienti; i++)
					this->clienti[i] = clienti[i];
			}
			else if (this->dimClienti > 0 && clienti == nullptr) throw new Exceptie("Lista clientilor trattoriei nu poate sa fie nula pentru un numar de clienti pozitiv!");
		}
		else throw new Exceptie("Numarul clientilor trattoriei trebuie sa fie nenegativ!");
	}
	bool areProduse() {
		if (this->dimMeniuDeBaza > 0 && this->meniuDeBaza != nullptr) return true;
		if (this->dimMeniuPizza > 0 && this->meniuPizza != nullptr) return true;
		return false;
	}
	float calculPretMinim() {
		float pretMinim1 = 0, pretMinim2 = 0;
		if (this->dimMeniuDeBaza > 0 && this->meniuDeBaza != nullptr) {
			pretMinim1 = this->meniuDeBaza[0]->calculPret();
			for (int i = 1; i < this->dimMeniuDeBaza; i++)
				if (this->meniuDeBaza[i]->calculPret() < pretMinim1) pretMinim1 = this->meniuDeBaza[i]->calculPret();
		}
		if (this->dimMeniuPizza > 0 && this->meniuPizza != nullptr) {
			pretMinim2 = this->meniuPizza[0]->calculPret();
			for (int i = 1; i < this->dimMeniuPizza; i++)
				if (this->meniuPizza[i]->calculPret() < pretMinim2) pretMinim2 = this->meniuPizza[i]->calculPret();
		}
		if (pretMinim1 && pretMinim2 && pretMinim1 < pretMinim2)
			return pretMinim1;
		if (pretMinim1 && pretMinim2 && pretMinim1 > pretMinim2)
			return pretMinim2;
		return 0;
	}
	void actualizareStocuri();
	void afisareMeniu() {
		cout << "Meniu - " << this->denumire << " - ";
		printf("%.1f", this->rating);
		cout << " / 5 stele\n";
		cout << "-------------------------------------------------------------------\n";
		if (this->areProduse() == false) cout << "[ NU EXISTA PRODUSE ]\n";
		else {
			if (this->dimMeniuPizza > 0 && this->meniuPizza != nullptr) {
				cout << "[ PIZZA ]\n\n";
				for (int i = 0; i < this->dimMeniuPizza; i++) {
					this->meniuPizza[i]->afisareProdus();
					cout << "\n";
				}
				if (this->dimMeniuDeBaza > 0 && this->meniuDeBaza != nullptr)
					cout << "\n\n";
			}
			if (this->dimMeniuDeBaza > 0 && this->meniuDeBaza != nullptr) {
				cout << "[ ALTE PRODUSE ]\n\n";
				for (int i = 0; i < this->dimMeniuDeBaza; i++) {
					this->meniuDeBaza[i]->afisareProdus();
					cout << "\n";
				}
			}
		}
		cout << "-------------------------------------------------------------------";
	}
	friend ostream& operator<<(ostream& out, const Trattorie& t) {
		out << "Denumire: " << t.denumire << " ";
		out << "| Administrator: " << t.administrator << " ";
		out << "| Adresa: " << t.adresa << " ";
		out << "| Telefon: ";
		if (t.telefon != nullptr)
			out << t.telefon << " ";
		else out << "N/A ";
		out << "| Mail: ";
		if (t.mail != nullptr)
			out << t.mail;
		else out << "N/A";
		out << "\nOra incepere program: " << t.oraIncepereProgram << " ";
		out << "| Ora terminare program: " << t.oraTerminareProgram << " ";
		out << "| Rating: " << t.rating;
		out << "\nNr materii prime pe stoc: " << t.dimStoc;
		if (t.dimStoc > 0 && t.stoc != nullptr)
			for (int i = 0; i < t.dimStoc; i++)
				out << "\n  " << *t.stoc[i];
		out << "\nNr pizza din meniu: " << t.dimMeniuPizza;
		if (t.dimMeniuPizza > 0 && t.meniuPizza != nullptr)
			for (int i = 0; i < t.dimMeniuPizza; i++)
				out << "\n  " << *t.meniuPizza[i];
		out << "\nNr produse din meniu: " << t.dimMeniuDeBaza;
		if (t.dimMeniuDeBaza > 0 && t.meniuDeBaza != nullptr)
			for (int i = 0; i < t.dimMeniuDeBaza; i++)
				out << "\n  " << *t.meniuDeBaza[i];
		out << "\nNr clienti: " << t.dimClienti;
		if (t.dimClienti > 0 && t.clienti != nullptr)
			for (int i = 0; i < t.dimClienti; i++)
				out << "\n  " << *t.clienti[i];
		return out;
	}
	void operator>>(istream& in) {
		delete[] this->telefon;
		this->telefon = nullptr;
		delete[] this->mail;
		this->mail = nullptr;
		delete[] this->stoc;
		this->stoc = nullptr;
		delete[] this->meniuDeBaza;
		this->meniuDeBaza = nullptr;
		delete[] this->meniuPizza;
		this->meniuPizza = nullptr;
		delete[] this->clienti;
		this->clienti = nullptr;

		string buffer;
		cout << "Denumire trattorie: ";
		getline(cin, buffer);
		if (buffer.length() > 0) this->denumire = buffer;
		else throw new Exceptie("Denumirea trattoriei nu poate fi nula!");
		cout << "Administratorul trattoriei: ";
		getline(cin, buffer);
		if (buffer.length() > 0) this->administrator = buffer;
		else throw new Exceptie("Numele administratorului trattoriei nu poate fi nul!");
		cout << "Adresa trattoriei: ";
		getline(cin, buffer);
		if (buffer.length() > 0) this->adresa = buffer;
		else throw new Exceptie("Adresa trattoriei nu poate fi nula!");
		cout << "Telefonul trattoriei: ";
		getline(cin, buffer);
		if (buffer.length() > 0) {
			this->telefon = new char[buffer.length() + 1];
			strcpy(this->telefon, buffer.data());
		}
		else throw new Exceptie("Telefonul trattoriei nu poate fi nul!");
		cout << "Mail-ul trattoriei: ";
		getline(cin, buffer);
		if (buffer.length() > 0) {
			this->mail = new char[buffer.length() + 1];
			strcpy(this->mail, buffer.data());
		}
		else throw new Exceptie("Mail-ul trattoriei nu poate fi nul!");
		cout << "Ora incepere program: ";
		in >> this->oraIncepereProgram;
		cout << "Ora terminare program: ";
		in >> this->oraTerminareProgram;
		cout << "Rating trattorie: ";
		in >> this->rating;
		cout << "Dimensiunea stocului trattoriei: ";
		in >> this->dimStoc;
		if (this->dimStoc > 0) {
			this->stoc = new MateriePrima * [this->dimStoc];
			for (int i = 0; i < this->dimStoc; i++) {
				this->stoc[i] = new MateriePrima;
				*this->stoc[i] >> in;
			}
		}
		cout << "Dimensiunea meniului de baza: ";
		in >> this->dimMeniuDeBaza;
		if (this->dimMeniuDeBaza > 0) {
			this->meniuDeBaza = new Produs * [this->dimMeniuDeBaza];
			for (int i = 0; i < this->dimMeniuDeBaza; i++) {
				this->meniuDeBaza[i] = new Produs;
				*this->meniuDeBaza[i] >> in;
			}
		}
		cout << "Dimensiunea meniului de pizza: ";
		in >> this->dimMeniuPizza;
		if (this->dimMeniuPizza > 0) {
			this->meniuPizza = new Pizza * [this->dimMeniuPizza];
			for (int i = 0; i < this->dimMeniuPizza; i++) {
				this->meniuPizza[i] = new Pizza;
				*this->meniuPizza[i] >> in;
			}
		}
		this->dimClienti = 0;
	}
	MateriePrima operator[](int index) {
		if (index >= 0 && index < this->dimStoc && this->stoc != nullptr)
			return *this->stoc[index];
		else throw new Exceptie("Nu exista materie prima in stoc la indexul dat!");
	}
	Trattorie operator+(float rating) {
		if (rating >= 0) {
			Trattorie rez = *this;
			if (rez.rating + rating <= 5)
				rez.rating += rating;
			else throw new Exceptie("Rating-ul nu poate fi mai mare decat 5!");
			return rez;
		}
		else throw new Exceptie("Rating-ul adaugat trebuie sa fie nenegativ!");
	}
	Trattorie operator-(float rating) {
		if (rating >= 0) {
			Trattorie rez = *this;
			if (rez.rating - rating >= 0)
				rez.rating -= rating;
			else throw new Exceptie("Rating-ul nu poate fi mai mic decat 0!");
			return rez;
		}
		else throw new Exceptie("Rating-ul scazut trebuie sa fie nenegativ!");
	}
	Trattorie operator*(float rating) {
		if (rating >= 0) {
			Trattorie rez = *this;
			if (rez.rating + rating <= 5)
				rez.rating *= rating;
			else throw new Exceptie("Rating-ul nu poate fi mai mare decat 5!");
			return rez;
		}
		else throw new Exceptie("Rating-ul de inmultit trebuie sa fie nenegativ!");
	}
	Trattorie operator/(float rating) {
		if (rating > 0) {
			Trattorie rez = *this;
			if (rez.rating + rating <= 5)
				rez.rating /= rating;
			else throw new Exceptie("Rating-ul nu poate fi mai mare decat 5!");
			return rez;
		}
		else throw new Exceptie("Rating-ul de impartit trebuie sa fie pozitiv!");
	}
	Trattorie& operator++() {
		if (this->rating + 1 <= 5) {
			this->rating++;
			return *this;
		}
		else throw new Exceptie("Ratingul nu poate fi mai mare decat 5!");
	}
	Trattorie operator++(int) {
		if (this->rating + 1 <= 5) {
			Trattorie copie = *this;
			this->rating++;
			return copie;
		}
		else throw new Exceptie("Ratingul nu poate fi mai mare decat 5!");
	}
	Trattorie& operator--() {
		if (this->rating - 1 >= 0) {
			this->rating--;
			return *this;
		}
		else throw new Exceptie("Ratingul nu poate fi mai mic decat 0!");
	}
	Trattorie operator--(int) {
		if (this->rating - 1 >= 0) {
			Trattorie copie = *this;
			this->rating--;
			return copie;
		}
		else throw new Exceptie("Ratingul nu poate fi mai mic decat 0!");
	}
	explicit operator float() {
		return this->rating;
	}
	bool operator!() {
		if (this->rating) return false;
		return true;
	}
	bool operator<(const Trattorie& t) {
		if (this != &t) {
			if (this->rating < t.rating) return true;
			return false;
		}
		return false;
	}
	bool operator<=(const Trattorie& t) {
		if (this != &t) {
			if (this->rating <= t.rating) return true;
			return false;
		}
		return true;
	}
	bool operator>(const Trattorie& t) {
		if (this != &t) {
			if (this->rating > t.rating) return true;
			return false;
		}
		return false;
	}
	bool operator>=(const Trattorie& t) {
		if (this != &t) {
			if (this->rating >= t.rating) return true;
			return false;
		}
		return true;
	}
	bool operator==(const Trattorie& t) {
		if (this != &t) {
			if (this->denumire != t.denumire) return false;
			if (this->administrator != t.administrator) return false;
			if (this->adresa != t.adresa) return false;
			if (strcmp(this->telefon, t.telefon) != 0) return false;
			if (strcmp(this->mail, t.mail) != 0) return false;
			if (this->oraIncepereProgram != t.oraIncepereProgram) return false;
			if (this->oraTerminareProgram != t.oraTerminareProgram) return false;
			if (this->rating != t.rating) return false;
			if (this->dimStoc != t.dimStoc) return false;
			if (this->stoc == nullptr && t.stoc != nullptr) return false;
			if (this->stoc != nullptr && t.stoc == nullptr) return false;
			if (this->stoc != nullptr && t.stoc != nullptr)
				for (int i = 0; i < this->dimStoc; i++)
					if (!(*this->stoc[i] == *t.stoc[i])) return false;
			if (this->dimMeniuDeBaza != t.dimMeniuDeBaza) return false;
			if (this->meniuDeBaza == nullptr && t.meniuDeBaza != nullptr) return false;
			if (this->meniuDeBaza != nullptr && t.meniuDeBaza == nullptr) return false;
			if (this->meniuDeBaza != nullptr && t.meniuDeBaza != nullptr)
				for (int i = 0; i < this->dimMeniuDeBaza; i++)
					if (!(*this->meniuDeBaza[i] == *t.meniuDeBaza[i])) return false;
			if (this->dimMeniuPizza != t.dimMeniuPizza) return false;
			if (this->meniuPizza == nullptr && t.meniuPizza != nullptr) return false;
			if (this->meniuPizza != nullptr && t.meniuPizza == nullptr) return false;
			if (this->meniuPizza != nullptr && t.meniuPizza != nullptr)
				for (int i = 0; i < this->dimMeniuPizza; i++)
					if (!(*this->meniuPizza[i] == *t.meniuPizza[i])) return false;
			if (this->dimClienti != t.dimClienti) return false;
			if (this->clienti == nullptr && t.clienti != nullptr) return false;
			if (this->clienti != nullptr && t.clienti == nullptr) return false;
			if (this->clienti != nullptr && t.clienti != nullptr)
				for (int i = 0; i < this->dimClienti; i++)
					if (this->clienti[i] != t.clienti[i]) return false;
			return true;
		}
		return true;
	}
};

string Client::pizzaSauProdusMENIU(int id) {
	if (id < 0) id *= -1;
	Produs* referinta1 = nullptr;
	Pizza* referinta2 = nullptr;
	string rez = "-";
	if (this->restaurant->areProduse()) {
		if (this->restaurant->getDimMeniuDeBaza() > 0 && this->restaurant->getMeniuDeBaza() != nullptr) {
			for (int i = 0; i < this->restaurant->getDimMeniuDeBaza() && referinta1 == nullptr; i++)
				if (id == this->restaurant->getMeniuDeBaza()[i]->getID()) {
					referinta1 = this->restaurant->getMeniuDeBaza()[i];
					rez = "PRODUS";
				}
		}
		if (this->restaurant->getDimMeniuPizza() > 0 && this->restaurant->getMeniuPizza() != nullptr) {
			for (int i = 0; i < this->restaurant->getDimMeniuPizza() && referinta2 == nullptr; i++)
				if (id == this->restaurant->getMeniuPizza()[i]->getID()) {
					referinta2 = this->restaurant->getMeniuPizza()[i];
					rez = "PIZZA";
				}
		}
	}
	else throw new Exceptie("Restaurantul nu are produse sau pizza!");
	referinta1 = nullptr;
	referinta2 = nullptr;
	return rez;
}
string Client::pizzaSauProdusCOMANDA(int id) {
	if (id < 0) id *= -1;
	Produs* referinta1 = nullptr;
	Pizza* referinta2 = nullptr;
	string rez = "-";
	if (this->areComanda()) {
		if (this->nrProduse > 0 && this->comandaProduse != nullptr && this->cantitatiCeruteProduse != nullptr) {
			for (int i = 0; i < this->nrProduse && referinta1 == nullptr; i++)
				if (id == this->comandaProduse[i]->getID()) {
					referinta1 = this->comandaProduse[i];
					rez = "PRODUS";
				}
		}
		if (this->nrPizza > 0 && this->comandaPizza != nullptr && this->cantitatiCerutePizza != nullptr) {
			for (int i = 0; i < this->nrPizza && referinta2 == nullptr; i++)
				if (id == this->comandaPizza[i]->getID()) {
					referinta2 = this->comandaPizza[i];
					rez = "PIZZA";
				}
		}
	}
	else rez = "-";
	referinta1 = nullptr;
	referinta2 = nullptr;
	return rez;
}
void Client::adaugaProdus(int id, float cantitateCeruta) {
	if (cantitateCeruta > 0) {
		if (id < 0) id *= -1;
		Produs* referinta = nullptr;
		if (this->restaurant->areProduse()) {
			if (this->restaurant->getDimMeniuDeBaza() > 0 && this->restaurant->getMeniuDeBaza() != nullptr) {
				for (int i = 0; i < this->restaurant->getDimMeniuDeBaza() && referinta == nullptr; i++)
					if (id == this->restaurant->getMeniuDeBaza()[i]->getID())
						referinta = this->restaurant->getMeniuDeBaza()[i];
			}
		}
		else throw new Exceptie("Restaurantul nu are produse!");
		if (referinta == nullptr) throw new Exceptie("Nu s-a gasit niciun produs cu ID-ul dat!");
		else {
			if (this->nrProduse > 0 && this->comandaProduse != nullptr && this->cantitatiCeruteProduse != nullptr) {
				bool gasit = false; int index = -1;
				for (int i = 0; i < this->nrProduse && !gasit; i++)
					if (id == this->comandaProduse[i]->getID()) {
						gasit = true;
						index = i;
					}
				if (gasit) {
					this->cantitatiCeruteProduse[index] += cantitateCeruta;
				}
				else {
					Produs** copieComanda = new Produs * [this->nrProduse];
					float* copieCantitati = new float[this->nrProduse];
					for (int i = 0; i < this->nrProduse; i++) {
						copieComanda[i] = this->comandaProduse[i];
						copieCantitati[i] = this->cantitatiCeruteProduse[i];
					}
					delete[] this->comandaProduse;
					delete[] this->cantitatiCeruteProduse;
					this->nrProduse++;
					this->comandaProduse = new Produs * [this->nrProduse];
					this->cantitatiCeruteProduse = new float[this->nrProduse];
					for (int i = 0; i < this->nrProduse - 1; i++) {
						this->comandaProduse[i] = copieComanda[i];
						this->cantitatiCeruteProduse[i] = copieCantitati[i];
					}
					this->comandaProduse[this->nrProduse - 1] = referinta;
					this->cantitatiCeruteProduse[this->nrProduse - 1] = cantitateCeruta;
					delete[] copieComanda;
					copieComanda = nullptr;
					delete[] copieCantitati;
					copieCantitati = nullptr;
				}
			}
			else if (this->nrProduse == 0 && this->comandaProduse == nullptr && this->cantitatiCeruteProduse == nullptr) {
				this->nrProduse++;
				this->comandaProduse = new Produs * [this->nrProduse];
				this->cantitatiCeruteProduse = new float[this->nrProduse];
				this->comandaProduse[0] = referinta;
				this->cantitatiCeruteProduse[0] = cantitateCeruta;
			}
			else throw new Exceptie("Comanda corupta!");
		}
		referinta = nullptr;
	}
	else throw new Exceptie("Cantitatea ceruta din produsul adaugat trebuie sa fie pozitiva!");
}
void Client::eliminaProdus(int id, int cantitateEliminata) {
	if (cantitateEliminata > 0) {
		if (id < 0) id *= -1;
		Produs* referinta = nullptr;
		if (this->restaurant->areProduse()) {
			if (this->restaurant->getDimMeniuDeBaza() > 0 && this->restaurant->getMeniuDeBaza() != nullptr) {
				for (int i = 0; i < this->restaurant->getDimMeniuDeBaza() && referinta == nullptr; i++)
					if (id == this->restaurant->getMeniuDeBaza()[i]->getID())
						referinta = this->restaurant->getMeniuDeBaza()[i];
			}
		}
		else throw new Exceptie("Restaurantul nu are produse!");
		if (referinta == nullptr) throw new Exceptie("Nu s-a gasit niciun produs cu ID-ul dat!");
		else {
			if (this->nrProduse > 0 && this->comandaProduse != nullptr && this->cantitatiCeruteProduse != nullptr) {
				bool gasit = false; int index = -1;
				for (int i = 0; i < this->nrProduse && !gasit; i++)
					if (id == this->comandaProduse[i]->getID()) {
						gasit = true;
						index = i;
					}
				if (gasit) {
					if (this->cantitatiCeruteProduse[index] > cantitateEliminata)
						this->cantitatiCeruteProduse[index] -= cantitateEliminata;
					else {
						if (this->nrProduse == 1) {
							this->nrProduse = 0;
							delete[] this->comandaProduse;
							this->comandaProduse = nullptr;
							delete[] this->cantitatiCeruteProduse;
							this->cantitatiCeruteProduse = nullptr;
						}
						else {
							Produs** copieComanda = new Produs * [this->nrProduse];
							float* copieCantitati = new float[this->nrProduse];
							for (int i = 0; i < this->nrProduse; i++) {
								copieComanda[i] = this->comandaProduse[i];
								copieCantitati[i] = this->cantitatiCeruteProduse[i];
							}
							delete[] this->comandaProduse;
							delete[] this->cantitatiCeruteProduse;
							this->nrProduse--;
							this->comandaProduse = new Produs * [this->nrProduse];
							this->cantitatiCeruteProduse = new float[this->nrProduse];
							for (int i = 0; i < index; i++) {
								this->comandaProduse[i] = copieComanda[i];
								this->cantitatiCeruteProduse[i] = copieCantitati[i];
							}
							for (int j = index; j < this->nrProduse; j++) {
								this->comandaProduse[j] = copieComanda[j + 1];
								this->cantitatiCeruteProduse[j] = copieCantitati[j + 1];
							}
							delete[] copieComanda;
							copieComanda = nullptr;
							delete[] copieCantitati;
							copieCantitati = nullptr;
						}
					}
				}
				else throw new Exceptie("Nu s-a gasit produsul cu ID-ul dat!");
			}
			else if (this->nrProduse == 0 && this->comandaProduse == nullptr && this->cantitatiCeruteProduse == nullptr)
				throw new Exceptie("Nu se pot elimina produse dintr-o comanda nula!");
			else throw new Exceptie("Comanda corupta!");
		}
		referinta = nullptr;
	}
	else throw new Exceptie("Cantitatea eliminata din produsul adaugat trebuie sa fie pozitiva!");
}
void Client::adaugaPizza(int id, float cantitateCeruta, TipBlat tip) {
	if (cantitateCeruta > 0) {
		if (id < 0) id *= -1;
		Pizza* referinta = nullptr;
		if (this->restaurant->areProduse()) {
			if (this->restaurant->getDimMeniuPizza() > 0 && this->restaurant->getMeniuPizza() != nullptr) {
				for (int i = 0; i < this->restaurant->getDimMeniuPizza() && referinta == nullptr; i++)
					if (id == this->restaurant->getMeniuPizza()[i]->getID())
						referinta = this->restaurant->getMeniuPizza()[i];
			}
		}
		else throw new Exceptie("Restaurantul nu are pizza!");
		if (referinta == nullptr) throw new Exceptie("Nu s-a gasit nicio pizza cu ID-ul dat!");
		else {
			if (this->nrPizza > 0 && this->comandaPizza != nullptr && this->cantitatiCerutePizza != nullptr) {
				bool gasit = false; int index = -1;
				for (int i = 0; i < this->nrPizza && !gasit; i++)
					if (id == this->comandaPizza[i]->getID()) {
						gasit = true;
						index = i;
					}
				if (gasit) {
					this->cantitatiCerutePizza[index] += cantitateCeruta;
				}
				else {
					Pizza** copieComanda = new Pizza * [this->nrPizza];
					float* copieCantitati = new float[this->nrPizza];
					TipBlat* copieTip = new TipBlat[this->nrPizza];
					for (int i = 0; i < this->nrPizza; i++) {
						copieComanda[i] = this->comandaPizza[i];
						copieCantitati[i] = this->cantitatiCerutePizza[i];
						copieTip[i] = this->tipuri[i];
					}
					delete[] this->comandaPizza;
					delete[] this->cantitatiCerutePizza;
					delete[] this->tipuri;
					this->nrPizza++;
					this->comandaPizza = new Pizza * [this->nrPizza];
					this->cantitatiCerutePizza = new float[this->nrPizza];
					this->tipuri = new TipBlat[this->nrPizza];
					for (int i = 0; i < this->nrPizza - 1; i++) {
						this->comandaPizza[i] = copieComanda[i];
						this->cantitatiCerutePizza[i] = copieCantitati[i];
						this->tipuri[i] = copieTip[i];
					}
					this->comandaPizza[this->nrPizza - 1] = referinta;
					this->cantitatiCerutePizza[this->nrPizza - 1] = cantitateCeruta;

					if (referinta->getNrOptiuniBlat() > 0 && referinta->getOptiuniBlat() != nullptr) {
						int ok = 0;
						for (int i = 0; i < referinta->getNrOptiuniBlat() && !ok; i++)
							if (referinta->getOptiuniBlat()[i] == tip) {
								ok = 1;
								this->tipuri[this->nrPizza - 1] = tip;
							}
						if (!ok) {
							ok = 0;
							for (int i = 0; i < referinta->getNrOptiuniBlat() && !ok; i++)
								if (referinta->getOptiuniBlat()[i] == TipBlat::SUBTIRE) {
									ok = 1;
									this->tipuri[this->nrPizza - 1] = TipBlat::SUBTIRE;
								}
							if (!ok) {
								ok = 0;
								for (int i = 0; i < referinta->getNrOptiuniBlat() && !ok; i++)
									if (referinta->getOptiuniBlat()[i] == TipBlat::NORMAL) {
										ok = 1;
										this->tipuri[this->nrPizza - 1] = TipBlat::NORMAL;
									}
								if (!ok) this->tipuri[this->nrPizza - 1] = TipBlat::PUFOS;
							}
						}
					}
					else this->tipuri[this->nrPizza - 1] = TipBlat::SUBTIRE;

					delete[] copieComanda;
					copieComanda = nullptr;
					delete[] copieCantitati;
					copieCantitati = nullptr;
				}
			}
			else if (this->nrPizza == 0 && this->comandaPizza == nullptr && this->cantitatiCerutePizza == nullptr) {
				this->nrPizza++;
				this->comandaPizza = new Pizza * [this->nrPizza];
				this->cantitatiCerutePizza = new float[this->nrPizza];
				this->tipuri = new TipBlat[this->nrPizza];
				this->comandaPizza[0] = referinta;
				this->cantitatiCerutePizza[0] = cantitateCeruta;

				if (referinta->getNrOptiuniBlat() > 0 && referinta->getOptiuniBlat() != nullptr) {
					int ok = 0;
					for (int i = 0; i < referinta->getNrOptiuniBlat() && !ok; i++)
						if (referinta->getOptiuniBlat()[i] == tip) {
							ok = 1;
							this->tipuri[0] = tip;
						}
					if (!ok) {
						ok = 0;
						for (int i = 0; i < referinta->getNrOptiuniBlat() && !ok; i++)
							if (referinta->getOptiuniBlat()[i] == TipBlat::SUBTIRE) {
								ok = 1;
								this->tipuri[0] = TipBlat::SUBTIRE;
							}
						if (!ok) {
							ok = 0;
							for (int i = 0; i < referinta->getNrOptiuniBlat() && !ok; i++)
								if (referinta->getOptiuniBlat()[i] == TipBlat::NORMAL) {
									ok = 1;
									this->tipuri[0] = TipBlat::NORMAL;
								}
							if (!ok) this->tipuri[0] = TipBlat::PUFOS;
						}
					}
				}
				else this->tipuri[0] = TipBlat::SUBTIRE;

			}
			else throw new Exceptie("Comanda corupta!");
		}
		referinta = nullptr;
	}
	else throw new Exceptie("Cantitatea ceruta din pizza adaugata trebuie sa fie pozitiva!");
}
void Client::eliminaPizza(int id, int cantitateEliminata) {
	if (cantitateEliminata > 0) {
		if (id < 0) id *= -1;
		Pizza* referinta = nullptr;
		if (this->restaurant->areProduse()) {
			if (this->restaurant->getDimMeniuPizza() > 0 && this->restaurant->getMeniuPizza() != nullptr) {
				for (int i = 0; i < this->restaurant->getDimMeniuPizza() && referinta == nullptr; i++)
					if (id == this->restaurant->getMeniuPizza()[i]->getID())
						referinta = this->restaurant->getMeniuPizza()[i];
			}
		}
		else throw new Exceptie("Restaurantul nu are pizza!");
		if (referinta == nullptr) throw new Exceptie("Nu s-a gasit nicio pizza cu ID-ul dat!");
		else {
			if (this->nrPizza > 0 && this->comandaPizza != nullptr && this->cantitatiCerutePizza != nullptr) {
				bool gasit = false; int index = -1;
				for (int i = 0; i < this->nrPizza && !gasit; i++)
					if (id == this->comandaPizza[i]->getID()) {
						gasit = true;
						index = i;
					}
				if (gasit) {
					if (this->cantitatiCerutePizza[index] > cantitateEliminata)
						this->cantitatiCerutePizza[index] -= cantitateEliminata;
					else {
						if (this->nrPizza == 1) {
							this->nrPizza = 0;
							delete[] this->comandaPizza;
							this->comandaPizza = nullptr;
							delete[] this->cantitatiCerutePizza;
							this->cantitatiCerutePizza = nullptr;
						}
						else {
							Pizza** copieComanda = new Pizza * [this->nrPizza];
							float* copieCantitati = new float[this->nrPizza];
							TipBlat* copieTip = new TipBlat[this->nrPizza];
							for (int i = 0; i < this->nrPizza; i++) {
								copieComanda[i] = this->comandaPizza[i];
								copieCantitati[i] = this->cantitatiCerutePizza[i];
								copieTip[i] = this->tipuri[i];
							}
							delete[] this->comandaPizza;
							delete[] this->cantitatiCerutePizza;
							delete[] this->tipuri;
							this->nrPizza--;
							this->comandaPizza = new Pizza * [this->nrPizza];
							this->cantitatiCerutePizza = new float[this->nrPizza];
							this->tipuri = new TipBlat[this->nrPizza];
							int i, j;
							for (i = 0; i < index; i++) {
								this->comandaPizza[i] = copieComanda[i];
								this->cantitatiCerutePizza[i] = copieCantitati[i];
								this->tipuri[i] = copieTip[i];
							}
							for (j = index; j < this->nrPizza; j++) {
								this->comandaPizza[j] = copieComanda[j + 1];
								this->cantitatiCerutePizza[j] = copieCantitati[j + 1];
								this->tipuri[j] = copieTip[j + 1];
							}
							delete[] copieComanda;
							copieComanda = nullptr;
							delete[] copieCantitati;
							copieCantitati = nullptr;
							delete[] copieTip;
							copieTip = nullptr;
						}
					}
				}
				else throw new Exceptie("Nu s-a gasit pizza cu ID-ul dat!");
			}
			else if (this->nrPizza == 0 && this->comandaPizza == nullptr && this->cantitatiCerutePizza == nullptr)
				throw new Exceptie("Nu se pot elimina pizze dintr-o comanda nula!");
			else throw new Exceptie("Comanda corupta!");
		}
		referinta = nullptr;
	}
	else throw new Exceptie("Cantitatea eliminata din pizza adaugata trebuie sa fie pozitiva!");
}
bool Client::calculDisponibilitate() {
	if ((this->nrPizza > 0 && this->comandaPizza != nullptr && this->cantitatiCerutePizza != nullptr) || (this->nrProduse > 0 && this->comandaProduse != nullptr && this->cantitatiCeruteProduse != nullptr)) {
		if (this->restaurant != nullptr) {
			int dim = this->restaurant->getDimStoc();
			MateriePrima** copieStoc = new MateriePrima * [dim];
			float* cantitatiNecesarePerMaterie = new float[dim];
			for (int i = 0; i < dim; i++) {
				copieStoc[i] = this->restaurant->getStoc()[i];
				cantitatiNecesarePerMaterie[i] = 0;
			}
			int i = 0, j = 0, k = 0;
			if (this->nrPizza > 0 && this->comandaPizza != nullptr && this->cantitatiCerutePizza != nullptr) {
				for (i = 0; i < this->nrPizza; i++) {
					for (j = 0; j < this->comandaPizza[i]->getNrMateriiPrime(); j++) {
						for (k = 0; k < dim; k++) {
							if (copieStoc[k] == this->comandaPizza[i]->getRetetar()[j]) {
								cantitatiNecesarePerMaterie[k] += this->cantitatiCerutePizza[i] * this->comandaPizza[i]->uniformizareCantitate(j);
							}
						}
					}
				}
			}
			if (this->nrProduse > 0 && this->comandaProduse != nullptr && this->cantitatiCeruteProduse != nullptr) {
				for (i = 0; i < this->nrProduse; i++) {
					for (j = 0; j < this->comandaProduse[i]->getNrMateriiPrime(); j++) {
						for (k = 0; k < dim; k++) {
							if (copieStoc[k] == this->comandaProduse[i]->getRetetar()[j]) {
								//cantitatiNecesarePerMaterie[k] += this->cantitatiCeruteProduse[i] * this->comandaProduse[i]->getCantitatiNecesare()[j];
								cantitatiNecesarePerMaterie[k] += this->cantitatiCeruteProduse[i] * this->comandaProduse[i]->uniformizareCantitate(j);
							}
						}
					}
				}
			}
			for (i = 0; i < dim; i++) {
				if (cantitatiNecesarePerMaterie[i] > this->restaurant->getStoc()[i]->returnCantitateInGrame())
					return false;
			}
			delete[] copieStoc;
			copieStoc = nullptr;
			delete[] cantitatiNecesarePerMaterie;
			cantitatiNecesarePerMaterie = nullptr;
			return true;
		}
		else throw new Exceptie("Clientul nu apartine de un restaurant!");
	}
	return true;
}
void Trattorie::actualizareStocuri() {
	if (this->dimClienti > 0 && this->clienti != nullptr) {
		for (int c = 0; c < this->dimClienti; c++) {
			if ((this->clienti[c]->getNrPizza() > 0 && this->clienti[c]->getComandaPizza() != nullptr && this->clienti[c]->getCantitatiCerutePizza() != nullptr) || (this->clienti[c]->getNrProduse() > 0 && this->clienti[c]->getComandaProduse() != nullptr && this->clienti[c]->getCantitatiCeruteProduse() != nullptr)) {
				if (this->clienti[c]->getRestaurant() != nullptr) {
					int dim = this->dimStoc;
					MateriePrima** copieStoc = new MateriePrima * [dim];
					float* cantitatiNecesarePerMaterie = new float[dim];
					for (int i = 0; i < dim; i++) {
						copieStoc[i] = this->stoc[i];
						cantitatiNecesarePerMaterie[i] = 0;
					}
					int i = 0, j = 0, k = 0;
					if (this->clienti[i]->getNrPizza() > 0 && this->clienti[c]->getComandaPizza() != nullptr && this->clienti[c]->getCantitatiCerutePizza() != nullptr) {
						for (i = 0; i < this->clienti[c]->getNrPizza(); i++) {
							for (j = 0; j < this->clienti[c]->getComandaPizza()[i]->getNrMateriiPrime(); j++) {
								for (k = 0; k < dim; k++) {
									if (copieStoc[k] == this->clienti[c]->getComandaPizza()[i]->getRetetar()[j]) {
										cantitatiNecesarePerMaterie[k] += this->clienti[c]->getCantitatiCerutePizza()[i] * this->clienti[c]->getComandaPizza()[i]->uniformizareCantitate(j);
									}
								}
							}
						}
					}
					if (this->clienti[c]->getNrProduse() > 0 && this->clienti[c]->getComandaProduse() != nullptr && this->clienti[c]->getCantitatiCeruteProduse() != nullptr) {
						for (i = 0; i < this->clienti[c]->getNrProduse(); i++) {
							for (j = 0; j < this->clienti[c]->getComandaProduse()[i]->getNrMateriiPrime(); j++) {
								for (k = 0; k < dim; k++) {
									if (copieStoc[k] == this->clienti[c]->getComandaProduse()[i]->getRetetar()[j]) {
										cantitatiNecesarePerMaterie[k] += this->clienti[c]->getCantitatiCeruteProduse()[i] * this->clienti[c]->getComandaProduse()[i]->uniformizareCantitate(j);
									}
								}
							}
						}
					}
					for (i = 0; i < dim; i++) {
						if (cantitatiNecesarePerMaterie[i] > this->stoc[i]->returnCantitateInGrame())
							throw new Exceptie("Actualizare imposibila!");
						else this->stoc[i]->setCantitateDisponibila(this->stoc[i]->getCantitateDisponibila() -
							MateriePrima::transformare(this->stoc[i]->getUnitate(), UnitateDeMasura::GRAM, cantitatiNecesarePerMaterie[i]));
					}
					delete[] copieStoc;
					copieStoc = nullptr;
					delete[] cantitatiNecesarePerMaterie;
					cantitatiNecesarePerMaterie = nullptr;
				}
				else throw new Exceptie("Clientul nu apartine de un restaurant!");
			}
		}
	}
	else throw new Exceptie("Restaurantul nu are clienti!");
}
istream& operator>>(istream& in, Client& c) {
	delete[] c.comandaProduse;
	c.comandaProduse = nullptr;
	delete[] c.cantitatiCeruteProduse;
	c.cantitatiCeruteProduse = nullptr;
	delete[] c.comandaPizza;
	c.comandaPizza = nullptr;
	delete[] c.cantitatiCerutePizza;
	c.cantitatiCerutePizza = nullptr;
	delete[] c.tipuri;
	c.tipuri = nullptr;
	c.restaurant = nullptr;

	cout << "Nume client: ";
	string buffer;
	getline(cin, buffer);
	if (buffer.length() > 0) c.nume = buffer;
	else throw new Exceptie("Numele clientului nu poate sa fie nul!");
	cout << "Sex: ";
	getline(cin, buffer);
	if (buffer.length() > 0) c.sex = buffer;
	else throw new Exceptie("Sexul clientului nu poate fi nul!");
	cout << "Telefon: ";
	getline(cin, buffer);
	if (buffer.length() > 0) c.telefon = buffer;
	else throw new Exceptie("Telefonul clientului nu poate fi nul!");
	cout << "Varsta: ";
	in >> c.varsta;
	cout << "RESTAURANT:\n";
	c.restaurant = new Trattorie;
	cin.get();
	*c.restaurant >> in;
	cout << "BUGETUL CLIENTULUI: ";
	in >> c.buget;
	return in;
}

class IFisier {
public:
	virtual void primaryStream(const char*) = 0;
	virtual void secondaryStream() = 0;
};

class DateTrattorie : public IFisier {
private:
	Trattorie* restaurant = nullptr;
	MateriePrima** stoc = nullptr;
	Pizza** meniuPizza = nullptr;
	Produs** meniuDeBaza = nullptr;
public:
	DateTrattorie() {}
	DateTrattorie(Trattorie* restaurant) {
		this->restaurant = restaurant;
	}
	~DateTrattorie() {
		this->restaurant = nullptr;
		delete[] this->stoc;
		this->stoc = nullptr;
		delete[] this->meniuDeBaza;
		this->meniuDeBaza = nullptr;
		delete[] this->meniuPizza;
		this->meniuPizza = nullptr;
	}
	string removeSpaces(string myString) {
		// Find the first character that is not a space
			int index = 0;
		while (index < myString.length() && myString[index] == ' ') {
			index++;
		}

		// Remove leading spaces if any
		if (index < myString.length()) {
			myString = myString.substr(index);
		}
		
		return myString;
	}
	void primaryStream(const char* numeFisier) {
		ifstream f(numeFisier);
		if (!f) throw Exceptie("Fisierul nu exista sau nu poate fi citit!");
		else {
			if (this->restaurant != nullptr) {
				string line, element; char* ch_elements; int i_elements; float f_elements;
				getline(f, line, ',');
				this->restaurant->setDenumire(removeSpaces(line));
				getline(f, line, ',');
				this->restaurant->setAdministrator(removeSpaces(line));
				getline(f, line, ',');
				this->restaurant->setAdresa(removeSpaces(line));
				getline(f, line, ',');
				ch_elements = new char[removeSpaces(line).length() + 1];
				strcpy(ch_elements, removeSpaces(line).data());
				this->restaurant->setTelefon(ch_elements);
				delete[] ch_elements;
				getline(f, line);
				ch_elements = new char[removeSpaces(line).length() + 1];
				strcpy(ch_elements, removeSpaces(line).data());
				this->restaurant->setMail(ch_elements);
				delete[] ch_elements;
				getline(f, line, ',');
				i_elements = stoi(removeSpaces(line));
				this->restaurant->setOraIncepereProgram(i_elements);
				getline(f, line, ',');
				i_elements = stoi(removeSpaces(line));
				this->restaurant->setOraTerminareProgram(i_elements);
				getline(f, line);
				f_elements = stof(removeSpaces(line));
				this->restaurant->setRating(f_elements);
				//stoc
				getline(f, line);
				i_elements = stoi(removeSpaces(line));
				this->stoc = new MateriePrima * [i_elements];
				for (int i = 0; i < i_elements; i++) {
					getline(f, line, ',');
					ch_elements = new char[removeSpaces(line).length() + 1];
					strcpy(ch_elements, removeSpaces(line).data());
					getline(f, line, ',');
					float cant = stof(removeSpaces(line));
					getline(f, line, ',');
					UnitateDeMasura unit;
					if (removeSpaces(line) == "gram") unit = UnitateDeMasura::GRAM;
					else if (removeSpaces(line) == "litru") unit = UnitateDeMasura::LITRU;
					else if (removeSpaces(line) == "mililitru") unit = UnitateDeMasura::MILILITRU;
					else throw new Exceptie("Unitate de masura citita invalida!");
					getline(f, line);
					float pret = stof(removeSpaces(line));
					this->stoc[i] = new MateriePrima(ch_elements, cant, unit, pret);
				}
				this->restaurant->setStoc(i_elements, this->stoc);
				//meniuPizza
				getline(f, line);
				i_elements = stoi(removeSpaces(line));
				this->meniuPizza = new Pizza * [i_elements];
				for (int i = 0; i < i_elements; i++) {
					getline(f, line, ',');
					int id = stoi(removeSpaces(line));
					getline(f, line, ',');
					string denumire = removeSpaces(line);
					getline(f, line);
					int nrMatPrime = stoi(removeSpaces(line));
					MateriePrima** retetar = new MateriePrima * [nrMatPrime];
					float* cantN = new float[nrMatPrime];
					for (int j = 0; j < nrMatPrime; j++) {
						getline(f, line, ',');
						char* numeMat = new char[removeSpaces(line).length() + 1];
						strcpy(numeMat, removeSpaces(line).data());
						bool exists = false;
						for (int k = 0; k < this->restaurant->getDimStoc() && !exists; k++) {
							if (!strcmp(numeMat, this->restaurant->getStoc()[k]->getDenumire())) {
								exists = true;
								retetar[j] = (this->restaurant->getStoc()[k]);
							}
						}
						if (!exists) throw new Exceptie("Nu exista materia prima!");
						getline(f, line);
						cantN[j] = stof(removeSpaces(line));
					}
					getline(f, line, ',');
					float adaos = stof(removeSpaces(line));
					getline(f, line);
					int nrBlat = stoi(removeSpaces(line));
					TipBlat tipuri[3];
					for (int j = 0; j < nrBlat; j++) {
						getline(f, line);
						TipBlat tip;
						if (removeSpaces(line) == "subtire") tip = TipBlat::SUBTIRE;
						else if (removeSpaces(line) == "normal") tip = TipBlat::NORMAL;
						else if (removeSpaces(line) == "pufos") tip = TipBlat::PUFOS;
						else throw new Exceptie("Tip de blat citit invalid!");
						tipuri[j] = tip;
					}
					getline(f, line);
					int marime = stoi(removeSpaces(line));
					this->meniuPizza[i] = new Pizza(id, denumire, nrMatPrime, retetar, cantN, adaos, nrBlat, tipuri, marime);

					delete[] retetar;
					delete[] cantN;
					retetar = nullptr;
					cantN = nullptr;
				}
				this->restaurant->setMeniuPizza(i_elements, this->meniuPizza);
				//meniuDeBaza
				getline(f, line);
				i_elements = stoi(removeSpaces(line));
				this->meniuDeBaza = new Produs * [i_elements];
				for (int i = 0; i < i_elements; i++) {
					getline(f, line, ',');
					int id = stoi(removeSpaces(line));
					getline(f, line, ',');
					string denumire = removeSpaces(line);
					getline(f, line);
					int nrMatPrime = stoi(removeSpaces(line));
					MateriePrima** retetar = new MateriePrima * [nrMatPrime];
					float* cantN = new float[nrMatPrime];
					for (int j = 0; j < nrMatPrime; j++) {
						getline(f, line, ',');
						char* numeMat = new char[removeSpaces(line).length() + 1];
						strcpy(numeMat, removeSpaces(line).data());
						bool exists = false;
						for (int k = 0; k < this->restaurant->getDimStoc() && !exists; k++) {
							if (!strcmp(numeMat, this->restaurant->getStoc()[k]->getDenumire())) {
								exists = true;
								retetar[j] = (this->restaurant->getStoc()[k]);
							}
						}
						if (!exists) throw new Exceptie("Nu exista materia prima!");
						getline(f, line);
						cantN[j] = stof(removeSpaces(line));
					}
					getline(f, line);
					float adaos = stof(removeSpaces(line));
					this->meniuDeBaza[i] = new Produs(id, denumire, nrMatPrime, retetar, cantN, adaos);

					delete[] retetar;
					delete[] cantN;
					retetar = nullptr;
					cantN = nullptr;
				}
				this->restaurant->setMeniuDeBaza(i_elements, this->meniuDeBaza);
				getline(f, line);
				f_elements = stof(removeSpaces(line));
				Client::procentMinimBacsis = f_elements;
			}
			else throw new Exceptie("Nu exista restaurant asociat!");
		}
		f.close();
	}
	void secondaryStream() {
		ofstream f("save.txt");
		if (!f) throw Exceptie("Fisierul nu a putut fi creat!");
		else {
			if (this->restaurant != nullptr) {
				f << this->restaurant->getDenumire() << ", " << this->restaurant->getAdministrator() << ", " << this->restaurant->getAdresa() <<
					", " << this->restaurant->getTelefon() << ", " << this->restaurant->getMail() << endl;
				f << this->restaurant->getOraIncepereProgram() << ", " << this->restaurant->getOraTerminareProgram() <<
					", " << this->restaurant->getRating() << endl;
				f << this->restaurant->getDimStoc() << endl;
				for (int i = 0; i < this->restaurant->getDimStoc(); i++) {
					f << this->restaurant->getStoc()[i]->getDenumire() << ", "
						<< this->restaurant->getStoc()[i]->getCantitateDisponibila() << ", ";
					if (this->restaurant->getStoc()[i]->getUnitate() == UnitateDeMasura::GRAM)
						f << "gram, ";
					else if (this->restaurant->getStoc()[i]->getUnitate() == UnitateDeMasura::LITRU)
						f << "litru, ";
					else if (this->restaurant->getStoc()[i]->getUnitate() == UnitateDeMasura::MILILITRU)
						f << "mililitru, ";
					f << this->restaurant->getStoc()[i]->getPretPerUnitate() << endl;
				}
				f << this->restaurant->getDimMeniuPizza() << endl;
				for (int i = 0; i < this->restaurant->getDimMeniuPizza(); i++) {
					f << this->restaurant->getMeniuPizza()[i]->getID() << ", " <<
						this->restaurant->getMeniuPizza()[i]->getDenumire() << ", " <<
						this->restaurant->getMeniuPizza()[i]->getNrMateriiPrime() << endl;
					for (int j = 0; j < this->restaurant->getMeniuPizza()[i]->getNrMateriiPrime(); j++) {
						f << this->restaurant->getMeniuPizza()[i]->getRetetar()[j]->getDenumire() << ", " <<
							this->restaurant->getMeniuPizza()[i]->getCantitatiNecesare()[j] << endl;
					}
					f << this->restaurant->getMeniuPizza()[i]->getAdaos() << ", "
						<< this->restaurant->getMeniuPizza()[i]->getNrOptiuniBlat() << endl;
					for (int j = 0; j < this->restaurant->getMeniuPizza()[i]->getNrOptiuniBlat(); j++) {
						if (this->restaurant->getMeniuPizza()[i]->getOptiuniBlat()[j] == TipBlat::SUBTIRE)
							f << "subtire" << endl;
						else if (this->restaurant->getMeniuPizza()[i]->getOptiuniBlat()[j] == TipBlat::NORMAL)
							f << "normal" << endl;
						else if (this->restaurant->getMeniuPizza()[i]->getOptiuniBlat()[j] == TipBlat::PUFOS)
							f << "pufos" << endl;
					}
					f << this->restaurant->getMeniuPizza()[i]->getMarime() << endl;
				}
				f << this->restaurant->getDimMeniuDeBaza() << endl;
				for (int i = 0; i < this->restaurant->getDimMeniuDeBaza(); i++) {
					f << this->restaurant->getMeniuDeBaza()[i]->getID() << ", " <<
						this->restaurant->getMeniuDeBaza()[i]->getDenumire() << ", " <<
						this->restaurant->getMeniuDeBaza()[i]->getNrMateriiPrime() << endl;
					for (int j = 0; j < this->restaurant->getMeniuDeBaza()[i]->getNrMateriiPrime(); j++) {
						f << this->restaurant->getMeniuDeBaza()[i]->getRetetar()[j]->getDenumire() << ", " <<
							this->restaurant->getMeniuDeBaza()[i]->getCantitatiNecesare()[j] << endl;
					}
					f << this->restaurant->getMeniuDeBaza()[i]->getAdaos() << endl;
				}
				f << Client::procentMinimBacsis;
			}
			else throw new Exceptie("Nu exista restaurant asociat!");
		}
		f.close();
	}
};

class DateClient : public IFisier {
private:
	Client* client = nullptr;

	vector<Produs> vProdus;
	vector<Produs>::iterator itProdus;
	list<Pizza> lPizza;
	list<Pizza>::iterator itPizza;

	set<Produs> setProdus;
	set<Produs>::iterator it2Produs;
	set<Pizza> setPizza;
	set<Pizza>::iterator it2Pizza;

	map<int, Produs> mapProdus;
	map<int, Produs>::iterator it3Produs;
	map<int, Pizza> mapPizza;
	map<int, Pizza>::iterator it3Pizza;
public:
	DateClient() {}
	DateClient(Client* client) {
		this->client = client;
	}
	~DateClient() {
		this->client = nullptr;
	}
	void gatherData() {
		for (int i = 0; i < this->client->getNrProduse(); i++) {
			vProdus.push_back(*this->client->getComandaProduse()[i]);
			setProdus.insert(*this->client->getComandaProduse()[i]);
			//mapProdus[this->client->getComandaProduse()[i]->getID()] = *this->client->getComandaProduse()[i];
			mapProdus[i] = *this->client->getComandaProduse()[i];
		}
		for (int i = 0; i < this->client->getNrPizza(); i++) {
			lPizza.push_back(*this->client->getComandaPizza()[i]);
			setPizza.insert(*this->client->getComandaPizza()[i]);
			//mapPizza[this->client->getComandaPizza()[i]->getID()] = *this->client->getComandaPizza()[i];
			mapPizza[i] = *this->client->getComandaPizza()[i];
		}
	}
	void primaryStream(const char* numeFisier) {
		fstream f(numeFisier, ios::app);
		if (!f) throw Exceptie("Fisierul nu a putut fi creat sau deschis!");
		else {
			f << endl << endl;
			cout << endl << endl;
			f << "COMANDA: " << this->client->getNume() << endl << endl;
			cout << "COMANDA: " << this->client->getNume() << endl << endl;
			if (setPizza.size() == 0) f << "[NICIO PIZZA COMANDATA]";
			else
				for (it2Pizza = setPizza.begin(); it2Pizza != setPizza.end(); it2Pizza++) {
					f << *it2Pizza << endl;
					cout << *it2Pizza << endl;
				}
			f << endl;
			cout << endl;
			if (setProdus.size() == 0) f << "[NICIUN PRODUS COMANDAT]";
			else
				for (it2Produs = setProdus.begin(); it2Produs != setProdus.end(); it2Produs++) {
					f << *it2Produs << endl;
					cout << *it2Produs << endl;
				}
		}
		f.close();
	}
	void secondaryStream() {
		ofstream f("detailed-report.txt");
		if (!f) throw Exceptie("Fisierul nu a putut fi creat!");
		else {
			f << this->client->getNume() << endl << endl;
			cout << this->client->getNume() << endl << endl;
			if (lPizza.size() == 0) f << "[NICIO PIZZA COMANDATA]";
			else
				for (itPizza = lPizza.begin(); itPizza != lPizza.end(); itPizza++) {
					f << *itPizza << endl;
					cout << *itPizza << endl;
				}
			f << endl;
			cout << endl;
			if (vProdus.size() == 0) f << "[NICIUN PRODUS COMANDAT]";
			else
				/*for (int i = 0; i < vProdus.size(); i++)
					f << vProdus[i] << endl;*/
				for (itProdus = vProdus.begin(); itProdus != vProdus.end(); itProdus++) {
					f << *itProdus << endl;
					cout << *itProdus << endl;
				}
		}
	}
	void tertiaryStream() {
		ofstream f("compact-report.txt");
		if (!f) throw Exceptie("Fisierul nu a putut fi creat!");
		else {
			f << this->client->getNume() << endl << endl;
			cout << this->client->getNume() << endl << endl;
			if (mapPizza.size() == 0) f << "[NICIO PIZZA COMANDATA]";
			else
				for (it3Pizza = mapPizza.begin(); it3Pizza != mapPizza.end(); it3Pizza++) {
					f << it3Pizza->first << " : " << it3Pizza->second.getDenumire() << endl;
					cout << it3Pizza->first << " : " << it3Pizza->second.getDenumire() << endl;
				}
			f << endl;
			cout << endl;
			if (mapProdus.size() == 0) f << "[NICIUN PRODUS COMANDAT]";
			else
				/*for (int i = 0; i < vProdus.size(); i++)
					f << vProdus[i] << endl;*/
				for (it3Produs = mapProdus.begin(); it3Produs != mapProdus.end(); it3Produs++) {
					f << it3Produs->first << " : " << it3Produs->second.getDenumire() << endl;
					cout << it3Produs->first << " : " << it3Produs->second.getDenumire() << endl;
				}
		}
	}
};

float Client::procentMinimBacsis = 10.0;
int* Produs::listaIDuri = nullptr;
int Produs::nrIDuri = 0;

int main(int argc, char** argv) {
	int initializator = 0;
	if (argc == 1) {
		cout << "\nDoriti sa folositi date hardcodate sau din fisierul default?";
		do {
			cout << "\n[1 pt date hardcodate, 2 pentru date din fisierul default] : ";
			cin >> initializator;
		} while (initializator != 1 && initializator != 2);
		if (initializator == 1) {

			//INITIALIZARE VALORI
			MateriePrima m1("Sunca", 1000, UnitateDeMasura::GRAM, 0.1);
			MateriePrima m2("Patrunjel", 250, UnitateDeMasura::GRAM, 0.05);
			MateriePrima m3("Rosii", 400, UnitateDeMasura::GRAM, 0.2);
			MateriePrima m4("Apa plata", 20, UnitateDeMasura::LITRU, 5);
			MateriePrima m5("Paine", 600, UnitateDeMasura::GRAM, 0.01);
			MateriePrima m6("Sos iute", 950, UnitateDeMasura::MILILITRU, 0.1);
			MateriePrima m7("Branza", 300, UnitateDeMasura::GRAM, 0.25);

			MateriePrima* retetarP1[2] = { &m1, &m5 };
			float cantitatiNecesareP1[2] = { 50, 100 };
			Produs p1(1, "Sandvis cu Sunca", 2, retetarP1, cantitatiNecesareP1, 15);

			MateriePrima* retetarP2[3] = { &m1, &m3, &m5 };
			float cantitatiNecesareP2[3] = { 50, 25, 100 };
			Produs p2(1, "Sandvis cu Sunca si Rosii", 3, retetarP2, cantitatiNecesareP2, 20);

			MateriePrima* retetarP3[1] = { &m4 };
			float cantitatiNecesareP3[1] = { 1 };
			Produs p3(3, "Sticla de apa plata", 1, retetarP3, cantitatiNecesareP3, 5);

			MateriePrima* retetarP4[2] = { &m5, &m7 };
			float cantitatiNecesareP4[2] = { 250, 200 };
			TipBlat optiuniP4[2] = { TipBlat::PUFOS, TipBlat::SUBTIRE };
			Pizza p4(4, "Pizza Quattro Formaggi", 2, retetarP4, cantitatiNecesareP4, 30, 2, optiuniP4, 30);

			MateriePrima* retetarP5[5] = { &m1, &m2, &m3, &m5, &m7 };
			float cantitatiNecesareP5[5] = { 250, 50, 100, 300, 150 };
			TipBlat optiuniP5[1] = { TipBlat::NORMAL };
			Pizza p5(5, "Pizza Taraneasca", 5, retetarP5, cantitatiNecesareP5, 35, 1, optiuniP5, 40);

			MateriePrima* retetarP6[4] = { &m1, &m5, &m6, &m7 };
			float cantitatiNecesareP6[4] = { 300, 300, 100, 100 };
			TipBlat optiuniP6[3] = { TipBlat::PUFOS, TipBlat::NORMAL, TipBlat::SUBTIRE };
			Pizza p6(6, "Pizza Diavola", 4, retetarP6, cantitatiNecesareP6, 33, 3, optiuniP6, 35);

			MateriePrima* stoc[7] = { &m1, &m2, &m3, &m4, &m5, &m6, &m7 };
			Produs* meniuDeBaza[3] = { &p1, &p2, &p3 };
			Pizza* meniuPizza[3] = { &p4, &p5, &p6 };
			Trattorie t("Trattoria Berceni", "Gurau Adrian-Florin", "B-dul Ct. Brancoveanu", "021 0487 8900", "trattoria.berceni@gmail.com", 13, 24, 4.6, stoc, 7, meniuDeBaza, 3, meniuPizza, 3, nullptr, 0);

			//INTRODUCERE
			int decizie = 0;
			cout << "Bun venit!\n\n";
			cout << "Doresti sa te identifici sau sa ramai anonim?\n";
			do {
				cout << "[1 pt a te identifica, 2 pentru a ramane anonim] : ";
				cin >> decizie;
			} while (decizie != 1 && decizie != 2);
			cout << "\n";
			Client c;
			if (decizie == 1) {
				string buffer = ""; int val = 0;
				cin.get();
				do {
					cout << "Care este numele tau? : ";
					getline(cin, buffer);
				} while (!buffer.length());
				try {
					c.setNume(buffer);
				}
				catch (Exceptie* ex) {
					cout << endl << endl << ex->getMesaj() << endl << endl;
					delete ex;
					ex = nullptr;
				}
				do {
					cout << "Care este sexul tau? : ";
					getline(cin, buffer);
				} while (!buffer.length());
				try {
					c.setSex(buffer);
				}
				catch (Exceptie* ex) {
					cout << endl << endl << ex->getMesaj() << endl << endl;
					delete ex;
					ex = nullptr;
				}
				do {
					cout << "Care este numarul tau de telefon? : ";
					getline(cin, buffer);
				} while (!buffer.length());
				try {
					c.setTelefon(buffer);
				}
				catch (Exceptie* ex) {
					cout << endl << endl << ex->getMesaj() << endl << endl;
					delete ex;
					ex = nullptr;
				}
				cout << "Care este varsta ta? : ";
				cin >> val;
				try {
					c.setVarsta(val);
				}
				catch (Exceptie* ex) {
					cout << endl << endl << ex->getMesaj() << endl << endl;
					delete ex;
					ex = nullptr;
				}
			}
			if (decizie == 2)
				cout << "OK. Intelegem!";
			cout << "\n";
			float buget = -1;

			cout << "Care este bugetul tau (RON)? : ";
			cin >> buget;
			if (buget < 0) buget *= -1;
			try {
				c.setBuget(buget);
			}
			catch (Exceptie* ex) {
				cout << endl << endl << ex->getMesaj() << endl << endl;
				delete ex;
				ex = nullptr;
			}

			//CONTINUARE INITIALIZARE
			Client* clienti[1] = { &c };
			try {
				t.setClienti(1, clienti);
				c.setRestaurant(&t);
			}
			catch (Exceptie* ex) {
				cout << endl << endl << ex->getMesaj() << endl << endl;
				delete ex;
				ex = nullptr;
			}
			cout << "\nCLIENT:";
			cout << "\n-----------------------------------------------\n";
			cout << c;
			cout << "\n-----------------------------------------------\n";
			cout << "\n\nRESTAURANT:";
			cout << "\n-----------------------------------------------\n";
			cout << t;
			cout << "\n-----------------------------------------------\n";
			cout << "\n\n\n\n\n";

			//INCEPUT PROPRIU-ZIS GESTIUNE COMANDA
			int id = -1; string optiune = ""; float cantitate = 0; TipBlat tip = TipBlat::SUBTIRE; int dummy = 0;

			DateTrattorie dt(&t);
			DateClient dc(&c);

			if (t.areProduse()) {
				t.afisareMeniu();
				if (t.calculPretMinim() > c.getBuget())
					cout << "\nDupa ce ai analizat meniul, ai observat ca bugetul tau\nnu este suficient de mare pentru acest restaurant.\n\n\n";
				else {
					cout << "\n\n\n";

					cout << "[Scrie 'help' pentru o lista completa de comenzi]\n";
					//MAI MULTA INTERACTIVITATE IN CONSOLA
					do {
						cout << "$ ";
						cin >> optiune;

						if (optiune == "help") {
							cout << "\nLISTA COMENZI:";
							cout << "\n'adauga' -> pentru a adauga un produs in comanda";//
							cout << "\n'elimina' -> pentru a elimina un produs din comanda";//
							cout << "\n'buget' -> pentru a consulta bugetul propriu";//
							cout << "\n'meniu' -> pentru a afisa meniul";
							cout << "\n'comanda' -> pentru a afisa comanda";
							cout << "\n'checkout' -> pentru a finaliza comanda";//
							cout << "\n'save' -> pentru a salva datele curente in fisier";
							cout << "\n'multi-raport' -> pentru a crea/adauga la un raport multi-utilizator";
							cout << "\n'raport-detaliat' -> pentru a crea un raport detaliat al utilizatorului curent";
							cout << "\n'raport-compact' -> pentru a crea un raport compact al utilizatorului curent";
							cout << "\n'exit' -> pentru a iesi din program";
							cout << "\n\n";
						}
						else if (optiune == "adauga") {
							try {
								cout << "\nIntroduceti ID-ul produsului pe care doriti sa-l adaugati: ";
								cin >> id;
								if (c.pizzaSauProdusCOMANDA(id) == "PIZZA") {
									cout << "\nIntroduceti cantitatea de adaugat dorita: ";
									cin >> cantitate;
									c.adaugaPizza(id, cantitate, TipBlat::SUBTIRE);
									if (c.calculDisponibilitate()) cout << "\nADAUGAT!\n\n";
									else {
										c.eliminaPizza(id, cantitate);
										cout << "\nNu exista suficiente resurse pentru a adauga pizza in cantitatea dorita!\n\n";
									}
								}
								else if (c.pizzaSauProdusCOMANDA(id) == "PRODUS") {
									cout << "\nIntroduceti cantitatea de adaugat dorita: ";
									cin >> cantitate;
									c.adaugaProdus(id, cantitate);
									if (c.calculDisponibilitate()) cout << "\nADAUGAT!\n\n";
									else {
										c.eliminaProdus(id, cantitate);
										cout << "\nNu exista suficiente resurse pentru a adauga produsul in cantitatea dorita!\n\n";
									}
								}
								else if (c.pizzaSauProdusMENIU(id) == "PIZZA") {
									cout << "\nIntroduceti cantitatea de adaugat dorita: ";
									cin >> cantitate;
									cout << "\nIntroduceti tipul de blat dorit (1 pt subtire, 2 pt normal, 3 pt pufos): ";
									cin >> dummy;
									switch (dummy) {
									case 1: tip = TipBlat::SUBTIRE; break;
									case 2: tip = TipBlat::NORMAL; break;
									case 3: tip = TipBlat::PUFOS; break;
									}
									c.adaugaPizza(id, cantitate, tip);
									if (c.calculDisponibilitate()) cout << "\nADAUGAT!\n\n";
									else {
										c.eliminaPizza(id, cantitate);
										cout << "\nNu exista suficiente resurse pentru a adauga pizza in cantitatea dorita!\n\n";
									}
								}
								else if (c.pizzaSauProdusMENIU(id) == "PRODUS") {
									cout << "\nIntroduceti cantitatea de adaugat dorita: ";
									cin >> cantitate;
									c.adaugaProdus(id, cantitate);
									if (c.calculDisponibilitate()) cout << "\nADAUGAT!\n\n";
									else {
										c.eliminaProdus(id, cantitate);
										cout << "\nNu exista suficiente resurse pentru a adauga produsul in cantitatea dorita!\n\n";
									}
								}
								else cout << "\nNU S-A GASIT PRODUS/PIZZA IN MENIU/COMANDA CU ID-UL DAT!\n\n";
							}
							catch (Exceptie* ex) {
								cout << endl << endl << ex->getMesaj() << endl << endl;
								delete ex;
								ex = nullptr;
							}
						}
						else if (optiune == "elimina") {
							try {
								cout << "\nIntroduceti ID-ul produsului pe care doriti sa-l eliminati: ";
								cin >> id;
								cout << "\nIntroduceti cantitatea pe care doriti sa o eliminati: ";
								cin >> cantitate;
								if (c.areComanda()) {
									if (c.pizzaSauProdusCOMANDA(id) == "PIZZA") {
										c.eliminaPizza(id, cantitate);
										cout << "\nELIMINAT!\n\n";
									}
									else if (c.pizzaSauProdusCOMANDA(id) == "PRODUS") {
										c.eliminaProdus(id, cantitate);
										cout << "\nELIMINAT!\n\n";
									}
									else cout << "\nNU S-A GASIT PRODUS/PIZZA IN COMANDA CU ID-UL DAT!\n\n";
								}
								else cout << "\nNU SE POATE ELIMINA PRODUS/PIZZA DINTR-O COMANDA GOALA!\n\n";
							}
							catch (Exceptie* ex) {
								cout << endl << endl << ex->getMesaj() << endl << endl;
								delete ex;
								ex = nullptr;
							}
						}
						else if (optiune == "meniu") {
							cout << "\n";
							t.afisareMeniu();
							cout << "\n\n";
						}
						else if (optiune == "comanda") {
							cout << "\n";
							c.afiseazaComanda();
							cout << "\n\n";
						}
						else if (optiune == "checkout") {
							try {
								cout << "\n";
								if (c.areComanda()) {
									if (c.calculDisponibilitate()) {
										if (c.getBuget() >= c.calculPretComanda()) {
											c.setBuget(c.getBuget() - c.calculPretComanda());
											t.actualizareStocuri();
											dc.gatherData();
											c.stergeComanda();
											cout << "POFTA BUNA!";
										}
										else cout << "BUGETUL DISPONIBIL NU ESTE SUFICIENT DE MARE!";
									}
									else cout << "COMANDA NU POATE FI SATISFACUTA DIN CAUZA RESURSELOR INSUFICIENTE ALE RESTAURANTULUI!";
								}
								else cout << "NU SE POATE DA CHECKOUT LA O COMANDA GOALA!";
								cout << "\n\n";
							}
							catch (Exceptie* ex) {
								cout << endl << endl << ex->getMesaj() << endl << endl;
								delete ex;
								ex = nullptr;
							}
						}
						else if (optiune == "buget") {
							cout << "\n";
							cout << "Bugetul tau este: ";
							printf("%.2fRON", c.getBuget());
							cout << "\n\n";
						}
						else if (optiune == "save") {
							dt.secondaryStream();
							cout << "\nDatele au fost salvate in fisierul save.txt!\n\n";
						}
						else if (optiune == "multi-raport") {
							cout << "\nCe nume sa aiba fisierul? : ";
							string temp;
							cin >> temp;
							dc.primaryStream(temp.data());
							cout << "\nRaport creat/continuat cu numele " << temp << "!\n\n";
						}
						else if (optiune == "raport-detaliat") {
							dc.secondaryStream();
							cout << "\nRaport creat!\n\n";
						}
						else if (optiune == "raport-compact") {
							dc.tertiaryStream();
							cout << "\nRaport creat!\n\n";
						}
						else if (optiune != "help" && optiune != "adauga" && optiune != "elimina" && optiune != "save" && optiune != "multi-raport" && optiune != "raport-detaliat" && optiune != "raport-compact"
							&& optiune != "buget" && optiune != "checkout" && optiune != "exit" && optiune != "meniu" && optiune != "comanda")
							cout << "\n[Scrie 'help' pentru o lista completa de comenzi]\n";

					} while (optiune != "exit");
				}
			}
			else cout << "Din pacate, nu exista meniu!\n\n\n";
			//Produs::distrugeListaIDuri();
			return 0;

		}
	}
	if (argc == 2 || initializator == 2) {
		Trattorie t;
		DateTrattorie dt(&t);
		if (initializator == 2) { //fisier default
			dt.primaryStream("default.txt");
		}
		else { //fisier parametru
			dt.primaryStream(argv[1]);
		}

		//INTRODUCERE
		int decizie = 0;
		cout << "Bun venit!\n\n";
		cout << "Doresti sa te identifici sau sa ramai anonim?\n";
		do {
			cout << "[1 pt a te identifica, 2 pentru a ramane anonim] : ";
			cin >> decizie;
		} while (decizie != 1 && decizie != 2);
		cout << "\n";
		Client c;
		DateClient dc(&c);
		if (decizie == 1) {
			string buffer = ""; int val = 0;
			cin.get();
			do {
				cout << "Care este numele tau? : ";
				getline(cin, buffer);
			} while (!buffer.length());
			try {
				c.setNume(buffer);
			}
			catch (Exceptie* ex) {
				cout << endl << endl << ex->getMesaj() << endl << endl;
				delete ex;
				ex = nullptr;
			}
			do {
				cout << "Care este sexul tau? : ";
				getline(cin, buffer);
			} while (!buffer.length());
			try {
				c.setSex(buffer);
			}
			catch (Exceptie* ex) {
				cout << endl << endl << ex->getMesaj() << endl << endl;
				delete ex;
				ex = nullptr;
			}
			do {
				cout << "Care este numarul tau de telefon? : ";
				getline(cin, buffer);
			} while (!buffer.length());
			try {
				c.setTelefon(buffer);
			}
			catch (Exceptie* ex) {
				cout << endl << endl << ex->getMesaj() << endl << endl;
				delete ex;
				ex = nullptr;
			}
			cout << "Care este varsta ta? : ";
			cin >> val;
			try {
				c.setVarsta(val);
			}
			catch (Exceptie* ex) {
				cout << endl << endl << ex->getMesaj() << endl << endl;
				delete ex;
				ex = nullptr;
			}
		}
		if (decizie == 2)
			cout << "OK. Intelegem!";
		cout << "\n";
		float buget = -1;

		cout << "Care este bugetul tau (RON)? : ";
		cin >> buget;
		if (buget < 0) buget *= -1;
		try {
			c.setBuget(buget);
		}
		catch (Exceptie* ex) {
			cout << endl << endl << ex->getMesaj() << endl << endl;
			delete ex;
			ex = nullptr;
		}

		//CONTINUARE INITIALIZARE
		Client* clienti[1] = { &c };
		try {
			t.setClienti(1, clienti);
			c.setRestaurant(&t);
		}
		catch (Exceptie* ex) {
			cout << endl << endl << ex->getMesaj() << endl << endl;
			delete ex;
			ex = nullptr;
		}
		cout << "\nCLIENT:";
		cout << "\n-----------------------------------------------\n";
		cout << c;
		cout << "\n-----------------------------------------------\n";
		cout << "\n\nRESTAURANT:";
		cout << "\n-----------------------------------------------\n";
		cout << t;
		cout << "\n-----------------------------------------------\n";
		cout << "\n\n\n\n\n";

		//INCEPUT PROPRIU-ZIS GESTIUNE COMANDA
		int id = -1; string optiune = ""; float cantitate = 0; TipBlat tip = TipBlat::SUBTIRE; int dummy = 0;

		if (t.areProduse()) {
			t.afisareMeniu();
			if (t.calculPretMinim() > c.getBuget())
				cout << "\nDupa ce ai analizat meniul, ai observat ca bugetul tau\nnu este suficient de mare pentru acest restaurant.\n\n\n";
			else {
				cout << "\n\n\n";

				cout << "[Scrie 'help' pentru o lista completa de comenzi]\n";
				//MAI MULTA INTERACTIVITATE IN CONSOLA
				do {
					cout << "$ ";
					cin >> optiune;

					if (optiune == "help") {
						cout << "\nLISTA COMENZI:";
						cout << "\n'adauga' -> pentru a adauga un produs in comanda";//
						cout << "\n'elimina' -> pentru a elimina un produs din comanda";//
						cout << "\n'buget' -> pentru a consulta bugetul propriu";//
						cout << "\n'meniu' -> pentru a afisa meniul";
						cout << "\n'comanda' -> pentru a afisa comanda";
						cout << "\n'checkout' -> pentru a finaliza comanda";//
						cout << "\n'save' -> pentru a salva datele curente in fisier";
						cout << "\n'multi-raport' -> pentru a crea/adauga la un raport multi-utilizator";
						cout << "\n'raport-detaliat' -> pentru a crea un raport detaliat al utilizatorului curent";
						cout << "\n'raport-compact' -> pentru a crea un raport compact al utilizatorului curent";
						cout << "\n'exit' -> pentru a iesi din program";
						cout << "\n\n";
					}
					else if (optiune == "adauga") {
						try {
							cout << "\nIntroduceti ID-ul produsului pe care doriti sa-l adaugati: ";
							cin >> id;
							if (c.pizzaSauProdusCOMANDA(id) == "PIZZA") {
								cout << "\nIntroduceti cantitatea de adaugat dorita: ";
								cin >> cantitate;
								c.adaugaPizza(id, cantitate, TipBlat::SUBTIRE);
								if (c.calculDisponibilitate()) cout << "\nADAUGAT!\n\n";
								else {
									c.eliminaPizza(id, cantitate);
									cout << "\nNu exista suficiente resurse pentru a adauga pizza in cantitatea dorita!\n\n";
								}
							}
							else if (c.pizzaSauProdusCOMANDA(id) == "PRODUS") {
								cout << "\nIntroduceti cantitatea de adaugat dorita: ";
								cin >> cantitate;
								c.adaugaProdus(id, cantitate);
								if (c.calculDisponibilitate()) cout << "\nADAUGAT!\n\n";
								else {
									c.eliminaProdus(id, cantitate);
									cout << "\nNu exista suficiente resurse pentru a adauga produsul in cantitatea dorita!\n\n";
								}
							}
							else if (c.pizzaSauProdusMENIU(id) == "PIZZA") {
								cout << "\nIntroduceti cantitatea de adaugat dorita: ";
								cin >> cantitate;
								cout << "\nIntroduceti tipul de blat dorit (1 pt subtire, 2 pt normal, 3 pt pufos): ";
								cin >> dummy;
								switch (dummy) {
								case 1: tip = TipBlat::SUBTIRE; break;
								case 2: tip = TipBlat::NORMAL; break;
								case 3: tip = TipBlat::PUFOS; break;
								}
								c.adaugaPizza(id, cantitate, tip);
								if (c.calculDisponibilitate()) cout << "\nADAUGAT!\n\n";
								else {
									c.eliminaPizza(id, cantitate);
									cout << "\nNu exista suficiente resurse pentru a adauga pizza in cantitatea dorita!\n\n";
								}
							}
							else if (c.pizzaSauProdusMENIU(id) == "PRODUS") {
								cout << "\nIntroduceti cantitatea de adaugat dorita: ";
								cin >> cantitate;
								c.adaugaProdus(id, cantitate);
								if (c.calculDisponibilitate()) cout << "\nADAUGAT!\n\n";
								else {
									c.eliminaProdus(id, cantitate);
									cout << "\nNu exista suficiente resurse pentru a adauga produsul in cantitatea dorita!\n\n";
								}
							}
							else cout << "\nNU S-A GASIT PRODUS/PIZZA IN MENIU/COMANDA CU ID-UL DAT!\n\n";
						}
						catch (Exceptie* ex) {
							cout << endl << endl << ex->getMesaj() << endl << endl;
							delete ex;
							ex = nullptr;
						}
					}
					else if (optiune == "elimina") {
						try {
							cout << "\nIntroduceti ID-ul produsului pe care doriti sa-l eliminati: ";
							cin >> id;
							cout << "\nIntroduceti cantitatea pe care doriti sa o eliminati: ";
							cin >> cantitate;
							if (c.areComanda()) {
								if (c.pizzaSauProdusCOMANDA(id) == "PIZZA") {
									c.eliminaPizza(id, cantitate);
									cout << "\nELIMINAT!\n\n";
								}
								else if (c.pizzaSauProdusCOMANDA(id) == "PRODUS") {
									c.eliminaProdus(id, cantitate);
									cout << "\nELIMINAT!\n\n";
								}
								else cout << "\nNU S-A GASIT PRODUS/PIZZA IN COMANDA CU ID-UL DAT!\n\n";
							}
							else cout << "\nNU SE POATE ELIMINA PRODUS/PIZZA DINTR-O COMANDA GOALA!\n\n";
						}
						catch (Exceptie* ex) {
							cout << endl << endl << ex->getMesaj() << endl << endl;
							delete ex;
							ex = nullptr;
						}
					}
					else if (optiune == "meniu") {
						cout << "\n";
						t.afisareMeniu();
						cout << "\n\n";
					}
					else if (optiune == "comanda") {
						cout << "\n";
						c.afiseazaComanda();
						cout << "\n\n";
					}
					else if (optiune == "checkout") {
						try {
							cout << "\n";
							if (c.areComanda()) {
								if (c.calculDisponibilitate()) {
									if (c.getBuget() >= c.calculPretComanda()) {
										c.setBuget(c.getBuget() - c.calculPretComanda());
										t.actualizareStocuri();
										dc.gatherData();
										c.stergeComanda();
										cout << "POFTA BUNA!";
									}
									else cout << "BUGETUL DISPONIBIL NU ESTE SUFICIENT DE MARE!";
								}
								else cout << "COMANDA NU POATE FI SATISFACUTA DIN CAUZA RESURSELOR INSUFICIENTE ALE RESTAURANTULUI!";
							}
							else cout << "NU SE POATE DA CHECKOUT LA O COMANDA GOALA!";
							cout << "\n\n";
						}
						catch (Exceptie* ex) {
							cout << endl << endl << ex->getMesaj() << endl << endl;
							delete ex;
							ex = nullptr;
						}
					}
					else if (optiune == "buget") {
						cout << "\n";
						cout << "Bugetul tau este: ";
						printf("%.2fRON", c.getBuget());
						cout << "\n\n";
					}
					else if (optiune == "save") {
						dt.secondaryStream();
						cout << "\nDatele au fost salvate in fisierul save.txt!\n\n";
					}
					else if (optiune == "multi-raport") {
						cout << "\nCe nume sa aiba fisierul? : ";
						string temp;
						cin >> temp;
						dc.primaryStream(temp.data());
						cout << "\nRaport creat/continuat cu numele " << temp << "!\n\n";
						}
					else if (optiune == "raport-detaliat") {
						dc.secondaryStream();
						cout << "\nRaport creat!\n\n";
						}
					else if (optiune == "raport-compact") {
						dc.tertiaryStream();
						cout << "\nRaport creat!\n\n";
						}
					else if (optiune != "help" && optiune != "adauga" && optiune != "elimina" && optiune != "save" && optiune != "multi-raport" && optiune != "raport-detaliat" && optiune != "raport-compact"
						&& optiune != "buget" && optiune != "checkout" && optiune != "exit" && optiune != "meniu" && optiune != "comanda")
						cout << "\n[Scrie 'help' pentru o lista completa de comenzi]\n";

				} while (optiune != "exit");
			}
		}
		else cout << "Din pacate, nu exista meniu!\n\n\n";
		//Produs::distrugeListaIDuri();

		return 0;
	}
	if (argc != 1 && argc != 2) {
		cout << "\nEroare: Prea multe fisiere de input.\n";
		return 0;
	}
}