#pragma once
#include "Electrocasnic.h"
class MasinaSpalat : public Electrocasnic
{
private:
    double capacitate;

public:
    MasinaSpalat(string marca, string model, int an, double pret, double capacitate);
    void afiseaza() const override;
};