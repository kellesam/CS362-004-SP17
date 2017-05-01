#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

int asserttrue(int left, int right) {
	if (left != right) {
		printf("Function did not return <%d>\n", right);
		return 0;
	}
	else
		return 1;
}

int main() {
    int newCards = 1;
	int newActions = 2;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	
	// ----------- TEST 1: all possible combinations of treasure --------------
	
	printf("\nTEST 1: all combinations of treaure (4 = copper, 5 = silver, 6 = gold)\n");
	for (i = copper; i <= gold; i++) {		//i = have		
		for (j = copper; j <= gold; j++) {	//j = want
			
			if (i == copper && j == gold)
				printf("\nPlayer has %d, trashes for %d (should be rejected)\n", i, j);
			else
				printf("\nPlayer has %d, trashes for %d\n", i, j);
			
			G.hand[thisPlayer][0] = i;
			G.hand[thisPlayer][1] = estate;
			G.hand[thisPlayer][2] = estate;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = estate;
			choice2 = j;
			
			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			
			printf("before: cards in hand: ");
			for (m = 0; m < testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
			}
			printf(", expected: ");
			for (m = 0; m < G.handCount[thisPlayer]; m++) {
				printf("(%d)", G.hand[thisPlayer][m]);
			}
			printf("\n");
			
			printf("before: discard pile = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
			if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
				printf("ASSERT FAILED: discard pile = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
			}
			
			printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
			if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
				printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
			}
			
			printf("before: supply %d = %d, expected = %d\n", j, testG.supplyCount[j], G.supplyCount[j]);
			if (!asserttrue(testG.supplyCount[j], G.supplyCount[j])) {
				printf("ASSERT FAILED: supply %d = %d, expected = %d\n", j, testG.supplyCount[j], G.supplyCount[j]);
			}
			
			printf("Play card\n");
			cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
			
			if (i == copper && j == gold)
				G.hand[thisPlayer][0] = i;
			else {
				G.hand[thisPlayer][0] = j;
				discarded = 2;
			}
			
			printf("after: cards in hand: ");
			for (m = 0; m < testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
			}
			printf(", expected: ");
			for (m = 0; m < G.handCount[thisPlayer] - 1; m++) {
				printf("(%d)", G.hand[thisPlayer][m]);
			}
			printf("\n");
			
			printf("after: discard pile = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
			if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded)) {
				printf("ASSERT FAILED: discard pile = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
			}
			
			printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded)) {
				printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			}
			
			if (i == copper && j == gold) {
				printf("no change: treaure card = %d, expected = %d\n", testG.hand[thisPlayer][4], G.hand[thisPlayer][4]);
				if (!asserttrue(testG.hand[thisPlayer][4], G.hand[thisPlayer][4])) {
					printf("ASSERT FAILED: treaure card = %d, expected = %d\n", testG.hand[thisPlayer][4], G.hand[thisPlayer][4]);
				}
				
				printf("after: supply %d = %d, expected = %d\n", j, testG.supplyCount[j], G.supplyCount[j]);
				if (!asserttrue(testG.supplyCount[j], G.supplyCount[j])) {
					printf("ASSERT FAILED: supply %d = %d, expected = %d\n", j, testG.supplyCount[j], G.supplyCount[j]);
				}
			}
			else {
				printf("card changed: treaure card = %d, expected = %d\n", testG.hand[thisPlayer][4], j);
				if (!asserttrue(testG.hand[thisPlayer][4], j)) {
					printf("ASSERT FAILED: treaure card = %d, expected = %d\n", testG.hand[thisPlayer][4], j);
				}
				
				printf("after: supply %d = %d, expected = %d\n", j, testG.supplyCount[j], G.supplyCount[j] - newCards);
				if (!asserttrue(testG.supplyCount[j], G.supplyCount[j] - newCards)) {
					printf("ASSERT FAILED: supply %d = %d, expected = %d\n", j, testG.supplyCount[j], G.supplyCount[j] - newCards);
				}
			}
		}
	}	
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


