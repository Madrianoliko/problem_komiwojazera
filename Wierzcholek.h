#pragma once

using namespace std;

class Wierzcholek
{
public:

	char miasto;
	double wspolrzednaX;
	double wspolrzednaY;
	int liczbaUzyc = 0;
	int numerWierzcholka;
	bool bylOdwiedzony = false;;
	int numerUnii = 0;

	void setMiasto(char miasto) {
		this->miasto = miasto;
	}

	void setWspolrzednaX(double wspolrzednaX) {
		this->wspolrzednaX = wspolrzednaX;
	}

	void setWspolrzednaY(double wspolrzednaY) {
		this->wspolrzednaX = wspolrzednaY;
	}
	void setNumerWierzcholka(int numerWierzcholka) {
		this->numerWierzcholka = numerWierzcholka;
	}
	void setNumerUnii(int numerUnii) {
		this->numerUnii = numerUnii;
	}
	

	char getMiasto() {
		return this->miasto;
	}

	double getWspolrzednaX() {
		return this->wspolrzednaX;
	}

	double getWspolrzednaY() {
		return this->wspolrzednaY;
	}
	int getNumerWierzcholka() {
		return this->numerWierzcholka;
	}
	int getNumerUnii() {
		return this->numerUnii;
	}
	void setBylOdwiedzony(bool bylOdwiedzony) {
		this->bylOdwiedzony = bylOdwiedzony;
	}
	bool getBylOdwiedzony() {
		return this->bylOdwiedzony;
	}

	void SortX(Wierzcholek tab[], int n)
	{
		Wierzcholek temp;
		for (int i = 0; i < n; i++) {
			for (int j = n - 1; j > i; j--) {

				if (tab[j].getWspolrzednaX() < tab[j - 1].getWspolrzednaX()) {
					temp = tab[j];
					tab[j] = tab[j - 1];
					tab[j - 1] = temp;
				}
			}
		}

	}


	void SortY(Wierzcholek tab[], int n)
	{
		Wierzcholek temp;
		for (int i = 0; i < n; i++) {
			for (int j = n - 1; j > i; j--) {

				if (tab[j].getWspolrzednaY() < tab[j - 1].getWspolrzednaY()) {
					temp = tab[j];
					tab[j] = tab[j - 1];
					tab[j - 1] = temp;
				}
			}
		}

	}
	 
};

