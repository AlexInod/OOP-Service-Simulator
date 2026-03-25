#include "Receptioner.h"
Receptioner::Receptioner(string n, string p, string cnp, string data, string oras) : Angajat(n, p, cnp, data, oras) {}
void Receptioner::adaugaCerere(int idCerere)
{
    idCereri.push_back(idCerere);
}
void Receptioner::afiseaza() const
{
    Angajat::afiseaza();
    cout << " Receptioner/CereriAdaugate:" << idCereri.size() << endl;
}
double Receptioner::getSalariu() const
{
    return Angajat::getSalariu();
}