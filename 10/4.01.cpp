#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// 4.1. Adott egy szövegfájl, ami egy recept hozzávalóit tartalmazza.
//      A fájl minden sora egy számmal kezdődik, ami egy összetevőből
//      szükséges mennyiség, majd vesszővel elválsztva tőle az összetevő neve jön.
//  a.) Add meg azt az összetevőt, amiből a legtöbb, és amiből a legkevesebb kell.
//  b.) Add meg, hány olyan összetevő van, amiből kevesebb, mint egy egységnyi kell.
//  c ) Add meg egy tetszőleges összetevőről, hogy mennyi kell belőle.
struct Osszetevo
{
    double mennyiseg;
    std::string nev;

    friend std::ostream& operator<<(std::ostream& s, const Osszetevo& o)
    {
        s << o.nev << ", " << o.mennyiseg;
        return s;
    }
};

void read_file(std::fstream& f, std::vector<Osszetevo>& v)
{
    char delim;
    while (f.good())
    {
        Osszetevo o;
        f >> std::ws >> o.mennyiseg >> delim >> std::ws;
        std::getline(f, o.nev);
        v.push_back(o);
    }
}

Osszetevo& legtobb_ref(std::vector<Osszetevo>& osszetevok)
{
    Osszetevo* max = &osszetevok[0];

    for (Osszetevo& o : osszetevok)
    {
        if (o.mennyiseg > max->mennyiseg) max = &o;
    }

    return *max;
}

Osszetevo legtobb(std::vector<Osszetevo>& osszetevok)
{
    Osszetevo max = osszetevok[0];
    for (Osszetevo o : osszetevok)
    {
        if (o.mennyiseg > max.mennyiseg) max = o;
    }
    return max;
}

Osszetevo& legkevesebb_ref(std::vector<Osszetevo>& osszetevok)
{
    Osszetevo* min = &osszetevok[0];

    for (Osszetevo& o : osszetevok)
    {
        if (o.mennyiseg < min->mennyiseg) min = &o;
    }

    return *min;
}

Osszetevo legkevesebb(std::vector<Osszetevo>& osszetevok)
{
    Osszetevo min = osszetevok[0];
    for (Osszetevo o : osszetevok)
    {
        if (o.mennyiseg < min.mennyiseg) min = o;
    }
    return min;
}

int egynel_kevesebb(const std::vector<Osszetevo>& osszetevok)
{
    int db = 0;
    for (const Osszetevo& o : osszetevok)
    {
        if (o.mennyiseg < 1) db++;
    }
    return db;
}

double mennyi(const std::vector<Osszetevo> osszetevok, std::string mi)
{
    for (const Osszetevo& o : osszetevok)
    {
        if (o.nev == mi) return o.mennyiseg;
    }
    return -1;
}

int main()
{
    std::fstream f("4.01.input.txt");
    if (f.good())
    {
        std::vector<Osszetevo> osszetevok;
        read_file(f, osszetevok);

        // for (const Osszetevo& o : osszetevok)
        // {
        //     std::cout << o << '\n';
        // }

        if (osszetevok.size() != 0)
        {
            std::cout << "Legtobb: " << legtobb(osszetevok).nev << '\n';
            std::cout << "Legkevesebb: " << legkevesebb(osszetevok).nev << '\n';
            std::cout << "Kevesebb, mint egy egyseg: " << egynel_kevesebb(osszetevok) << " db\n";
            
            std::string keres = "vanilias cukor";
            double ennyi = mennyi(osszetevok, keres);
            if (ennyi != -1)
            {
                std::cout << keres << ": " << ennyi << '\n';
            }
            else
            {
                std::cout << keres << " nincs a receptben\n";
            }
        }
    }
    else
    {
        std::cout << "A fajl nem erheto el\n";
    }

    return 0;
}
