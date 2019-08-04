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
        printf("\n\nTesting get winners!\n");
    }


    r = initializeGame(numPlayer, k, seed, &G);
    G.hand[0][0] = estate;
    G.hand[0][1] = duchy;
    G.handCount[0] = 2;
    G.handCount[1] = 0;
    int winners[2] = { -1, -1};


    if(NOISY_TEST) {
        printf("Player 1 wins, P2 no cards ");
    }
    getWinners(winners, &G);
    assert(winners[0] == 1);

    if(NOISY_TEST) {
        printf("Player 2 wins with province ");
    }
    G.hand[1][0] = province;
    G.handCount[1] = 1;

    getWinners(winners, &G);
    assert(winners[1] == 1);
    
}