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
        printf("\n\nTesting initializing game!\n");
    }
    r = initializeGame(numPlayer, k, seed, &G);

    if (NOISY_TEST) {
        printf("Correct 2 players: ");
    }
    assert(G.numPlayers == 2);

    if (NOISY_TEST) {
        printf("Correct curse: ");
    }
    assert(G.supplyCount[curse] == 10);

    if (NOISY_TEST) {
        printf("Correct duchy: ");
    }
    assert(G.supplyCount[duchy] == 8);

    if (NOISY_TEST) {
        printf("Correct province: ");
    }
    assert(G.supplyCount[province] == 8);


    if (NOISY_TEST) {
        printf("Correct estate: ");
    }
    assert(G.supplyCount[estate] == 8);

    if (NOISY_TEST) {
        printf("Correct copper: ");
    }
    assert(G.supplyCount[copper] == 46); 

    if (NOISY_TEST) {
        printf("Correct silver: ");
    }
    assert(G.supplyCount[silver] == 40);

    if (NOISY_TEST) {
        printf("Correct gold: ");
    }
    assert(G.supplyCount[gold] == 30);

    if (NOISY_TEST) {
        printf("Correct great hall: ");
    }
    assert(G.supplyCount[great_hall] == 8);

    
    numPlayer = 3;
    r = initializeGame(numPlayer, k, seed, &G);

    if (NOISY_TEST) {
        printf("Correct 3 players: ");
    }
    assert(G.numPlayers == 3);

    if (NOISY_TEST) {
        printf("Correct curse: ");
    }
    assert(G.supplyCount[curse] == 20);

    if (NOISY_TEST) {
        printf("Correct duchy: ");
    }
    assert(G.supplyCount[duchy] == 12);

    if (NOISY_TEST) {
        printf("Correct province: ");
    }
    assert(G.supplyCount[province] == 12);


    if (NOISY_TEST) {
        printf("Correct estate: ");
    }
    assert(G.supplyCount[estate] == 12);

    if (NOISY_TEST) {
        printf("Correct copper: ");
    }
    assert(G.supplyCount[copper] == 39); 

    if (NOISY_TEST) {
        printf("Correct silver: ");
    }
    assert(G.supplyCount[silver] == 40);

    if (NOISY_TEST) {
        printf("Correct gold: ");
    }
    assert(G.supplyCount[gold] == 30);

    if (NOISY_TEST) {
        printf("Correct great hall: ");
    }
    assert(G.supplyCount[great_hall] == 12);
}