#ifndef PODESAVANJA_H
#define PODESAVANJA_H

#include "main.h"

typedef struct{
    int sifraDodatka;
    int sifraStavke;
} DodatakStavka;

void izborStola(Sql *sql);
void prikaziMeni(Sql *sql, int sifraStola);
void prikazJelovnika(Sql *sql, int idMenija);
void prikazPicovnika(Sql *sql, int idMenija);

#endif
