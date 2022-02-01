#include <iostream>
#include <windows.h>
#include<algorithm>
#include <fstream>
#include <vector>
#include <conio.h>
#include <sstream>

using namespace std;

struct Adresat
{
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};

vector <string> podzielLinijkeNaPojedynczeDaneAdresata(string linijkaWszystkichDanychAdresata)
{
    vector <string> pojedynczeDaneAdresata;
    string danaAdresata = "";

    for (int pozycjaWyrazu = 0; pozycjaWyrazu <= linijkaWszystkichDanychAdresata.size(); pozycjaWyrazu++)
    {
        if (linijkaWszystkichDanychAdresata[pozycjaWyrazu] != '|' )
        {
            danaAdresata += linijkaWszystkichDanychAdresata[pozycjaWyrazu];
        }
        else
        {
            pojedynczeDaneAdresata.push_back(danaAdresata);
            danaAdresata = "";
        }
    }
    return pojedynczeDaneAdresata;
}

void wczytajAdresatowZPliku(vector<Adresat>&adresaci)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    int id;
    vector <string> pojedynczeDaneAdresata;
    string linia;
    string linijkaWszystkichDanychAdresata;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good())
    {
        while(getline(plik,linia))
        {
            linijkaWszystkichDanychAdresata=linia;
            pojedynczeDaneAdresata=podzielLinijkeNaPojedynczeDaneAdresata(linijkaWszystkichDanychAdresata);

            adresat.id = atoi(pojedynczeDaneAdresata[0].c_str());
            adresat.imie = pojedynczeDaneAdresata[1];
            adresat.nazwisko = pojedynczeDaneAdresata[2];
            adresat.numerTelefonu = pojedynczeDaneAdresata[3];
            adresat.email = pojedynczeDaneAdresata[4];
            adresat.adres = pojedynczeDaneAdresata[5];

            adresaci.push_back(adresat);
        }
        plik.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
}

string zmienLiteryNaDuze(string wyraz)
{
  transform(wyraz.begin(),wyraz.end(),wyraz.begin(),::toupper);
  return wyraz;
}

void zapiszAdresata(vector<Adresat>&adresaci)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    int id;
    if(adresaci.size()==0)
    {
        id=1;
    }
    else
    {
        id=adresaci[adresaci.size()-1].id+1;
    }

    cout<<"Podaj imie i nazwisko adresta: ";
    cin>>imie>>nazwisko;
    //aby program nie traktowal jako rozne tych samych imion i nazwisk ze wzgledu na wielkosc liter
    imie=zmienLiteryNaDuze(imie);
    nazwisko=zmienLiteryNaDuze(nazwisko);

    int i=0;
    while (i<adresaci.size())
    {
        imie=zmienLiteryNaDuze(imie);
        nazwisko=zmienLiteryNaDuze(nazwisko);

        if(adresaci[i].imie == imie && adresaci[i].nazwisko == nazwisko)
        {
            cout<<"Taka osoba jest juz zapisana. Wpisz inne imie i nazwisko: ";
            cin>>imie>>nazwisko;
            i=0;
        }
        else
        {
            i++;
        }
    }

    cout<<"Podaj nr telefonu: ";
    cin.sync(); // oprozniam bufor
    getline(cin, numerTelefonu);
    cout<<"Podaj email: ";
    cin>>email;
    cout<<"Podaj adres: ";
    cin.sync(); // oprozniam bufor
    getline(cin, adres);

    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.email = email;
    adresat.adres = adres;
    adresat.id = id;

    adresaci.push_back(adresat);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik<<id<<"|"<<imie<<"|"<<nazwisko<<"|"<<numerTelefonu<<"|"<<email<<"|"<<adres<<"|"<<endl;
        plik.close();

        cout<<"Adresat zapisany do ksiazki adresowej"<<endl;
        Sleep(1000);
    }
    else
    {
        cout<<"Nie mozna otworzyc pliku: \"KsiazkaAdresowa.txt\""<<endl;
    }
}

void wypiszAdresatow(vector<Adresat>&adresaci, int i)
{
    cout<<"id: "<<adresaci[i].id<<"|imie: "<<adresaci[i].imie<<"|nazwisko: "<<adresaci[i].nazwisko<<"|tel.: "<<adresaci[i].numerTelefonu<<"|email: "<<adresaci[i].email<<"|adres: "<<adresaci[i].adres<<"|"<<endl;
}

