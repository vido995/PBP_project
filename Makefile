CFLAGS	= -g -Wall 
CF = `mysql_config --cflags --libs`

main: konobar.o gost.o sefSale.c radnikKojiSprema.o main.c
	gcc $(CFLAGS) -o $@ $^ $(CF) 

radnikKojiSprema.o: radnikKojiSprema.c radnikKojiSprema.h
	gcc  $(CFLAGS) -c -o $@ $< $(CF)

sefSale.o: gost.o konobar.o sefSale.c sefSale.h
	gcc  $(CFLAGS) $^ -o $@ $(CF)

gost.o: gost.c gost.h
	gcc  $(CFLAGS) -c -o $@ $< $(CF)

konobar.o: konobar.c konobar.h
	gcc  $(CFLAGS) -c -o $@ $< $(CF)

.PHONY: clean

clean:
	rm -rf *~ *.o