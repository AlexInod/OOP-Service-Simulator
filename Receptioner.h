#pragma once
#include "Angajat.h"
class Receptioner : public Angajat
{
private:
    vector<int> idCereri;

public:
    Receptioner(string n, string p, string cnp, string data, string oras);
    void adaugaCerere(int idCerere);
    double getSalariu() const override;
    void afiseaza() const override;
};