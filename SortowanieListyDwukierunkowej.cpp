//Lista dwukierunkowa
//Emil Hotkowski
//www.algorytm.org

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Deklaracja klasy listy dwukierunkowej
class lista {
public:
    class ogniwo {
    public:
        ogniwo* next;
        ogniwo* prev;
        double value;
    };
    class interator {
    public:
        ogniwo* wsk;
        interator next(interator it);
    };
    lista(double v);
    void wyswietl();
    interator poczatek;
    interator koniec;
    interator insert_list(interator it, double v);
    interator delete_list(interator it);
    interator begin();
    interator end();
    interator get(double v);
    int size;


};

//Przyklad uzycia     
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
    while (getline(file, unused))
        ++i;
    file.close();
    cout << i << endl;
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

    


    

   
    lista Lx(i);
    lista Ly(i);
    //////pobierz wskaznik na pierwszy element listy
    lista::interator itx = Lx.begin();
    lista::interator ity = Ly.begin();
    for  (int k = 0; k < i; k++)
    {       
       Lx.insert_list(itx, array2[k]);
       itx = itx.next(itx);
       Ly.insert_list(ity, array3[k]);
       ity = ity.next(ity);
    }

    cout << "\n";
    Lx.wyswietl();
    cout << "\n";
    Ly.wyswietl();
    cout << "\n";
  

    



    ////uwtorz liste z elementem o wartosci 2
    //lista L(2);

    ////pobierz wskaznik na pierwszy element listy
    //lista::interator it = L.begin();

    ////wstaw element 3, za pierwszym elementem
    //L.insert_list(it, 3);

    ////przesun wskaznik na kolejny element
    //it = it.next(it);

    ////wstaw element o wartosci 8, za elementem o wartosci 3
    //L.insert_list(it, 8);

    ////wstaw element o wartosci 12, za elementem o wartosci 3    
    //L.insert_list(it, 12);

    ////wyswietl zawartosc listy
    //L.wyswietl();
    //cout << "\n";

    ////pobierz wskaznik na element o wartosci 8
    //it = L.get(8);
    //cout << it.wsk->value << "\n";

    //usun element o wartosci 8 z listy
    //L.delete_list(it);

    ////wyswietl zawartosc listy
    //L.wyswietl();
    //cout << "\n";

    system("PAUSE");
    return EXIT_SUCCESS;
}


//***************
// METODY
//***************

//Konstruktor listy
//tworzy nowa liste dwukierunkowa z jednym elementem o zadanej wartosci v
lista::lista(double v) {
    ogniwo* a = new ogniwo;
    a->next = a;
    a->prev = a;
    a->value = v;
    poczatek.wsk = a;
    koniec.wsk = a;
    size = 1;
}

//Wstawia nowy element do listy dwukierunkowej
//Element ma wartosc v i jest wstawiany za elementem wskazywanym przez iterator it
lista::interator lista::insert_list(interator it, double v) {
    ogniwo* a = it.wsk;
    ogniwo* b = new ogniwo;
    ogniwo* c = a->next;
    b->next = c;
    b->prev = a;
    b->value = v;
    c->prev = b;
    a->next = b;
    if (b->next == b)koniec.wsk = b; //popraw koniec listy, jezeli dodajemy za ostatnim elementem
    size++;
    return it;
}

//Usuwa z listy dwukierunkowej element wskazywany przez iteroator it
lista::interator lista::delete_list(interator it) {
    ogniwo* b = it.wsk;
    ogniwo* a = b->prev;
    ogniwo* c = b->next;
    a->next = c;
    c->prev = a;
    if (poczatek.wsk == b) poczatek.wsk = c; //popraw poczatek listy, jezeli usuwamy pierwszy element
    if (koniec.wsk == b) koniec.wsk = a;     //popraw koniec listy, jezeli usuwamy ostatni element
    delete b;
    it.wsk = a;
    size--;
    return it;
}

//Zwraca poczatek listy dwukierunkowej
lista::interator lista::begin() {
    return poczatek;
}

//Zwraca koniec listy dwukierunkowej
lista::interator lista::end() {
    return koniec;
}

//Wyswietla zwartosc listy dwukierunkowej
void lista::wyswietl() {
    interator it = poczatek;
    for (int i = 0; i < size; i++) {
        cout << it.wsk-> value << " ";
        it.wsk = it.wsk->next;
    }
}

//Zwraca wskaznik na kolejny element w liscie dwukierunkowej
lista::interator lista::interator::next(interator it) {
    it.wsk = it.wsk->next;
    return it;
}

//Zwraca wskaznik na element o zadanej wartosci v
lista::interator lista::get(double v) {
    interator it = poczatek;
    for (int i = 0; i < size; i++) {
        int x = it.wsk->value;
        if (x == v) break;
        else it.wsk = it.wsk->next;
    }
    return it;
}