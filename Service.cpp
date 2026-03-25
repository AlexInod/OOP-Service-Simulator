#include "Service.h"
#include "Utile.h"
#include "Tehnician.h"
#include "Supervizor.h"
#include "Receptioner.h"
#include "Frigider.h"
#include "Televizor.h"
#include "MasinaSpalat.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
using namespace std;
void Service::citesteAngajati(string NF)
{
    string linie;
    ifstream fisier(NF);
    if (!fisier.is_open())
    {
        cout << "err deschidere fisier ang" << endl;
        return;
    }
    while (getline(fisier, linie))
    {
        if (linie.empty())
            continue;
        vector<string> date = Utile::split(linie, ',');
        if (date.size() < 6)
            continue;
        string tip = date[0], nume = date[1], prenume = date[2], cnp = date[3], dataAng = date[4], oras = date[5];
        try
        {

            if (tip == "Tehnician")
            {
                vector<string> competente;
                for (size_t i = 6; i < date.size(); i++)
                    competente.push_back(date[i]);
                angajati.push_back(new Tehnician(nume, prenume, cnp, dataAng, oras, competente));
            }
            else if (tip == "Receptioner")
            {
                angajati.push_back(new Receptioner(nume, prenume, cnp, dataAng, oras));
            }
            else if (tip == "Supervizor")
            {
                angajati.push_back(new Supervizor(nume, prenume, cnp, dataAng, oras));
            }
            else
            {
                cout << "Tip necunosscut" << tip << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "err la ang" << e.what() << endl;
        }
    }
    fisier.close();
    cout << "Incarcat Ang done" << endl;
}
void Service::afiseazaAng()
{
    cout << "Lista:" << endl;
    for (auto a : angajati)
        a->afiseaza();
    cout << "-----" << endl;
}
void Service::citesteElectro(string NM)
{
    string linie;
    ifstream fisier(NM);
    if (!fisier.is_open())
    {
        cout << "err la deschiderea fisier electro";
        return;
    }
    while (getline(fisier, linie))
    {
        if (linie.empty())
            continue;
        vector<string> date = Utile::split(linie, ',');
        if (date.size() < 6)
            continue;
        string tip = date[0], marca = date[1], model = date[2];
        int an = stoi(date[3]);      
        double pret = stod(date[4]); 
        try
        {
            if (tip == "Frigider")
            {
                bool congelator = (stoi(date[5]) == 1);
                electrocasnice.push_back(new Frigider(marca, model, an, pret, congelator));
            }

            else if (tip == "TV")
            {
                double diagonala = stod(date[5]);
                electrocasnice.push_back(new Televizor(marca, model, an, pret, diagonala));
            }
            else if (tip == "MasinaSpalat")
            {
                double capacitate = stod(date[5]);
                electrocasnice.push_back(new MasinaSpalat(marca, model, an, pret, capacitate));
            }
        }
        catch (...)
        {
            cout << "err la electro" << linie << endl;
        }
    }
    fisier.close();
    cout << "Electro incarcate" << endl;
}
void Service::afiseazaElectro()
{
    cout << "Lista Electrocasnice: " << endl;
    for (auto e : electrocasnice)
    {
        e->afiseaza();
        cout << "-----" << endl;
    }
}
void Service::afiseazaCereri()
{
    cout << "Lista Cereri:" << endl;
    for (auto c : cereri)
    {
        c->afiseaza();
        cout << "-----" << endl;
    }
}

void Service::citesteCereri(string numeFisier)
{
    ifstream fisier(numeFisier);
    if (!fisier.is_open())
    {
        cout << "err la fisier cereri" << endl;
        return;
    }
    string linie;
    while (getline(fisier, linie))
    {
        if (linie.empty())
            continue;
        vector<string> date = Utile::split(linie, ',');
        if (date.size() < 6)
            continue;
        try
        {
            int id = stoi(date[0]);
            string tip = date[1];
            string marca = date[2];
            string model = date[3];
            string data = date[4];
            int complexitate = stoi(date[5]);
            cereri.push_back(new Cerere(id, tip, marca, model, data, complexitate));
        }
        catch (...)
        {
            cout << "err la cereri" << linie << endl;
        }
    }
    fisier.close();
    cout << "Cereri incarcate" << endl;
}
Electrocasnic *Service::cautaElectro(string marca, string model)
{
    for (auto e : electrocasnice)
    {
        if (e->getMarca() == marca && e->getModel() == model)
        {
            return e;
        }
    }
    return nullptr;
}
void Service::runSimulator()
{
    int nrT = 0, nrR = 0, nrS = 0;
    for (auto ang : angajati)
    {
        if (dynamic_cast<Tehnician *>(ang))
            nrT++;
        else if (dynamic_cast<Receptioner *>(ang))
            nrR++;
        else if (dynamic_cast<Supervizor *>(ang))
            nrS++;
    }

    if (nrT < 3 || nrR < 1 || nrS < 1)
    {
        cout << "Prea putini angajati...." << "Necesar:3 Tehnicieni,1 Receptioner,1Supervizor." << "Aveti: " << nrT << "T, " << nrR << " R, " << nrS << " S." << endl;
        return;
    }
    cout << "Start Simulator:" << endl;
    vector<Cerere *> coada = cereri;
    int timp = 0, activ = 1;
    for (auto c : cereri)
    {
        assignReceptioner(c->id);
    }
    while (activ)
    {
        timp++;
        cout << "Timp: " << timp << endl;
        int working = 0, aloc = 0;
        for (auto ang : angajati)
        {
            Tehnician *t = dynamic_cast<Tehnician *>(ang); 
            if (t != nullptr)
            {
                for (int i = t->cereriactive.size() - 1; i >= 0; i--)
                {
                    Cerere *c = t->cereriactive[i];
                    working = 1;
                    c->durataRamasa--;
                    if (c->durataRamasa <= 0)
                    {
                        cout << "-x " << t->getNume() << "Finished cererea#" << c->id << endl;
                        c->status = "Finished";
                        t->adaugaReparation(c->pret);
                        t->cereriactive.erase(t->cereriactive.begin() + i);
                    }
                    else
                    {
                        cout << "-x " << t->getNume() << " lucreaza la cererea#" << c->id << " timp ramas: " << c->durataRamasa << "s" << endl;
                    }
                }
            }
        }
        for (int i = coada.size() - 1; i >= 0; i--)
        {
            Cerere *c = coada[i];
            if (c->durata == 0)
            {
                Electrocasnic *e = cautaElectro(c->marca, c->model);
                if (e == nullptr)
                {
                    cout << "-x Cererea#" << c->id << " Respinsa " << c->model << " nu reparam asa cv :(" << endl;
                    c->status = "Rejected";
                    string cheie = c->tip + " " + c->marca + " " + c->model; 
                    statsRefuzuri[cheie]++;
                    coada.erase(coada.begin() + i); 
                    continue;
                }
                c->durata = e->getVechime() * c->complexitate;
                c->durataRamasa = c->durata;
                c->pret = e->getPret() * c->durata;
            }
            Tehnician *best = nullptr;
            int min = 999999;
            for (auto ang : angajati)
            {
                Tehnician *t = dynamic_cast<Tehnician *>(ang);
                if (t && t->cereriactive.size() < 3)
                {
                    bool stieSaRepare = t->stiesaReparation(c->tip) || t->stiesaReparation(c->marca);
                    if (stieSaRepare)
                    {
                        int sarcina = 0;
                        for (auto ca : t->cereriactive)
                            sarcina += ca->durataRamasa;
                        if (sarcina < min)
                        {
                            min = sarcina;
                            best = t;
                        }
                    }
                }
            }
            if (best != nullptr)
            {
                cout << " -x- Cererea #" << c->id << " preluata de " << best->getNume() << endl;
                c->status = "Alocata";
                best->cereriactive.push_back(c);
                coada.erase(coada.begin() + i);
                aloc = 1;
                working = true;
            }
        }
        if (!working && coada.empty())
        {
            cout << "Toate comenzile is gata.Ending Simulator" << endl;
            activ = 0;
        }
        else if (!coada.empty() && !working && !aloc)
        {
            cout << "!:Au ramas " << coada.size() << " cereri pe care nimeni nu le poate repara (lipsa competente)!" << endl;
            for (auto c : coada)
            {
                c->status = "Respinsa-FaraTehnician";
                cout << " -x Respingere fortata: Cererea #" << c->id << endl;
            }
            coada.clear(); 
            activ = false;
        }
        this_thread::sleep_for(chrono::milliseconds(1000)); 
    }
}
bool comparaSalariu(Angajat *a, Angajat *b)
{
    return a->getSalariu() > b->getSalariu();
}
bool comparaCereriAlfabetic(Cerere *a, Cerere *b)
{
    if (a->tip != b->tip)
        return a->tip < b->tip;
    if (a->marca != b->marca)
        return a->marca < b->marca;
    return a->model < b->model;
}
void Service::rapoarte()
{
    ofstream fAng("raport_ang.csv");
    fAng << "ID,Nume,Rol,Salariu_Final,Bonus" << endl;
    for (auto ang : angajati)
    {
        fAng << ang->getId() << "," << ang->getNume() << ",";
        Tehnician *t = dynamic_cast<Tehnician *>(ang);
        Supervizor *s = dynamic_cast<Supervizor *>(ang);
        Receptioner *r = dynamic_cast<Receptioner *>(ang);
        if (t)
        {
            fAng << "Tehnician," << t->getSalariu() << ",Inclus";
        }
        else if (s)
        {
            fAng << "Supervizor," << s->getSalariu() << ",0";
        }
        else if (r)
        {
            fAng << "Receptioner," << r->getSalariu() << ",0";
        }
        fAng << endl;
    }
    fAng.close();
    cout << "Generat raport angajati" << endl;

    ofstream fCer("raport_cer.csv");
    fCer << "ID,Tip,Marca,Model,Status,Pret,Durata_Totala" << endl;
    for (auto c : cereri)
    {
        fCer << c->id << "," << c->tip << "," << c->marca << "," << c->model << "," << c->status << "," << c->pret << "," << c->durata << endl;
    }
    fCer.close();
    cout << "Generat raport cereri" << endl;

    // 1.top3 ang:
    vector<Angajat *> topAngajati = angajati;
    sort(topAngajati.begin(), topAngajati.end(), comparaSalariu);

    ofstream f1("raport_top3_salarii.csv");
    f1 << "Loc,Nume,Rol,Salariu_Final" << endl;
    for (size_t i = 0; i < topAngajati.size() && i < 3; i++)
    {
        f1 << (i + 1) << "," << topAngajati[i]->getNume() << "," << topAngajati[i]->getSalariu() << endl;
    }
    f1.close();
    cout << "Raport_top3_salarii.csv generat." << endl;

    // 2.Cereri waitin (sortate)
    vector<Cerere *> cereriAsteptare;
    for (auto c : cereri)
    {
        if (c->status == "InAsteptare" || c->status == "Waiting")
            cereriAsteptare.push_back(c);
    }
    sort(cereriAsteptare.begin(), cereriAsteptare.end(), comparaCereriAlfabetic);

    ofstream f2("raport_asteptare.csv");
    f2 << "ID,Tip,Marca,Model,Data" << endl;
    for (auto c : cereriAsteptare)
    {
        f2 << c->id << "," << c->tip << "," << c->marca << "," << c->model << "," << c->data << endl;
    }
    f2.close();
    cout << "Raport_asteptare.csv generat." << endl;

    // 3.Raport fails
    vector<pair<string, int>> listaEsecuri;
    for (auto const &[cheie, val] : statsRefuzuri)
    {
        listaEsecuri.push_back({cheie, val});
    }
    sort(listaEsecuri.begin(), listaEsecuri.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         { return a.second > b.second; }); 

    ofstream f3("raport_fail.csv");
    f3 << "Aparat,Nr_Refuzuri" << endl;
    for (auto p : listaEsecuri)
    {
        f3 << p.first << "," << p.second << endl;
    }
    f3.close();
    cout << "Raport_fail.csv generat." << endl;
}

void Service::concediazaAngajat(int idTarget)
{
    bool gasit = false;
    for (size_t i = 0; i < angajati.size(); i++)
    {
        if (angajati[i]->getId() == idTarget)
        {
            delete angajati[i];
            angajati.erase(angajati.begin() + i);
            cout << "Angajatul cu ID" << idTarget << " a demisionat." << endl;
            gasit = true;
            break;
        }
    }
    if (!gasit)
    {
        cout << "err:Nu am gasit niciun angajat cu ID " << idTarget << endl;
    }
}

void Service::angajeazaManual()
{
    cout << "Angajare noua:" << endl;
    int anNastere;
    cout << "Introduceti Anul Nasterii: ";
    cin >> anNastere;
    if (2026 - anNastere < 16)
    {
        cout << "Nu are mai mult de 16 :(" << endl;
        return;
    }
    string nume, prenume, cnp, dataAng, oras, tip;
    cout << "Nume: ";
    cin >> nume;
    cout << "Prenume: ";
    cin >> prenume;
    cout << "CNP (13 cifre): ";
    cin >> cnp;
    cout << "Data Angajarii(zi.luna.an): ";
    cin >> dataAng;
    cout << "Oras: ";
    cin >> oras;
    cout << "Rol (Tehnician/Receptioner/Supervizor):";
    cin >> tip;
    try
    {
        if (tip == "Tehnician")
        {
            vector<string> competente;
            cout << "Cate marci stie sa repare? ";
            int nr;
            cin >> nr;
            for (int i = 0; i < nr; i++)
            {
                string marca;
                cout << "Marca" << i + 1 << ": ";
                cin >> marca;
                competente.push_back(marca);
            }
            angajati.push_back(new Tehnician(nume, prenume, cnp, dataAng, oras, competente));
        }
        else if (tip == "Supervizor")
        {
            angajati.push_back(new Supervizor(nume, prenume, cnp, dataAng, oras));
        }
        else if (tip == "Receptioner")
        {
            angajati.push_back(new Receptioner(nume, prenume, cnp, dataAng, oras));
        }
        else
        {
            cout << "Rol invalid......Angajare anulata." << endl;
            return;
        }
        cout << "Angajatul" << nume << "a fost adaugat." << endl;
    }
    catch (const exception &e)
    {
        cout << "Eroare la creare ang: " << e.what() << endl;
    }
}

void Service::assignReceptioner(int idCerere)
{
    vector<Receptioner *> rec;
    for (auto a : angajati)
        if (auto r = dynamic_cast<Receptioner *>(a))
            rec.push_back(r);
    if (!rec.empty())
        rec[rand() % rec.size()]->adaugaCerere(idCerere);
}

void Service::modificaNumeAngajat()
{
    int id;
    cout << "Introdu ID angajat: ";
    if (!(cin >> id))
    {
        cout << "Eroare: ID-ul trebuie sa fie un numar!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    for (auto ang : angajati)
    {
        if (ang->getId() == id)
        {
            string numeNou, prenumeNou;
            cout << "Nume actual:" << ang->getNume() << endl;
            cout << "Nume Nou: ";
            cin >> numeNou;
            cout << "Prenume Nou:";
            cin >> prenumeNou;
            cout << "Update done." << endl;
            return;
        }
    }
    cout << "Angajatul nu a fost gasit." << endl;
}

void Service::adaugaElectrocasnicManual()
{
    cout << "Adaugare electro:" << endl;

    string tip;
    cout << "Tip(TV/Frigider/MasinaSpalat):";
    cin >> tip;

    if (tip != "TV" && tip != "Frigider" && tip != "MasinaSpalat")
    {
        cout << "Tip invalid! Trebuie sa fie exact: TV, Frigider sau MasinaSpalat." << endl;
        return;
    }

    string marca, model;
    int an;
    double pret;

    cout << "Marca: ";
    cin >> marca;
    cout << "Model: ";
    cin >> model;
    cout << "An Fabricatie: ";
    cin >> an;
    cout << "Pret (baza): ";
    cin >> pret;

    try
    {
        if (tip == "TV")
        {
            double diag;
            cout << "Diagonala (cm): ";
            cin >> diag;
            electrocasnice.push_back(new Televizor(marca, model, an, pret, diag));
        }
        else if (tip == "Frigider")
        {
            int areCongelator;
            cout << "Are Congelator? (1-Da, 0-Nu): ";
            cin >> areCongelator;
            electrocasnice.push_back(new Frigider(marca, model, an, pret, (bool)areCongelator));
        }
        else if (tip == "MasinaSpalat")
        {
            double cap;
            cout << "Capacitate (kg): ";
            cin >> cap;
            electrocasnice.push_back(new MasinaSpalat(marca, model, an, pret, cap));
        }
        cout << " -> " << tip << " " << marca << " adaugat in database!" << endl;
    }
    catch (...)
    {
        cout << "Eroare la adaugare electro" << endl;
    }
}

void Service::stergeElectrocasnic()
{
    cout << "Sterge Electro:" << endl;
    if (electrocasnice.empty())
    {
        cout << "Lista goala" << endl;
        return;
    }

    string marca, model;
    cout << "Marca de sters: ";
    cin >> marca;
    cout << "Model de sters: ";
    cin >> model;
    bool sters = false;
    for (size_t i = 0; i < electrocasnice.size(); i++)
    {
        if (electrocasnice[i]->getMarca() == marca && electrocasnice[i]->getModel() == model)
        {
            delete electrocasnice[i];
            electrocasnice.erase(electrocasnice.begin() + i);
            cout << "-x Modelul " << marca << " " << model << " a fost sters." << endl;
            sters = true;
            break;
        }
    }
    if (!sters)
    {
        cout << "Nu am gasit modelul:" << endl;
    }
}