bool sprawdzCzyImieWystepujeWKsiazce (vector<Adresat>&adresaci, string imie)
{
    bool istnieje=false;

    for (int i=0; i<adresaci.size(); i++)
    {
        if(adresaci[i].imie == imie)
            istnieje=true;
    }
    return istnieje;
}

void wyszukajPoImieniu(vector<Adresat>&adresaci)
{
    if(adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        string imie;
        cout<<"Podaj szukane imie: ";
        cin>>imie;
        imie=zmienLiteryNaDuze(imie);

        if(sprawdzCzyImieWystepujeWKsiazce (adresaci, imie)==true)
        {
            for (int i=0; i<adresaci.size(); i++)
            {
                if(adresaci[i].imie == imie)
                {
                    wypiszAdresatow(adresaci, i);
                }
            }
        }
        else cout<<"Brak osob o imieniu \""<<imie<<"\" w ksiazce adresowej!"<<endl;
        system("pause");
    }
}

bool sprawdzCzyNazwiskoWystepujeWKsiazce (vector<Adresat>&adresaci, string nazwisko)
{
    bool istnieje=false;

    for (int i=0; i<adresaci.size(); i++)
    {
        if(adresaci[i].nazwisko == nazwisko)
            istnieje=true;
    }
    return istnieje;
}

void wyszukajPoNazwisku(vector<Adresat>&adresaci)
{
    if (adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        string nazwisko;
        cout<<"Podaj szukane nazwisko: ";
        cin>>nazwisko;
        nazwisko=zmienLiteryNaDuze(nazwisko);

        if(sprawdzCzyNazwiskoWystepujeWKsiazce (adresaci, nazwisko)==true)
        {

            for (int i=0; i<adresaci.size(); i++)
            {
                if(adresaci[i].nazwisko == nazwisko)
                {
                    wypiszAdresatow(adresaci, i);
                }
            }
        }
        else cout<<"Brak osob o nazwisku \""<<nazwisko<<"\" w ksiazce adresowej!"<<endl;
        system("pause");
    }
}

void wypiszWszystkichAdresatow(vector<Adresat>&adresaci)
{
    if(adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        cout<<"Wszyscy adresaci ("<<adresaci.size()<<") z ksiazki adresowej: "<<endl<<endl;
        for (int i=0; i<adresaci.size(); i++)

        {
            wypiszAdresatow(adresaci,i);
        }
        system("pause");
    }
}

bool sprawdzCzyIdWystepujeWKsiazce (vector<Adresat>&adresaci, int id)
{
    bool istnieje=false;

    for (int i=0; i<adresaci.size(); i++)
    {
        if(adresaci[i].id == id)
            istnieje=true;
    }
    return istnieje;
}

void ZapiszZmienioneDaneDoPliku (vector<Adresat>&adresaci)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    int id;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out);

    if (plik.good())
    {
        for (int i=0; i<adresaci.size(); i++)
        {
            plik<<adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
        }
        plik.close();

    }
    else
    {
        cout<<"Nie mozna otworzyc pliku: \"KsiazkaAdresowa.txt\""<<endl;
    }
}

void usunAdresata(vector<Adresat>&adresaci)
{
    int id;
    char znak;
    if(adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        cout<<"Wybierz z ponizszej listy id adresata, ktorego chcesz usunac z ksiazki adresowej: "<<endl<<endl;
        wypiszWszystkichAdresatow(adresaci);
        cin>>id;

        if(sprawdzCzyIdWystepujeWKsiazce (adresaci, id)==true)
        {
            for (auto it= adresaci.begin(); it != adresaci.end(); it++)
            {
                if(it->id==id)
                {
                    cout<<"Jesli jestes pewny, ze chcesz usunac adresata o id \""<<id<<"\", wcisnij \"t\""<<endl;

                    znak = getch();

                    if (znak == 't')
                    {
                        cout<<"Adresat o id \""<<id<<"\" zostal usuniety z ksiazki adresowej"<<endl;
                        Sleep(2000);
                        adresaci.erase(it);
                        ZapiszZmienioneDaneDoPliku (adresaci);
                        break;
                    }
                }
            }
        }
        else cout<<"Brak osob o id \""<<id<<"\" w ksiazce adresowej!"<<endl;
        system("pause");
    }
}

