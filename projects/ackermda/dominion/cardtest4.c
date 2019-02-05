/* -----------------------------------------------------------------------
 * Name: David Ackerman
 * CS 362
 * Professor Roberts
 * Assignment 3 - Unit Tests
 * February 10, 2019
 * 
 * cardtest4.c
 * 
 * Tests the Village Card:
 * - draws a card
 * - increments player's actions by
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "testAssert.h"

void testVillageDrawsCard(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    gainCard(estate, state, 1, currentPlayer);
    int expectedCard = estate;
    int expectedHandCount = state->handCount[currentPlayer] + 1;
    int expectedDeckCount = state->deckCount[currentPlayer] - 1;
    cardEffect(village, 0, 0, 0, state, 0, 0);
    int actualCard = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
    int actualHandCount = state->handCount[currentPlayer];
    int actualDeckCount = state->deckCount[currentPlayer] - 1;

    assertTrue(actualCard, expectedCard, "Village Draws Correct Card");
    assertTrue(actualHandCount, expectedHandCount, "Village Hand Count Increments");
    assertTrue(actualDeckCount, expectedDeckCount, "Village Deck Count Decrements");
}

void testVillageIncrementsPlayersActions(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    gainCard(estate, state, 1, currentPlayer);
    int expectedActions = state->numActions + 2;
    cardEffect(village, 0, 0, 0, state, 0, 0);
    int actualActions = state->numActions;
    assertTrue(actualActions, expectedActions, "Village Actions Increments by 2");
}

int main(int argc, char** argv) {
    struct gameState state;
    memset(&state, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &state);

    testVillageDrawsCard(&state);
    testVillageIncrementsPlayersActions(&state);
    return 0;
}