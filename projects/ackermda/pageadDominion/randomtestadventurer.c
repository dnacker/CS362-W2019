#include "dominion_helpers.h"
#include "assertEquals.h"
#include "random.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int isTreasure(int card) {
    return card == copper ||
        card == silver ||
        card == gold;
}

int checkAdventurer(struct gameState* post) {
    SelectStream(1);
    int drawnTreasure = 0;
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    int currentPlayer = whoseTurn(post);
    int deckIndex = pre.deckCount[currentPlayer] - 1;
    int tempDeck[MAX_DECK];
    int tempIndex = 0;
    int j;
    while (drawnTreasure < 2) {
        if (deckIndex < 0) {
            for (j = 0; j < pre.discardCount[currentPlayer]; j++) {
                pre.deck[currentPlayer][j] = pre.discard[currentPlayer][j];
            }
            pre.deckCount[currentPlayer] = pre.discardCount[currentPlayer];
            pre.discardCount[currentPlayer] = 0;
            shuffle(currentPlayer, &pre);
            deckIndex = pre.deckCount[currentPlayer] - 1;
        }
        int currentCard = pre.deck[currentPlayer][deckIndex];
        pre.deckCount[currentPlayer]--;
        if (isTreasure(currentCard)) {
            drawnTreasure++;
            pre.hand[currentPlayer][pre.handCount[currentPlayer]++] = currentCard;
        } else {
            tempDeck[tempIndex++] = currentCard;
        }
        deckIndex--;
    }
    while (tempIndex >= 0) {
        pre.discard[currentPlayer][pre.discardCount[currentPlayer]++] = tempDeck[tempIndex--];
    }

    SelectStream(1);
    cardEffect(adventurer, 0, 0, 0, post, 0, 0);
    return assertEquals(&pre, post);
}

int main() {
    struct gameState g;
    int i;
    
    for (i = 0; i < 20000; i++) {
        generateRandomGameState(&g);
        checkAdventurer(&g);
    }

    return 0;
}