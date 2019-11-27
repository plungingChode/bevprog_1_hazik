#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

struct Film
{
    unsigned int szavazatok;
    float pontszam;
    std::string cim;
    int ev;

    friend bool operator<(const Film& lhs, const Film& rhs)
    {
        return (lhs.pontszam < rhs.pontszam) ||
               (lhs.pontszam == rhs.pontszam && lhs.szavazatok < rhs.szavazatok);
    }

    friend bool operator>(const Film& lhs, const Film& rhs)
    {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Film& m)
    {
        stream << m.cim 
               << " (" << m.ev << ") -> " << m.pontszam 
               << " [" << m.szavazatok << " szavazat]";
        return stream;
    }
};

void read_file(std::ifstream& f, std::vector<Film>& v)
{
    char separator_sink;
    while(f.good())
    {
        Film m;
        f >> std::ws >> m.szavazatok;
        f >> std::ws >> m.pontszam >> std::ws;
        std::getline(f, m.cim, '(');
        m.cim = m.cim.substr(0, m.cim.length() - 1);
        f >> m.ev >> separator_sink >> std::ws;

        // std::cout << m << '\n';

        v.push_back(m);
    }
}

// A csoport
uint64_t osszes_szavazat(std::vector<Film>& filmek)
{
    // uint64_t == unsigned long long (csak azt sokaig tart kiirni)
    uint64_t osszes = 0;
    for (const Film& f : filmek)
    {
        // if (osszes + f.szavazatok >= ULONG_LONG_MAX)
        // {
        //     std::cout << "uint64 overflow" << '\n';
        // }
        osszes += f.szavazatok;
    }
    return osszes;
}

Film legjobb_2002(std::vector<Film>& filmek)
{
    Film legjobb;
    for (const Film& f : filmek)
    {
        if (f.ev == 2002 && f.szavazatok >= 100)
        {
            if (f > legjobb) {
                // std::cout << f << '\n';
                legjobb = f;
            } 
        }
    }

    return legjobb;
}

void print_csak_ot(std::vector<Film>& filmek)
{
    std::map<int, int> ot;
    for (const Film& f : filmek)
    {
        if (f.szavazatok == 5)
        {
            ot[f.ev]++;
        }
    }

    std::pair<int, int> legtobb;
    for (const std::pair<int, int>& p : ot)
    {
        if (p.second > legtobb.second) legtobb = p;
    }

    std::cout << "  * " << legtobb.first 
              << " (" << legtobb.second << " ilyen film)\n";
}

// B csoport
std::string legtobb_szavazo(std::vector<Film>& filmek)
{
    Film legtobb;
    for (const Film& f : filmek)
    {
        if (f.szavazatok > legtobb.szavazatok)
        {
            legtobb = f;
        }
    }
    return legtobb.cim;
}

std::string abs_legjobb_92(std::vector<Film>& filmek)
{
    Film legjobb;
    bool egyertelmu = true;

    for (const Film& f : filmek)
    {
        if (f.ev == 1992 && f.szavazatok >= 100)
        {
            if (f.pontszam > legjobb.pontszam)
            {
                // std::cout << "EGYERTELMU: " << legjobb << " --> " << f << '\n'; 
                legjobb = f;
                egyertelmu = true;
            }
            else if (f.pontszam == legjobb.pontszam)
            {
                // std::cout << "NEM EGYERTELMU: " << f << " <---> " << legjobb << '\n';
                egyertelmu = false;
            }
        }
    }

    std::string retVal;
    if (egyertelmu)
    {
        retVal = legjobb.cim;
    }
    else
    {
        retVal = "...de nincs";
    }
    return retVal;
}

void print_legtobbszor_pont(std::vector<Film>& filmek)
{
    std::map<float, int> pontok;
    for (const Film& f : filmek)
    {
        pontok[f.pontszam]++;
    }

    std::pair<float, int> legtobbszor;
    for (const std::pair<float, int>& p : pontok)
    {
        if (p.second > legtobbszor.second)
        {
            legtobbszor = p;
        }
    }

    std::cout << "  * " << legtobbszor.first 
              << " (" << legtobbszor.second << " elofordulas)\n";
}

int main()
{
    std::ifstream f("imdb_ratings.txt");
    std::vector<Film> filmek;
    
    std::string fejlec;
    std::getline(f, fejlec);
    read_file(f, filmek);
    f.close();

    std::cout << "\n=== A csoport ===\n";
    std::cout << "Osszes szavazat: " 
              << osszes_szavazat(filmek) << '\n';

    std::cout << "Legjobb 2002-es film: " 
              << legjobb_2002(filmek).cim << '\n';

    std::cout << "Az az ev, ahol a legtobb olyan film van, amire csak oten szavaztak:\n";
    print_csak_ot(filmek);

    std::cout << "\n=== B csoport ===\n";
    std::cout << "Legtobb szavazo: " 
              << legtobb_szavazo(filmek) << '\n';

    std::string legjobb_92 = abs_legjobb_92(filmek);
    std::cout << "Egyertelmuen legjobb 1992-es film (ha van): " 
              << legjobb_92 << '\n';

    std::cout << "A legtobbszor szereplo pontszam:\n";
    print_legtobbszor_pont(filmek);

    return 0;
}