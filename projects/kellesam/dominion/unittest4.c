#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "fullDeckCount"

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
	
	for (i = 0; i < G.deckCount[thisPlayer]; i++)
		G.deck[thisPlayer][i] = estate;

	for (i = 0; i < G.handCount[thisPlayer]; i++)
		G.hand[thisPlayer][i] = estate;
	
	G.discardCount[thisPlayer] = 5;
	for (i = 0; i < G.discardCount[thisPlayer]; i++)
		G.discard[thisPlayer][i] = estate;
	
	// ----------- TEST 1: invalid card --------------
	printf("\nTEST 1: invalid card\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("Current deck: ");
	for (i = 0; i < testG.deckCount[thisPlayer]; i++)
		printf("(%d)", testG.deck[thisPlayer][i]);
	
	printf("\nCurrent hand: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
		printf("(%d)", testG.hand[thisPlayer][i]);
		
	printf("\nCurrent discard: ");
	for (i = 0; i < testG.discardCount[thisPlayer]; i++)
		printf("(%d)", testG.discard[thisPlayer][i]);
	
	int curCard = -964;
	printf("\nSearching for card (%d)\n", curCard);
	
	result = fullDeckCount(thisPlayer, curCard, &testG);
	
	printf("card count = %d, expected = %d\n", result, 0);
	if (!asserttrue(result, 0)) {
		printf("ASSERT FAILED: card count = %d, expected = %d\n", result, 0);
	}
	
	// ----------- TEST 2: card not present --------------
	printf("\nTEST 2: card not present\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("Current deck: ");
	for (i = 0; i < testG.deckCount[thisPlayer]; i++)
		printf("(%d)", testG.deck[thisPlayer][i]);
	
	printf("\nCurrent hand: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
		printf("(%d)", testG.hand[thisPlayer][i]);
		
	printf("\nCurrent discard: ");
	for (i = 0; i < testG.discardCount[thisPlayer]; i++)
		printf("(%d)", testG.discard[thisPlayer][i]);
	
	curCard = 2;
	printf("\nSearching for card (%d)\n", curCard);
	result = fullDeckCount(thisPlayer, curCard, &testG);
	
	printf("card count = %d, expected = %d\n", result, 0);
	if (!asserttrue(result, 0)) {
		printf("ASSERT FAILED: card count = %d, expected = %d\n", result, 0);
	}
	
	// ----------- TEST 3: card in deck --------------
	printf("\nTEST 3: card in deck\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	testG.deck[thisPlayer][0] = 2;
	
	printf("Current deck: ");
	for (i = 0; i < testG.deckCount[thisPlayer]; i++)
		printf("(%d)", testG.deck[thisPlayer][i]);
	
	printf("\nCurrent hand: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
		printf("(%d)", testG.hand[thisPlayer][i]);
		
	printf("\nCurrent discard: ");
	for (i = 0; i < testG.discardCount[thisPlayer]; i++)
		printf("(%d)", testG.discard[thisPlayer][i]);
	
	curCard = 2;
	printf("\nSearching for card (%d)\n", curCard);
	result = fullDeckCount(thisPlayer, curCard, &testG);
	
	printf("card count = %d, expected = %d\n", result, 1);
	if (!asserttrue(result, 1)) {
		printf("ASSERT FAILED: card count = %d, expected = %d\n", result, 1);
	}
	
	// ----------- TEST 4: card in deck and hand --------------
	printf("\nTEST 4: card in deck and hand\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	testG.deck[thisPlayer][0] = 2;
	testG.hand[thisPlayer][2] = 2;
	testG.hand[thisPlayer][4] = 2;
	
	printf("Current deck: ");
	for (i = 0; i < testG.deckCount[thisPlayer]; i++)
		printf("(%d)", testG.deck[thisPlayer][i]);
	
	printf("\nCurrent hand: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
		printf("(%d)", testG.hand[thisPlayer][i]);
		
	printf("\nCurrent discard: ");
	for (i = 0; i < testG.discardCount[thisPlayer]; i++)
		printf("(%d)", testG.discard[thisPlayer][i]);
	
	curCard = 2;
	printf("\nSearching for card (%d)\n", curCard);
	result = fullDeckCount(thisPlayer, curCard, &testG);
	
	printf("card count = %d, expected = %d\n", result, 3);
	if (!asserttrue(result, 3)) {
		printf("ASSERT FAILED: card count = %d, expected = %d\n", result, 3);
	}
	
	// ----------- TEST 5: card in deck, hand, and discard --------------
	printf("\nTEST 5: card in deck, hand, and discard\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	testG.deck[thisPlayer][0] = 2;
	testG.hand[thisPlayer][2] = 2;
	testG.hand[thisPlayer][4] = 2;
	testG.discard[thisPlayer][1] = 2;
	testG.discard[thisPlayer][3] = 2;
	
	printf("Current deck: ");
	for (i = 0; i < testG.deckCount[thisPlayer]; i++)
		printf("(%d)", testG.deck[thisPlayer][i]);
	
	printf("\nCurrent hand: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
		printf("(%d)", testG.hand[thisPlayer][i]);
		
	printf("\nCurrent discard: ");
	for (i = 0; i < testG.discardCount[thisPlayer]; i++)
		printf("(%d)", testG.discard[thisPlayer][i]);
	
	curCard = 2;
	printf("\nSearching for card (%d)\n", curCard);
	result = fullDeckCount(thisPlayer, curCard, &testG);
	
	printf("card count = %d, expected = %d\n", result, 5);
	if (!asserttrue(result, 5)) {
		printf("ASSERT FAILED: card count = %d, expected = %d\n", result, 5);
	}
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);


	return 0;
}


