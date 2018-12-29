#ifndef GOST_H
#define GOST_H

#include "main.h"

typedef struct{
    int sifraDodatka;
    int sifraStavke;
} DodatakStavka;

void prikazPicovnika(Sql *sql, int idMenija);
void prikazJelovnika(Sql *sql, int idMenija);
void prikaziMeni(Sql *sql, int sifraStola);
void prikaziTipJela(Sql *sql);
void prikaziTipPica(Sql *sql);
#endif