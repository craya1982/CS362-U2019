#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void assert(int value) {
    if (NOISY_TEST) {
        char *result =  value == 1 ? "passed" : "failed";
        printf("Test %s\n", result);
    }
}

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

/**
 * TESTING TRIBUTE
 */

    //Test player has 1 card

    //Test player
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    G.hand[0][0] = estate;
    G.hand[0][1] = estate;
    G.hand[0][2] = ambassador;
    G.handCount[0] = 3;
    G.playedCardCount = 0;
    ambassadorCard(2, 0, 0, 2, &G); 

    return 0;
}