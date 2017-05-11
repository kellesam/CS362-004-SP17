CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer.c dominion.c rngs.o
	echo "Random test for adventurer card:" > randomtestadventurer.out
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.c rngs.o $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	
randomtestcard1.out: randomtestcard1.c dominion.c rngs.o
	echo "Random test for smithy card:" > randomtestcard1.out
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.c rngs.o $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	
randomtestcard2.out: randomtestcard2.c dominion.c rngs.o
	echo "Random test for mine card:" > randomtestcard2.out
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.c rngs.o $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	
unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Unit test for isGameOver function:" > unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	
	echo "Unit test for updateCoins function:" >> unittestresults.out
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	
	echo "Unit test for gainCard function:" >> unittestresults.out
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	
	echo "Unit test for fullDeckCount function:" >> unittestresults.out
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	
	echo "Unit test for smithy card:" >> unittestresults.out
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	
	echo "Unit test for adventurer card:" >> unittestresults.out
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	
	echo "Unit test for village card:" >> unittestresults.out
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	
	echo "Unit test for mine card:" >> unittestresults.out
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out randomtestadventurer.out randomtestcard1.out randomtestcard2.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out randomtestadventurer randomtestadventurer.out randomtestcard1 randomtestcard1.out randomtestcard2 randomtestcard2.out
