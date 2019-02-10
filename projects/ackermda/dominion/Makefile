CFLAGS= -Wall -fpic -coverage -lm -std=c99

testAssert.o: testAssert.h testAssert.c
	gcc -c testAssert.c -g $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o testAssert.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o testAssert.o rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c dominion.o testAssert.o rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c dominion.o testAssert.o rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c dominion.o testAssert.o rngs.o $(CFLAGS)

cardtest: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o testAssert.o rngs.o
	gcc -o cardtest1 cardtest1.c dominion.o testAssert.o rngs.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c dominion.o testAssert.o rngs.o $(CFLAGS)
	gcc -o cardtest3 cardtest3.c dominion.o testAssert.o rngs.o $(CFLAGS)
	gcc -o cardtest4 cardtest4.c dominion.o testAssert.o rngs.o $(CFLAGS)

runtests: unittest cardtest 
	echo "Unit Test Results" > unittestresult.out
	./unittest1 &>> unittestresult.out
	./unittest2 &>> unittestresult.out
	./unittest3 &>> unittestresult.out
	./unittest4 &>> unittestresult.out
	./cardtest1 &>> unittestresult.out
	./cardtest2 &>> unittestresult.out
	./cardtest3 &>> unittestresult.out
	./cardtest4 &>> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

unittest1: unittest1.c dominion.o rngs.o testAssert.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o testAssert.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o testAssert.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o testAssert.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o testAssert.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o testAssert.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o testAssert.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o testAssert.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o testAssert.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o testAssert.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o testAssert.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o testAssert.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o testAssert.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o testAssert.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o testAssert.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o testAssert.o $(CFLAGS)

clean:
	rm -f *.o *.exe playdom player *.gcov *.gcda *.gcno *.so *.out testDrawCard
