#include "main.h"
#include "podesavanja.h"
#include "radnici.h"

int main(){
    Sql sql;
    sql.connection = mysql_init(NULL);
    
    if(mysql_real_connect(sql.connection,"localhost", "root", "root", "mydb",0, NULL, 0) == NULL){
        printf("Failed to connect to database\n\n");
        printf("%s\n",mysql_error(sql.connection));
    } else {
        printf("\nDobrodosli!\n\n");
    }

    int stanje = 0;

    while(1){
        printf("%s:\n%s\n%s\n\n",
            "Izaberite opciju",
            "1. Radnici restorana", 
            "2. Podesavanja vezana za sto");
        scanf("%i", &stanje);

        switch(stanje){
            case 1:
				printf("***** Prikaz za radnike *****\n");
                prikazZaRadnike(&sql);
            break;
            case 2:
				printf("***** Prikaz za radnike ******\n");
                izborStola(&sql);
            break;
            default:
                printf("\nNiste izabrali nijednu validnu opciju!\n");
        }
    }
    mysql_close(sql.connection);
    return 0;
}