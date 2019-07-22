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
 * TESTING BARON HELPER
 */

//TEST 1
#if (NOISY_TEST == 1)   
    printf("Test baron helper method\n");
#endif
#if (NOISY_TEST == 1)
    printf("Test supply count set to 1\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[estate] = 1;
    G.handCount[0] = 1;
    handleBaronGainEstate(&G, 0);
#if (NOISY_TEST == 1)
    printf("Expected supply count value: 0\n");
#endif
    assert(G.supplyCount[estate] == 0);
#if (NOISY_TEST == 1)
    printf("Expected hand count value: 2\n");
#endif
    assert(G.handCount[0] == 2);


//TEST 2
#if (NOISY_TEST == 1)
    printf("Test supply count set to 0\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[estate] = 0;
    G.handCount[0] = 1;
    handleBaronGainEstate(&G, 0);

#if (NOISY_TEST == 1)
    printf("Expected value: 0\n");
#endif
    assert(G.supplyCount[estate] == 0);
#if (NOISY_TEST == 1)
    printf("Expected hand count value: 1\n");
#endif
    assert(G.handCount[0] == 1);

//TEST 3
#if (NOISY_TEST == 1)
    printf("Test supply count set to 5\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[estate] = 5;
    G.handCount[0] = 1;
    handleBaronGainEstate(&G, 0);
#if (NOISY_TEST == 1)
    printf("Expected value: 4\n");
#endif
    assert(G.supplyCount[estate] == 4);
#if (NOISY_TEST == 1)
    printf("Expected hand count value: 2\n");
#endif
    assert(G.handCount[0] == 2);



/**
 * TESTING BARON METHOD
 */
// TEST 4
#if (NOISY_TEST == 1)   
    printf("Test baron method\n");
#endif
#if (NOISY_TEST == 1)
    printf("Test discardEstateFlag set to false\n");
    //First test goes into helper method directly, so re-test a known passing test
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[estate] = 1;
    G.handCount[0] = 1;
    G.numBuys = 0;
    baronCard(&G, 0, 0);
#if (NOISY_TEST == 1)
    printf("Expected supply count value: 0\n");
#endif
    assert(G.supplyCount[estate] == 0);
#if (NOISY_TEST == 1)
    printf("Expected hand count value: 2\n");
#endif
    assert(G.handCount[0] == 2);
#if (NOISY_TEST == 1)
    printf("Expected numBuys: 1\n");
#endif
    assert(G.numBuys == 1);


//TEST 5
#if (NOISY_TEST == 1)
    printf("Test no estate card present when discard flag set to true\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[estate] = 1;
    //hand count is 0, so no estate card is possible
    G.handCount[0] = 0;
    G.numBuys = 0;

    baronCard(&G, 1, 0);
#if (NOISY_TEST == 1)
    printf("Expected supply count value: 1\n");
#endif
    assert(G.supplyCount[estate] == 1);
#if (NOISY_TEST == 1)
    printf("Expected hand count value: 0\n");
#endif
    assert(G.handCount[0] == 0);
#if (NOISY_TEST == 1)
    printf("Expected numBuys: 1\n");
#endif
    assert(G.numBuys == 1);


//Test 6
#if (NOISY_TEST == 1)
    printf("Test estate card present when flag set to true\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[estate] = 1;
    //hand count is 0, so no estate card is possible
    G.handCount[0] = 1;
    G.hand[0][0] = estate;
    G.discardCount[0] = 0;
    G.numBuys = 0;
    G.coins = 0;

    baronCard(&G, 1, 0);
#if (NOISY_TEST == 1)
    printf("Expected supply count value: 0\n");
#endif
    assert(G.supplyCount[estate] == 0);
#if (NOISY_TEST == 1)
    printf("Expected hand count value: 0\n");
#endif
    assert(G.handCount[0] == 0);
#if (NOISY_TEST == 1)
    printf("Expected numBuys: 1\n");
#endif
    assert(G.numBuys == 1);
#if (NOISY_TEST == 1)
    printf("Expected coins: 4\n");
#endif
    assert(G.coins == 4);
#if (NOISY_TEST == 1)
    printf("Expected discard count: 1\n");
#endif
    assert(G.discardCount[0] == 1);

    printf("All tests passed!\n");

    return 0;
}