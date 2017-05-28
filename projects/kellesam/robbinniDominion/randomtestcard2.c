#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int asserttrue(int left, int right) {
	if (left != right) {
		printf("Function did not return <%d>\n", right);
		return 0;
	}
	else
		return 1;
}

void checkCard(int thisPlayer, struct gameState *post) {
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	int discarded = 1;
	
	int oldCardIndex = floor(Random() * post->handCount[thisPlayer]);
	int oldCard = pre.hand[thisPlayer][oldCardIndex];
	int newCard = floor(Random() * (treasure_map + 5));
	
	int i, j, r;
	r = cardEffect(mine, oldCardIndex, newCard, 0, post, 0, 0);
	
	if (oldCard == copper && newCard == gold)
		discarded = 1;
	else {
		pre.hand[thisPlayer][oldCardIndex] = newCard;
		discarded = 2;
	}
	
	j = pre.hand[thisPlayer][oldCardIndex];  //store card we will trash

	int valid = 1;
	//test that function returns error if player tries to trash non-treasure card
	if (pre.hand[thisPlayer][oldCardIndex] < copper || pre.hand[thisPlayer][oldCardIndex] > gold) {
		valid = 0;
		if (!asserttrue(r, -1))
			printf("ASSERT FAILED: function return = %d, expected = %d\n", r, -1);
	}

	//test that function returns error if player tries to gain invalid card
	if (newCard > treasure_map || newCard < curse) {
		valid = 0;
		if (!asserttrue(r, -1))
			printf("ASSERT FAILED: function return = %d, expected = %d\n", r, -1);
	}
	
	//test that function returns error if player tries to gain card more than +3
	if ( (getCost(pre.hand[thisPlayer][oldCardIndex]) + 3) < getCost(newCard) ) {
		valid = 0;
		if (!asserttrue(r, -1))
			printf("ASSERT FAILED: function return = %d, expected = %d\n", r, -1);
	}
	
	if (valid) {
		//test that player's discard pile gains the mine card and discarded treasure
		if (!asserttrue(post->discardCount[thisPlayer], pre.discardCount[thisPlayer] + discarded))
			printf("ASSERT FAILED: discard pile = %d, expected = %d\n", post->discardCount[thisPlayer], pre.discardCount[thisPlayer] + discarded);

		//test that player's hand gains the new card and loses two cards (treasure and mine)
		if (!asserttrue(post->handCount[thisPlayer], pre.handCount[thisPlayer] + 1 - discarded))
			printf("ASSERT FAILED: hand count = %d, expected = %d\n", post->handCount[thisPlayer], pre.handCount[thisPlayer] + 1 - discarded);
	}
	
	if (oldCard == copper && newCard == gold) {
		//test that player's hand doesn't change if they try to gain a too-expensive card
		if (!asserttrue(post->hand[thisPlayer][oldCardIndex], pre.hand[thisPlayer][oldCardIndex]))
			printf("ASSERT FAILED: treaure card = %d, expected = %d\n", post->hand[thisPlayer][oldCardIndex], pre.hand[thisPlayer][oldCardIndex]);
		
		//test that supply doesn't change if player tries to gain a too-expensive card
		if (!asserttrue(post->supplyCount[newCard], pre.supplyCount[newCard]))
			printf("ASSERT FAILED: supply %d = %d, expected = %d\n", newCard, post->supplyCount[newCard], pre.supplyCount[newCard]);
	}
	else {
		//test that player's hand gains the new card
		if (!asserttrue(post->hand[thisPlayer][oldCardIndex], newCard))
			printf("ASSERT FAILED: treaure card = %d, expected = %d\n", post->hand[thisPlayer][oldCardIndex], newCard);
		
		//test that supply is decremented by one
		if (!asserttrue(post->supplyCount[newCard], pre.supplyCount[newCard] - 1))
			printf("ASSERT FAILED: supply %d = %d, expected = %d\n", newCard, post->supplyCount[newCard], pre.supplyCount[newCard] - 1);
	}
	
	return;
}

int main () {
printf("Made it to here\n");
	int i, n, r, p, deckCount, discardCount, handCount;

	int k[10] = {	adventurer, council_room, feast, gardens, mine,
					remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing mine card.\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 100; n++) {		//no. of times to run random test
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);		//fill struct with random data
		}
		p = floor(Random() * 4);		//randomly choose a player
		
		G.deckCount[p] = floor(Random() * MAX_DECK);		//randomly choose deckCount
		for (i = 0; i < G.deckCount[p]; i++)
			G.deck[p][i] = floor(Random() * treasure_map);		//fill deck with random cards
		
		G.discardCount[p] = floor(Random() * MAX_DECK);		//randomly choose discardCount
		for (i = 0; i < G.discardCount[p]; i++)
			G.discard[p][i] = floor(Random() * treasure_map);	//fill discard with random cards
		
		G.handCount[p] = floor(Random() * MAX_HAND);		//randomly choose handCount
		for (i = 0; i < G.handCount[p]; i++)
			G.hand[p][i] = floor(Random() * treasure_map);		//fill hand with random cards
		
		for (i = 0; i < treasure_map + 1; i++) {
			G.supplyCount[i] = floor(Random() * 50);		//randomly choose size of each supply pile
		}
		
		G.playedCardCount = floor(Random() * 10);			//randomly choose playedCardCount
		
		checkCard(p, &G);
	}

	printf ("ALL TESTS OK\n");

	return 0;
}
