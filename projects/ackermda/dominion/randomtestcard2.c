#include "dominion_helpers.h"
#include "assertEquals.h"
#include "random.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int checkVillage(struct gameState* post) {
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    int currentPlayer = whoseTurn(post);
    
    SelectStream(1);
    pre.hand[currentPlayer][pre.handCount[currentPlayer]++] = pre.deck[currentPlayer][--pre.deckCount[currentPlayer]];
    pre.numActions += 2;
    SelectStream(1);
    cardEffect(village, 0, 0, 0, post, 0, 0);

    return assertEquals(&pre, post);
}

int main() {
    struct gameState g;
    int i;
    
    for (i = 0; i < 2000; i++) {
        generateRandomGameState(&g);
        checkVillage(&g);
    }

    return 0;
}