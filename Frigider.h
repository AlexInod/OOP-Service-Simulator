#pragma once
#include "Electrocasnic.h"
class Frigider : public Electrocasnic
{
private:
    bool congelator;

public:
    Frigider(string marca, string model, int an, double pret, bool congelator);
    void afiseaza() const override;
};
