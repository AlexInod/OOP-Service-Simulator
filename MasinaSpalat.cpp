#include "MasinaSpalat.h"
MasinaSpalat::MasinaSpalat(string m, string mod, int an, double pret, double capacitate) : Electrocasnic("MasinaSpalat", m, mod, an, pret), capacitate(capacitate) {}
void MasinaSpalat::afiseaza() const
{
    Electrocasnic::afiseaza();
    cout << "Capacitate in kg:" << capacitate << endl;
}
