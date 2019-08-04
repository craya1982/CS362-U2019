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
 * TESTING MINE
 */

    if (NOISY_TEST) {
        printf("\n\nTesting Mine Card!\n");
    }

    if (NOISY_TEST) {
        printf("Testing Invalid Cards return -1\n");
    }

    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    G.hand[0][0] = province;
    G.hand[0][1] = adventurer;
    G.hand[0][2] = mine;
    G.handCount[0] = 3;
    G.playedCardCount = 0;
    assert(cardEffect_Mine(0, 0, treasure_map, &G, 2) == -1);
    assert(cardEffect_Mine(0, 1, treasure_map, &G, 2) == -1);

    G.hand[0][0] = copper;

    assert(cardEffect_Mine(0, 0, estate, &G, 2) == -1);
    assert(cardEffect_Mine(0, 1, -1, &G, 2) == -1);

    if (NOISY_TEST) {
        printf("Testing gain treasure map\n");
    }
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    G.hand[0][0] = copper;
    G.hand[0][1] = adventurer;
    G.hand[0][2] = mine;
    G.handCount[0] = 3;
    G.playedCardCount = 0;

    cardEffect_Mine(0, 0, treasure_map, &G, 2);

    assert(G.hand[0][1] == treasure_map);

    return 0;
}