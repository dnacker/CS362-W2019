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
#include "testAssert.h"

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
    buyCard(card, state);
    int lastDiscardIndex = state->discardCount[currentPlayer] - 1;
    int cardGained = state->discard[currentPlayer][lastDiscardIndex];
    assertTrue(card, cardGained, "Card Gained");
    assertTrue(state->discardCount[currentPlayer], preDiscardCount + 1, "Discard Size Increments");
}

void testBuyCardDecreasesBuy(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preBuys = state->numBuys;
    buyCard(card, state);
    assertTrue(state->numBuys, preBuys - 1, "Buy decreases");
}

void testBuyCardDecreasesCoins(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preCoins = state->coins;
    buyCard(card, state);
    assertTrue(state->coins, preCoins - getCost(card), "Coins decreases");
}

void testBuyCardDecreasesSupply(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preSupply = state->supplyCount[card];
    buyCard(card, state);
    assertTrue(state->supplyCount[card], preSupply - 1, "Supply decreases");
}

void assertBuyCardFails(struct gameState* state, int card, char* message) {
    int preSupply = state->supplyCount[card];
    int preBuys = state->numBuys;
    int preCoins = state->coins;
    buyCard(card, state);
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, message);
    strcat(buffer, ": Buys are unchanged");
    assertTrue(state->numBuys, preBuys, buffer);
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, message);
    strcat(buffer, ": Coins are unchanged");
    assertTrue(state->coins,  preCoins, buffer);
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, message);
    strcat(buffer, ": Supply is unchanged");
    assertTrue(state->supplyCount[card],  preSupply, buffer);
}

void testBuyCardFailsNoSupply(struct gameState* state, int card) {
    initializeState(state, 0, 10, 1);
    assertBuyCardFails(state, card, "No Supply");
}

void testBuyCardFailsNotEnoughGold(struct gameState* state, int card) {
    initializeState(state, 1, 0, 1);
    assertBuyCardFails(state, card, "No Coins");
}

void testBuyCardFailsNotEnoughBuys(struct gameState* state, int card) {
    initializeState(state, 1, 10, 0);
    assertBuyCardFails(state, card, "No Buys");
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
        testBuyCardFailsNotEnoughBuys(&gameState, i);
        if (getCost(i) > 0) {
            testBuyCardFailsNotEnoughGold(&gameState, i);
        }
    }

    return 0;
}