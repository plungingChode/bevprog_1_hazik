#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

#define ellenoriz(x) if (x) feladat++; else cout << "a feltetel nem teljesult a " << __LINE__ << ". sorban" << endl

/** Szabályok:
    - kódolni az ///Innetol ///Idáig részen lehet
    - csak az a beugró érvényes, amely nem tartalmaz semmilyen kód változtatást a main()-ben, és már nincs benne kikommentezve semmi
    - az eredeti main() egészében nem kikommentezhetõ!
    - az "ellenoriz"-en kívül nem tartalmaz #define sorokat, és azt sem szabad megváltoztatni
    - ha szükségesnek érzed a standard C++ könyvtárból adhatsz hozzá #include-okat
*/

/// Innentol

struct Kontener
{
    string kod;
    string fajta;
    double maxaru;
    double toltottseg;
};

struct Hajo
{
    string nev;
    int kapacitas;
    vector<Kontener> rakter;
};

void berakod(Kontener& k, Hajo& h)
{
    if (h.rakter.size() < (size_t)h.kapacitas)
    {
        h.rakter.push_back(k);
    }
}

double arukirak(const string& fajta, double mennyiseg, Hajo& h)
{
    for (Kontener& k : h.rakter)
    {
        if (k.fajta == fajta)
        {
            if (k.toltottseg < mennyiseg)
            {
                mennyiseg -= k.toltottseg;
                k.toltottseg = 0;
            }
            else
            {
                k.toltottseg -= mennyiseg; 
                return 0;
            }
        }
    }
    return mennyiseg;
}



/// Idaig


int main() {

    srand(time(0));
    int feladat = 0;

    Kontener k1;
    Kontener k2;
    Kontener k3;

    k1.kod        = "A236FG";
    k1.fajta      = "aru szallito";
    k1.maxaru     = 50.5;
    k1.toltottseg = 48.7;

    k2.kod        = "H112KI";
    k2.fajta      = "huto";
    k2.maxaru     = 20000;
    k2.toltottseg = 15000;

    k3.kod        = "T10GO";
    k3.fajta      = "tartaly";
    k3.maxaru     = 35000;
    k3.toltottseg = 21894.1;

    ellenoriz( k1.maxaru+k2.maxaru+k3.maxaru == 55050.5 && k2.kod.compare( "H112KI" ) == 0 && k3.toltottseg == 21894.1 && k1.fajta.compare( "aru szallito" ) == 0 );


    Hajo h1;
    h1.nev = "TISZA";
    h1.kapacitas = 5;

    ellenoriz( h1.rakter.size() == 0 && h1.kapacitas == 5 && h1.nev.compare("TISZA") == 0 );


    berakod( k3, h1 );
    berakod( k2, h1 );
    berakod( k1, h1 );
    Kontener k4 = {"A017GJ", "aru szallito", 50.5, 45.1};   berakod( k4, h1 );
    Kontener k5 = {"A846SO", "aru szallito", 75.0, 73.2};   berakod( k5, h1 );
    Kontener k6 = {"H218CA", "huto", 20000, 17890};         berakod( k6, h1 );

    ellenoriz( h1.rakter.size() == (size_t)h1.kapacitas && h1.rakter[rand()%3+2].fajta.compare( "aru szallito" ) == 0 );


    Hajo h2;
    h2.nev = "URAL";
    h2.kapacitas = 3;
    berakod( k6, h2 );
    Kontener k7 = {"H627EB","huto", 15000, 14000};          berakod( k7, h2 );
    Kontener k8 = {"H213VI","huto", 15000, 12784.4};        berakod( k8, h2 );

    /// arukirak()
    ///     paraméterek: a megadott típusú áruból, az adott mennyiséget szereténk kipakolni, az adott hajó rakteréből
    ///     viszatérési érték: az adott típusú aruból mekkora igényt nem sikerült kielégíteni (0, ha hiánytalanul teljesítettük az igényt)
    double hiany1 = arukirak( "aru szallito", 200.0, h1  );
    double hiany2 = arukirak( "tartaly", 23000, h1 );
    double hiany3 = arukirak( "huto", 35000, h2 );

    int x = rand()%3+2;
    ellenoriz( fabs( hiany1 - 33 )<0.01 && fabs( hiany2 - 1105.9 )<0.01 && fabs( hiany3 )<0.01 &&
               fabs( (h2.rakter[0].toltottseg + h2.rakter[1].toltottseg + h2.rakter[2].toltottseg) - 9674.4 )<0.01 &&
               h1.rakter[x].toltottseg == h1.rakter[x].toltottseg );


    cout << "\n" << feladat << "/4 feladat" <<endl;
    if( feladat == 4 ) cout << "Hivj egy felugyelot, hogy lepontozzon!" <<endl;
    return 0;
}
