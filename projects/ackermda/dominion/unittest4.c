/* -----------------------------------------------------------------------
 * Name: David Ackerman
 * CS 362
 * Professor Roberts
 * Assignment 3 - Unit Tests
 * February 10, 2019
 * 
 * unittest4.c
 * 
 * Tests the isGameOver function.
 * 
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "testAssert.h"

void resetSupplyCounts(struct gameState* state) {
    int i;
    for (i = 0; i < treasure_map + 1; i++) {
        state->supplyCount[i] = 100;
    }
}

void initializeState(struct gameState* state) {
    memset(state, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, great_hall, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, state);
    resetSupplyCounts(state);
}

int testGameOverWhenProvinceSupplyEmpty(struct gameState* state) {
    resetSupplyCounts(state);
    state->supplyCount[province] = 0;
    int actual = isGameOver(state);
    int expected = 1;
    return assertTrue(actual, expected, "isGameOver: Province Supply 0");
}

int testGameOverWhenThreeSupplyEmpty(struct gameState* state) {
    resetSupplyCounts(state);
    state->supplyCount[estate] = 0;
    state->supplyCount[smithy] = 0;
    state->supplyCount[gardens] = 0;
    int actual = isGameOver(state);
    int expected = 1;
    return assertTrue(actual, expected, "isGameOver: Three Supply 0");
}

int testGameNotOverWhenTwoPilesEmpty(struct gameState* state) {
    resetSupplyCounts(state);
    state->supplyCount[estate] = 0;
    state->supplyCount[smithy] = 0;
    int actual = isGameOver(state);
    int expected = 0;
    return assertTrue(actual, expected, "isGameOver: Two Supply 0");
}

int testGameNotOverWhenOnePileEmpty(struct gameState* state) {
    resetSupplyCounts(state);
    state->supplyCount[estate] = 0;
    int actual = isGameOver(state);
    int expected = 0;
    return assertTrue(actual, expected, "isGameOver: One Supply 0");
}

int testGameNotOverWhenNoPilesEmpty(struct gameState* state) {
    resetSupplyCounts(state);
    int actual = isGameOver(state);
    int expected = 0;
    return assertTrue(actual, expected, "isGameOver: No Supply Empty");
}

int main(int argc, char** argv) {
    int total = 0;
    int failed = 0;
    struct gameState state;
    initializeState(&state);
    printf("Testing isGameOver\n");
    failed += testGameOverWhenThreeSupplyEmpty(&state);
    failed += testGameOverWhenProvinceSupplyEmpty(&state);
    failed += testGameNotOverWhenTwoPilesEmpty(&state);
    failed += testGameNotOverWhenOnePileEmpty(&state);
    failed += testGameNotOverWhenNoPilesEmpty(&state);

    total += 5;
    printf("Passed %d out of %d Tests\n\n", total - failed, total);
    return 0;
}