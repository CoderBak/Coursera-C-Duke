#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "input.h"

void addCard(deck_t * deck, future_cards_t * fc, char value_let, char suit_let, int index) {
    if (value_let != '?') {
        card_t cur = card_from_letters(value_let, suit_let);
        add_card_to(deck, cur);
        return;
    }
    card_t * ptr = add_empty_card(deck);
    add_future_card(fc, index, ptr);
}

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    size_t len = strlen(str);
    int flag = 0;
    deck_t * newDeck = malloc(sizeof(deck_t));
    newDeck->n_cards = 0;
    newDeck->cards = NULL;
    size_t i = 0;
    for(; i < len; i ++) {
        if (str[i] == ' ' || str[i] == '\n') {
            continue;
        }
        if (flag) {
            addCard(newDeck, fc, str[i - 1], str[i], atoi(str + i));
            if (str[i - 1] == '?') {
                for(; i < len - 1; i ++) {
                    if (str[i + 1] == ' ' || str[i + 1] == '\n') {
                        break;
                    }
                }
            }
        }
        flag = 1 - flag;
    }
    if (newDeck->n_cards < 5) {
        return NULL;
    }
    return newDeck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    char * line = NULL;
    size_t len = 0, cnt = 0;
    deck_t ** tmp = NULL;
    while(getline(&line, &len, f) >= 0) {
        tmp = realloc(tmp, (cnt + 1) * sizeof(deck_t*));
        tmp[cnt ++] = hand_from_string(line, fc);
        if (tmp[cnt - 1] == NULL) {
            perror("Invalid hand.");
            return NULL;
        }
        free(line);
        line = NULL;
    }
    free(line);
    *n_hands = cnt;
    return tmp;
}