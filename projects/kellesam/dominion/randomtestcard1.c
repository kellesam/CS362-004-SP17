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
	
	cardEffectSmithy(post, thisPlayer, 0);
	
	//test that player's hand gains two cards (gain three cards, lose one smithy)
	if (!asserttrue(post->handCount[thisPlayer], pre.handCount[thisPlayer] + 2))
		printf("ASSERT FAILED: hand count = %d, expected = %d\n", post->handCount[thisPlayer], pre.handCount[thisPlayer] + 2);
	
	//test that player's deck loses three cards
	if (!asserttrue(post->deckCount[thisPlayer], pre.deckCount[thisPlayer] - 3))
		printf("ASSERT FAILED: deck count = %d, expected = %d\n", post->deckCount[thisPlayer], pre.deckCount[thisPlayer] - 3);
	
	//test that player's discard gains one card
	if (!asserttrue(post->discardCount[thisPlayer], pre.discardCount[thisPlayer] + 1)) {
		printf("ASSERT FAILED: discard count = %d, expected = %d\n", post->discardCount[thisPlayer], pre.discardCount[thisPlayer] + 1);
	}
	
	return;
}

int main () {

	int i, n, r, p, deckCount, discardCount, handCount;

	int k[10] = {	adventurer, council_room, feast, gardens, mine,
					remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing cardEffectSmithy.\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 20; n++) {		//no. of times to run random test
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
		
		checkCard(p, &G);
	}

	printf ("ALL TESTS OK\n");

	return 0;
}
