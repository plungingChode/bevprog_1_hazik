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

struct Szerelveny
{
    string tipus;
    int azonosito;
    int maxkapacitas;
    double kihasznaltsag;
};

struct Vonat
{
    string mozdony;
    int maximalisvontatmany;
    vector<Szerelveny> szerelvenyek;
};

void csatol(Vonat& v, Szerelveny& sz)
{
    if (v.szerelvenyek.size() < (size_t)v.maximalisvontatmany)
    {
        v.szerelvenyek.push_back(sz);
    }
}

double rakomany(Vonat& v, const string& tipus, double mennyiseg)
{
    for (Szerelveny& sz : v.szerelvenyek)
    {
        if (sz.tipus == tipus)
        {
            double befer = sz.maxkapacitas - sz.kihasznaltsag;
            if (mennyiseg <= befer)
            {
                sz.kihasznaltsag += mennyiseg;
                return 0;
            }
            else
            {
                sz.kihasznaltsag += befer;
                mennyiseg -= befer;
            }
        }
    }

    return mennyiseg;
}


/// Idaig


int main() {

    srand(time(0));
    int feladat = 0;

    Szerelveny sz1;
    sz1.tipus  = "szemely kocsi";
    sz1.azonosito = 729;
    sz1.maxkapacitas = 80;
    sz1.kihasznaltsag = 20;

    Szerelveny sz2;
    sz2.tipus = "teher vagon";
    sz2.azonosito = 14641;
    sz2.maxkapacitas = 35000;
    sz2.kihasznaltsag = 15246.5;

    Szerelveny sz3;
    sz3.tipus = "tartaly kocsi";
    sz3.azonosito = 8673;
    sz3.maxkapacitas = 25000;
    sz3.kihasznaltsag = 345.7;

    ellenoriz( sz1.tipus.compare( "szemely kocsi" ) == 0 && sz1.maxkapacitas+sz2.maxkapacitas+sz3.maxkapacitas-80 == 60000 && sqrt(sz2.azonosito)==121 && sz3.kihasznaltsag == 345.7 );


    Vonat v1;
    v1.mozdony = "Taurus";
    v1.maximalisvontatmany = 3;

    ellenoriz( v1.mozdony.compare("Taurus") == 0 && v1.maximalisvontatmany == 3 && v1.szerelvenyek.size() == 0 );


    csatol( v1, sz1 );
    Szerelveny sz4 = {"szemely kocsi", 731, 80, 45}; csatol( v1, sz4 );
    Szerelveny sz5 = {"szemely kocsi", 732, 54, 9};  csatol( v1, sz5 );
    csatol( v1, sz2 );

    ellenoriz( v1.szerelvenyek.size() == (size_t)v1.maximalisvontatmany && v1.szerelvenyek[rand()%3].tipus.compare( "szemely kocsi" ) == 0 );


    Vonat v2;
    v2.mozdony = "Bulldog";
    v2.maximalisvontatmany = 5;
    csatol( v2, sz2 );
    csatol( v2, sz3 );
    Szerelveny sz6 = {"teher vagon", 11231, 40000, 0}; csatol( v2, sz6 );
    Szerelveny sz7 = {"auto szallito", 90067, 12, 9};  csatol( v2, sz7 );
    Szerelveny sz8 = {"teher vagon", 21562, 40000, 0};  csatol( v2, sz8 );
    
    /// rakomany()
    ///     paraméterek: a megadott vonatra, az adott típusú szerelvényre szeretnénk elhelyezni, az adott rakomány mennyiséget
    ///     viszatérési érték: az adott típusú rakományból mekkora mennyiséget nem sikerült felrakni a vonatra (0, ha felfért minden)
    double maradek1 = rakomany( v2, "tartaly kocsi", 1001.2 );
    double maradek2 = rakomany( v2, "teher vagon", 88000 );
    double maradek3 = rakomany( v1, "szemely kocsi", 200 );

    int x = rand()%3;
    ellenoriz( maradek1 == maradek2 && maradek3 == 60 &&
               v2.szerelvenyek[0].kihasznaltsag == v2.szerelvenyek[0].maxkapacitas &&
               v2.szerelvenyek[1].kihasznaltsag == 1346.9 &&
               v1.szerelvenyek[x].kihasznaltsag == v1.szerelvenyek[x].maxkapacitas );


    cout << "\n" << feladat << "/4 feladat" <<endl;
    if( feladat == 4 ) cout << "Hivj egy felugyelot, hogy lepontozzon!" <<endl;
    return 0;

}
