/* -----------------------------------------------------------------------
 * Name: David Ackerman
 * CS 362
 * Professor Roberts
 * Assignment 3 - Unit Tests
 * February 10, 2019
 * 
 * cardtest2.c
 * 
 * Tests the Adventurer Card:
 * - draws first two treasure cards from deck (only two treasures exist)
 * - draws first two treasure cards for deck (multiple treasures)
 * - draws two treasure cards from deck and discard
 * - draws one treasure card if only one exists after a shuffle
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "testAssert.h"

void assertAdventurerDrawsFirstTwoTreasuresFromDeck(struct gameState* state, char* message) {
    int currentPlayer = state->whoseTurn;
    int expectedCard1 = gold;
    int expectedCard2 = silver;
    cardEffect(adventurer, 0, 0, 0, state, 0, 0);
    int topHandIndex = state->handCount[currentPlayer] - 1;
    int actualCard1 = state->hand[currentPlayer][topHandIndex - 1];
    int actualCard2 = state->hand[currentPlayer][topHandIndex];
    assertTrue(actualCard1, expectedCard1, message);
    assertTrue(actualCard2, expectedCard2, message);
}

void testAdventurerWithTwoTreasuresInDeckWithOtherCards(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    gainCard(duchy, state, 1, currentPlayer);
    gainCard(silver, state, 1, currentPlayer);
    gainCard(estate, state, 1, currentPlayer);
    gainCard(gold, state, 1, currentPlayer);
    assertAdventurerDrawsFirstTwoTreasuresFromDeck(state, "Adventurer Deck: Gold -> Estate -> Silver -> Duchy");
}

void testAdventurerWithThreeTreasuresInDeck(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    gainCard(copper, state, 1, currentPlayer);
    gainCard(silver, state, 1, currentPlayer);
    gainCard(gold, state, 1, currentPlayer);
    assertAdventurerDrawsFirstTwoTreasuresFromDeck(state, "Adventurer Deck: Gold -> Silver -> Copper");
}

void testAdventurerWithTreasureInDeckOneInDiscard(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    gainCard(gold, state, 1, currentPlayer);
    gainCard(silver, state, 0, currentPlayer);
    assertAdventurerDrawsFirstTwoTreasuresFromDeck(state, "Adventurer Deck: Gold, Discard: Silver");
}

void testAdventurerWithOneTreasureInDeck(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    gainCard(gold, state, 1, currentPlayer);
    gainCard(estate, state, 0, currentPlayer);
    int actualCard = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
    int expectedCard = gold;
    assertTrue(actualCard, expectedCard, "Adventurer Deck: Copper");
}

int main(int argc, char** argv) {
    struct gameState state;
    memset(&state, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &state);

    testAdventurerWithTwoTreasuresInDeckWithOtherCards(&state);
    testAdventurerWithThreeTreasuresInDeck(&state);
    testAdventurerWithTreasureInDeckOneInDiscard(&state);
    testAdventurerWithOneTreasureInDeck(&state);

    return 0;
}