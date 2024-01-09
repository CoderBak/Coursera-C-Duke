#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
    assert(value_letter(c) != ' ');
    assert(suit_letter(c) != ' ');
}

const char * ranking_to_string(hand_ranking_t r) {
    switch(r) {
        case STRAIGHT_FLUSH:
            return "STRAIGHT_FLUSH";
        case FOUR_OF_A_KIND:
            return "FOUR_OF_A_KIND";
        case FULL_HOUSE:
            return "FULL_HOUSE";
        case FLUSH:
            return "FLUSH";
        case STRAIGHT:
            return "STRAIGHT";
        case THREE_OF_A_KIND:
            return "THREE_OF_A_KIND";
        case TWO_PAIR:
            return "TWO_PAIR";
        case PAIR:
            return "PAIR";
        case NOTHING:
            return "NOTHING";
    }
    return "";
}

char value_letter(card_t c) {
    int val = c.value;
    if (2 <= val && val < 10) {
        return '0' + val;
    }
    switch(val) {
        case 10:
            return '0';
        case 11:
            return 'J';
        case 12:
            return 'Q';
        case 13:
            return 'K';
        case 14:
            return 'A';
    }
    return ' ';
}

int letter_value(char c) {
    if ('0' < c && c <= '9') {
        return c - '0';
    }
    switch(c) {
        case '0':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case 'A':
            return 14;
    }
    return 0;
}

char suit_letter(card_t c) {
    switch(c.suit) {
        case SPADES:
            return 's';
        case HEARTS:
            return 'h';
        case DIAMONDS:
            return 'd';
        case CLUBS:
            return 'c';
        default:
            return ' ';
    }
}

suit_t letter_suit(char c) {
    switch(c) {
        case 's':
            return SPADES;
        case 'h':
            return HEARTS;
        case 'd':
            return DIAMONDS;
        default:
            return CLUBS;
    }
}

void print_card(card_t c) {
    printf("%c%c",value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
    card_t temp;
    temp.value = letter_value(value_let);
    temp.suit = letter_suit(suit_let);
    return temp;
}

card_t card_from_num(unsigned c) {
    card_t temp;
    int val = c % 13 + 2;
    int suit = c / 13;
    temp.value = val;
    switch(suit) {
        case 0:
            temp.suit = SPADES;
            break;
        case 1:
            temp.suit = HEARTS;
            break;
        case 2:
            temp.suit = DIAMONDS;
            break;
        default:
            temp.suit = CLUBS;
    }
    return temp;
}
