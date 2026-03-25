#pragma once
#include "Electrocasnic.h"
class Televizor : public Electrocasnic
{
private:
    double diagonala;

public:
    Televizor(string marca, string model, int an, double pret, double diag);
    void afiseaza() const override;
};