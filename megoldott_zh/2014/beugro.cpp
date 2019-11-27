#include <iostream>
#include <cstdlib>
#include <ctime>
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

vector<int> csupa42(int mennyi)
{
    vector<int> v(mennyi);
    for (size_t i = 0; i < (size_t)mennyi; i++)
    {
        v[i] = 42;
    }
    return v;
}

struct B
{
    int c;
};

struct A 
{
    string s;
    B b;
};

void minimum(int m1, int m2, int& out)
{
    out = min(m1, m2);
}


int file_szamok_osszege()
{
    ifstream f("__szamok.txt");
    int sum;

    int next;
    while (f.good())
    {
        f >> next >> ws;
        sum += next;
    }
    f.close();
    return sum;
}

// Idaig

int main()
{
    int pont = 0;

    vector<int> k;
    k = csupa42(10);
    ellenoriz(k.size()==10 && k[0]==42, pont)

    A a;
    a.s="text";
    ellenoriz(a.s=="text", pont)

    a.b.c=1;
    ellenoriz(a.b.c==1, pont)

    int x1=0, x2=0;
    const int test_input = __LINE__;
    minimum(test_input,test_input*2,x1);
    minimum(test_input*2,test_input,x2);
    ellenoriz(test_input==x1 && test_input==x2, pont)

    srand(time(0));
    int osszeg = rand()%1000+1000;
    int tmp = osszeg;
    ofstream f("__szamok.txt");
    for (int i=0;i<10;i++)
    {
        int reszosszeg = rand()%100;
        tmp -= reszosszeg;
        f << reszosszeg << endl;
    }
    f << tmp << endl;
    f.close();
    int olvasottosszeg = file_szamok_osszege();
    ellenoriz(olvasottosszeg == osszeg, pont)

    cout << endl << pont << "/5 pont";
}
