#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Utile.h"
using namespace std;
class Angajat
{
protected:
    string nume, prenume, cnp, dataAng, domiciliu;
    int id;
    static int next;

public:
    Angajat(string n, string p, string cnp, string data, string oras);
    virtual ~Angajat() {}
    virtual double getSalariu() const;
    string getNume() const { return nume + " " + prenume; }
    string getCnp() const { return cnp; }
    int getId() const { return id; }
    virtual void afiseaza() const;
    void setNume(string n) { this->nume = n; }
    void setPrenume(string p) { this->prenume = p; }
};
