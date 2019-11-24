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

std::vector<Nap> read_file(std::fstream& f)
{
    std::vector<Nap> v;

    while(f.good())
    {
        std::string line;
        std::getline(f, line);

        unsigned int szokoz1 = line.find(' ');
        unsigned int szokoz2 = line.find(' ', szokoz1);

        Nap n;
        n.reggeli = std::stod(line.substr(0, szokoz1));
        n.deli = std::stod(line.substr(szokoz1 + 1, szokoz2));
        n.esti = std::stod(line.substr(szokoz2 + 1));

//        std::cout << n.reggeli << ' ' << n.deli << ' ' << n.esti << std::endl;

        v.push_back(n);
    }

    return v;
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
        std::vector<Nap> napok = read_file(f);
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
