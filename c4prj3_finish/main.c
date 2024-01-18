#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int trial(deck_t * deck, future_cards_t * fc, deck_t ** hands, size_t hand_count) {
    shuffle(deck);
    future_cards_from_deck(deck, fc);
    int winner = 0, flag = 0;
    for(int i = 1; i < hand_count; i ++) {
        if (compare_hands(hands[winner], hands[i]) != 0) {
            flag = 1;
            break;
        }
    }
    if (!flag) {
        return -1;
    }
    for(int i = 1; i < hand_count; i ++) {
        if (compare_hands(hands[winner], hands[i]) < 0) {
            winner = i;
        }
    }
    return winner;
}

int max(int x, int y) {
    return (x > y) ? x : y;
}

int main(int argc, char ** argv) {
    if (argc == 1 || argc > 3) {
        perror("Invalid arguments!");
        return EXIT_FAILURE;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Can't read file.");
        return EXIT_FAILURE;
    }
    int test_number = 10000; // Default
    if (argc == 3) {
        test_number = atoi(argv[2]);
    }
    if (test_number <= 0) {
        perror("Test number must be positive.");
        return EXIT_FAILURE;
    }
    size_t * hand_count = malloc(sizeof(size_t));
    *hand_count = 0;
    future_cards_t * fc = malloc(sizeof(future_cards_t));
    fc->n_decks = 0;
    fc->decks = NULL;
    deck_t ** hands = read_input(fp, hand_count, fc);
    if (hands == NULL) {
        perror("Invalid hands.");
        return EXIT_FAILURE;
    }
    if (*hand_count < 2) {
        perror("Invalid hands.");
        return EXIT_FAILURE;
    }
    int win_time[*hand_count], tie = 0;
    deck_t * valid_deck = build_remaining_deck(hands, *hand_count);
    memset(win_time, 0, sizeof(win_time));
    for(int i = 1; i <= test_number; i ++) {
        int result = trial(valid_deck, fc, hands, *hand_count);
        if (result == -1) {
            tie ++;
        } else {
            win_time[result] ++;
        }
    }
    for(int i = 0; i < *hand_count; i ++) {
        double rate = win_time[i] * 100.0 / test_number;
        printf("Hand %d won %d / %d times (%.2f%%)\n", i, win_time[i], test_number, rate);
    }
    printf("And there were %d ties\n", tie);
    free_deck(valid_deck);
    free(hand_count);
    for(int i = 0; i < fc->n_decks; i ++) {
        free(fc->decks[i].cards);
    }
    free(fc->decks);
    free(fc);
    free_deck(hands[0]);
    free_deck(hands[1]);
    free(hands);
    fclose(fp);
    return EXIT_SUCCESS;
}