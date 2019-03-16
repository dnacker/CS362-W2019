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

void resetPlayer(int currentPlayer, struct gameState* state) {
    state->handCount[currentPlayer] = 0;
    state->discardCount[currentPlayer] = 0;
    state->deckCount[currentPlayer] = 0;
    memset(state->hand[currentPlayer], 0, MAX_HAND * sizeof(state->hand[currentPlayer][0]));
    memset(state->deck[currentPlayer], 0, MAX_DECK * sizeof(state->hand[currentPlayer][0]));
    memset(state->discard[currentPlayer], 0, MAX_DECK * sizeof(state->hand[currentPlayer][0]));
    gainCard(adventurer, state, 2, currentPlayer);
}

int assertAdventurerDrawsFirstTwoTreasuresFromDeck(struct gameState* state, char* message) {
    int pass = 0;
    int currentPlayer = state->whoseTurn;
    int expectedCard1 = gold;
    int expectedCard2 = silver;
    cardEffect(adventurer, 0, 0, 0, state, 0, 0);
    int topHandIndex = state->handCount[currentPlayer] - 1;
    int actualCard1 = state->hand[currentPlayer][topHandIndex - 1];
    int actualCard2 = state->hand[currentPlayer][topHandIndex];
    pass += assertTrue(actualCard1, expectedCard1, message);
    pass += assertTrue(actualCard2, expectedCard2, message);
    return pass > 0 ? 1 : 0;
}

int testAdventurerWithTwoTreasuresInDeckWithOtherCards(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    resetPlayer(currentPlayer, state);
    gainCard(duchy, state, 1, currentPlayer);
    gainCard(silver, state, 1, currentPlayer);
    gainCard(estate, state, 1, currentPlayer);
    gainCard(gold, state, 1, currentPlayer);
    return assertAdventurerDrawsFirstTwoTreasuresFromDeck(state, "Adventurer Deck: Gold -> Estate -> Silver -> Duchy");
}

int testAdventurerWithThreeTreasuresInDeck(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    resetPlayer(currentPlayer, state);
    gainCard(copper, state, 1, currentPlayer);
    gainCard(silver, state, 1, currentPlayer);
    gainCard(gold, state, 1, currentPlayer);
    return assertAdventurerDrawsFirstTwoTreasuresFromDeck(state, "Adventurer Deck: Gold -> Silver -> Copper");
}

int testAdventurerWithTreasureInDeckOneInDiscard(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    resetPlayer(currentPlayer, state);
    gainCard(gold, state, 1, currentPlayer);
    gainCard(silver, state, 0, currentPlayer);
    return assertAdventurerDrawsFirstTwoTreasuresFromDeck(state, "Adventurer Deck: Gold, Discard: Silver");
}

int testAdventurerWithOneTreasureInDeck(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    resetPlayer(currentPlayer, state);
    gainCard(gold, state, 1, currentPlayer);
    gainCard(estate, state, 0, currentPlayer);
    int actualCard = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
    int expectedCard = gold;
    return assertTrue(actualCard, expectedCard, "Adventurer Deck: Copper");
}

int main(int argc, char** argv) {
    int total = 4;
    int failed = 0;
    struct gameState state;
    memset(&state, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &state);
    state.supplyCount[duchy] = 100;
    state.supplyCount[estate] = 100;
    state.supplyCount[copper] = 100;
    state.supplyCount[silver] = 100;
    state.supplyCount[gold] = 100;
    printf("Testing adventurer\n");
    failed += testAdventurerWithTwoTreasuresInDeckWithOtherCards(&state);
    failed += testAdventurerWithThreeTreasuresInDeck(&state);
    failed += testAdventurerWithTreasureInDeckOneInDiscard(&state);
    failed += testAdventurerWithOneTreasureInDeck(&state);
    printf("Passed %d out of %d Tests\n\n", total - failed, total);
    return 0;
}