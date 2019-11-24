#include <iostream>
#include <fstream>
#include <vector>

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
};

std::vector<Osszetevo> read_file(std::fstream& f)
{
    std::vector<Osszetevo> v;
    while (f.good())
    {

        std::string line;
        std::getline(f, line);
        unsigned int vesszo = line.find(',');

        Osszetevo o;
        o.mennyiseg = std::stod(line.substr(0, vesszo));
        o.nev = line.substr(vesszo + 1);
//        std::cout << o.mennyiseg << ',' << o.nev << '\n';

        v.push_back(o);
    }
    return v;
}

void szelso(const std::vector<Osszetevo>& osszetevok)
{
    Osszetevo max = osszetevok[0];
    Osszetevo min = osszetevok[0];

    for (const Osszetevo& o : osszetevok)
    {
        if (o.mennyiseg > max.mennyiseg) max = o;
        if (o.mennyiseg < min.mennyiseg) min = o;
    }

    std::cout << "Legtobb: " << max.nev << '\n';
    std::cout << "Legkevesebb: " << min.nev << '\n';
}

void keves(const std::vector<Osszetevo>& osszetevok)
{
    int db = 0;

    for (const Osszetevo& o : osszetevok)
    {
        if (o.mennyiseg < 1) db++;
    }

    std::cout << "Kevesebb, mint egy egyseg: " << db << " db\n";
}

void mennyi(const std::vector<Osszetevo>& osszetevok, std::string mi)
{
    for (const Osszetevo& o : osszetevok)
    {
        if (o.nev == mi)
        {
            std::cout << mi << ": " << o.mennyiseg << '\n';
            return;
        }
    }
    std::cout << mi << " nincs a receptben\n";
}

int main()
{
    std::fstream f("4.01.input.txt");
    if (f.good())
    {
        std::vector<Osszetevo> osszetevok = read_file(f);
        if (osszetevok.size() != 0)
        {
            szelso(osszetevok);
            keves(osszetevok);
            mennyi(osszetevok, "liszt");
        }
    }
    else
    {
        std::cout << "A fajl nem erheto el\n";
    }

    return 0;
}
