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


    if (NOISY_TEST) {
        printf("\n\nTesting end turn!\n");
    }


    r = initializeGame(numPlayer, k, seed, &G);
    G.whoseTurn = 0;
    G.hand[0][0] = estate;
    G.hand[0][1] = baron;
    G.handCount[0] = 2;
    G.handCount[1] = 0;
    G.discardCount[0] = 0;

    endTurn(&G);
    if(NOISY_TEST) {
        printf("Testing player 0 hand count ");
    }
    assert(G.handCount[0] == 0);
    if(NOISY_TEST) {
        printf("Testing player 1 hand count ");
    }
    assert(G.handCount[1] == 5);
    if(NOISY_TEST) {
        printf("Testing player 0 discard count ");
    }
    assert(G.discardCount[0] == 2);
    if(NOISY_TEST) {
        printf("Testing player 0 1st discard is estate ");
    }
    assert(G.discard[0][0] == estate);
    if(NOISY_TEST) {
        printf("Testing player 0 2nd discard is baron ");
    }
    assert(G.discard[0][1] == baron);
    if(NOISY_TEST) {
        printf("Testing outpost played set to 0 ");
    }
    assert(G.outpostPlayed == 0);
    if(NOISY_TEST) {
        printf("Testing phase set to 0 ");
    }
    assert(G.phase == 0);
    if(NOISY_TEST) {
        printf("Testing num actions set to 1 ");
    }
    assert(G.numActions == 1);
    if(NOISY_TEST) {
        printf("Testing coins set to 0 ");
    }
    assert(G.coins == 0);
    if(NOISY_TEST) {
        printf("Testing num buys set to 1 ");
    }
    assert(G.numBuys == 1);
    if(NOISY_TEST) {
        printf("Testing played card count set to 0 ");
    }
    assert(G.playedCardCount == 0);

}