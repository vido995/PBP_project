CFLAGS	= -g -Wall `mysql_config --cflags --libs`

main: radnici.o podesavanja.o main.c
	gcc -o $@ $^ $(CFLAGS)

podesavanja.o: podesavanja.c podesavanja.h
	gcc -o $(CFLAGS) -c -o $@ $<

radnici.o: radnici.c radnici.h
	gcc -o $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *~ *.o