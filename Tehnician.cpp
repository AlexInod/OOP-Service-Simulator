#include "Tehnician.h"
Tehnician::Tehnician(string n, string p, string cnp, string data, string oras, vector<string> comp) : Angajat(n, p, cnp, data, oras), competente(comp)
{
    valoareReparation = 0.0;
} 
void Tehnician::adaugaReparation(double val)
{
    valoareReparation += val;
}
bool Tehnician::stiesaReparation(string marca)
{
    for (const auto &c : competente) 
        if (c == marca)
            return true;
    return false;
}
double Tehnician::getSalariu() const
{
    double baza = Angajat::getSalariu();
    return baza + (0.02 * valoareReparation);
}
void Tehnician::afiseaza() const
{
    Angajat::afiseaza();
    cout << " Tehnician/Competente:";
    for (const auto &c : competente)
        cout << c << " ";
    cout << endl;
}