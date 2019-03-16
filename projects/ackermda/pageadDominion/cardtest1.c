/* -----------------------------------------------------------------------
 * Name: David Ackerman
 * CS 362
 * Professor Roberts
 * Assignment 3 - Unit Tests
 * February 10, 2019
 * 
 * cardtest1.c
 * 
 * Tests the Smithy Card:
 * - hand count increments by 3
 * - deck count decrements by 3
 * - top three cards are drawn from deck
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "testAssert.h"

void resetPlayer(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    state->supplyCount[copper] = 100;
    state->supplyCount[silver] = 100;
    state->supplyCount[gold] = 100;
    state->supplyCount[smithy] = 1;
    gainCard(copper, state, 1, currentPlayer);
    gainCard(silver, state, 1, currentPlayer);
    gainCard(gold, state, 1, currentPlayer);
    gainCard(smithy, state, 2, currentPlayer);
}

int testSmithyHandCountIncrements(struct gameState* state) {
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    int preHandCount = state->handCount[currentPlayer];
    cardEffect(smithy, 0, 0, 0, state, 0, 0);
    int actualHandCount = state->handCount[currentPlayer];
    int expectedHandCount = preHandCount + 2;
    return assertTrue(actualHandCount, expectedHandCount, "smithy: Increments Hand Count");
}

int testSmithyDeckCountDecrements(struct gameState* state) {
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    int preDeckCount = state->deckCount[currentPlayer];
    cardEffect(smithy, 0, 0, 0, state, 0, 0);
    int actualDeckCount = state->deckCount[currentPlayer];
    int expectedDeckCount = preDeckCount - 3;
    return assertTrue(actualDeckCount, expectedDeckCount, "smithy: Decrements Deck Count");
}

int testSmithyDrawsCardsFromDeck(struct gameState* state) {
    resetPlayer(state);
    int pass = 0;
    int currentPlayer = state->whoseTurn;
    int expectedCard1 = gold;
    int expectedCard2 = silver;
    int expectedCard3 = copper;
    cardEffect(smithy, 0, 0, 0, state, 0, 0);
    int topHandIndex = state->handCount[currentPlayer] - 1;
    int actualCard1 = state->hand[currentPlayer][topHandIndex - 2];
    int actualCard2 = state->hand[currentPlayer][topHandIndex - 1];
    int actualCard3 = state->hand[currentPlayer][topHandIndex];
    pass += assertTrue(actualCard1, expectedCard1, "smithy: First Card From Deck is First Card Drawn");
    pass += assertTrue(actualCard2, expectedCard2, "smithy: Second Card From Deck is Second Card Drawn");
    pass += assertTrue(actualCard3, expectedCard3, "smithy: Third Card From Deck is Third Card Drawn");
    return pass > 0 ? 1 : 0;
}

int main(int argc, char** argv) {
    int total = 3;
    int failed = 0;
    struct gameState state;
    memset(&state, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &state);
    printf("Testing smithy\n");

    failed += testSmithyHandCountIncrements(&state);
    failed += testSmithyDeckCountDecrements(&state);
    failed += testSmithyDrawsCardsFromDeck(&state);
    printf("Passed %d out of %d Tests\n\n", total - failed, total);
    return 0;
}