#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver"

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
    int numPlayers;
	int maxPlayers = 4;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	
	// ----------- TEST 1: game ends when province pile is empty --------------
	printf("\nTEST 1: game ends when province pile is empty\n");
	
	
	for (numPlayers = 2; numPlayers <= maxPlayers; numPlayers++) {
		memset(&G, 0, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayers, k, seed, &G); // initialize a new game
		
		for (e = 0; e < 4; e++) {
			for (d = 0; d < 4; d++) {
				for (p = 0; p < 4; p++) {

					G.supplyCount[estate] = e;
					G.supplyCount[duchy] = d;
					G.supplyCount[province] = p;
	
					if (p < 1) {
						if (!asserttrue(isGameOver(&G), 1))
							printf("ASSERT FAILED: continued with %d players, %d estate, %d duchy, %d province\n", numPlayers, e, d, p);
						else
							printf("Successful: game over with %d players, %d estate, %d duchy, %d province\n\n", numPlayers, e, d, p);
					}
					else {
						if (!asserttrue(isGameOver(&G), 0))
							printf("ASSERT FAILED: game over with %d players, %d estate, %d duchy, %d province\n", numPlayers, e, d, p);
						else
							printf("Successful: continued with %d players, %d estate, %d duchy, %d province\n", numPlayers, e, d, p);
					}
				}
			}
		}
	}
	
	// ----------- TEST 2: game ends when 3+ supply piles are empty --------------
	printf("\nTEST 2: game ends when 3+ supply piles are empty\n");
	
	for (numPlayers = 2; numPlayers <= maxPlayers; numPlayers++) {
		memset(&G, 0, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayers, k, seed, &G); // initialize a new game
		
		for (i = 0; i < treasure_map + 1; i++) {
			
			G.supplyCount[i] = 0;
			
			if (i > 1) {
				if (!asserttrue(isGameOver(&G), 1))
					printf("ASSERT FAILED: continued with %d players, %d empty supply piles\n", numPlayers, i);
				else
					printf("Successful: game over with %d players, %d empty supply piles\n", numPlayers, i);
			}
			else {
				if (!asserttrue(isGameOver(&G), 0))
					printf("ASSERT FAILED: game over with %d players, %d empty supply piles\n", numPlayers, i);
				else
					printf("Successful: continued with %d players, %d empty supply piles\n", numPlayers, i);
			}
		}
	}
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);


	return 0;
}


