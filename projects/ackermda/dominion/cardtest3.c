/* -----------------------------------------------------------------------
 * Name: David Ackerman
 * CS 362
 * Professor Roberts
 * Assignment 3 - Unit Tests
 * February 10, 2019
 * 
 * cardtest3.c
 * 
 * Tests the Council Room Card:
 * - draws 4 cards
 * - increments player's buy
 * - draws a card for each other player
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "testAssert.h"

void testCouncilRoomDrawsFourCards(struct gameState* state) {
    int i;
    int currentPlayer = state->whoseTurn;
    for (i = 0; i < state->numPlayers; i++) {
        state->deckCount[i] = 0;
        gainCard(duchy, state, 1, i);
        gainCard(silver, state, 1, i);
        gainCard(estate, state, 1, i);
        gainCard(gold, state, 1, i);
    }
    int expectedCard1 = gold;
    int expectedCard2 = estate;
    int expectedCard3 = silver;
    int expectedCard4 = duchy;
    int expectedHandCount = state->handCount[currentPlayer] + 4;
    int expectedDeckCount = state->deckCount[currentPlayer] - 4;
    cardEffect(council_room, 0, 0, 0, state, 0, 0);
    int lastHandIndex = state->handCount[currentPlayer] - 1;
    int actualCard1 = state->hand[currentPlayer][lastHandIndex - 3];
    int actualCard2 = state->hand[currentPlayer][lastHandIndex - 2];
    int actualCard3 = state->hand[currentPlayer][lastHandIndex - 1];
    int actualCard4 = state->hand[currentPlayer][lastHandIndex];
    int actualHandCount = state->handCount[currentPlayer];
    int actualDeckCount = state->deckCount[currentPlayer];

    assertTrue(actualCard1, expectedCard1, "Council Room First Card Drawn");
    assertTrue(actualCard2, expectedCard2, "Council Room Second Card Drawn");
    assertTrue(actualCard3, expectedCard3, "Council Room Third Card Drawn");
    assertTrue(actualCard4, expectedCard4, "Council Room Fourth Card Drawn");
    assertTrue(actualHandCount, expectedHandCount, "Council Room Hand Size Increases by 4");
    assertTrue(actualDeckCount, expectedDeckCount, "Council Room Deck Size Decreases by 4");
}

void testCouncilRoomIncrementsBuy(struct gameState* state) {
    int i;
    for (i = 0; i < state->numPlayers; i++) {
        state->deckCount[i] = 0;
        gainCard(duchy, state, 1, i);
        gainCard(silver, state, 1, i);
        gainCard(estate, state, 1, i);
        gainCard(gold, state, 1, i);
    }
    int expectedBuys = state->numBuys + 1;
    cardEffect(council_room, 0, 0, 0, state, 0, 0);
    int actualBuys = state->numBuys;
    assertTrue(actualBuys, expectedBuys, "Council Room Buys Increments");
}

void testCouncilRoomDrawsOtherPlayersCards(struct gameState* state) {
    int i, actualHandSize, actualDeckSize, actualCard;
    for (i = 0; i < state->numPlayers; i++) {
        state->deckCount[i] = 0;
        gainCard(duchy, state, 1, i);
        gainCard(silver, state, 1, i);
        gainCard(estate, state, 1, i);
        gainCard(gold, state, 1, i);
    }
    int currentPlayer = state->whoseTurn;
    int expectedHandSize = state->handCount[currentPlayer] + 1;
    int expectedDeckSize = state->deckCount[currentPlayer] - 1;
    int expectedCard = gold;
    cardEffect(council_room, 0, 0, 0, state, 0, 0);

    for (i = 0; i < state->numPlayers; i++) {
        if (i != currentPlayer) {
            actualHandSize = state->handCount[i];
            actualDeckSize = state->deckCount[i];
            actualCard = state->hand[i][actualHandSize - 1];
            assertTrue(actualHandSize, expectedHandSize, "Council Room Hand Size Increases by 1");
            assertTrue(actualDeckSize, expectedDeckSize, "Council Room Deck Size Decrements by 1");
            assertTrue(actualCard, expectedCard, "Council Room Card Drawn");
        }
    }
}

int main(int argc, char** argv) {
    struct gameState state;
    memset(&state, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(4, cards, 1, &state);

    testCouncilRoomDrawsFourCards(&state);
    testCouncilRoomIncrementsBuy(&state);
    testCouncilRoomDrawsOtherPlayersCards(&state);
    return 0;
}