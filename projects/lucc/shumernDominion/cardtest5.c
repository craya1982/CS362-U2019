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
        printf("\n\nTesting draw card!\n");
    }


    r = initializeGame(numPlayer, k, seed, &G);

    if(NOISY_TEST) {
        printf("Player 1 draws card, P2 unchanged ");
    }
    G.handCount[0] = 0;
    G.handCount[1] = 0;
    drawCard(0, &G);
    assert(G.handCount[0] == 1 && G.handCount[1] == 0);

    if(NOISY_TEST) {
        printf("Player 2 draws card, P1 unchanged ");
    }
    
    drawCard(1, &G);
    assert(G.handCount[0] == 1 && G.handCount[1] == 1);

    if (NOISY_TEST) {
        printf("Test P1 deck count empty ");
    }
    r = initializeGame(numPlayer, k, seed, &G);
    G.deckCount[0] = 0;
    G.discard[0][0] = estate;
    G.discardCount[0] = 1;
    G.handCount[0] = 0;
    drawCard(0, &G);
    assert(G.handCount[0] == 1 && G.deckCount[0] == 0 && G.discardCount[0] == 0 && G.deck[0][0] == estate);

}