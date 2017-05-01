#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "updateCoins"

int asserttrue(int left, int right) {
	if (left != right) {
		printf("Function did not return <%d>\n", right);
		return 0;
	}
	else
		return 1;
}

int main() {
    int newCards = 0;
	int newActions = 2;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
	int e, d, p;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
	int maxPlayers = 4;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	
	// ----------- TEST 1: no treasure in hand --------------
	printf("\nTEST 1: no treasure in hand\n");
	
	for (bonus = -1; bonus < 2; bonus++) {
		
		G.hand[thisPlayer][0] = estate;
		G.hand[thisPlayer][1] = estate;
		G.hand[thisPlayer][2] = estate;
		G.hand[thisPlayer][3] = estate;
		G.hand[thisPlayer][4] = estate;
		G.coins = 0;
	
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		printf("Bonus = %d\n", bonus);
		
		printf("before: coin count = %d, expected = %d\n", testG.coins, G.coins);
		if (!asserttrue(testG.coins, G.coins)) {
			printf("ASSERT FAILED: coin count = %d, expected = %d\n", testG.coins, G.coins);
		}

		updateCoins(thisPlayer, &testG, bonus);

		printf("after: coin count = %d, expected = %d\n", testG.coins, G.coins + bonus);
		if (!asserttrue(testG.coins, G.coins + bonus)) {
			printf("ASSERT FAILED: coin count = %d, expected = %d\n", testG.coins, G.coins + bonus);
		}
	}
	
	// ----------- TEST 2: add copper --------------
	printf("\nTEST 2: add copper\n");
	
	G.hand[thisPlayer][0] = estate;
	G.hand[thisPlayer][1] = estate;
	G.hand[thisPlayer][2] = estate;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = estate;
	G.coins = 0;
	bonus = 0;
	
	for (i = 0; i < G.handCount[thisPlayer]; i++) {	
	
		G.hand[thisPlayer][i] = copper;
		
		printf("Adding %d copper\n", i + 1);
		
		printf("before: coin count = %d, expected = %d\n", G.coins, i);
		if (!asserttrue(G.coins, i)) {
			printf("ASSERT FAILED: coin count = %d, expected = %d\n", G.coins, i);
		}

		updateCoins(thisPlayer, &G, bonus);

		printf("after: coin count = %d, expected = %d\n", G.coins, i + 1);
		if (!asserttrue(G.coins, i + 1)) {
			printf("ASSERT FAILED: coin count = %d, expected = %d\n", G.coins, i + 1);
		}
	}
	
	// ----------- TEST 3: add silver --------------
	printf("\nTEST 3: add silver\n");
	
	G.hand[thisPlayer][0] = estate;
	G.hand[thisPlayer][1] = estate;
	G.hand[thisPlayer][2] = estate;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = estate;
	G.coins = 0;
	bonus = 0;
	
	for (i = 0; i < G.handCount[thisPlayer]; i++) {	
	
		G.hand[thisPlayer][i] = silver;
		
		printf("Adding %d silver\n", i + 1);
		
		printf("before: coin count = %d, expected = %d\n", G.coins, i*2);
		if (!asserttrue(G.coins, i*2)) {
			printf("ASSERT FAILED: coin count = %d, expected = %d\n", G.coins, i*2);
		}

		updateCoins(thisPlayer, &G, bonus);

		printf("after: coin count = %d, expected = %d\n", G.coins, i*2 + 2);
		if (!asserttrue(G.coins, i*2 + 2)) {
			printf("ASSERT FAILED: coin count = %d, expected = %d\n", G.coins, i*2 + 2);
		}
	}
	
	// ----------- TEST 4: add gold --------------
	printf("\nTEST 4: add gold\n");
	
	G.hand[thisPlayer][0] = estate;
	G.hand[thisPlayer][1] = estate;
	G.hand[thisPlayer][2] = estate;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = estate;
	G.coins = 0;
	bonus = 0;
	
	for (i = 0; i < G.handCount[thisPlayer]; i++) {	
	
		G.hand[thisPlayer][i] = gold;
		
		printf("Adding %d gold\n", i + 1);
		
		printf("before: coin count = %d, expected = %d\n", G.coins, i*3);
		if (!asserttrue(G.coins, i*3)) {
			printf("ASSERT FAILED: coin count = %d, expected = %d\n", G.coins, i*3);
		}

		updateCoins(thisPlayer, &G, bonus);

		printf("after: coin count = %d, expected = %d\n", G.coins, i*3 + 3);
		if (!asserttrue(G.coins, i*3 + 3)) {
			printf("ASSERT FAILED: coin count = %d, expected = %d\n", G.coins, i*3 + 3);
		}
	}

	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);


	return 0;
}


