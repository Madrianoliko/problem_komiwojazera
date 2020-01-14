#include <iostream>
#include <fstream>
#include <string>
#include "Point.h"
#include <Windows.h>
#include <cstdio>

using namespace std;
   
int main(int argc, char* argv[])
{


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
    //cout << i << endl;
    file2.open("zadanie2-miasta.txt");
    if (!file2)
    {
        cout << "Nie można otworzyc pliku :(";
        exit(0);
    }
    char* array1;
    array1 = new char[i];
    double* array2;
    array2 = new double[i];
    double* array3;
    array3 = new double[i];

    while (!file2.eof())
    {
        file2 >> array1[j];
        file2 >> array2[j];
        file2 >> array3[j];
        j++;
    }
    file2.close();

    for (int k = 0; k < i; k++)
    {
        cout << array1[k] << " ";
        cout << array2[k] << " ";
        cout << array3[k] << " \n";
    }


    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 10;
    Position.Y = 10;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,
        Position);
    cout << "^";
    for (int y=11; y < 11+16; y++) {
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        Position.Y = y;
        SetConsoleCursorPosition(hOut,
            Position);
        cout << "|";
    }
    

    for (int x = 0+10; x < 30+10; x++) {
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        Position.X = x;
        SetConsoleCursorPosition(hOut,
            Position);
        cout << "-";
    }
    cout << "> 30";
        
    for (int k = 0; k < i; k++)
    {  
        
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        Position.X = array3[k]+10;
        Position.Y = 100 - array2[k] - 29;
        SetConsoleCursorPosition(hOut,
            Position);
        cout <<"("<< k+1<<")";
    }
    
        
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 28;    
    SetConsoleCursorPosition(hOut,
        Position);

    



    system("PAUSE");
    return EXIT_SUCCESS;
}

