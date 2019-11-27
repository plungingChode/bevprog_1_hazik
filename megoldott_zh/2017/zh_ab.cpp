#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

struct Angle
{
    double hour = 0;
    double min = 0;
    double sec = 0;
};

std::ostream& operator<<(std::ostream& stream, const Angle& a)
{
    stream << "{hour=" << a.hour << ", min=" << a.min << ", sec=" << a.sec << '}';
    return stream;
}

struct Star
{
    std::string common_name;
    char sibling;
    Angle ra;
    Angle dec;
    std::string color_class;
    double vis_magnitude; // latszolagos fenyesseg, 0 == hianyzik
    double abs_magnitude; // 0 == hianyzik
    double parallax; // szog?
    double parallax_error;
    double distance; // naptol, fenyev
    std::string gliese_code;
    std::string other;
};

std::ostream& operator<<(std::ostream& stream, const Star& s)
{
    stream << s.common_name << ';' << s.sibling;
    return stream;
}

void read_file(std::ifstream& f, std::vector<Star>& v)
{
    const char delim = ';';
    char delim_sink;
    while (f.good())
    {
        f >> std::ws;

        Star s;
        std::getline(f, s.common_name, delim);

        f >> s.sibling;
        if (s.sibling == delim)
        {
            s.sibling = '-';
        }
        else 
        {
            f >> delim_sink;
        }

        f >> s.ra.hour >> s.ra.min  >> delim_sink;
        f >> s.dec.min >> s.dec.sec >> delim_sink;

        std::getline(f, s.color_class, delim);

        f >> s.vis_magnitude  >> delim_sink;
        f >> s.abs_magnitude  >> delim_sink;
        f >> s.parallax       >> delim_sink;
        f >> s.parallax_error >> delim_sink;
        f >> s.distance       >> delim_sink;

        std::getline(f, s.gliese_code, delim);
        std::getline(f, s.other);
        f >> std::ws;

        v.push_back(s);
    }
}

// A csoport
double bright_avg_distance(std::vector<Star>& v)
{
    double sum_distance = 0;
    int cnt = 0;
    for (Star& s : v)
    {
        if (s.vis_magnitude <= 6 && s.vis_magnitude != 0)
        {
            sum_distance += s.distance;
            cnt++;
        }
    }
    return sum_distance / cnt;
}

std::string second_color(std::vector<Star>& v)
{
    std::map<std::string, int> color_counts;
    for (const Star& s1 : v)
    {
        color_counts[s1.color_class]++;
    }

    int max = -1;
    std::string max_color;
    for (std::pair<std::string, int> elem : color_counts)
    {
        if (elem.second > max) 
        {
            max = elem.second;
            max_color = elem.first;
        }
    }

    int second_max = -1;
    std::string second_max_color;
    for (std::pair<std::string, int> elem : color_counts)
    {
        if (elem.second > second_max && elem.second < max)
        {
            second_max = elem.second;
            second_max_color = elem.first;
        }
    }

    return second_max_color;
}

// B csoport
void multi_systems(std::vector<Star>& v)
{
    std::map<char, int> siblings;
    for (const Star& s : v)
    {
        if (s.sibling != '-')
        {
            siblings[s.sibling]++;
        }
    }

    char least = 'A';
    char most = 'A' + siblings.size() - 1;
    for (char c = most; c > least; c--)
    {
        int current = siblings[c];
        for (char d = most; d > c; d--)
        {
            current -= siblings[d];
        }
        std::cout << "   * "
                  << (int)(c - least + 1) 
                  << " csillagbol allo naprendszer: " 
                  << current << " db" << '\n';
    }
}

double avg_parallax_error(std::vector<Star>& v)
{
    double sum_error = 0;
    int cnt = 0;
    for (const Star& s : v)
    {
        if (s.parallax != 0)
        {
            sum_error += s.parallax_error / s.parallax * 100;
            cnt++;
        }
    }
    return sum_error / cnt;
}

// A es B csoport
double distance(Star& s1, Star& s2)
{
    double lambda1 = (s1.ra.hour + s1.ra.min / 60) / 24 * 360 * 3.14 / 180;
    double phi1 = s1.dec.min + s1.dec.sec * 60 * 3.14 / 180;

    double x1 = s1.distance * std::cos(phi1) * std::cos(lambda1);
    double y1 = s1.distance * std::cos(phi1) * std::sin(lambda1);
    double z1 = s1.distance * std::sin(phi1);

    double lambda2 = (s2.ra.hour + s2.ra.min / 60) / 24 * 360 * 3.14 / 180;
    double phi2 = s2.dec.min + s2.dec.sec * 60 * 3.14 / 180;

    double x2 = s2.distance * std::cos(phi2) * std::cos(lambda2);
    double y2 = s2.distance * std::cos(phi2) * std::sin(lambda2);
    double z2 = s2.distance * std::sin(phi2);

    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) + std::pow(z2 - z1, 2));
}

std::pair<Star, Star> max_distance(std::vector<Star>& v)
{
    std::pair<Star, Star> farthest(v[0], v[0]);
    int max_dist = 0;
    for (Star& s1 : v)
    {
        for (Star& s2 : v)
        {
            double dist = distance(s1, s2);
            if (dist > max_dist)
            {
                max_dist = dist;
                farthest.first = s1;
                farthest.second = s2;
            }
        }
    }
    return farthest;
}

int main()
{
    std::ifstream f("NearStars.csv");
    if (f.good())
    {
        std::string discard;
        std::getline(f, discard);

        std::vector<Star> stars;
        read_file(f, stars);

        // for (Star& s : stars)
        // {
        //     std::cout << s << '\n';
        // }

        std::pair<Star, Star> tavoli = max_distance(stars);

        std::cout << "=== A csoport ===" << '\n';
        std::cout << "Szabad szemmel lathato csillagok atlagos tavolsaga: " << bright_avg_distance(stars) << " fenyev\n";
        std::cout << "A masodik leggyakoribb szin: " << second_color(stars) << '\n';
        std::cout << "A ket legtavolabbi csillag: " << tavoli.first.common_name << " es " << tavoli.second.common_name << '\n';

        std::cout << "\n=== B csoport ===" << '\n';
        std::cout << "Mutli naprendszerek: \n";
        multi_systems(stars);
        std::cout << "\nRelativ paralaxis hiba atlaga: " << avg_parallax_error(stars) << '\n';
        std::cout << "A ket legtavolabbi csillag: " << tavoli.first.common_name << " es " << tavoli.second.common_name << '\n';
    }

    f.close();
    return 0;
}
