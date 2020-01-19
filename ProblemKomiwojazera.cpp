#include <iostream>
#include <fstream>
#include <string>
#include "Wierzcholek.h"
#include <Windows.h>
#include "Krawedz.h"

using namespace std;


int main()
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //odczytanie pliku 1 w celu zliczenia lini

    ifstream file, file2;
    int i = 0, x = 0, j = 0, koniec = 0;
    long  int value;
    string choose;

    file.open("zadanie2-miasta.txt");
    if (!file)
    {
        cout << "Nie można otworzyc pliku :(";
        exit(0);
    }
    string unused;
    while (getline(file, unused)) {
        ++i;
    }
    file.close();

    //odczytanie pliku 2 odczytania danych

    file2.open("zadanie2-miasta.txt");
    if (!file2)
    {
        cout << "Nie można otworzyc pliku :(";
        exit(0);
    }


    //deklaracja tablic dynamicznych

    Wierzcholek* tabWierzcholkow;
    tabWierzcholkow = new Wierzcholek[i];
    Wierzcholek* tabWierzcholkowPrim;
    tabWierzcholkowPrim = new Wierzcholek[i];
    Wierzcholek* tabWierzcholkowBis;
    tabWierzcholkowBis = new Wierzcholek[i];

    // zczytanie danych
    for (int k=0; k < i; k++) {
        file2 >> tabWierzcholkow[k].miasto;
        file2 >> tabWierzcholkow[k].wspolrzednaY;
        file2 >> tabWierzcholkow[k].wspolrzednaX;
    }
    file2.close();
    
    //kopiowanie tablicy w celu obliczenia maksymalnych odleglosci na osi OX i OY w celu stworzenia skalowalnego wykresu

    for (int k = 0; k < i; k++) {
        tabWierzcholkowPrim[k] = tabWierzcholkow[k];
    }
    // testowanie poprawnego wyswietlania oraz realizacja podpunktu b)

    for (int k = 0; k < i; k++) {
        cout << tabWierzcholkowPrim[k].getMiasto() << " ";
        cout << tabWierzcholkowPrim[k].getWspolrzednaY() << " ";
        cout << tabWierzcholkowPrim[k].getWspolrzednaX() << endl;;
        tabWierzcholkow[k].numerWierzcholka = k;
    }

    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // oznaczanie osi OY z gory

    //sortowanie po Y
    for (int k = 0; k < i; k++) {
        tabWierzcholkowPrim->SortY(tabWierzcholkowPrim, i);
    }
    for (int k = 0; k < i; k++) {
        tabWierzcholkowBis[k] = tabWierzcholkowPrim[k];
    }

    //wyznaczanie dlugosci osi OY
    double dlugoscOY = tabWierzcholkowPrim[i - 1].getWspolrzednaY() -
        tabWierzcholkowPrim[0].getWspolrzednaY();

    Position.Y = i;
    Position.X = 3;
    SetConsoleCursorPosition(hOut,
        Position);
    cout << tabWierzcholkowPrim[i - 1].getWspolrzednaY();

    //Rysowanie Osi OY
    Position.X = 10;
    Position.Y = i;
    SetConsoleCursorPosition(hOut,
        Position);
    cout << "^";

    for (int y = i + 1; y < i + dlugoscOY; y++) {
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        Position.Y = y;
        SetConsoleCursorPosition(hOut,
            Position);
        cout << "|";
    }

    // Oznaczanie osi OY dol
    Position.Y = i + dlugoscOY;
    Position.X = 3;
    SetConsoleCursorPosition(hOut,
        Position);
    cout << tabWierzcholkowPrim[0].getWspolrzednaY();

    //sortowanie po X
    for (int k = 0; k < i; k++) {
        tabWierzcholkowPrim->SortX(tabWierzcholkowPrim, i);
    }

    // Oznaczani osi OX z lewej;
    Position.Y = i + dlugoscOY + 1;
    Position.X = 5;
    SetConsoleCursorPosition(hOut,
        Position);
    cout << tabWierzcholkowPrim[0].getWspolrzednaX();

    //wyznaczanie dlugosci osi OX
    double dlugoscOX = tabWierzcholkowPrim[i - 1].getWspolrzednaX() -
        tabWierzcholkowPrim[0].getWspolrzednaX();

    //rysowanie osi x
    Position.Y = i + dlugoscOY;

    for (int x = 0 + 10; x < 10 + dlugoscOX; x++) {
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        Position.X = x;
        SetConsoleCursorPosition(hOut,
            Position);
        cout << "-";
    }
    //oznaczenie osi OX z prawej 
    cout << ">" << tabWierzcholkowPrim[i - 1].getWspolrzednaX();
    
    //rysowanie punktow
    for (int k = 0; k < i; k++)
    {

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        Position.X = tabWierzcholkow[k].getWspolrzednaX() + 10 - tabWierzcholkowPrim[0].getWspolrzednaX();
        Position.Y = tabWierzcholkowBis[i - 1].getWspolrzednaY() + i - tabWierzcholkow[k].getWspolrzednaY();
        SetConsoleCursorPosition(hOut,
            Position);
        cout << "(" << tabWierzcholkow[k].getNumerWierzcholka() << ")";
    }

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = dlugoscOY + i + 3;
    SetConsoleCursorPosition(hOut,
        Position);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    double drogaBezOpt = 0;
    double* tabOdleglosci;
    tabOdleglosci = new double[i];




    for (int k = 0; k < i - 1; k++) {
        tabOdleglosci[k] = sqrt(pow((((tabWierzcholkow[k].getWspolrzednaX() - tabWierzcholkow[k + 1].getWspolrzednaX())) * 71), 2)
            + pow((((tabWierzcholkow[k].getWspolrzednaY() - tabWierzcholkow[k + 1].getWspolrzednaY())) * 111), 2));
        drogaBezOpt = drogaBezOpt + tabOdleglosci[k];
    }
    cout << "Droga bez optymalizacji: " << drogaBezOpt << " km";


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Wyznaczenie ((i-1) * ((i-1) + 1)) / 2 krawedzi  miedzy wierzcholkami


    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = dlugoscOY + i + 5;
    SetConsoleCursorPosition(hOut,
        Position);

    int iloscKrawedzi = ((i-1) * ((i-1) + 1)) / 2;
    

    Krawedz* tabKrawedzi;
    tabKrawedzi = new Krawedz[iloscKrawedzi];
    int iterator=0;
    
    // uzaleznienie tabKrawedzi od tabWierzcholkow
  
        for (int k = 0; k < i - 1; k++) {
            for (int j = k + 1; j < i; j++)
            {
               
                tabKrawedzi[iterator].miastoA = tabWierzcholkow[k].getMiasto();
                tabKrawedzi[iterator].miastoB = tabWierzcholkow[j].getMiasto();
                tabKrawedzi[iterator].numerWierzcholkaA = tabWierzcholkow[k].getNumerWierzcholka();
                tabKrawedzi[iterator].numerWierzcholkaB = tabWierzcholkow[j].getNumerWierzcholka();
                tabKrawedzi[iterator].dlugoscKrawedzi = sqrt(pow((((tabWierzcholkow[k].getWspolrzednaX() - tabWierzcholkow[j].getWspolrzednaX())) * 71), 2) +
                    pow((((tabWierzcholkow[k].getWspolrzednaY() - tabWierzcholkow[j].getWspolrzednaY())) * 111), 2));
                //cout << tabKrawedzi[iterator].numerWierzcholkaA << " ";
                //cout << tabKrawedzi[iterator].numerWierzcholkaB << " ";
                iterator++;
                
                
            }
        }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //sortowanie po najmnieszej krawedzi

        for (int k = 0; k < iloscKrawedzi; k++) {    
           
            tabKrawedzi->SortKrawedzie(tabKrawedzi, iloscKrawedzi);            

        }


    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = dlugoscOY + i + 6;
    SetConsoleCursorPosition(hOut,
        Position);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Wyznaczanie najkrotszej drogi

    //Pobranie pierwszej krawedzi
    
    Krawedz* tabKrawedziOpt;
    tabKrawedziOpt = new Krawedz[i];

    for (int k = 0; k < i; k++) {
        if (tabKrawedzi[0].getMiastoA() == tabWierzcholkow[k].getMiasto()) {
            tabWierzcholkow[k].liczbaUzyc++;
          //  tabWierzcholkow[k].bylOdwiedzony = true;
         //   cout << tabWierzcholkow[k].getNumerWierzcholka()<< "  ";
            tabWierzcholkow[k].setNumerUnii(1);
            }
        if (tabKrawedzi[0].getMiastoB() == tabWierzcholkow[k].getMiasto()) {
            tabWierzcholkow[k].liczbaUzyc++;
        //    cout << tabWierzcholkow[k].getNumerWierzcholka()<< endl;
            tabWierzcholkow[k].setNumerUnii(1);
        }
    }

    tabKrawedziOpt[0] = tabKrawedzi[0];
    
    double drogaOpt = 0;
    
    // pobranie reszty krawedzi ze sprawdzeniem:
                                   // czy istnieja juz dwie odnogi
                                   // czy nie zachodzi cykl

    iterator = 1;
    int numerNowejUni = 2;
    int nowaUnia;

        for (int j=1; j < iloscKrawedzi; j++) {
            for (int k = 0; k < i; k++) {
                if (tabKrawedzi[j].getMiastoA() == tabWierzcholkow[k].getMiasto()) {
                    if ((tabWierzcholkow[k].liczbaUzyc < 2)) {
                        for (int l = 0; l < i; l++) {
                            if (tabKrawedzi[j].getMiastoB() == tabWierzcholkow[l].getMiasto()){
                                if (tabWierzcholkow[l].liczbaUzyc < 2) {



                                    if (tabWierzcholkow[k].getNumerUnii() != tabWierzcholkow[l].getNumerUnii()) {
                                        if (tabWierzcholkow[k].getNumerUnii() == 0) {
                                            tabWierzcholkow[k].setNumerUnii(tabWierzcholkow[l].getNumerUnii());
                                            //cout << "               ";
                                        }
                                        
                                        else if (tabWierzcholkow[l].getNumerUnii() == 0) {
                                            tabWierzcholkow[l].setNumerUnii(tabWierzcholkow[k].getNumerUnii());
                                            //cout << "        ";
                                        }
                                        else {
                                            nowaUnia = tabWierzcholkow[l].getNumerUnii();
                                            for (int p = 0; p < i; p++) {
                                                if (tabWierzcholkow[p].getNumerUnii() == nowaUnia) {
                                                    tabWierzcholkow[p].setNumerUnii(tabWierzcholkow[k].getNumerUnii());
                                                }
                                            }
                                        }
                                   
                                   /// // cout << tabKrawedzi[j].getNumerWierzcholkaA() << "  ";
                                    /// / cout << tabKrawedzi[j].getNumerWierzcholkaB() << endl;
                                        drogaOpt = drogaOpt + tabKrawedzi[j].getDlugoscKrawedzi();
                                        tabKrawedziOpt[iterator] = tabKrawedzi[j];


                                        tabWierzcholkow[k].liczbaUzyc++;
                                        tabWierzcholkow[l].liczbaUzyc++;

                                        iterator++;
                                    } else if((tabWierzcholkow[k].getNumerUnii() == 0) && (tabWierzcholkow[l].getNumerUnii() == 0)){

                                        tabWierzcholkow[k].setNumerUnii(numerNowejUni);
                                        tabWierzcholkow[l].setNumerUnii(numerNowejUni);
                                        numerNowejUni++;

                                    //    cout << tabKrawedzi[j].getNumerWierzcholkaA() << "  ";
                                  //     cout << tabKrawedzi[j].getNumerWierzcholkaB() << endl;
                                        drogaOpt = drogaOpt + tabKrawedzi[j].getDlugoscKrawedzi();
                                        tabKrawedziOpt[iterator] = tabKrawedzi[j];


                                        tabWierzcholkow[k].liczbaUzyc++;
                                        tabWierzcholkow[l].liczbaUzyc++;
                                        iterator++;
                                    }
                               
                                }
                            }
                        }
                    }
                }
            }
        }


        for (int k = 0; k < i; k++) {
            if (tabWierzcholkow[k].liczbaUzyc == 1) {
                for (int j = 0; j < i; j++) {
                    if (tabWierzcholkow[j].liczbaUzyc == 1 && tabWierzcholkow[k].getNumerWierzcholka() != tabWierzcholkow[j].getNumerWierzcholka()) {
                        for (int p = 0; p < iloscKrawedzi; p++) {
                            if (tabKrawedzi[p].getNumerWierzcholkaA() == tabWierzcholkow[k].getNumerWierzcholka() && tabKrawedzi[p].getNumerWierzcholkaB() == tabWierzcholkow[j].getNumerWierzcholka()) {
                                tabKrawedziOpt[iterator] = tabKrawedzi[p];
                                //cout << tabWierzcholkow[j].getNumerWierzcholka() << "  ";
                                //cout << tabWierzcholkow[k].getNumerWierzcholka() << endl;
                                iterator++;
                            }
                            else if (tabKrawedzi[p].getNumerWierzcholkaB() == tabWierzcholkow[k].getNumerWierzcholka() && tabKrawedzi[p].getNumerWierzcholkaB() == tabWierzcholkow[j].getNumerWierzcholka()) {
                                tabKrawedziOpt[iterator] = tabKrawedzi[p];
                               //cout << tabWierzcholkow[j].getNumerWierzcholka() << "  ";
                               //cout << tabWierzcholkow[k].getNumerWierzcholka() << endl;
                                iterator++;
                            }
                        }
                    }
                }
            }
        }


        Krawedz* tabKrawedziOptHammilton;
        tabKrawedziOptHammilton = new Krawedz[iterator];

        /*for (int k = 0; k < iterator; k++) {
            cout << tabKrawedziOpt[k].getNumerWierzcholkaA() << endl;
            cout << tabKrawedziOpt[k].getNumerWierzcholkaB() << endl;
        }*/
        
        
        tabKrawedziOptHammilton[0].numerWierzcholkaA = tabKrawedziOpt[0].getNumerWierzcholkaA();
        tabKrawedziOptHammilton[0].numerWierzcholkaB = tabKrawedziOpt[0].getNumerWierzcholkaB();

        tabKrawedziOpt[0].numerWierzcholkaA = -1;
        tabKrawedziOpt[0].numerWierzcholkaB = -1;

        cout << "Najlepszy cykl drogi to: " << endl;
        //cout << endl << tabKrawedziOptHammilton[0].getNumerWierzcholkaA() << " -> ";
        //cout << tabKrawedziOptHammilton[0].getNumerWierzcholkaB() << " -> ";

        
        int ostatni = 0;
        // posortowanie krawedzi w celu wyznaczenia wyswietlenia drogi
        int k = 0;
        while (k < iterator - 1) {


            for (int j = 0; j < iterator; j++) {
                if (tabKrawedziOptHammilton[k].getNumerWierzcholkaB() == tabKrawedziOpt[j].getNumerWierzcholkaA()) {

                    tabKrawedziOptHammilton[k + 1] = tabKrawedziOpt[j];

                    tabKrawedziOpt[j].numerWierzcholkaA = -1;
                    tabKrawedziOpt[j].numerWierzcholkaB = -1;
                    cout << tabKrawedziOptHammilton[k + 1].getNumerWierzcholkaB() << " -> ";
                    if (k == iterator - 2) {
                        ostatni = tabKrawedziOptHammilton[k + 1].getNumerWierzcholkaA();
                    }
                    k = k + 1;
                       

                }
                else if (tabKrawedziOptHammilton[k].getNumerWierzcholkaB() == tabKrawedziOpt[j].getNumerWierzcholkaB()) {

                    tabKrawedziOptHammilton[k + 1] = tabKrawedziOpt[j];

                    tabKrawedziOpt[j].numerWierzcholkaA = -1;
                    tabKrawedziOpt[j].numerWierzcholkaB = -1;
                    cout << tabKrawedziOptHammilton[k + 1].getNumerWierzcholkaA() << " -> " ;
                    if (k == iterator - 2) {
                        ostatni = tabKrawedziOptHammilton[k + 1].getNumerWierzcholkaA();
                    }
                    k = k + 1;

                }
                else if (tabKrawedziOptHammilton[k].getNumerWierzcholkaA() == tabKrawedziOpt[j].getNumerWierzcholkaA()) {

                    tabKrawedziOptHammilton[k + 1] = tabKrawedziOpt[j];

                    tabKrawedziOpt[j].numerWierzcholkaA = -1;
                    tabKrawedziOpt[j].numerWierzcholkaB = -1;
                    cout << tabKrawedziOptHammilton[k + 1].getNumerWierzcholkaB() << " -> ";
                    if (k == iterator - 2) {
                        ostatni = tabKrawedziOptHammilton[k + 1].getNumerWierzcholkaB();
                    }
                    k = k + 1;

                }
                else if (tabKrawedziOptHammilton[k].getNumerWierzcholkaA() == tabKrawedziOpt[j].getNumerWierzcholkaB()) {

                    tabKrawedziOptHammilton[k + 1] = tabKrawedziOpt[j];

                    tabKrawedziOpt[j].numerWierzcholkaA = -1;
                    tabKrawedziOpt[j].numerWierzcholkaB = -1;
                    cout << tabKrawedziOptHammilton[k + 1].getNumerWierzcholkaA() << " -> ";
                    if (k == iterator - 2) {
                        ostatni = tabKrawedziOptHammilton[k + 1].getNumerWierzcholkaA();
                    }
                    k = k + 1;

                }

            }
        }
        if (tabKrawedziOptHammilton[0].getNumerWierzcholkaA() == ostatni) {
            cout << tabKrawedziOptHammilton[0].getNumerWierzcholkaB() << endl;
        }
        else if (tabKrawedziOptHammilton[0].getNumerWierzcholkaB() == ostatni) {
            cout << tabKrawedziOptHammilton[0].getNumerWierzcholkaA() << endl;
        }
            

        
         

        cout << endl << "Droga z optymalizacja: " << drogaOpt << " km" << endl;


    delete[] tabWierzcholkow;
    delete[] tabWierzcholkowPrim; 
    delete[] tabWierzcholkowBis;
    delete[] tabOdleglosci;
    delete[] tabKrawedzi;
    delete[] tabKrawedziOpt;
    delete[] tabKrawedziOptHammilton;
    system("PAUSE");
    return EXIT_SUCCESS;
}

