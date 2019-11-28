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

int haromszor(int x)
{
    return x * 3;
}

bool kisebb_mint_szaz(int x)
{
    return x < 100;
}

void jegyekre_bont(int x, int& j1, int& j2)
{
    j2 = x % 10;
    j1 = (x - j2) / 10;
}

struct Kor
{
    float origo_x, origo_y;
    float r;
};

struct Negyzet
{
    float x1, x2;
    float y1, y2;
};

Negyzet befoglalo_negyzet(const Kor& k)
{
    Negyzet n;
    n.x1 = k.origo_x - k.r;
    n.y1 = k.origo_y - k.r;
    n.x2 = n.x1 + k.r * 2;
    n.y2 = n.y1 + k.r * 2;
    return n;
}

int max(vector<int> v)
{
    int max_val = v[0];
    for (const int i : v)
    {
        if (i > max_val)
        {
            max_val = i;
        }
    }
    return max_val;
}

// Idaig

int main()
{
    int pont = 0;
    srand(time(0));

    int a = rand() % 99 + 1;
    int b = haromszor(a);
    ellenoriz(a*3==b, pont);

    ellenoriz(kisebb_mint_szaz(a) && !kisebb_mint_szaz(100+a), pont);

    int j1, j2;
    jegyekre_bont(a, j1, j2); //max ket jegyu szamokra kell csak mukodjon
    ellenoriz(a == 10*j1+j2 && j2<10, pont);

    Kor k;
    k.origo_x = 1.0;
    k.origo_y = 1.0;
    k.r = 1.5;

    Negyzet n;
    n.x1=0.0;
    n.y1=0.0;
    n.x2=1.0;
    n.y2=1.0;

    ellenoriz(k.r==1.5 && n.x1==0, pont);

    k.origo_x = rand()%100;
    k.origo_y = rand()%100;
    k.r = rand()%100;
    n = befoglalo_negyzet(k);
    //az alabbi keplet azert ilyen korulmenyes hogy a kerekitesi hibak ne okozzanak problemat
    ellenoriz(int((n.x1+n.x2)/2.0+0.5) == int(k.origo_x+0.5) &&
              int((n.y1+n.y2)/2.0+0.5) == int(k.origo_y+0.5) &&
              int(fabs(n.x1-n.x2)/2.0+0.5) == int(k.r+0.5) &&
              int(fabs(n.y1-n.y2)/2.0+0.5) == int(k.r+0.5)
              , pont)

    vector<int> v(100,0);
    for (unsigned int i=0;i<v.size();i++) {
        v[i] = rand()%10 - 200;
    }
    v[rand()%v.size()] = a-190;
    ellenoriz(max(v)==a-190, pont)

    cout << endl << pont << "/6 pont";
}
