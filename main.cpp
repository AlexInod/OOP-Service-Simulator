#include <iostream>
#include <string>
#include "Service.h"

using namespace std;

void afiseazaMeniu()
{
    cout << "\n======" << endl;
    cout << " SERVICE MENU" << endl;
    cout << "======" << endl;
    cout << "1. Incarca tot (Angajati, Electrocasnice, Cereri)" << endl;
    cout << "2. Afiseaza tot ce am incarcat " << endl;
    cout << "3. PORNESTE SIMULAREA " << endl;
    cout << "4. Angajeaza o persoana noua" << endl;
    cout << "5. Concediaza un angajat (dupa ID)" << endl;
    cout << "6. Modifica numele unui angajat (dupa ID)" << endl;
    cout << "7. Adauga Electrocasnic in catalog" << endl;
    cout << "8. Sterge Electrocasnic din catalog" << endl;
    cout << "0. Iesire" << endl;
    cout << "Alege: ";
}
int main()
{
    Service &app = Service::getInstance(); 
    int optiune;
    bool ruleaza = true;

    while (ruleaza)
    {
        afiseazaMeniu();
        cin >> optiune;
        switch (optiune)
        {
        case 1:
            cout << "Incarc datele..." << endl;
            app.citesteAngajati("angajati.txt");
            app.citesteElectro("electrocasnice.txt");
            app.citesteCereri("cereri.txt");
            break;

        case 2:
            app.afiseazaAng();
            app.afiseazaElectro();
            app.afiseazaCereri();
            break;
        case 3:
            app.runSimulator();
            app.rapoarte();
            break;
        case 4:
            app.angajeazaManual();
            break;
        case 5:
            int idDeSters;
            cout << "Introdu ID-ul angajatului care pleaca:";
            cin >> idDeSters;
            app.concediazaAngajat(idDeSters);
            break;
        case 6:
            app.modificaNumeAngajat();
            break;
        case 7:
            app.adaugaElectrocasnicManual();
            break;
        case 8:
            app.stergeElectrocasnic();
            break;
        case 0:
            cout << "CLosed" << endl;
            ruleaza = false;
            break;
        default:
            cout << "Wrong option" << endl;
        }
    }
    return 0;
}