void edytujAdresata(vector<Adresat>&adresaci)
{
    char wybor;

    if(adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        while(true)
        {
            system("cls");
            int id;

            cout<<"Wybierz z ponizszej listy id adresata, ktorego dane chcesz edytowac: "<<endl<<endl;
            wypiszWszystkichAdresatow(adresaci);
            cin>>id;
            system("cls");

            if(sprawdzCzyIdWystepujeWKsiazce (adresaci, id)==true)
            {
                for (int i=0; i<adresaci.size(); i++)
                {
                    if(adresaci[i].id == id)
                    {
                        cout<<"Jakie dane adresata:"<<endl;
                        wypiszAdresatow(adresaci, i);
                        cout<<"chcesz edytowac?"<<endl<<endl;
                        cout<<"1 - imie"<<endl;
                        cout<<"2 - nazwisko"<<endl;
                        cout<<"3 - numer telefonu"<<endl;
                        cout<<"4 - email"<<endl;
                        cout<<"5 - adres"<<endl;
                        cout<<"6 - powrot do menu"<<endl;
                        cout<<endl<<"Twoj wybor: ";
                        cin>>wybor;
                        cout<<endl;

                        if (wybor=='1')
                        {
                            string imie;
                            cout<<"Wpisz nowe imie: ";
                            cin>>imie;
                            imie=zmienLiteryNaDuze(imie);
                            adresaci[i].imie = imie;
                            ZapiszZmienioneDaneDoPliku (adresaci);
                            cout<<"Imie zostalo zmienione na: \""<<imie<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='2')
                        {
                            string nazwisko;
                            cout<<"Wpisz nowe nazwisko: ";
                            cin>>nazwisko;
                            nazwisko=zmienLiteryNaDuze(nazwisko);
                            adresaci[i].nazwisko = nazwisko;
                            ZapiszZmienioneDaneDoPliku (adresaci);
                            cout<<"nazwisko zostalo zmienione na: \""<<nazwisko<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='3')
                        {
                            string numerTelefonu;
                            cout<<"Wpisz nowy numer telefonu: ";
                            cin.sync(); // oprozniam bufor
                            getline(cin, numerTelefonu);
                            adresaci[i].numerTelefonu = numerTelefonu;
                            ZapiszZmienioneDaneDoPliku (adresaci);
                            cout<<"Numer telefonu zostal zmieniony na: \""<<numerTelefonu<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='4')
                        {
                            string email;
                            cout<<"Wpisz nowy adres email: ";
                            cin>>email;
                            adresaci[i].email = email;
                            ZapiszZmienioneDaneDoPliku (adresaci);
                            cout<<"Adres email zostal zmieniony na: \""<<email<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='5')
                        {
                            string adres;
                            cout<<"Wpisz nowy adres: ";
                            cin.sync(); // oprozniam bufor
                            getline(cin, adres);
                            adresaci[i].adres = adres;
                            ZapiszZmienioneDaneDoPliku (adresaci);
                            cout<<"Adres zostal zmieniony na: \""<<adres<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='6')
                        {
                            return;
                        }
                    }
                }
            }
            else cout<<"Brak osob o id \""<<id<<"\" w ksiazce adresowej!"<<endl;
            system("pause");
        }
    }
}

int main()
{
    vector <Adresat> adresaci;
    char wybor;

    wczytajAdresatowZPliku(adresaci);

    while(true)
    {
        system("cls");
        cout<<"1. Dodaj adresata"<<endl;
        cout<<"2. Wyszukaj po imieniu"<<endl;
        cout<<"3. Wyszukaj po nazwisku"<<endl;
        cout<<"4. Wyswietl wszystkich adresatow"<<endl;
        cout<<"5. Usun adresata"<<endl;
        cout<<"6. Edyduj adresata"<<endl;
        cout<<"9. Zakoncz program"<<endl;
        cout<<endl<<"Twoj wybor: ";
        cin>>wybor;
        cout<<endl;

        if (wybor=='1')
        {
            zapiszAdresata(adresaci);
        }
        else if (wybor=='2')
        {
            wyszukajPoImieniu(adresaci);
        }
        else if (wybor=='3')
        {
            wyszukajPoNazwisku(adresaci);            ;
        }
        else if (wybor=='4')
        {
            wypiszWszystkichAdresatow(adresaci);
        }
        else if (wybor=='5')
        {
            usunAdresata(adresaci);
        }
        else if (wybor=='6')
        {
            edytujAdresata(adresaci);
        }
        else if (wybor=='9')
        {
            exit(0);
        }
    }
    return 0;
}
