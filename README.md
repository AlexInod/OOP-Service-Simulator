# OOP-Service-Simulator

Un proiect C++ care simulează activitatea unui service de reparații electrocasnice. Motorul de simulare funcționează pe baza unor ticuri executate la fiecare secundă.

##  Arhitectura Claselor

###  Personal

Sistemul este construit pe baza unei ierarhii de clase:

* **Clasă de bază:** `Angajat`
* **Clase derivate:**

  * `Tehnician`
  * `Supervizor`
  * `Receptioner`

#### Caracteristici:

* **Tehnicienii**

  * Dețin competențe specifice
  * Pot lucra simultan la maximum 3 cereri
  * Primesc bonusuri pentru reparațiile finalizate
* **Recepționerul**

  * Gestionează cererile înregistrate
* **Supervizorul**

  * Rol de coordonare (logică de business)

### Echipamente

Ierarhia electrocasnicelor:

* **Clasă de bază:** `Electrocasnice`
* **Clase derivate:**

  * `Frigider`
  * `Televizor`
  * `MasinaDeSpalat`

#### Atribute:

* Exemple: capacitate, diagonală, alte specificații relevante

###  Management

* `Service` – nucleul aplicației, gestionează:

  * angajații
  * cererile
  * electrocasnicele
* `Cerere` – modelează o intervenție/reparație

###  Inițializare și Validare

* Se utilizează **Factory Pattern** pentru:

  * citirea datelor din fișiere `.txt`
  * instanțierea dinamică a obiectelor
* Validare inițială:

  * minim **3 tehnicieni**
  * minim **1 supervizor**
  * minim **1 recepționer**

###  Simularea Reparațiilor

* La fiecare tic:

  * durata cererilor active scade cu 1 secundă
* La finalizare:

  * cererea este marcată ca finalizată
  * tehnicianul primește bonus

### Tratarea Refuzurilor

* Cererile imposibil de rezolvat sunt:

  * respinse
  * marcate corespunzător

### Meniu Interactiv

Utilizatorul poate:

* adăuga / șterge angajați
* adăuga / șterge electrocasnice
* actualiza numele angajaților (ex: căsătorie)

### Rapoarte Finale

La finalul simulării se generează fișiere CSV:

* top salarii
* cereri rămase în așteptare (sortate)
* statistica refuzurilor

## Testare

* Proiect testat pe **6 cazuri diferite**
* Fiecare caz este organizat în foldere separate, cu nume sugestive


