#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

struct Csillag
{
    std::string nev;
    std::string konstellacio;
    double fenyesseg;
    double tavolsag;
    std::string szinkep;
    double tomeg;
    double sugar;
    double homerseklet;
    int bolygok;

    friend std::ostream& operator<<(std::ostream& stream, const Csillag& cs)
    {
        stream << cs.nev << ", " << cs.konstellacio 
               << "; feny=" << cs.fenyesseg << "; tav=" << cs.tavolsag
               << "; szin=" << cs.szinkep << "; tomeg=" << cs.tomeg 
               << " Nap; sugar=" << cs.sugar << " Nap; hom=" << cs.homerseklet
               << " K; bolygok=" << cs.bolygok;

        return stream; 
    }
};

void read_file(std::ifstream& f, std::vector<Csillag>& v)
{
    const char delim = ',';
    char delim_sink;
    while (f.good())
    {
        Csillag cs;
        std::getline(f, cs.nev, delim);
        f >> std::ws;
        std::getline(f, cs.konstellacio, delim);
        f >> cs.fenyesseg >> delim_sink;
        f >> cs.tavolsag >> delim_sink >> std::ws;
        std::getline(f, cs.szinkep, delim);
        f >> cs.tomeg >> delim_sink;
        f >> cs.sugar >> delim_sink;
        f >> cs.homerseklet >> delim_sink;
        f >> cs.bolygok >> std::ws;

        // std::cout << cs << '\n';
        v.push_back(cs);
    }
}

// A csoport
int nehezebb_min2_bolygo(std::vector<Csillag>& v)
{
    int db = 0;
    for (const Csillag& cs : v)
    {
        if (cs.tomeg > 1 && cs.bolygok >= 2)
        {
            db++;
        }
    }
    return db;
}

void print_tobb_nap_tipusu(std::vector<Csillag>& v)
{
    int nap_tip = 0;
    int osszes = 0;
    for (const Csillag& cs : v)
    {
        if (cs.szinkep[0] == 'G')
        {
            nap_tip += cs.bolygok;
        }
        osszes += cs.bolygok;
    }

    float szazalek = nap_tip / (float)osszes;
    std::cout << "  * ";
    if (szazalek > 0.5)
    {
        std::cout << "igen, ";
    }
    else
    {
        std::cout << "nem, ";
    }
    std::cout << szazalek * 100 << "%\n";
}

std::string max_lathato_host(std::vector<Csillag>& v)
{
    std::map<std::string, int> hostok;
    for (const Csillag& cs : v)
    {
        if (cs.fenyesseg <= 6)
        {
            hostok[cs.konstellacio]++;
        }
    }

    std::pair<std::string, int> legtobb;
    legtobb.second = 0;

    for (const std::pair<std::string, int>& p : hostok)
    {
        if (p.second > legtobb.second)
        {
            // std::cout << p.first << '=' << p.second << '\n';
            legtobb = p;
        }
    }

    return legtobb.first;
}

// B csoport
int kisebb_max2_bolygo(std::vector<Csillag>& v)
{
    int db = 0;
    for (const Csillag& cs : v)
    {
        if (cs.sugar < 1 && cs.bolygok <= 2)
        {
            db++;
        }
    }
    return db;
}

void print_kevesebb_nap_tipusu(std::vector<Csillag>& v)
{
    int nap_tip = 0;
    for (const Csillag& cs : v)
    {
        if (cs.szinkep[0] == 'G')
        {
            nap_tip++;
        }
    }

    float szazalek = nap_tip / (float)v.size();
    std::cout << "  * ";
    if (szazalek < 0.3)
    {
        std::cout << "igen, ";
    }
    else
    {
        std::cout << "nem, ";
    }
    std::cout << szazalek * 100 << "%\n";
}

std::string max_bolygok(std::vector<Csillag>& v)
{
    std::map<std::string, int> bolygok;
    for (const Csillag& cs : v)
    {
        bolygok[cs.konstellacio] += cs.bolygok;
    }

    std::pair<std::string, int> legtobb;
    legtobb.second = 0;

    for (const std::pair<std::string, int>& p : bolygok)
    {
        if (p.second > legtobb.second)
        {
            // std::cout << p.first << '=' << p.second << '\n';
            legtobb = p;
        }
    }

    return legtobb.first;
}


int main()
{
    std::ifstream f("exosolarsystems_final.txt");
    std::vector<Csillag> csillagok;

    read_file(f, csillagok);

    std::cout << "\n=== A csoport ===\n";
    std::cout << "1.) Napnal nehezebb, legalabb 2 exobolygo: "
              << nehezebb_min2_bolygo(csillagok) << " db\n";

    std::cout << "2.) Tobbsegben vannak a Nap tipusu csillagok exobolygoi?\n";
    print_tobb_nap_tipusu(csillagok);

    std::cout << "3.) A legtobb lathato csillagot tartalmazo konstellacio: "
              << max_lathato_host(csillagok) << '\n';

    std::cout << "\n=== B csoport ===\n";
    std::cout << "1.) Napnal kisebb, legfeljebb 2 exobolygo: "
              << kisebb_max2_bolygo(csillagok) << " db\n";    

    std::cout << "2.) Kevesebb, mint 30%-e a Nap tipusu csillag?\n";
    print_kevesebb_nap_tipusu(csillagok);
    
    std::cout << "3.) A legtobb exobolygot tartalmazo konstellacio: "
              << max_bolygok(csillagok) << '\n';

    return 0;
}