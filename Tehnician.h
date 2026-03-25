#pragma once
#include "Angajat.h"
#include "Cerere.h"
class Tehnician : public Angajat
{
private:
    vector<string> competente;
    double valoareReparation;

public:
    vector<Cerere *> cereriactive;
    Tehnician(string n, string p, string cnp, string data, string oras, vector<string> comp);
    void adaugaReparation(double valoare);
    bool stiesaReparation(string marca);
    double getSalariu() const override;
    void afiseaza() const override;
    bool disponibil()
    {
        return cereriactive.size() < 3;
    }
};