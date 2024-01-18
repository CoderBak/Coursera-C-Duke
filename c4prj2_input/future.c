#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "future.h"

void add_future_card(future_cards_t *fc, size_t index, card_t *ptr) {
    // Resize to (index + 1) size
    if (fc->n_decks <= index) {
        size_t origin = fc->n_decks;
        fc->n_decks = index + 1;
        fc->decks = realloc(fc->decks, fc->n_decks * sizeof(deck_t));
        for(size_t i = origin; i < fc->n_decks; i ++) {
            fc->decks[i].n_cards = 0;
            fc->decks[i].cards = NULL;
        }
    }
    fc->decks[index].n_cards ++;
    fc->decks[index].cards = realloc(fc->decks[index].cards, fc->decks[index].n_cards * sizeof(card_t));
    fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t *deck, future_cards_t *fc) {
    size_t cnt = fc->n_decks;
    for(size_t i = 0; i < cnt; i ++) {
        card_t * cur = deck->cards[i];
        for(size_t j = 0; j < fc->decks[i].n_cards; j ++) {
            fc->decks[i].cards[j]->suit = cur->suit;
            fc->decks[i].cards[j]->value = cur->value;
        }
    }
}