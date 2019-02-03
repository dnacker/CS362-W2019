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
#include <assert.h>

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

void testDrawNextCardFromDeck(struct gameState* gameState) {
    struct gameState pre;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int nextCardIndex = gameState->deckCount[currentPlayer] - 1;
    int nextCard = gameState->deck[currentPlayer][nextCardIndex];
    drawCard(currentPlayer, gameState);
    int currentCardIndex = gameState->handCount[currentPlayer] - 1;
    int drawnCard = gameState->hand[currentPlayer][currentCardIndex];
    memcpy(gameState, &pre, sizeof(struct gameState));
    assert(nextCard == drawnCard);
}

void testDrawIncrementsHand(struct gameState* gameState) {
    struct gameState pre;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int preHandCount = gameState->handCount[currentPlayer];
    drawCard(currentPlayer, gameState);
    int postHandCount = gameState->handCount[currentPlayer];
    memcpy(gameState, &pre, sizeof(struct gameState));
    assert(postHandCount == preHandCount + 1);
}

void testDrawDecrementsDeck(struct gameState* gameState) {
    struct gameState pre;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int preDeckCount = gameState->deckCount[currentPlayer];
    drawCard(currentPlayer, gameState);
    int postDeckCount = gameState->deckCount[currentPlayer];
    memcpy(gameState, &pre, sizeof(struct gameState));
    assert(postDeckCount == preDeckCount - 1);
}

void testDrawShufflesEmptyDeck(struct gameState* gameState) {
    struct gameState pre;
    memcpy(&pre, gameState, sizeof(struct gameState));
    int currentPlayer = gameState->whoseTurn;
    int preDiscardCount = gameState->discardCount[currentPlayer];
    drawCard(currentPlayer, gameState);
    int postDeckCount = gameState->deckCount[currentPlayer];
    int postDiscardCount = gameState->discardCount[currentPlayer];
    memcpy(gameState, &pre, sizeof(struct gameState));
    assert(postDeckCount == preDiscardCount - 1);
    assert(postDiscardCount == 0);
}

void testDrawAllCards(struct gameState* gameState) {
    int i;
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
    assert(postHandCount == preHandCount + preDeckCount + preDiscardCount);
    assert(postDeckCount == 0);
    assert(postDiscardCount == 0);
}

int main(int argc, char** argv) {
    struct gameState gameState;
    memset(&gameState, 0, sizeof(struct gameState));
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
    initializeGame(1, cards, 1, &gameState);

    fflush(stdout);
    setupDeckWithOneCard(&gameState);
    testDrawIncrementsHand(&gameState);
    testDrawDecrementsDeck(&gameState);
    testDrawNextCardFromDeck(&gameState);
    testDrawAllCards(&gameState);

    fflush(stdout);
    setupDeckWithTenCards(&gameState);
    testDrawIncrementsHand(&gameState);
    testDrawDecrementsDeck(&gameState);
    testDrawNextCardFromDeck(&gameState);
    testDrawAllCards(&gameState);

    fflush(stdout);
    setupDeckWithNoCards(&gameState);
    testDrawIncrementsHand(&gameState);
    testDrawShufflesEmptyDeck(&gameState);
    testDrawAllCards(&gameState);

    return 0;
}