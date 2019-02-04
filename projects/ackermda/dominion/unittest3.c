/* -----------------------------------------------------------------------
 * Name: David Ackerman
 * CS 362
 * Professor Roberts
 * Assignment 3 - Unit Tests
 * February 10, 2019
 * 
 * unittest3.c
 * 
 * Tests the scoreFor function.
 * 
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

void initializeState(struct gameState* state, int victoryCards[], int size) {
    int i;
    memset(state, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, great_hall, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, state);
    for (i = 0; i < treasure_map + 1; i++) {
        state->supplyCount[i] = 100;
    }
}

void resetPlayer(struct gameState* state) {
    int currentPlayer = state->whoseTurn;
    state->deckCount[currentPlayer] = 0;
    state->handCount[currentPlayer] = 0;
    state->discardCount[currentPlayer] = 0;
}

void testCardValueInDeck(struct gameState* state, int vals[], int card) {
    printf("Testing card %d\n", card); fflush(stdout);
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    assert(gainCard(card, state, 1, currentPlayer) == 0);
    int actualScore = scoreFor(currentPlayer, state);
    printf("ActualScore: %d, ExpectedScore: %d\n", actualScore, vals[card]); fflush(stdout);
    assert(actualScore == vals[card]);
}

void testCardValueInHand(struct gameState* state, int vals[], int card) {
    printf("Testing card %d\n", card); fflush(stdout);
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    gainCard(card, state, 2, currentPlayer);
    int actualScore = scoreFor(currentPlayer, state);
    printf("ActualScore: %d, ExpectedScore: %d\n", actualScore, vals[card]); fflush(stdout);
    assert(actualScore == vals[card]);
}

void testCardValueInDiscard(struct gameState* state, int vals[], int card) {
    printf("Testing card %d\n", card); fflush(stdout);
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    gainCard(card, state, 0, currentPlayer);
    int actualScore = scoreFor(currentPlayer, state);
    printf("ActualScore: %d, ExpectedScore: %d\n", actualScore, vals[card]); fflush(stdout);
    assert(actualScore == vals[card]);
}

void testCardValueInAllThree(struct gameState* state, int vals[], int card) {
    printf("Testing card %d\n", card); fflush(stdout);
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    gainCard(card, state, 0, currentPlayer);
    gainCard(card, state, 1, currentPlayer);
    gainCard(card, state, 2, currentPlayer);
    int actualScore = scoreFor(currentPlayer, state);
    printf("ActualScore: %d, ExpectedScore: %d\n", actualScore, 3*vals[card]); fflush(stdout);
    assert(actualScore == 3*vals[card]);
}

void testCardValueOneOfEach(struct gameState* state, int vals[]) {
    printf("Testing one of each"); fflush(stdout);
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    gainCard(curse, state, 0, currentPlayer);
    gainCard(estate, state, 0, currentPlayer);
    gainCard(duchy, state, 0, currentPlayer);
    gainCard(province, state, 0, currentPlayer);
    gainCard(great_hall, state, 0, currentPlayer);
    int actualScore = scoreFor(currentPlayer, state);
    int expectedScore = vals[curse] + vals[estate] + vals[duchy] + vals[province] + vals[great_hall];
    printf("ActualScore: %d, ExpectedScore: %d\n", actualScore, expectedScore); fflush(stdout);
    assert(actualScore == expectedScore);
}

void testGardenWorthOnePointForEveryTenCards(struct gameState* state) {
    int i, j;
    resetPlayer(state);
    int currentPlayer = state->whoseTurn;
    for (i = 1; i <= 19; i++) {
        state->deckCount[currentPlayer] = 0;
        state->handCount[currentPlayer] = 0;
        state->discardCount[currentPlayer] = 0;
        for (j = 0; j < i; j++) {
            gainCard(copper, state, 0, currentPlayer);
        }
        gainCard(gardens, state, 0, currentPlayer);
        int actualScore = scoreFor(currentPlayer, state);
        int expectedScore = i / 10;
        assert(actualScore == expectedScore);
    }
}

int main(int argc, char** argv) {
    int i;
    struct gameState state;
    int vals[treasure_map + 1];
    vals[curse] = -1;
    vals[estate] = 1;
    vals[duchy] = 3;
    vals[province] = 6;
    vals[great_hall] = 1;
    int victoryCards[] = {curse, estate, duchy, province, great_hall};
    initializeState(&state, victoryCards, 5);

    for (i = 0; i < 5; i++) {
        testCardValueInDeck(&state, vals, victoryCards[i]);
        testCardValueInHand(&state, vals, victoryCards[i]);
        testCardValueInDiscard(&state, vals, victoryCards[i]);
        testCardValueInAllThree(&state, vals, victoryCards[i]);
    }
    testCardValueOneOfEach(&state, vals);
    testGardenWorthOnePointForEveryTenCards(&state);

    return 0;
}