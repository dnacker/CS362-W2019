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

int testBuyCardIsGained(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int currentPlayer = state->whoseTurn;
    int preDiscardCount = state->discardCount[currentPlayer];
    int pass = 0;
    buyCard(card, state);
    int lastDiscardIndex = state->discardCount[currentPlayer] - 1;
    int cardGained = state->discard[currentPlayer][lastDiscardIndex];
    pass += assertTrue(card, cardGained, "buyCard: Card Gained");
    pass += assertTrue(state->discardCount[currentPlayer], preDiscardCount + 1, "buyCard: Discard Size Increments");
    return pass > 0 ? 1 : 0;
}

int testBuyCardDecreasesBuy(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preBuys = state->numBuys;
    buyCard(card, state);
    return assertTrue(state->numBuys, preBuys - 1, "buyCard: Buy decreases");
}

int testBuyCardDecreasesCoins(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preCoins = state->coins;
    buyCard(card, state);
    return assertTrue(state->coins, preCoins - getCost(card), "buyCard: Coins decreases");
}

int testBuyCardDecreasesSupply(struct gameState* state, int card) {
    initializeState(state, 1, 10, 1);
    int preSupply = state->supplyCount[card];
    buyCard(card, state);
    return assertTrue(state->supplyCount[card], preSupply - 1, "buyCard: Supply decreases");
}

int assertBuyCardFails(struct gameState* state, int card, char* message) {
    int preSupply = state->supplyCount[card];
    int preBuys = state->numBuys;
    int preCoins = state->coins;
    int pass = 0;
    buyCard(card, state);
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, message);
    strcat(buffer, ": Buys are unchanged");
    pass += assertTrue(state->numBuys, preBuys, buffer);
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, message);
    strcat(buffer, ": Coins are unchanged");
    pass += assertTrue(state->coins,  preCoins, buffer);
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, message);
    strcat(buffer, ": Supply is unchanged");
    pass += assertTrue(state->supplyCount[card],  preSupply, buffer);
    return pass > 0 ? 1 : 0;
}

int testBuyCardFailsNoSupply(struct gameState* state, int card) {
    initializeState(state, 0, 10, 1);
    return assertBuyCardFails(state, card, "buyCard: No Supply");
}

int testBuyCardFailsNotEnoughGold(struct gameState* state, int card) {
    initializeState(state, 1, 0, 1);
    return assertBuyCardFails(state, card, "buyCard: No Coins");
}

int testBuyCardFailsNotEnoughBuys(struct gameState* state, int card) {
    initializeState(state, 1, 10, 0);
    return assertBuyCardFails(state, card, "buyCard: No Buys");
}

int main(int argc, char** argv) {
    int i;
    int failed = 0;
    int total = 0;
    struct gameState gameState;
    memset(&gameState, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &gameState);
    printf("Testing buyCard\n");
    for (i = 0; i < treasure_map + 1; i++) {
        total += 6;
        failed += testBuyCardIsGained(&gameState, i);
        failed += testBuyCardDecreasesBuy(&gameState, i);
        failed += testBuyCardDecreasesCoins(&gameState, i);
        failed += testBuyCardDecreasesSupply(&gameState, i);
        failed += testBuyCardFailsNoSupply(&gameState, i);
        failed += testBuyCardFailsNotEnoughBuys(&gameState, i);
        if (getCost(i) > 0) {
            failed += testBuyCardFailsNotEnoughGold(&gameState, i);
            total++;
        }
    }
    printf("Passed %d out of %d Tests\n\n", total - failed, total);

    return 0;
}