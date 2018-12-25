CFLAGS	= -g -Wall 
CF = `mysql_config --cflags --libs`

main: radnici.o podesavanja.o main.c
	gcc $(CFLAGS) -o $@ $^ $(CF) 

podesavanja.o: podesavanja.c podesavanja.h
	gcc  $(CFLAGS) -c -o $@ $< $(CF)

radnici.o: radnici.c radnici.h
	gcc  $(CFLAGS) -c -o $@ $< $(CF)

.PHONY: clean

clean:
	rm -rf *~ *.o