#include "Frigider.h"
Frigider::Frigider(string m, string mod, int an, double pret, bool congelator) : Electrocasnic("Frigider", m, mod, an, pret), congelator(congelator) {}
void Frigider::afiseaza() const
{
    Electrocasnic::afiseaza();
    if (congelator == 1)
        cout << "Congelator:Da" << endl;
    else
        cout << "Congelator:Nu" << endl;
}