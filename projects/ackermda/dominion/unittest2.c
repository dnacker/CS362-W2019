/* -----------------------------------------------------------------------
 * Name: David Ackerman
 * CS 362
 * Professor Roberts
 * Assignment 3 - Unit Tests
 * February 10, 2019
 * 
 * unittest2.c
 * 
 * Tests the buyCard function.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

void initializeState(struct gameState* state, int numSupply, int coins, int buys) {
    int i;
    for (i = 0; i < treasure_map + 1; i++) {
        state->supplyCount[i] = numSupply;
    }
    state->coins = coins;
    state->numBuys = buys;
}

void testBuyCardIsGained(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int currentPlayer = state->whoseTurn;
    int preDiscardCount = state->discardCount[currentPlayer];
    int result = buyCard(card, state);
    int lastDiscardIndex = state->discardCount - 1;
    int cardGained = state->discard[currentPlayer][lastDiscardIndex];
    assert(result == 0);
    assert(card == cardGained);
    assert(state->discardCount[currentPlayer] == preDiscardCount + 1);
}

void testBuyCardDecreasesBuy(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preBuys = state->numBuys;
    int result = buyCard(card, state);
    assert(result == 0);
    assert(state->numBuys == preBuys - 1);
}

void testBuyCardDecreasesCoins(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preCoins = state->coins;
    int result = buyCard(card, state);
    assert(result == 0);
    assert(state->coins = preCoins - getCost(card));
}

void testBuyCardDecreasesSupply(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preSupply = state->supplyCount[card];
    int result = buyCard(card, state);
    assert(result == 0);
    assert(state->supplyCount[card] == preSupply - 1);
}

void assertBuyCardFails(struct gameState* state, int card) {
    int preSupply = state->supplyCount[card];
    int preBuys = state->numBuys;
    int preCoins = state->coins;
    int result = buyCard(card, state);
    assert(result == -1);
    assert(state->numBuys == preBuys);
    assert(state->coins == preCoins);
    assert(state->supplyCount[card] == preSupply);
}

void testBuyCardFailsNoSupply(struct gameState* state, int card) {
    initializeState(state, 0, 10, 1);
    assertBuyCardFails(state, card);
}

void testBuyCardFailsNotEnoughGold(struct gameState* state, int card) {
    initializeState(state, 1, 0, 1);
    assertBuyCardFails(state, card);
}

void testBuyCardFailsNotEnoughBuys(struct gameState* state, int card) {
    initializeState(state, 1, 10, 0);
    assertBuyCardFails(state, card);
}

int main(int argc, char** argv) {
    int i;
    struct gameState gameState;
    memset(&gameState, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &gameState);

    for (i = 0; i < treasure_map + 1; i++) {
        testBuyCardIsGained(&gameState, i);
        testBuyCardDecreasesBuy(&gameState, i);
        testBuyCardDecreasesCoins(&gameState, i);
        testBuyCardDecreasesSupply(&gameState, i);
        testBuyCardFailsNoSupply(&gameState, i);
        testBuyCardFailsNotEnoughGold(&gameState, i);
        testBuyCardFailsNotEnoughBuys(&gameState, i);
    }

    return 0;
}