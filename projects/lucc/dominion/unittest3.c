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
 * TESTING AMBASSADOR
 */

    if (NOISY_TEST) {
        printf("\n\nTesting ambassador function!\n");
    }

   //Test invalid amount of cards to discard
    if (NOISY_TEST) {
        printf("Testing number of cards to discard\n");
    }
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    
    if (NOISY_TEST) {
        printf("3 Cards (invalid) ");
    }
    assert(ambassadorCard(3, 1, 0, 0, &G) == -1);
    
    if (NOISY_TEST) {
        printf("-1 Cards (invalid) ");
    }
    assert(ambassadorCard(-1, 1, 0, 0, &G) == -1);
    
    if (NOISY_TEST) {
        printf("0 Cards (valid) ");
    }
    assert(ambassadorCard(0, 1, 0, 0, &G) != -1);
    
    if (NOISY_TEST) {
        printf("2 Cards (valid) ");
    }
    assert(ambassadorCard(2, 1, 0, 0, &G) != -1);

   //Test selected card to discard is the hand position doesnt execute
    if (NOISY_TEST) {
        printf("Testing selected card to discard is the same as handPos (invalid) ");
    }
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    assert(ambassadorCard(2, 1, 0, 1, &G) == -1);


    //Test 2 cards to discard, hand has 2 cards, one of which is ambassador card -- should return -1
    if (NOISY_TEST) {
        printf("Testing not enough cards to discard! ");
    }
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    G.hand[0][0] = estate;
    G.hand[0][1] = ambassador;
    G.handCount[0] = 2;
    assert(ambassadorCard(2, 0, 0, 1, &G) == -1);

    //Test supply count is increased
    if (NOISY_TEST) {
        printf("Supply count increased! ");
    }
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    G.hand[0][0] = estate;
    G.hand[0][1] = estate;
    G.hand[0][2] = ambassador;
    G.handCount[0] = 3;
    G.supplyCount[estate] = 0;
    ambassadorCard(2, 0, 0, 2, &G);

    assert(G.supplyCount[estate] == 2);

    //Test playedCardCount is increased
    if (NOISY_TEST) {
        printf("Played card count should increase by 1 ");
    }
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);
    G.numActions = 0;
    G.hand[0][0] = estate;
    G.hand[0][1] = estate;
    G.hand[0][2] = ambassador;
    G.handCount[0] = 3;
    G.playedCardCount = 0;
    ambassadorCard(2, 0, 0, 2, &G);

    assert(G.playedCardCount == 1);

    return 0;
}