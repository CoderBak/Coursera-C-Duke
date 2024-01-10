#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

int card_equal(card_t x, card_t y) {
    if (x.suit == y.suit && x.value == y.value) {
        return 1;
    }
    return 0;
}

void print_hand(deck_t * hand){
    deck_t cur = *hand;
    for (size_t i = 0; i < cur.n_cards; i ++) {
        print_card(*cur.cards[i]);
        printf(" ");
    }
}

int deck_contains_cnt(deck_t * d, card_t c) {
    deck_t cur = *d;
    int cnt = 0;
    for (size_t i = 0; i < cur.n_cards; i ++) {
        if (card_equal(*cur.cards[i], c)) {
            cnt += 1;
        }
    }
    return cnt;
}

int deck_contains(deck_t * d, card_t c) {
    if (deck_contains_cnt(d, c) == 0) {
        return 0;
    }
    return 1;
}

void shuffle(deck_t * d){
    size_t len = d -> n_cards;
    size_t cnt = 0;
    size_t pos[len + 1];
    card_t newDeck[len + 1];
    for (size_t i = 0; i < len; i ++) {
        pos[i] = -1;
    }
    while (cnt < len) {
        size_t random = rand() % len;
        if (pos[random] == -1) {
            pos[random] = cnt;
            cnt ++;
        }
    }
    for (size_t i = 0; i < len; i ++) {
        newDeck[pos[i]] = *(d -> cards[i]);
    }
    for (size_t i = 0; i < len; i ++) {
        *(d -> cards[i]) = newDeck[i];
    }
}

void assert_full_deck(deck_t * d) {
    deck_t cur = *d;
    for (size_t i = 0; i < cur.n_cards; i ++) {
        assert_card_valid(*cur.cards[i]);
        assert(deck_contains_cnt(d, *cur.cards[i]) == 1);
    }
}
