/* -----------------------------------------------------------------------
 * Name: David Ackerman
 * CS 362
 * Professor Roberts
 * Assignment 3 - Unit Tests
 * February 10, 2019
 * 
 * unittest1.c
 * 
 * Tests the drawcard function on various deck conditions.
 * Condition 1: deck has one card in it
 * Condition 2: deck has 10 cards in it
 * Condition 3: deck has 0 cards in it, and discard has 10 cards in it
 *
 * For each condition, we test that the player's hand size changes appropriately,
 * the player's deck size changes appropriately, the next appropriate card is drawn,
 * we can draw all the cards from their deck.
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "testAssert.h"

void setupDeckWithNCards(struct gameState* gameState, int cards[], int numCards) {
    int i;
    int currentPlayer = gameState->whoseTurn;
    for (i = 0; i < numCards; i++) {
        gameState->deck[currentPlayer][i] = cards[i];
    }
    gameState->deckCount[currentPlayer] = numCards;
    gameState->discardCount[currentPlayer] = 0;
}

void putNCardsIntoDiscardFromDeck(struct gameState* gameState, int numCardsToDiscard) {
    int i;
    int currentPlayer = gameState->whoseTurn;
    int nextCardIndex = gameState->deckCount[currentPlayer] - 1;
    for (i = 0; i < numCardsToDiscard; i++) {
        if (nextCardIndex < 0) {
            break;
        }
        gameState->discard[currentPlayer][i] = gameState->deck[currentPlayer][nextCardIndex];
        gameState->deckCount[currentPlayer]--;
        gameState->discardCount[currentPlayer]++;
    }
}

void setupDeckWithOneCard(struct gameState* gameState) {
    int cards[] = {adventurer};
    setupDeckWithNCards(gameState, cards, 1);
}

void setupDeckWithTenCards(struct gameState* gameState) {
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
    setupDeckWithNCards(gameState, cards, 10);
}

void setupDeckWithNoCards(struct gameState* gameState) {
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    setupDeckWithNCards(gameState, cards, 10);
    putNCardsIntoDiscardFromDeck(gameState, 10);
}

int testDrawNextCardFromDeck(struct gameState* gameState) {
    struct gameState pre;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int nextCardIndex = gameState->deckCount[currentPlayer] - 1;
    int nextCard = gameState->deck[currentPlayer][nextCardIndex];
    drawCard(currentPlayer, gameState);
    int currentCardIndex = gameState->handCount[currentPlayer] - 1;
    int drawnCard = gameState->hand[currentPlayer][currentCardIndex];
    memcpy(gameState, &pre, sizeof(struct gameState));
    return assertTrue(nextCard, drawnCard, "drawCard: Draw Next Card");
}

int testDrawIncrementsHand(struct gameState* gameState) {
    struct gameState pre;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int preHandCount = gameState->handCount[currentPlayer];
    drawCard(currentPlayer, gameState);
    int postHandCount = gameState->handCount[currentPlayer];
    memcpy(gameState, &pre, sizeof(struct gameState));
    return assertTrue(postHandCount, preHandCount + 1, "drawCard: Increments Hand Size");
}

int testDrawDecrementsDeck(struct gameState* gameState) {
    struct gameState pre;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int preDeckCount = gameState->deckCount[currentPlayer];
    drawCard(currentPlayer, gameState);
    int postDeckCount = gameState->deckCount[currentPlayer];
    memcpy(gameState, &pre, sizeof(struct gameState));
    return assertTrue(postDeckCount, preDeckCount - 1, "drawCard: Decrements Deck");
}

int testDrawShufflesEmptyDeck(struct gameState* gameState) {
    struct gameState pre;
    int pass = 0;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int preDiscardCount = gameState->discardCount[currentPlayer];
    drawCard(currentPlayer, gameState);
    int postDeckCount = gameState->deckCount[currentPlayer];
    int postDiscardCount = gameState->discardCount[currentPlayer];
    memcpy(gameState, &pre, sizeof(struct gameState));
    pass += assertTrue(postDeckCount, preDiscardCount - 1, "drawCard: Deck Size is 1 less than Pre Discard Size");
    pass += assertTrue(postDiscardCount, 0, "drawCard: Discard Is Empty");
    return pass > 0 ? 1 : 0;
}

int testDrawAllCards(struct gameState* gameState) {
    int i;
    int pass = 0;
    struct gameState pre;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int preHandCount = gameState->handCount[currentPlayer];
    int preDeckCount = gameState->deckCount[currentPlayer];
    int preDiscardCount = gameState->discardCount[currentPlayer];
    for (i = 0; i < preDeckCount + preDiscardCount; i++) {
        drawCard(currentPlayer, gameState);
    }
    int postHandCount = gameState->handCount[currentPlayer];
    int postDeckCount = gameState->deckCount[currentPlayer];
    int postDiscardCount = gameState->discardCount[currentPlayer];
    memcpy(gameState, &pre, sizeof(struct gameState));
    pass += assertTrue(postHandCount, preHandCount + preDeckCount + preDiscardCount, "drawCard: Hand Size is Sum of all Cards");
    pass += assertTrue(postDeckCount, 0, "drawCard: Deck Size is 0");
    pass += assertTrue(postDiscardCount, 0, "drawCard: Discard Size is 0");
    return pass > 0 ? 1 : 0;
}

int main(int argc, char** argv) {
    struct gameState gameState;
    int total = 0;
    int failed = 0;
    memset(&gameState, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &gameState);
    printf("Testing drawCard\n");

    setupDeckWithOneCard(&gameState);
    failed += testDrawIncrementsHand(&gameState);
    failed += testDrawDecrementsDeck(&gameState);
    failed += testDrawNextCardFromDeck(&gameState);
    failed += testDrawAllCards(&gameState);
    total += 4;

    setupDeckWithTenCards(&gameState);
    failed += testDrawIncrementsHand(&gameState);
    failed += testDrawDecrementsDeck(&gameState);
    failed += testDrawNextCardFromDeck(&gameState);
    failed += testDrawAllCards(&gameState);
    total += 4;

    setupDeckWithNoCards(&gameState);
    failed += testDrawIncrementsHand(&gameState);
    failed += testDrawShufflesEmptyDeck(&gameState);
    failed += testDrawAllCards(&gameState);
    total += 3;

    printf("Passed %d out of %d Tests\n\n", total - failed, total);

    return 0;
}