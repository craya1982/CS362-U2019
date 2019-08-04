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
 * TESTING MINION
 */

    if (NOISY_TEST) {
        printf("\n\nTesting Minion\n");
    }
    //test cases
    //test incremented numActions with various combinations
    if (NOISY_TEST) {
        printf("Testing numActions always incremented\n");
    }
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    cardEffect_Minion(0, 0, 1, &G, 0);
    assert(G.numActions == 1);
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    cardEffect_Minion(0, 0, 1, &G, 1);
    assert(G.numActions == 1);
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    cardEffect_Minion(0, 0, 1, &G, 0);
    assert(G.numActions == 1);
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    cardEffect_Minion(1, 1, 0, &G, 0);
    assert(G.numActions == 1);
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    cardEffect_Minion(1, 1, 0, &G, 1);
    assert(G.numActions == 1);
    //test position discarded from hand
    if (NOISY_TEST) {
        printf("Testing discarding card from provided position\n");
    }
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);

    G.hand[0][0] = minion;
    G.hand[0][1] = estate;

    cardEffect_Minion(0, 1, 0, &G, 0);
    assert(G.hand[0][0] != minion);


    //test choosecoinsflag and that hand was not discard
    if (NOISY_TEST) {
        printf("Testing coins chosen no extra cards discarded\n");
    }
   r = initializeGame(numPlayer, k, seed, &G);

    G.hand[0][0] = minion;
    G.hand[0][1] = estate;

    G.handCount[0] = 2;
    int coins = G.coins;

    cardEffect_Minion(0, 1, 0, &G, 0);
    assert(G.hand[0][0] != minion);
    assert(G.handCount[0] == 1);
    assert(G.hand[0][0] == estate);
    assert(G.coins == coins + 2);

    //test hand was discarded and coins not incremented and players had hands redrawn
    //less than 4 cards for player 2
    if (NOISY_TEST) {
        printf("Testing discard user cards, 2nd player cards not discarded\n");
    }
    r = initializeGame(numPlayer, k, seed, &G);

    G.hand[0][0] = minion;
    G.hand[0][1] = estate;

    G.handCount[0] = 2;

    G.hand[1][0] = minion;
    G.hand[1][1] = estate;

    G.handCount[1] = 2;

    coins = G.coins;

    cardEffect_Minion(0, 0, 1, &G, 0);
    assert(G.handCount[0] == 4);
    assert(G.coins == coins);


    assert(G.hand[1][0] == minion);
    assert(G.handCount[1] == 2);
    assert(G.hand[1][1] == estate);

    //test p2 has 5 cards
    if (NOISY_TEST) {
        printf("Testing discard user cards, 2nd player cards discarded\n");
    }
    r = initializeGame(numPlayer, k, seed, &G);

    G.hand[0][0] = minion;
    G.hand[0][1] = estate;

    G.handCount[0] = 2;

    G.hand[1][0] = minion;
    G.hand[1][1] = estate;
    G.hand[1][2] = baron;
    G.hand[1][3] = minion;
    G.hand[1][4] = estate;

    G.handCount[1] = 5;

    coins = G.coins;

    cardEffect_Minion(0, 0, 1, &G, 0);
    assert(G.handCount[0] == 4);
    assert(G.coins == coins);


    assert(G.handCount[1] == 4);

    printf("All minion tests pass!\n");
    return 0;
}