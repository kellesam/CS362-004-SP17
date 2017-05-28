#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

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

	
	// ----------- TEST 1: player gains 3 cards, discards 1 --------------
	printf("\nTEST 1: player gains 3 cards, discards 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	newCards = 3;
	
	printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("Play card\n");
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded)) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	}

	
	// ----------- TEST 2: the 3 cards are from the current player's deck --------------
	printf("\nTEST 2: the 3 cards are from the current player's deck\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	newCards = 3;
	
	printf("before: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("Play card\n");
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
		
	printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards)) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
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
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

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
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	for (i = 0; i < treasure_map + 1; i++) {
		printf("after: supply %d = %d, expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
		if (!asserttrue(testG.supplyCount[i], G.supplyCount[i])) {
			printf("ASSERT FAILED: supply %d = %d, expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
		}
	}

	
	// ----------- TEST 5: discard pile gains 1 card --------------
	printf("\nTEST 5: discard pile gains 1 card\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("before: discard pile = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	}
	
	printf("Play card\n");
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("after: discard pile = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded)) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	}
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


