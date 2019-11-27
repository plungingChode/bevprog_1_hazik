#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

#define ellenoriz(felt, pont) if (felt) pont++; else cerr << "Nem teljesul a feltetel a " << __LINE__<< ". sorban." <<endl;

/* Szabalyok:
    - csak az a beugr� �rv�nyes, amely nem tartalmaz semmilyen v�ltoztat�st a main()-ben,
        �s m�r nincs benne kommentezve semmi
    - az "ellenoriz"-en k�v�l nem tartalmaz #define sorokat, �s azt sem szabad megv�ltoztatni
*/

// Innentol

int fv(int sz)
{
    return sz * -1;
}

struct Hallgato
{
    string nev;
    vector<int> jegyek;
};

void jegyatlag(const Hallgato& h, float& atlag)
{
    atlag = 0;
    for (const int i : h.jegyek)
    {
        atlag += i;
    }
    atlag /= h.jegyek.size();
}

string monogram(const Hallgato& h)
{
    string nev = h.nev;

    string mg = "";
    mg += nev[0];
    size_t spc = nev.find(' ');

    while (spc != string::npos)
    {
        mg += nev[spc + 1];
        spc = nev.find(' ', spc + 1);
    }

    return mg;
}

// Idaig

int main()
{
    int pont = 0;

    int a = fv(4);
    int b = fv(2);
    ellenoriz(a == -4 && b == -2 , pont)

    Hallgato h1;
    h1.nev="Gipsz Jakab";
    h1.jegyek.push_back(5);
    ellenoriz(h1.jegyek.size()==1 && h1.nev=="Gipsz Jakab" , pont)

    h1.jegyek.push_back(4);
    float atlag;
    jegyatlag(h1, atlag);
    ellenoriz(atlag==4.5 , pont)

    Hallgato h2;
    h2.nev="Nagy Janos Balazs";
    string m1 = monogram(h1);
    string m2 = monogram(h2);
    ellenoriz(m1=="GJ" && m2=="NJB" , pont)


    cout << endl << pont << "/4 pont";
}
