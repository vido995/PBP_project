#include "radnici.h"

void prikazZaRadnike(Sql *sql){
	int stanje = 0;
	
	printf("%s:\n%s\n%s\n%s\n%s\n\n",
		"Izaberite opciju",
		"1. Sef sale", 
		"2. Konobar",
		"3. Sanker",
		"4. Kuvar");
	scanf("%i", &stanje);

	switch(stanje){
		case 1:
			prikazZaSefaSale(sql);
		break;
		case 2:
			prikazZaKonobare(sql);
		break;
		case 3:
			prikazZaSankereIKuvare(sql);
		break;
		case 4:
			prikazZaSankereIKuvare(sql);
		break;
		default:
			printf("\nNiste izabrali nijednu validnu opciju!\n");
	}
}

void prikazZaSefaSale(Sql *sql) {
	int stanje = 0;
	
	printf("%s:\n%s\n%s\n%s\n%s\n\n",
		"Izaberite opciju",
		"1. Dodaj radnika", 
		"2. Dodaj stavku",
		"3. Napravi novi meni",
		"4. Nazad");
	scanf("%i", &stanje);

	switch(stanje){
		case 1:
			dodajRadnika(sql);
		break;
		case 2:
			dodajStavku(sql);
		break;
		case 3:
			dodajNoviMeni(sql); // TODO: Triger kad se dodaje novi meni da se poslednjem vreme do postavi na sada. 
		break;
		case 4:
			prikazZaRadnike(sql);
		// Stolovi se insertuju kroz skripte.
		default:
			printf("\nNiste izabrali nijednu validnu opciju!\n");
	}
}

void dodajRadnika(Sql *sql) {
	printf ("Unesite:\n");
	printf("Sifru radnika:\n");
	int sifra = 0;
	scanf("%i", &sifra);
	char ime[45], prezime[45];
	printf("Ime:\n");
	scanf("%s", ime);
	printf("Prezime:\n");
	scanf("%s", prezime);

	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Radnik (idRadnika, ime, prezime) values ('%d', '%s', '%s');", sifra, ime, prezime);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
	
	int stanje = 0;
	
	printf("%s:\n%s\n%s\n%s\n\n",
		"Kreirani radnik radi kao:",
		"1. Konobar", 
		"2. Sanker",
		"3. Kuvar");
	
	scanf("%i", &stanje);
	
	switch(stanje){
		case 1:
			dodajKonobara(sql, sifra);
		break;
		case 2:
			dodajSankeraKuvara(sql, sifra, "pice");
		break;
		case 3:
			dodajSankeraKuvara(sql, sifra, "jelo");
		break;
		default:
			printf("\nNiste izabrali nijednu validnu opciju!\n");
	}

	prikazZaSefaSale(sql);
}

void dodajKonobara(Sql *sql, int sifra) {
	printf ("Za konobara unesite:\n");
	printf("Depozit:\n");
	double depozit = 0;
	scanf("%lf", &depozit);
	
	strcpy(sql->query,"");
	
	sprintf(sql->query, "insert into Konobar (idKonobara, depozit) values ('%i', '%lf');", sifra, depozit);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
}

void dodajSankeraKuvara(Sql *sql, int sifra, char* tipStavke) {
	strcpy(sql->query,"");
	
	sprintf(sql->query, "insert into RadnikKojiPriprema (idRadnikaKojiPriprema, tipStavke) values ('%i', '%s');", sifra, tipStavke);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
}

// TODO
void dodajStavku(Sql *sql) {
	int tipStavke = 0;
	
	printf("%s:\n%s\n%s\n\n",
		"Koji tip stavke unosite:",
		"1. Jelo", 
		"2. Pice");
		
	scanf("%i", &tipStavke);
	
	printf ("Unesite:\n");
	printf("Sifru stavke:\n");
	int sifra = 0;
	scanf("%i", &sifra);
	char *naziv = (char *) malloc(100);
	char *opis = (char *) malloc(100); 
	printf("Naziv:\n");
	scanf ("%ms", &naziv);
	printf("Cenu:\n");
	double cena = 0;
	scanf("%lf", &cena);
	printf("Opis:\n");
	scanf ("%ms", &opis);
	
	strcpy(sql->query,"");
	
	sprintf(sql->query, "insert into Stavka (idStavke, naziv, cena, opis) values (%i, %s, %lf, %s);", sifra, naziv, cena, opis);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
	
	if (tipStavke == 1) {
		dodajJelo(sql, sifra);
	} else {
		dodajPice(sql, sifra);
	}

	prikazZaSefaSale(sql);
}

void dodajJelo(Sql *sql, int sifra) {
	printf("gramazu\n");
	int gramaza = 0;
	scanf("%i", &gramaza);
	printf("broj osoba\n");
	int brojOsoba = 0;
	scanf("%i", &brojOsoba);
	
	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Jelo (idJela, gramaza, brojOsoba) values (%i, %i, %i);", sifra, gramaza, brojOsoba);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
	
	// TODO: Dodati izbor za tip jela!
}

void dodajPice(Sql *sql, int sifra) {
	printf("kolicinu\n");
	double kolicina = 0;
	scanf("%lf", &kolicina);
	
	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Pice (idPica, kolicina) values (%i, %lf);", sifra, kolicina);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
	
	// TODO: Dodati izbor za tip pica!
	// TODO: Dodati izbor za dodatak uz pice!
}

