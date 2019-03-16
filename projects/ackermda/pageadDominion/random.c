#include "random.h"
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_CARDS 27

void generateRandomGameState(struct gameState* state) {
    int i,j;
    srand(time(NULL));
    
    for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*) state)[i] = rand() % 256;
    }
    state->numPlayers = rand() % MAX_PLAYERS + 1;
    state->whoseTurn = rand() % state->numPlayers;
    state->playedCardCount = rand() % MAX_DECK;
    for (j = 0; j < state->playedCardCount; j++) {
        state->playedCards[j] = rand() % NUM_CARDS;    
    }

    for (i = 0; i < state->numPlayers; i++) {
        state->deckCount[i] = rand() % MAX_DECK;
        state->discardCount[i] = rand() % MAX_DECK;
        state->handCount[i] = rand() % MAX_HAND;

        for (j = 0; j < state->deckCount[i]; j++) {
            state->deck[i][j] = rand() % NUM_CARDS;    
        }

        for (j = 0; j < state->discardCount[i]; j++) {
            state->discard[i][j] = rand() % NUM_CARDS;    
        }

        for (j = 0; j < state->handCount[i]; j++) {
            state->hand[i][j] = rand() % NUM_CARDS;    
        }
    }
}