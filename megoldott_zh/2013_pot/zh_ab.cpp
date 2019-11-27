#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

struct Outbreak
{
    std::string category;
    std::string outbreak;
    std::string location;
    double lat;
    double lon;
    std::string date;
    int cases; // -1 == N/A
    int fatalities;
    std::string impact_scale;
    std::string source_citation;
    std::string source_url;

    friend std::ostream& operator<<(std::ostream& stream, const Outbreak& o)
    {
        stream << o.outbreak << " in " << o.location << " @ " << o.date
               << ", C=" << o.cases << ", F=" << o.fatalities;
        return stream;
    }
};

void read_file(std::ifstream& f, std::vector<Outbreak>& v)
{
    const char delim = ',';
    char delim_sink;
    while (f.good())
    {
        Outbreak o;

        std::getline(f, o.category, delim);
        std::getline(f, o.outbreak, delim);
        std::getline(f, o.location, delim);
        f >> o.lat >> delim_sink;
        f >> o.lon >> delim_sink;
        std::getline(f, o.date, delim);
        f >> o.cases >> delim_sink;
        f >> o.fatalities >> delim_sink;
        std::getline(f, o.impact_scale, delim);
        std::getline(f, o.source_citation, delim);
        std::getline(f, o.source_url);
        f >> std::ws;

        // std::cout << o << '\n';

        v.push_back(o);
    }
}

// A csoport

// ezt a mondatot nem teljesen értem 
// v~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// a) hibás feltöltések: ahol ismeretlen a megbetegedések száma,
// de a halálos áldozatok száma ismert, ott a két érték megegyezésével 
// is jelölhetik a megbetegedések számát. Sorold fel az ilyen tételeket! 
void print_record_errors(std::vector<Outbreak>& v)
{
    for (Outbreak& o : v)
    {
        if (o.cases == o.fatalities)
        {
            std::cout << "  * " << o << '\n';
        }
    }
}

float measles_mortality(std::vector<Outbreak>& v)
{
    float rate = 0;
    int cases = 0;
    for (const Outbreak& o : v)
    {
        if (o.category == "Measles") 
        {
            if (o.cases != -1)
            {
                rate += o.fatalities / (float)o.cases;
                cases++;
            }
        }
    }
    return rate / (float)cases;
}

// B csoport

void print_special_cases(std::vector<Outbreak>& v)
{
    for (const Outbreak& o : v)
    {
        if (o.category != "Other" && o.category != o.outbreak)
        {
            std::cout << "  * " << o << '\n';
        }
    }
}

long whp_cough_fatalities(std::vector<Outbreak>& v)
{
    long fatalities = 0;
    for (const Outbreak& o : v)
    {
        if (o.category == "Whooping Cough" && o.fatalities != -1)
        {
            fatalities += o.fatalities;
        }
    }
    return fatalities;
}


// A es B csoport
void print_mostly_africa(std::vector<Outbreak>& v)
{
    std::map<std::string, long> total_cases;
    std::map<std::string, long> africa_cases;

    for (const Outbreak& o : v)
    {
        if (o.cases != -1)
        {
            total_cases[o.category] += o.cases;
        
            // Afrika => lat: -27..36, lon: -28..62
            if (o.lat >= -27 && o.lat <= 36 &&
                o.lon >= -28 && o.lon <= 62)
            {
                africa_cases[o.category] += o.cases;
            }
        }
    }

    for (const std::pair<std::string, long>& p : total_cases)
    {
        double ratio = africa_cases[p.first] / (double)p.second;
        if (ratio >= (2.0 / 3.0))
        {
            std::cout << "  * " << p.first << '\n';
        }
    }
}

int main() 
{
    std::ifstream f("jarvany.csv");
    std::vector<Outbreak> outbreaks;

    std::string header;
    std::getline(f, header);

    read_file(f, outbreaks);
    f.close();

    std::cout << "\n=== A csoport ===\n";
    std::cout << "a.) Ugyanannyi megbetegedes, mint halalos aldozat (?):\n";
    print_record_errors(outbreaks);

    std::cout << "\nb.) Kanyaro atlagos mortalitasi rataja: "
              << measles_mortality(outbreaks) << '\n';

    std::cout << "c.) Az esetek legalabb 2/3-a Afrikaban:\n";
    print_mostly_africa(outbreaks);

    std::cout << "\n=== B csoport ===\n";
    std::cout << "a.) Kulonleges esetek:\n";
    print_special_cases(outbreaks);

    std::cout << "\nb.) Szamarkohoges halalos aldozatai: "
              << whp_cough_fatalities(outbreaks) << " fo\n";

    std::cout << "c.) Az esetek legalabb 2/3-a Afrikaban:\n";
    print_mostly_africa(outbreaks);

    return 0;
}