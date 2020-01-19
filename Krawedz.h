#pragma once
class Krawedz
{

public:

	char miastoA;
	char miastoB;
	int numerWierzcholkaA;
	int numerWierzcholkaB;
	long double dlugoscKrawedzi;

	void setMiastoA(char miastoA) {
		this->miastoA = miastoA;
	}
	void setMiastoB(char miastoB) {
		this->miastoB = miastoB;
	}
	void setNumerWierzcholkaA(int numerWierzcholkaA) {
		this->numerWierzcholkaA;
	}
	void setNumerWierzcholkaB(int numerWierzcholkaB) {
		this->numerWierzcholkaB;
	}
	void setDlugoscKrawedzi (double dlugoscKrawedzi) {
		this->dlugoscKrawedzi = dlugoscKrawedzi;
	}
	char getMiastoA() {
		return this->miastoA;
	}
	char getMiastoB() {
		return this->miastoB;
	}
	int getNumerWierzcholkaA() {
		return this->numerWierzcholkaA;
	}
	int getNumerWierzcholkaB() {
		return this->numerWierzcholkaB;
	}
	double getDlugoscKrawedzi() {
		return this->dlugoscKrawedzi;
	}
	void SortKrawedzie(Krawedz tab[], int n)
	{
		Krawedz temp;
		for (int i = 0; i < n; i++) {
			for (int j = n - 1; j > i; j--) {

				if (tab[j].getDlugoscKrawedzi() < tab[j - 1].getDlugoscKrawedzi()) {
					temp = tab[j];
					tab[j] = tab[j - 1];
					tab[j - 1] = temp;
				}
			}
		}

	}
};

