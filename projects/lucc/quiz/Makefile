CFLAGS= -Wall -fpic -coverage -lm -std=c99

runFile: testme.o
	./testme.o

testme.o: testme.c
	gcc -o testme.o testme.c -g $(CFLAGS)

testmeCoverage: clean testme.o
	./testme.o >> testmeCoverage.out
	gcov testme.c -b -f >> testmeCoverage.out
	cat testme.c.gcov >> testmeCoverage.out

clean:
	rm -f *.o testme.o *.gcov *.gcda *.gcno *.so *.out
