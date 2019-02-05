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
    gainCard(copper, state, 1, currentPlayer);
    gainCard(silver, state, 1, currentPlayer);
    gainCard(gold, state, 1, currentPlayer);
}

void testSmithyHandCountIncrements(struct gameState* state) {
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    int preHandCount = state->handCount[currentPlayer];
    cardEffect(smithy, 0, 0, 0, state, 0, 0);
    int actualHandCount = state->handCount[currentPlayer];
    int expectedHandCount = preHandCount + 3;
    assertTrue(actualHandCount, expectedHandCount, "Smithy Increments Hand Count");
}

void testSmithyDeckCountDecrements(struct gameState* state) {
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    int preDeckCount = state->deckCount[currentPlayer];
    cardEffect(smithy, 0, 0, 0, state, 0, 0);
    int actualDeckCount = state->deckCount[currentPlayer];
    int expectedDeckCount = preDeckCount - 3;
    assertTrue(actualDeckCount, expectedDeckCount, "Smithy Decrements Deck Count");
}

void testSmithyDrawsCardsFromDeck(struct gameState* state) {
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    int topHandIndex = state->handCount[currentPlayer] - 1;
    int expectedCard1 = gold;
    int expectedCard2 = silver;
    int expectedCard3 = copper;
    cardEffect(smithy, 0, 0, 0, state, 0, 0);
    int actualCard1 = state->hand[currentPlayer][topHandIndex + 1];
    int actualCard2 = state->hand[currentPlayer][topHandIndex + 2];
    int actualCard3 = state->hand[currentPlayer][topHandIndex + 3];
    assertTrue(actualCard1, expectedCard1, "Smithy First Card From Deck is First Card Drawn");
    assertTrue(actualCard2, expectedCard3, "Smithy Second Card From Deck is Second Card Drawn");
    assertTrue(actualCard3, expectedCard2, "Smithy Third Card From Deck is Third Card Drawn");
}

int main(int argc, char** argv) {
    struct gameState state;
    memset(&state, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &state);

    testSmithyHandCountIncrements(&state);
    testSmithyDeckCountDecrements(&state);
    testSmithyDrawsCardsFromDeck(&state);

    return 0;
}