#include "Supervizor.h"

Supervizor::Supervizor(string n, string p, string cnp, string data, string oras) : Angajat(n, p, cnp, data, oras) {}
double Supervizor::getSalariu() const
{
    double total = Angajat::getSalariu();
    total += (4000 * 0.20);
    return total;
}
void Supervizor::afiseaza() const
{
    Angajat::afiseaza();
    cout << " Supervizor " << endl;
}