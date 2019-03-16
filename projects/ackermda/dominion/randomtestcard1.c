#include "dominion_helpers.h"
#include "assertEquals.h"
#include "random.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

int checkCouncilRoom(struct gameState* post) {
    int i;
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    int currentPlayer = whoseTurn(post);
    
    SelectStream(1);
    for ( i = 0; i < 4; i++) {
        drawCard(currentPlayer, &pre);
    }
    for (i = 0; i < pre.numPlayers; i++) {
        if (i != currentPlayer) {
            drawCard(i, &pre);
        }
    }
    pre.numBuys++;

    SelectStream(1);
    cardEffect(council_room, 0, 0, 0, post, 0, NULL);
    return assertEquals(&pre, post);
}

int main() {
    struct gameState g;
    int i;
    
    for (i = 0; i < 2000; i++) {
        generateRandomGameState(&g);
        checkCouncilRoom(&g);
    }

    return 0;
}