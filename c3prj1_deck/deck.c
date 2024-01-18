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

void add_card_to(deck_t * deck, card_t c) {
    deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(card_t*));
    deck->cards[deck->n_cards] = malloc(sizeof(card_t));
    deck->cards[deck->n_cards]->suit = c.suit;
    deck->cards[deck->n_cards]->value = c.value;
    deck->n_cards ++;
}

card_t * add_empty_card(deck_t * deck) {
    card_t * empty_card = malloc(sizeof(card_t));
    empty_card->suit = 0;
    empty_card->value = 0;
    add_card_to(deck, *empty_card);
    free(empty_card);
    return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
    deck_t * deck = malloc(sizeof(deck_t));
    deck->n_cards = 0;
    deck->cards = NULL;
    for(int i = 0; i < 52; i ++) {
        card_t cur = card_from_num(i);
        if (!deck_contains(excluded_cards, cur)) {
            add_card_to(deck, cur);
        }
    }
    return deck;
}

void free_deck(deck_t * deck) {
    for(int i = 0; i < deck->n_cards; i ++) {
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
    deck_t * tmp = malloc(sizeof(deck_t));
    tmp->n_cards = 0;
    tmp->cards = NULL;
    for(size_t i = 0; i < n_hands; i ++) {
        for(size_t j = 0; j < hands[i]->n_cards; j ++) {
            card_t cur = *hands[i]->cards[j];
            if (suit_letter(cur) != ' ') {
                add_card_to(tmp, cur);
            }
        }
    }
    deck_t * newDeck = make_deck_exclude(tmp);
    free_deck(tmp);
    return newDeck;
}