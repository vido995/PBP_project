#include"konobar.h"

void prikazZaKonobare(Sql *sql, int sifraKonobara) {

    printf("******** Narudzbine koje cekaju da se plate ********\n");
	
    strcpy(sql->query, "");
    sprintf(sql->query, "select n.idNarudzbine as 'Sifra narudzbine', s.naziv as 'Naziv stola', s.idStola as 'Sifra stola' \
                        from Narudzbina n join Sto s on n.idStola = s.idStola \
                        join Racun r on r.idRacun = n.idRacuna \
                        where n.idKonobara = '%d' and r.naplaceno = false;", sifraKonobara);

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

    printf("******** Narudzbine koje ste preuzeli ********\n");
	
    strcpy(sql->query, "");
    sprintf(sql->query, "select n.idNarudzbine as 'Sifra narudzbine', s.naziv as 'Naziv stola', s.idStola as 'Sifra stola' from Narudzbina n join Sto s on n.idStola = s.idStola where n.usluzeno = false and n.idKonobara = '%d';", sifraKonobara);

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

    printf("******** Narudzbine koje jos uvek nisu preuzete ********\n");

    //Prikazati neusluzene narudzbine i nenaplacene racune
	strcpy(sql->query, "");
    sprintf(sql->query, "select n.idNarudzbine as 'Sifra narudzbine', s.naziv as 'Naziv stola', s.idStola as 'Sifra stola' from Narudzbina n join Sto s on n.idStola = s.idStola where n.usluzeno = false and n.idKonobara is null;");

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
	
	printf("Unesite sifru narudzbine koju zelite da naplatite, usluzite ili preuzmete:\n");
    printf("Ako zelite da osvezite listu narudzbina unesite \"osvezi\":\n");
	
    char pom[50];

    scanf("%s", pom);
	int sifraNarudzbine = 0;

    if (strcmp(pom, "osvezi") == 0) {
        prikazZaKonobare(sql, sifraKonobara);
    } else {
        sifraNarudzbine = strtol(pom, NULL, 10);
    }

	prikaziStavkeIzNarudzbine(sql, sifraNarudzbine, sifraKonobara);
	
}

void prikaziStavkeIzNarudzbine(Sql *sql, int sifraNarudzbine, int sifraKonobara) {

    strcpy(sql->query, "");
    sprintf(sql->query, "update Narudzbina set idKonobara = '%d' where idNarudzbine = '%i';", sifraKonobara, sifraNarudzbine);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

	strcpy(sql->query, "");
    sprintf(sql->query, "select ns.spremno as Spremno, s.naziv as Naziv, coalesce(d.naziv, 'bez dodatka') as 'Naziv dodatka', coalesce(d.kolicina, '') as 'Kolicina dodatka' \
						from NarudzbinaStavka ns join MeniStavka ms on ms.idMenija = ns.idMenija and ms.idStavke = ns.idStavke \
						join Stavka s on s.idStavke = ms.idStavke \
						left join DodatakStavkeIzNarudzbine dsn on dsn.idStavkeIzNarudzbine = ns.idStavkeIzNarudzbine \
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
	
	printf("Kad je sve spremno iz neke narudzbine mozete da je usluzite.\n");
	printf("Ukoliko ste usluzili narudzbinu unesite \"usluzeno\".\n");
    printf("Ukoliko ste naplatili narudzbinu unesite \"naplaceno\".\n");
	printf("Ukoliko zelite da vidite status neke druge narudzbine unesite \"nazad\".\n");
	
	
	char s[50];
	
	scanf ("%s", s);
	
	if(strcmp(s, "usluzeno") == 0) {
		strcpy(sql->query, "");
		sprintf(sql->query, "update Narudzbina set usluzeno = true where idNarudzbine = %i;", sifraNarudzbine);

		if(mysql_query(sql->connection, sql->query)){
			printf("%s\n",mysql_error(sql->connection));
			exit(EXIT_FAILURE);
		}
	} else if (strcmp(s, "naplaceno") == 0) {
        strcpy(sql->query, "");
		sprintf(sql->query, "update Racun r set naplaceno = true where exists(select * from Narudzbina n where n.idNarudzbine = %i and n.idRacuna = r.idRacun);", sifraNarudzbine);

		if(mysql_query(sql->connection, sql->query)){
			printf("%s\n",mysql_error(sql->connection));
			exit(EXIT_FAILURE);
		}
    }
	
	prikazZaKonobare(sql, sifraKonobara);
}
