compile: sieve.o driver.o
	gcc sieve.o driver.o -lm

run:
	./a.out $(args)

clean:
	-rm -f ./a.out *.o

sieve.o:
	gcc -c sieve.c

driver.p:
	gcc -c driver.c
