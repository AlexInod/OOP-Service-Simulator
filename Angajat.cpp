#include "Angajat.h"
#include "Utile.h"
#include <stdexcept>
int Angajat::next = 1;
Angajat::Angajat(string n, string p, string CNP, string data, string oras) : id(next++), nume(n), prenume(p), cnp(CNP), dataAng(data), domiciliu(oras)
{
    if (nume.length() < 3 || nume.length() > 30 || prenume.length() < 3 || prenume.length() > 30)
        throw invalid_argument("Numele si prenumele trebuie sa aiba intre 3 si 30 caractere");
    if (!Utile::validCnp(cnp))
        throw invalid_argument("Cnp invalid" + cnp);
}
double Angajat::getSalariu() const
{

    double salariu = 4000;
    int ani = Utile::Vechime(dataAng);
    int transe = ani / 3;
    salariu += 4000 * (0.05 * transe);
    if (domiciliu != "Bucuresti")
        salariu += 400;
    return salariu;
}
void Angajat::afiseaza() const
{
    cout << "ID:" << id << " Nume: " << nume << " Prenume: " << prenume << " Oras: " << domiciliu << " Salariu: " << getSalariu();
}