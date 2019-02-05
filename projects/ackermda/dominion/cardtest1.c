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
    int i;
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    for (i = 0; i < 10; i++) {
        gainCard(copper, state, 1, currentPlayer);
    }
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
    int topDeckIndex = state->deckCount[currentPlayer] - 1;
    int topHandIndex = state->handCount[currentPlayer] - 1;
    int expectedCard1 = state->deck[topDeckIndex];
    int expectedCard2 = state->deck[topDeckIndex - 1];
    int expectedCard3 = state->deck[topDeckIndex - 2];
    cardEffect(smithy, 0, 0, 0, state, 0, 0);
    int actualCard1 = state->hand[topHandIndex + 1];
    int actualCard2 = state->hand[topHandIndex + 2];
    int actualCard3 = state->hand[topHandIndex + 3];
    assertTrue(actualCard1, expectedCard1, "First Card From Deck is First Card Drawn");
    assertTrue(actualCard2, expectedCard3, "Second Card From Deck is Second Card Drawn");
    assertTrue(actualCard3, expectedCard2, "Third Card From Deck is Third Card Drawn");
}

int main(int argc, char** argv) {
    int i;
    struct gameState gameState;
    memset(&gameState, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &gameState);

    testSmithyHandCountIncrements(&state);
    testSmithyDeckCountDecrements(&state);
    testSmithyDrawsCardsFromDeck(&state);

    return 0;
}