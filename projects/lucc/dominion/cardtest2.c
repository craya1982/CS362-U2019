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
        printf("\n\nTesting shuffle!\n");
    }

    if (NOISY_TEST) {
        printf("Cards shuffled and at least two items don't match original position ");
    }
    r = initializeGame(numPlayer, k, seed, &G);
    G.deck[0][0] = estate;
    G.deck[0][1] = baron;
    G.deck[0][2] = treasure_map;
    G.deck[0][3] = copper;
    G.deck[0][4] = gold;
    G.deckCount[0] = 5;

    shuffle(0, &G);

    assert(G.deck[0][0] != estate || G.deck[0][1] != baron || G.deck[0][2] != treasure_map || G.deck[0][3] != copper || G.deck[0][4] != gold);

}