#pragma once
#include <vector>
#include <string>
#include "Angajat.h"
#include "Electrocasnic.h"
#include "Cerere.h"
#include <map>
using namespace std;
class Service
{
private:
    vector<Angajat *> angajati;
    vector<Electrocasnic *> electrocasnice;
    vector<Cerere *> cereri;
    map<string, int> statsRefuzuri;
    Service() {}

public:
    static Service &getInstance()
    {
        static Service instance;
        return instance;
    }
    void citesteAngajati(string NF);
    void afiseazaAng();
    void citesteElectro(string NF);
    void afiseazaElectro();
    void citesteCereri(string NF);
    void afiseazaCereri();
    ~Service()
    {
        for (auto a : angajati)
            delete a;
        for (auto e : electrocasnice)
            delete e;
        for (auto c : cereri)
            delete c;
    }
    Electrocasnic *cautaElectro(string marca, string model);
    void runSimulator();
    void rapoarte();
    void concediazaAngajat(int id);
    void angajeazaManual();
    void modificaNumeAngajat();
    void assignReceptioner(int id);
    void adaugaElectrocasnicManual();
    void stergeElectrocasnic();
};