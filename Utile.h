#pragma once
#include <string>
#include <iostream>
#include <ctime>
using namespace std;
class Utile
{
public:
    static int validCnp(const string &cnp)
    {
        if (cnp.length() != 13)
            return 0;
        for (char c : cnp)
            if (!isdigit(c))
                return 0;
        return 1;
    }
    static int Vechime(const string &dataAng)
    {
        if (dataAng.length() < 10)
            return 0;
        try
        {
            int anAng = stoi(dataAng.substr(6, 4));
            return 2026 - anAng;
        }
        catch (...)
        {
            return 0;
        }
    }

    static vector<string> split(string linie, char delimitator)
    {
        vector<string> cuvinte;
        int poz = 0;
        while ((poz = linie.find(delimitator)) != string::npos)
        {
            string cuvant = linie.substr(0, poz);
            cuvinte.push_back(cuvant);
            linie.erase(0, poz + 1);
        }
        if (!linie.empty())
        {
            cuvinte.push_back(linie);
        }
        return cuvinte;
    }
};
