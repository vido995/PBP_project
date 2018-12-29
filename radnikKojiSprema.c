#include"radnikKojiSprema.h"

void prikazZaSankere(Sql *sql, int sifraRadnikaKojiSprema) {
	//Prikazuju se sve stavke iz narudzbine koje nisu spremne

    printf("***** Stavke koje ste preuzeli *****\n");

    // TODO: NarudzbinaStavka mora imati svoj id zbog visestrukog narucivanja iste stavke u okviru jedne narudzbine

    strcpy(sql->query, "");
    sprintf(sql->query, "select ns.idStavkeIzNarudzbine 'Sifra stavke', s.naziv as Naziv, coalesce(d.naziv, 'bez dodatka') as 'Naziv dodatka', coalesce(d.kolicina, '') as 'Kolicina dodatka' \
						from NarudzbinaStavka ns join MeniStavka ms on ms.idMenija = ns.idMenija and ms.idStavke = ns.idStavke \
						join Stavka s on s.idStavke = ms.idStavke \
                        join Pice p on s.idStavke = p.idPica \
						left join DodatakStavkeIzNarudzbine dsn on dsn.idStavkeIzNarudzbine = ns.idStavkeIzNarudzbine \
						left join Dodatak d on d.idDodatak = dsn.idDodatka \
						where ns.spremno = false and ns.idRadnikPorudzbina = '%d' \
						order by ns.idNarudzbine", sifraRadnikaKojiSprema);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s",sql->column[i].name);

        for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
            printf(" ");
        }
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

            for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
                printf(" ");
            }
        }

        printf("\n\n");
    }
    
    printf("***** Stavke koje nisu preuzete *****\n");

	strcpy(sql->query, "");
    sprintf(sql->query, "select ns.idStavkeIzNarudzbine 'Sifra stavke', s.naziv as Naziv, coalesce(d.naziv, 'bez dodatka') as 'Naziv dodatka', coalesce(d.kolicina, '') as 'Kolicina dodatka' \
						from NarudzbinaStavka ns join MeniStavka ms on ms.idMenija = ns.idMenija and ms.idStavke = ns.idStavke \
						join Stavka s on s.idStavke = ms.idStavke \
                        join Pice p on s.idStavke = p.idPica \
						left join DodatakStavkeIzNarudzbine dsn on dsn.idStavkeIzNarudzbine = ns.idStavkeIzNarudzbine \
						left join Dodatak d on d.idDodatak = dsn.idDodatka \
						where ns.spremno = false and ns.idRadnikPorudzbina is null \
						order by ns.idNarudzbine");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s",sql->column[i].name);

        for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
            printf(" ");
        }
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);
            
            for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
                printf(" ");
            }
        }

        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
    
    izborStavkeZaPripremu(sql, sifraRadnikaKojiSprema, 1);
}

void prikazZaKuvare(Sql *sql, int sifraRadnikaKojiSprema) {
	//Prikazuju se sve stavke iz narudzbine koje nisu spremne

    printf("***** Stavke koje ste preuzeli *****\n");

	strcpy(sql->query, "");
    sprintf(sql->query, "select ns.idStavkeIzNarudzbine 'Sifra stavke', s.naziv as Naziv \
						from NarudzbinaStavka ns join MeniStavka ms on ms.idMenija = ns.idMenija and ms.idStavke = ns.idStavke \
						join Stavka s on s.idStavke = ms.idStavke \
                        join Jelo j on s.idStavke = j.idJela \
						where ns.spremno = false and ns.idRadnikPorudzbina = '%d' \
						order by ns.idNarudzbine", sifraRadnikaKojiSprema);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s",sql->column[i].name);

        for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
            printf(" ");
        }
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

            for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
                printf(" ");
            }
        }
        printf("\n\n");
    }

    printf("***** Stavke koje nisu preuzete *****\n");

	strcpy(sql->query, "");
    sprintf(sql->query, "select ns.idStavkeIzNarudzbine 'Sifra stavke', s.naziv as Naziv \
						from NarudzbinaStavka ns join MeniStavka ms on ms.idMenija = ns.idMenija and ms.idStavke = ns.idStavke \
						join Stavka s on s.idStavke = ms.idStavke \
                        join Jelo j on s.idStavke = j.idJela \
						where ns.spremno = false and ns.idRadnikPorudzbina is null \
						order by ns.idNarudzbine");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s",sql->column[i].name);

        for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
            printf(" ");
        }
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

            for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
                printf(" ");
            }
        }
        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
	
    izborStavkeZaPripremu(sql, sifraRadnikaKojiSprema, 0);
}

void izborStavkeZaPripremu(Sql *sql, int sifraRadnikaKojiSprema, int sanker) {


    printf("Unesite sifru stavke iz narudzbine  koju zelite da pripremite ili preuzmete:\n");
    printf("Ako zelite da osvezite listu narudzbina unesite \"osvezi\":\n");
	
    char pom[50];

    scanf("%s", pom);
	int sifraStavkeNarudzbine = 0;

    if (strcmp(pom, "osvezi") == 0) {
        if (sanker) {
            prikazZaSankere(sql, sifraRadnikaKojiSprema);
        } else {
            prikazZaKuvare(sql, sifraRadnikaKojiSprema);
        }
    } else {
        sifraStavkeNarudzbine = strtol(pom, NULL, 10);
    }

    strcpy(sql->query, "");
    sprintf(sql->query, "update NarudzbinaStavka ns set idRadnikPorudzbina = '%d' where idStavkeIzNarudzbine = '%d';", sifraRadnikaKojiSprema, sifraStavkeNarudzbine);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }


	printf("Ukoliko ste spremili stavku unesite \"spremno\".\n");
	printf("Ukoliko zelite da se vratite na prethodnu stranicu unesite \"nazad\".\n");
	
	
	char s[50];
	
	scanf ("%s", s);
	
	if(strcmp(s, "spremno") == 0) {
		strcpy(sql->query, "");
		sprintf(sql->query, "update NarudzbinaStavka ns set spremno = true where idStavkeIzNarudzbine = '%d';",  sifraStavkeNarudzbine);

		if(mysql_query(sql->connection, sql->query)){
			printf("%s\n",mysql_error(sql->connection));
			exit(EXIT_FAILURE);
		}
	} 
	
    if (sanker) {
	    prikazZaSankere(sql, sifraRadnikaKojiSprema);
    } else {
        prikazZaKuvare(sql, sifraRadnikaKojiSprema);
    }
}