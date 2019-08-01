#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 0

void assert(int value)
{
    if (NOISY_TEST)
    {
        char *result = value == 1 ? "passed" : "failed";
        printf("Test %s\n", result);
    }
}

int checkBaronCard(int p, struct gameState *post)
{
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int preHasEstate = 0;
    for (int x = 0; x < post->deckCount[p]; x++)
    {
        if (post->hand[p][x] == estate)
        {
            preHasEstate = 1;
        }
    }

    

    //int baronCard(struct gameState *state, int discardEstateFlag, int currentPlayer)
    int discardEstate = floor(Random() * 1.9); //0-0.9 false, 1-1.9 true
    baronCard(post, discardEstate, p);
    
    assert(pre.numBuys == (post->numBuys + 1));

    if (discardEstate == 0 || preHasEstate == 0)
    {
        if (pre.supplyCount[estate] == 0)
        {
            assert(pre.supplyCount[estate] == post->supplyCount[estate]);
            assert(pre.handCount[p] == post->handCount[p]);
            assert(pre.discardCount[p] == pre.discardCount[p]);
        }
        else
        {
            assert(pre.supplyCount[estate] == post->supplyCount[estate] - 1);
            assert(pre.handCount[p] == post->handCount[p] + 1);
            assert(pre.discardCount[p] == pre.discardCount[p]);
        }
    }
    else
    {
        assert(pre.supplyCount[estate] == post->supplyCount[estate] - 1);
        assert(pre.handCount[p] == post->handCount[p] + 1);
        assert(pre.discardCount[p] == pre.discardCount[p] + 1);
    }
}

int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G;
    printf("Testing baronCard.\n");

    printf("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char *)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 2);

        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        
        G.supplyCount[estate] = floor(Random() * 5);
        
        G.discardCount[p] = floor(Random() * MAX_DECK);
        int cards = floor(Random() * 5);
        
        G.handCount[p] = cards;
        for (int i = 0; i < cards; ++i)
        {
            int randCard = rand() % (treasure_map + 1);
            G.hand[p][i] = randCard;
            
        }
        checkBaronCard(p, &G);
    }

    printf("ALL TESTS OK\n");

    exit(0);

    return 0;
}
