#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>

struct Kontakt
{
    std::string nev;
    unsigned int szam;
};

void read_file(std::ifstream& f, std::vector<Kontakt>& v)
{
    while (f.good())
    {
        Kontakt k;
        std::getline(f, k.nev, ',');
        f >> k.szam >> std::ws;

        v.push_back(k);
    }
}

// 'const' parameter => csak olvasasra / 'megigerjuk', hogy nem valtoztatunk benne semmit
void map_pelda(const std::vector<Kontakt>& v)
{
    std::map<std::string, int> vnevek;
    /* 
    std::map<TKulcs, TErtek> m;
    ahol TKulcs a kulcs tipusa, 
         TErtek az ertek tipusa.

    A kulcsok kozul mindegyik csak egyszer szerepelhet, mig a hozzarandelt
    ertek akarhanyszor.

    Ertek hozzarandelese kulcshoz:
    */

    vnevek["Kovacs"] = 10;
    vnevek["Szabo"] = 8;
    vnevek["Nagy"] = 9;

    /*
    A kulcsokat nem nem kell elore megadni. Ha az adott kulcs
    meg nem szerepel a listaban, a [] operator segitsegevel
    magatol hozzaadodik.

    Ugyanakkor ha mar szerepel, felul is irhatjuk.
    */

    vnevek["Toth"] = 5;
    vnevek["Kovacs"] = 12;

    /*
    Ertek lekerdezese std::map-bol (pl. a "Kovacs" kulcshoz tartozo ertek):
    */

    int mennyi = vnevek["Kovacs"];
    std::cout << "Peldaul: \"Kovacs\"=" << mennyi << '\n';

    /*
    Ertek modositasa (kb. ugyanaz, mintha vektorban erteket modositanank,
    csak itt sorszam helyett valamilyen kulcs van):
    */
    
    int x = vnevek["Kovacs"];
    x++;
    vnevek["Kovacs"] = x;

    vnevek["Kovacs"] += 1;
    vnevek["Kovacs"]++;

    /*
    A fenti harom pelda ugyanazt jelenti.

    Szamoljuk meg, hogy a vezeteknevekbol tenyleg mennyi van!
        * valasszuk ki a teljes nev vezeteknev reszet
        * adjuk hozza a kulcsot a map-hez
        * noveljuk az adott kulcs erteket
        
    Ilyenkor biztosak lehetunk benne, hogy az ujonnan letrehozott
    szam tipusu (int, float, double, stb.) bejegyzesek 0. 
    Emiatt eleg eggyel megnovelnunk, hiszen
        * ha meg nem szerepel a bejegyzes: letrehozzuk, 0 --> 1
        * ha mar szerepel a bejegyzes: n --> n + 1
    */

    vnevek.clear();
    for (const Kontakt& k : v)
    {
        size_t szokoz = k.nev.find(' ');
        std::string vezeteknev = k.nev.substr(0, szokoz);
        vnevek[vezeteknev]++;
    }

    /*
    A bejegyzsesek paronkent vannak tarolva, ezeken keresztul tudjuk
    elerni a map elemeit:
    
    std::pair<TKulcs, TErtek> p;
    ahol a TKulcs es TErtek pontosan ugyanaz, mint a mapnel.
    */

    std::cout << "\nA 'vnevek' map elemei:\n";
    for (const std::pair<std::string, int>& p : vnevek)
    {
        std::string kulcs = p.first;
        int ertek = p.second;

        std::cout << kulcs << " = " << ertek << '\n';
    }
    std::cout << '\n';

    /*
    Most keressuk meg a legmagasabb ertekhez tartozo kulcsot
    */

    int max_ertek = 0;
    std::string max_kulcs;

    for (const std::pair<std::string, int>& p : vnevek)
    {
        if (p.second > max_ertek)
        {
            max_ertek = p.second;
            max_kulcs = p.first;
        }
    }

    std::cout << "A leggyakoribb vezeteknev: " << max_kulcs << ", " 
              << max_ertek << " elofordulassal.\n";

    /*
    Hany embert vezetekneve "Kovacs"?
    */

    std::cout << vnevek["Kovacs"] << " embert hivnak Kovacsnak\n";

    /*
    Hany ember vezetekneve "Abcdefg"? (alapertelmezett ertek == 0)
    */

    std::cout << vnevek["Abcdefg"] << " embert hivnak Abcdefg-nek\n";

    /*
    Van Lukacs vezeteknevu ember a listaban? (== tartalmazza-e a "Lukacs kulcsot")

    Mivel minden elem csak egyszer szerepel, a std::map::count csak 1 vagy 0 lehet
    */

    bool van_lukacs = vnevek.count("Lukacs");
    if (van_lukacs)
    {
        std::cout << "Van Lukacs vezeteknevu\n";
    }
    else
    {
        std::cout << "Nincs Lukacs vezeteknevu\n";
    }

    // https://en.cppreference.com/w/cpp/container/map
}

int main()
{
    std::ifstream f("pelda.txt");
    std::vector<Kontakt> tfkonyv;
    read_file(f, tfkonyv);
    f.close();

    // std::cout << tfkonyv.size() << '\n';
    map_pelda(tfkonyv);

    return 0;
}