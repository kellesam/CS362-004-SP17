#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "gainCard"

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
	int e, d, p;
	int result;
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

	
	// ----------- TEST 1: supply count for the card --------------
	printf("\nTEST 1: supply count for the card\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	for (i = -2; i < 3; i++) {
		testG.supplyCount[0] = i;
				
		printf("supply count = %d\n", i);
		
		result = gainCard(0, &testG, 2, thisPlayer);

		if (i < 1) {
			printf("gain card result = %d, expected = %d\n", result, -1);
			if (!asserttrue(result, -1))
				printf("ASSERT FAILED: gain card result = %d, expected = %d\n", result, -1);
			else
				printf("Successful: could not gain card with supply = %d\n", i);
		}
		else {
			printf("gain card result = %d, expected = %d\n", result, 0);
			if (!asserttrue(result, 0))
				printf("ASSERT FAILED: gain card result = %d, expected = %d\n", result, 0);
			else
				printf("Successful: can gain card with supply = %d\n", i);
		}
		
	}
	
	// ----------- TEST 2: add to discard --------------
	printf("\nTEST 2: add to discard\n");
	
	G.supplyCount[0] = 10;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("before: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	}
	
	printf("before: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("before: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0]);
	if (!asserttrue(testG.supplyCount[0], G.supplyCount[0])) {
		printf("ASSERT FAILED: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0]);
	}
	
	printf("Draw card\n");
	result = gainCard(0, &testG, 0, thisPlayer);
	
	printf("after: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards)) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards);
	}
	
	printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("after: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
	if (!asserttrue(testG.supplyCount[0], G.supplyCount[0] - 1)) {
		printf("ASSERT FAILED: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
	}
	
	// ----------- TEST 3: add to deck --------------
	printf("\nTEST 3: add to deck\n");
	
	G.supplyCount[0] = 10;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("before: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	}
	
	printf("before: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("before: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0]);
	if (!asserttrue(testG.supplyCount[0], G.supplyCount[0])) {
		printf("ASSERT FAILED: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0]);
	}
	
	printf("Draw card\n");
	result = gainCard(0, &testG, 1, thisPlayer);
	
	printf("after: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	}
	
	printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] + newCards);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] + newCards)) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] + newCards);
	}
	
	printf("after: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
	if (!asserttrue(testG.supplyCount[0], G.supplyCount[0] - 1)) {
		printf("ASSERT FAILED: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
	}
	
	// ----------- TEST 4: add to hand --------------
	printf("\nTEST 4: add to hand\n");
	
	G.supplyCount[0] = 10;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("before: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	}
	
	printf("before: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("before: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0]);
	if (!asserttrue(testG.supplyCount[0], G.supplyCount[0])) {
		printf("ASSERT FAILED: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0]);
	}
	
	printf("Draw card\n");
	result = gainCard(0, &testG, 2, thisPlayer);
	
	printf("after: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	}
	
	printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards)) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	}
	
	printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("after: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
	if (!asserttrue(testG.supplyCount[0], G.supplyCount[0] - 1)) {
		printf("ASSERT FAILED: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
	}
	
	// ----------- TEST 5: incorrect flag defaults to discard --------------
	printf("\nTEST 5: incorrect flag defaults to discard\n");
	
	G.supplyCount[0] = 10;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("before: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	}
	
	printf("before: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("before: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0]);
	if (!asserttrue(testG.supplyCount[0], G.supplyCount[0])) {
		printf("ASSERT FAILED: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0]);
	}
	
	printf("Draw card\n");
	result = gainCard(0, &testG, -18, thisPlayer);
	
	printf("after: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards)) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards);
	}
	
	printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("after: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
	if (!asserttrue(testG.supplyCount[0], G.supplyCount[0] - 1)) {
		printf("ASSERT FAILED: supply count = %d, expected = %d\n", testG.supplyCount[0], G.supplyCount[0] - 1);
	}
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);


	return 0;
}


