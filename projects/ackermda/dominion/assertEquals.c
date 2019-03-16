#include "assertEquals.h"
#include <stdio.h>

#define SUPPLY_COUNT 27

int testCards(struct gameState* expected, struct gameState* actual) {
    int i, j;
    int result = 1;
    for (i = 0; i < MAX_PLAYERS; i++) {
        for (j = 0; j < MAX_DECK; j++) {
            int expectedDeckCard = expected->deck[i][j];
            int expectedHandCard = expected->hand[i][j];
            int expectedDiscardCard = expected->discard[i][j];

            int actualDeckCard = actual->deck[i][j];
            int actualHandCard = actual->hand[i][j];
            int actualDiscardCard = actual->discard[i][j];

            if (expectedDeckCard != actualDeckCard) {
                printf("Deck: Player %d Card %d. Expected card: %d, Actual card %d\n", i, j, expectedDeckCard, actualDeckCard);
                result = 0;
            }

            if (expectedHandCard != actualHandCard) {
                printf("Hand: Player %d Card %d. Expected card: %d, Actual card %d\n", i, j, expectedHandCard, actualHandCard);
                result = 0;
            }

            if (expectedDiscardCard != actualDiscardCard) {
                printf("Discard: Player %d Card %d. Expected card: %d, Actual card %d\n", i, j, expectedDiscardCard, actualDiscardCard);
                result = 0;
            }
        }
    }
    return result;
}

int testCounts(struct gameState* expected, struct gameState* actual) {
    int i;
    int result = 1;
    for (i = 0; i < MAX_PLAYERS; i++) {
        int expectedDeckCount = expected->deckCount[i];
        int expectedHandCount = expected->handCount[i];
        int expectedDiscardCount = expected->discardCount[i];

        int actualDeckCount = actual->deckCount[i];
        int actualHandCount = actual->handCount[i];
        int actualDiscardCount = actual->discardCount[i];
        if (expectedDeckCount != actualDeckCount) {
            printf("Deck Count: Player %d. Expected deck count: %d, Actual deck count %d\n", i, expectedDeckCount, actualDeckCount);
            result = 0;
        }
        if (expectedHandCount != actualHandCount) {
            printf ("Hand Count: Player %d. Expected hand count: %d, Actual hand count %d\n", i, expectedHandCount, actualHandCount);
            result = 0;
        }
        if (expectedDiscardCount != actualDiscardCount) {
            printf ("Discard Count: Player %d. Expected Discard count: %d, Actual Discard count %d\n", i, expectedDiscardCount, actualDiscardCount);
            result = 0;
        }
    }
    return result;
}

int testSupplyCount(struct gameState* expected, struct gameState* actual) {
    int i;
    int result = 1;
    for (i = 0; i < SUPPLY_COUNT; i++) {
        int expectedSupply = expected->supplyCount[i];
        int actualSupply = actual->supplyCount[i];
        if (expectedSupply != actualSupply) {
            printf("Supply Count: Card %d, Expected supply %d, Actual supply %d\n", i, expectedSupply, actualSupply);
            result = 0;
        }
    }
    return result;
}

int testCurrentCounts(struct gameState* expected, struct gameState* actual) {
    int result = 1;
    int expectedCoins = expected->coins;
    int expectedActions = expected->numActions;
    int expectedBuys = expected->numBuys;

    int actualCoins = actual->coins;
    int actualActions = actual->numActions;
    int actualBuys = actual->numBuys;

    if (expectedCoins != actualCoins) {
        printf("Coins: Expected coins %d, Actual coins %d\n", expectedCoins, actualCoins);
        result = 0;
    }

    if (expectedActions != actualActions) {
        printf("Actions: Expected Actions %d, Actual Actions %d\n", expectedActions, actualActions);
        result = 0;
    }

    if (expectedBuys != actualBuys) {
        printf("Buys: Expected Buys %d, Actual Buys %d\n", expectedBuys, actualBuys);
        result = 0;
    }
    return result;
}

int testPlayedCards(struct gameState* expected, struct gameState* actual) {
    int i;
    int result = 1;
    for (i = 0; i < MAX_DECK; i++) {
        int expectedCard = expected->playedCards[i];
        int actualCard = actual->playedCards[i];
        if (expectedCard != actualCard) {
            printf("Played Cards: Expected card %d, Actual card %d\n", expectedCard, actualCard);
            result = 0;
        }
    }
    int expectedPlayedCardCount = expected->playedCardCount;
    int actualPlayedCardCount = actual->playedCardCount;
    if (expectedPlayedCardCount != actualPlayedCardCount) {
        printf("Played Card Count: Expected count %d, Actual count %d\n", expectedPlayedCardCount, actualPlayedCardCount);
        result = 0;
    }
    return result;
}

int assertEquals(struct gameState* expected, struct gameState* actual) {
    if (testCards(expected, actual) == 1 && 
        testCounts(expected, actual) == 1 &&
        testSupplyCount(expected, actual) == 1 &&
        testCurrentCounts(expected, actual) == 1 &&
        testPlayedCards(expected, actual) == 1)
        return 1;

    return 0;
}