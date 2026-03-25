#pragma once
#include "Angajat.h"
class Supervizor : public Angajat
{
public:
    Supervizor(string n, string p, string cnp, string data, string oras);
    double getSalariu() const override;
    void afiseaza() const override;
};