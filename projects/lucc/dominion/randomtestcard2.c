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

int checkMinionCard(int p, struct gameState *post)
{
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    
    int chooseCoinsCard = floor(Random() * 1.9); //0-0.9 false, 1-1.9 true
    int otherPlayer = p == 0 ? 1 : 0;

    minionCard(0, p, chooseCoinsCard, post);

    assert(pre.numActions == (post->numActions - 1 ));
    if (chooseCoinsCard == 0){
        assert(post->handCount[p] == 4);
        if (pre.handCount[otherPlayer] > 4) {
            assert(post->handCount[otherPlayer] == 4);
        }
        else {
            assert(post->handCount[otherPlayer] == pre.handCount[otherPlayer]);
        }
    }
    else
    {
        assert(pre.handCount[p] == (post->handCount[p] + 1));
        assert(pre.coins == (post->coins - 2));
    }
}

int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G;
    printf("Testing minionCard.\n");

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
        G.numPlayers = p;
        G.coins = Random() * 10;
        G.numBuys = Random() * 5;
        G.whoseTurn = p;

        for (int x = 0; x < 2; x++)
        {
            G.deckCount[x] = floor((Random() + 1) * MAX_DECK);
            for (int i = 0; i < G.deckCount[x]; ++i)
            {
                int randCard = rand() % (treasure_map + 1);
                G.deck[x][i] = randCard;
            }
            G.discardCount[x] = 0;

            int cards = floor((Random() + 1) * 10);
            G.handCount[x] = cards;
            for (int i = 0; i < cards; ++i)
            {
                if (i == 0)
                {
                    G.hand[x][i] = minion;
                }
                else
                {
                    int randCard = rand() % (treasure_map + 1);
                    G.hand[x][i] = randCard;
                }
            }
        }

        G.playedCardCount = 0;
        checkMinionCard(p, &G);
    }

    printf("ALL TESTS OK\n");

    exit(0);

    return 0;
}