void dodajNoviMeni(Sql *sql) {
	printf ("Unesite:\n");
	printf("sifru menija\n");
	int sifra = 0;
	scanf("%i", &sifra);
	printf("popust\n");
	int popust = 0;
	scanf("%i", &popust);
	
	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Meni (idMenija, vaziOd, vaziDo, popust) values ('%i', now(), NULL, '%i');", sifra, popust);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		printf("%s\n",mysql_error(sql->connection));
		exit (EXIT_FAILURE);
	}
	
	strcpy(sql->query,"");
	sprintf(sql->query, "update Meni set vaziDo = now() where vaziDo is null and idMenija != %i;", sifra);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		printf("%s\n",mysql_error(sql->connection));
		exit (EXIT_FAILURE);
	}
	
	printf ("Izaberite sve stavke koje su deo Vaseg novog menija navodjenjem sifre stavke:\n");
	printf ("(Kada izaberete sve stavke ukucajte \"kraj\")\n");
	
	ispisiSveStavke(sql);
	
	char s[50];
	
	scanf ("%s", s);
	
	while(strcmp(s, "kraj")) {
		int sifraStavke = 0;
		sifraStavke = (int)strtol(s,NULL,10);

		strcpy(sql->query,"");
		sprintf(sql->query, "insert into MeniStavka (idMenija, idStavke) values ('%i', '%i');", sifra, sifraStavke);
		
		if (mysql_query (sql->connection, sql->query) != 0) {
			printf ("Neuspesno izvrsavanje upita\n");
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}

		scanf ("%s", s);
	}

	prikazZaSefaSale(sql);
}

void ispisiSveStavke(Sql *sql) {
	strcpy(sql->query, "");
    sprintf(sql->query, "select s.idStavke as Sifra, s.naziv as Naziv, s.cena as Cena from Stavka s");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s\t",sql->column[i].name);
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s\t",sql->row[i]);
        }
        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
    printf("\n\n");
}

void prikazZaKonobare(Sql *sql) {
	//Prikazati neusluzene narudzbine i nenaplacene racune
	strcpy(sql->query, "");
    sprintf(sql->query, "select n.idNarudzbine as SifraNarudzbine, s.naziv as NazivStola, s.idStola as SifraStola from Narudzbina n join Sto s on n.idStola = s.idStola where n.usluzeno = false;");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s\t",sql->column[i].name);
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s\t",sql->row[i]);
        }
        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
    printf("\n\n");
	
	printf("Unesite sifru narudzbine koju zelite da usluzite:\n");
	
	int sifraNarudzbine = 0;
	scanf("%i", &sifraNarudzbine);
	prikaziStavkeIzNarudzbine(sql, sifraNarudzbine);
	
}

void prikaziStavkeIzNarudzbine(Sql *sql, int sifraNarudzbine) {
	strcpy(sql->query, "");
    sprintf(sql->query, "select ns.spremno as Spremno, s.naziv as Naziv, d.naziv as NazivDodatka, d.kolicina as DodatakKolicina \
						from NarudzbinaStavka ns join MeniStavka ms on ms.idMenija = ns.idMenija and ms.idStavke = ns.idStavke \
						join Stavka s on s.idStavke = ms.idStavke \
						left join DodatakStavkeIzNarudzbine dsn on dsn.idNarudzbine = ns.idNarudzbine and \
																dsn.idMenija = ms.idMenija and ms.idStavke = dsn.idStavke \
						left join Dodatak d on d.idDodatak = dsn.idDodatka \
						where ns.idNarudzbine = %i;", sifraNarudzbine);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s\t",sql->column[i].name);
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s\t",sql->row[i]);
        }
        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
    printf("\n\n");
	
	printf("Kad je sve spremno iz neke narudzbine mozete da je usluzite.\n");
	printf("Ukoliko ste usluzili narudzbinu unesite \"usluzeno\".\n");
	printf("Ukoliko zelite da vidite status neke druge narudzbine unesite \"nazad\".\n");
	
	
	char s[50];
	
	scanf ("%s", s);
	
	if(strcmp(s, "usluzeno") == 0) {
		printf("aaaaa");
		strcpy(sql->query, "");
		sprintf(sql->query, "update Narudzbina set usluzeno = true where idNarudzbine = %i;", sifraNarudzbine);

		if(mysql_query(sql->connection, sql->query)){
			printf("%s\n",mysql_error(sql->connection));
			exit(EXIT_FAILURE);
		}
	} 
	
	prikazZaKonobare(sql);
}

void prikazZaSankereIKuvare(Sql *sql) {
	//Prikazuju se sve stavke iz narudzbine koje nisu spremne
	// TODO: Razdvojiti za konobare i za kuvare i razmotriti dodatak, ovako ne bi trebalo da bude dobro...
	strcpy(sql->query, "");
    sprintf(sql->query, "select s.naziv as Naziv, d.naziv as NazivDodatka, d.kolicina as DodatakKolicina \
						from NarudzbinaStavka ns join MeniStavka ms on ms.idMenija = ns.idMenija and ms.idStavke = ns.idStavke \
						join Stavka s on s.idStavke = ms.idStavke \
						left join DodatakStavkeIzNarudzbine dsn on dsn.idNarudzbine = ns.idNarudzbine and \
																dsn.idMenija = ms.idMenija and ms.idStavke = dsn.idStavke \
						left join Dodatak d on d.idDodatak = dsn.idDodatka \
						where ns.spremno = false \
						order by ns.idNarudzbine");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s\t",sql->column[i].name);
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s\t",sql->row[i]);
        }
        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
    printf("\n\n");
	
}