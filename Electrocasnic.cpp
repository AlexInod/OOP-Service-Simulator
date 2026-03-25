#include "Electrocasnic.h"
Electrocasnic::Electrocasnic(string t, string m, string mod, int an, double prett) : tip(t), marca(m), model(mod), anFab(an), pret(prett) {}
void Electrocasnic::afiseaza() const
{
    cout << "Tip: " << tip << " Marca: " << marca << " Model: " << model 
         << " An: " << anFab
         << " Pret " << pret << " lei ";
}
string Electrocasnic::getMarca() const { return marca; }
string Electrocasnic::getModel() const { return model; }
string Electrocasnic::getTip() const { return tip; }
double Electrocasnic::getPret() const { return pret; }
int Electrocasnic::getVechime() const { return 2026 - anFab; }