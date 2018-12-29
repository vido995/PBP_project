#include "main.h"
#include "sefSale.h"
#include "konobar.h"
#include "radnikKojiSprema.h"

int main(){
    Sql sql;
    sql.connection = mysql_init(NULL);
    
    if(mysql_real_connect(sql.connection,"localhost", "root", "root", "mydb", 0, NULL, 0) == NULL){
        printf("Failed to connect to database\n\n");
        printf("%s\n",mysql_error(sql.connection));
    } else {
        printf("\nDobrodosli!\n");
        printf("Unesite svoju sifru:\n");
    }

    char tipRadnika[50];
    int nijeUnetaSifra = 1;

    int sifraRadnika;
    while(nijeUnetaSifra) {

        scanf("%d", &sifraRadnika);

        sprintf(sql.query, "select case when k.idKonobara is not null and k.sefSale = true then 'sefSale' when k.idKonobara is not null then 'konobar' \
                            when rp.idRadnikaKojiPriprema is not null and tipStavke = 'pice' then 'sanker' \
                            when rp.idRadnikaKojiPriprema is not null and tipStavke = 'jelo' then 'kuvar' end as TipRadnika \
                            from Radnik r left join Konobar k on r.idRadnika = k.idKonobara \
                            left join RadnikKojiPriprema rp on rp.idRadnikaKojiPriprema = r.idRadnika \
                            where r.idRadnika = '%d' limit 1;", sifraRadnika);
        
        if(mysql_query(sql.connection, sql.query)){
            printf("%s\n",mysql_error(sql.connection));
            exit(EXIT_FAILURE);
        }

        sql.result = mysql_use_result(sql.connection);
        sql.column = mysql_fetch_fields(sql.result);

        if ((sql.row = mysql_fetch_row(sql.result))) {
            sprintf(tipRadnika, "%s", sql.row[0]);
            nijeUnetaSifra = 0;
        } else {
            printf("Radnik sa ovom sifrom ne postoji! Unesite validnu sifru:\n");
        }

        while((sql.row = mysql_fetch_row(sql.result))){}
    }

    while(1) {
        if (strcmp(tipRadnika, "sefSale") == 0) {
            prikazZaSefaSale(&sql, sifraRadnika);
        } else if (strcmp(tipRadnika, "konobar") == 0) {
            prikazZaKonobare(&sql, sifraRadnika);
        } else if (strcmp(tipRadnika, "sanker") == 0) {
            prikazZaSankere(&sql, sifraRadnika);
        } else if (strcmp(tipRadnika, "kuvar") == 0) {
            prikazZaKuvare(&sql, sifraRadnika);
        }
    }
    mysql_close(sql.connection);
    return 0;
}
