#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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

	
	// ----------- TEST 1: player gains 2 cards, discards all other revealed cards --------------
	printf("\nTEST 1: player gains 2 cards, discards all other revealed cards\n");
	
	//go through all possible combinations of 2 treasures in deck
	for (i = 0; i < G.deckCount[thisPlayer]; i++) {
		for (j = i + 1; j < G.deckCount[thisPlayer]; j++) {
			
			//set player deck to have 2 randomly placed treasures
			for (m = 0; m < G.deckCount[thisPlayer]; m++) {
				G.deck[thisPlayer][m] = estate;
			}
			G.deck[thisPlayer][i] = copper;
			G.deck[thisPlayer][j] = copper;
			
			m = G.deckCount[thisPlayer] - 1;
			int treasureCount = 0;
			int disposalCount = 0;
			while (treasureCount < 2 && m > -1) {
				if (G.deck[thisPlayer][m] == copper || G.deck[thisPlayer][m] == silver || G.deck[thisPlayer][m] == gold)
					treasureCount++;
				else
					disposalCount++;
				m--;
			}
			
			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			newCards = 2;
			
			printf("\nTreasure placed at deck positions %d and %d\n", i, j);
			printf("Finding the two treasures will require disposing %d other cards\n", disposalCount);
			
			printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
			if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
				printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
			}
			
			printf("before: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
			if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
				printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
			}
			
			printf("Play card\n");
			cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded)) {
				printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			}
			
			printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - disposalCount);
			if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - disposalCount)) {
				printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - disposalCount);
			}
		}
	}
	
	
	// ----------- TEST 2: discard pile gains all discards --------------
	printf("\nTEST 2: discard pile gains all discards\n");
	
	//go through all possible combinations of 2 treasures in deck
	for (i = 0; i < G.deckCount[thisPlayer]; i++) {
		for (j = i + 1; j < G.deckCount[thisPlayer]; j++) {
			
			//set player deck to have 2 randomly placed treasures
			for (m = 0; m < G.deckCount[thisPlayer]; m++) {
				G.deck[thisPlayer][m] = estate;
			}
			G.deck[thisPlayer][i] = copper;
			G.deck[thisPlayer][j] = copper;
			
			m = G.deckCount[thisPlayer] - 1;
			int treasureCount = 0;
			int disposalCount = 0;
			while (treasureCount < 2 && m > -1) {
				if (G.deck[thisPlayer][m] == copper || G.deck[thisPlayer][m] == silver || G.deck[thisPlayer][m] == gold)
					treasureCount++;
				else
					disposalCount++;
				m--;
			}
			
			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			newCards = 2;
			
			printf("\nTreasure placed at deck positions %d and %d\n", i, j);
			printf("Finding the two treasures will require disposing %d other cards\n", disposalCount);
			
			printf("before: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
			if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
				printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
			}
			
			printf("Play card\n");
			cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("after: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + disposalCount + discarded);
			if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + disposalCount + discarded)) {
				printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + disposalCount + discarded);
			}
		}
	}
	
	
	// ----------- TEST 3: no change for other player --------------
	printf("\nTEST 3: no change for other players\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	newCards = 3;
	thisPlayer = 1;
	
	printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("before: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("Play card\n");
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	
	// ----------- TEST 4: no change in supply piles --------------
	printf("\nTEST 4: no change in supply piles\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	for (i = 0; i < treasure_map + 1; i++) {
		printf("before: supply %d = %d, expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
		if (!asserttrue(testG.supplyCount[i], G.supplyCount[i])) {
			printf("ASSERT FAILED: supply %d = %d, expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
		}
	}
	
	printf("Play card\n");
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	for (i = 0; i < treasure_map + 1; i++) {
		printf("after: supply %d = %d, expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
		if (!asserttrue(testG.supplyCount[i], G.supplyCount[i])) {
			printf("ASSERT FAILED: supply %d = %d, expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
		}
	}

	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


