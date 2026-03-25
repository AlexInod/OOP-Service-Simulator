#include "Televizor.h"
Televizor::Televizor(string m, string mod, int an, double pret, double diagonala) : Electrocasnic("Tv", m, mod, an, pret), diagonala(diagonala) {}
void Televizor::afiseaza() const
{
    Electrocasnic::afiseaza();
    cout << "Diagonala in cm:" << diagonala << endl;
}