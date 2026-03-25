#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Electrocasnic
{
protected:
    string tip, marca, model;
    int anFab;
    double pret;

public:
    Electrocasnic(string t, string m, string mod, int an, double pret);
    virtual ~Electrocasnic() {};
    virtual void afiseaza() const;
    string getMarca() const;
    string getModel() const;
    string getTip() const;
    double getPret() const;
    int getVechime() const;
};