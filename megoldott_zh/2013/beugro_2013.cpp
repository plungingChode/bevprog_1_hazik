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

int fv(int x)
{
    return x / 2;
}

struct Tomb
{
    int osszeg = 0;
    vector<int> v;
};

void legyen_egyenlo(Tomb& mi, Tomb mivel)
{
    mi = mivel;
}

bool egyenlo_e(const Tomb& t1, const Tomb& t2)
{
    bool egyenlo = (t1.v.size() == t2.v.size());
    if (egyenlo)
    {
        for (size_t i = 0; i < t1.v.size(); i++)
        {
            egyenlo = (t1.v[i] == t2.v[i]);
            if (!egyenlo) break;
        }
    }
    return egyenlo;
}

void osszead(Tomb& t)
{
    for (const int i : t.v)
    {
        t.osszeg += i;
    }
}

// Idaig

int main()
{
    int pont = 0;

    int a = fv(4);
    int b = fv(2);
    ellenoriz(a == 2 && b == 1 , pont)

    Tomb t;
    ellenoriz(t.v.size()==0 , pont)

    t.v = vector<int>(8,2);
    ellenoriz(t.v.size()==8 , pont)

    Tomb k;
    legyen_egyenlo(k,t);
    ellenoriz(k.v.size()==8 , pont)

    bool b1 = egyenlo_e(k,t);
    k.v[3]=3;
    bool b2 = egyenlo_e(k,t);
    ellenoriz(b1==true && b2==false , pont)

    osszead(t);
    osszead(k);
    ellenoriz( t.osszeg == 16 && k.osszeg == 17 , pont)

    cout << endl << pont << "/6 pont";
}
