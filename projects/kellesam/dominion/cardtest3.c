#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

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

	
	// ----------- TEST 1: player gains 1 card, discards 1 --------------
	printf("\nTEST 1: player gains 1 card, discards 1\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	newCards = 1;
	
	printf("before: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("before: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer])) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	}
	
	printf("Play card\n");
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded)) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	}
	
	printf("after: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	if (!asserttrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded)) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	}
	
	
	// ----------- TEST 2: the 1 card is from the current player's deck --------------
	printf("\nTEST 2: the 1 card is from the current player's deck\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("before: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	printf("Play card\n");
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
		
	printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards)) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	}
	
	// ----------- TEST 3: the current player gains 2 actions --------------
	printf("\nTEST 3: the player gains 2 actions\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("before: action count = %d, expected = %d\n", testG.numActions, G.numActions);
	if (!asserttrue(testG.numActions, G.numActions)) {
		printf("ASSERT FAILED: action count = %d, expected = %d\n", testG.numActions, G.numActions);
	}
	
	printf("Play card\n");
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
		
	printf("after: action count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
	if (!asserttrue(testG.numActions, G.numActions + newActions)) {
		printf("ASSERT FAILED: action count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
	}
	
	// ----------- TEST 4: no change for other player --------------
	printf("\nTEST 4: no change for other players\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
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
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("after: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	if (!asserttrue(testG.handCount[thisPlayer], G.handCount[thisPlayer])) {
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	}
	
	printf("after: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	if (!asserttrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer])) {
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	}
	
	
	// ----------- TEST 5: no change in supply piles --------------
	printf("\nTEST 5: no change in supply piles\n");
	
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

	
	// ----------- TEST 6: discard pile gains 1 card --------------
	printf("\nTEST 6: discard pile gains 1 card\n");
	
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


