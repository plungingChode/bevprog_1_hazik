#include <iostream>
#include <fstream>
#include <vector>

// 4.4. Adott egy szövegfájl, ami egy hónap minden napjának hőmérsékleti adatait tartalmazza:
//      minden sorban három szám van, egy napon mért reggeli, déli és esti hőmérsékletet.
//
//      a.) Add meg a havi átlaghőmérsékletet.

struct Nap
{
    double reggeli;
    double deli;
    double esti;

    double atlag() const
    {
        return (reggeli + deli + esti) / 3;
    }
};

void read_file(std::fstream& f, std::vector<Nap>& v)
{
    while (f.good())
    {
        Nap n;
        f >> std::ws >> n.reggeli >> std::ws >> n.deli >> std::ws >> n.esti;
        v.push_back(n);
    }
}

double havi_atlag(std::vector<Nap>& napok)
{
    double atlag = 0;

    for (const Nap& n : napok)
    {
       atlag += n.atlag();
    }

    return atlag / napok.size();
}

int main()
{
    std::fstream f("4.04.input.txt");
    if (f.good())
    {
        std::vector<Nap> napok;
        read_file(f, napok);

        if (napok.size() != 0)
        {
            std::cout << havi_atlag(napok) << std::endl;
        }
    }
    else
    {
        std::cout << "A fajl nem erheto el\n";
    }

    return 0;
}
