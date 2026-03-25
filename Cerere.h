#pragma once
#include <string>
#include <iostream>
using namespace std;
class Cerere
{
public:
    int id, complexitate, durata, durataRamasa;
    string tip, marca, model, data, status;
    double pret;
    Cerere(int id1, string tip1, string marca1, string model1, string data1, int complex) : id(id1), tip(tip1), marca(marca1), model(model1), data(data1), complexitate(complex)
    {
        status = "Waiting";
        durata = 0;
        durataRamasa = 0;
        pret = 0.0;
    }
    void afiseaza() const
    {
        cout << "Cerere#" << id << " " << tip << " " << marca << " " << model << " " << " Complexitatea:" << complexitate << " Status " << status << endl;
    }
};