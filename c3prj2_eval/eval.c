#include "eval.h"
#include "cards.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
    const card_t * const * cp1 = vp1;
    const card_t * const * cp2 = vp2;
    card_t x = *(*cp1);
    card_t y = *(*cp2);
    if (x.value != y.value) {
        return - (x.value - y.value);
    }
    return (suit_letter(x) - suit_letter(y));
}

suit_t flush_suit(deck_t * hand) {
    int cnt[30] = {0};
    for (size_t i = 0; i < hand->n_cards; i ++) {
        cnt[suit_letter(*(hand->cards[i])) - 'a'] += 1;
    }
    for (int i = 'a'; i <= 'z'; i ++) {
        if (cnt[i - 'a'] >= 5) {
            switch(i) {
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
    }
    return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
    unsigned maxE = 0;
    for (size_t i = 0; i < n; i ++) {
        maxE = (maxE < arr[i]) ? arr[i] : maxE;
    }
    return maxE;
}

size_t get_match_index(unsigned * match_counts, size_t n, unsigned n_of_akind) {
    for (size_t i = 0; i < n; i ++) {
        if (match_counts[i] == n_of_akind) {
            return i;
        }
    }
    assert(0);
}

ssize_t find_secondary_pair(deck_t * hand,
                            unsigned * match_counts,
                            size_t match_idx) {
    for (size_t i = 0; i < hand->n_cards; i ++) {
        if (match_counts[i] > 1) {
            if ((*(hand->cards[i])).value != (*(hand->cards[match_idx])).value) {
                return i;
            }
        }
    }
    return -1;
}

int suit_number(suit_t x) {
    switch(x) {
        case SPADES: return 3;
        case HEARTS: return 2;
        case DIAMONDS: return 1;
        default: return 0;
    }
}

int unique_cards(card_t ** cards, int suits[][4], size_t index, size_t len, int list[]) {
    int cnt = 0;
    suits[0][suit_number(cards[index]->suit)] = 1;
    list[0] = cards[index]->value;
    for (size_t i = index + 1; i < len; i ++) {
        if (cards[i]->value != cards[i - 1]->value) {
            list[++ cnt] = cards[i]->value;
        }
        suits[cnt][suit_number(cards[i]->suit)] = 1;
    }
    return cnt + 1;
}

int is_5_straight_at(int suits[][4], int list[], size_t index, suit_t fs) {
    for (size_t pos = index + 1; pos <= index + 4; pos ++) {
        if (list[pos] != list[pos - 1] - 1 ||
            (fs != NUM_SUITS && suits[pos][suit_number(fs)] != 1)) {
            return 0;
        }
    }
    return (fs == NUM_SUITS || suits[index][suit_number(fs)] == 1);
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
    int len = hand->n_cards;
    int suits[len + 1][4], list[len + 1];
    memset(list, 0, sizeof(list));
    memset(suits, 0, sizeof(suits));
    int new_len = unique_cards(hand->cards, suits, index, len, list);
    if (new_len < 5 || (fs != NUM_SUITS && hand->cards[index]->suit != fs)) {
        return 0;
    }
    if (is_5_straight_at(suits, list, 0, fs)) {
        return 1;
    }
    if (list[0] == 14) {
        for (int j = 0; j < 4; j ++) {
            suits[new_len][j] = suits[0][j];
        }
        list[new_len ++] = 1;
        return - (is_5_straight_at(suits, list, new_len - 5, fs));
    }
    return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				                  unsigned n,
				                  hand_ranking_t what,
                                  size_t idx) {
    hand_eval_t ans;
    ans.ranking = what;
    size_t len = hand->n_cards;
    int flag[len + 1], cnt = 0;
    memset(flag, 0, sizeof(flag));
    for (size_t i = idx; i < idx + n; i ++) {
        ans.cards[cnt ++] = hand->cards[i];
        flag[i] = 1;
    }
    for (size_t i = 0; i < len; i ++) {
        if (!flag[i] && cnt < 5) {
            ans.cards[cnt ++] = hand->cards[i];
        }
    }
    return ans;
}

int ranking_num(hand_ranking_t x) {
    switch(x) {
        case STRAIGHT_FLUSH: return 8;
        case FOUR_OF_A_KIND: return 7;
        case FULL_HOUSE: return 6;
        case FLUSH: return 5;
        case STRAIGHT: return 4;
        case THREE_OF_A_KIND: return 3;
        case TWO_PAIR: return 2;
        case PAIR: return 1;
        default: return 0;
    }
}

int compare_hands(deck_t * hand1, deck_t * hand2) {
    qsort(hand1->cards, hand1->n_cards, sizeof(card_t), card_ptr_comp);
    qsort(hand2->cards, hand2->n_cards, sizeof(card_t), card_ptr_comp);
    hand_eval_t h1 = evaluate_hand(hand1);
    hand_eval_t h2 = evaluate_hand(hand2);
    if (h1.ranking != h2.ranking) {
        return ranking_num(h1.ranking) - ranking_num(h2.ranking);
    }
    for (size_t i = 0; i < 5; i ++) {
        if (h1.cards[i]->value != h2.cards[i]->value) {
            return h1.cards[i]->value - h2.cards[i]->value;
        }
    }
    return 0;
}

//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand);

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
    assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
    unsigned nextv = from->cards[ind]->value;
    size_t to_ind = 0;
    while (count > 0) {
        assert(ind < from->n_cards);
        assert(nextv >= 2);
        assert(to_ind <5);
        if (from->cards[ind]->value == nextv && 
            (fs == NUM_SUITS || from->cards[ind]->suit == fs)){
            to[to_ind] = from->cards[ind];
            to_ind++;
            count--;
            nextv--;
        }
        ind++;
    }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
    if (hand->n_cards < 5){
        return 0;
    }
    for(size_t i = 0; i <= hand->n_cards -5; i++) {
        int x = is_straight_at(hand, i, fs);
        if (x != 0){
            if (x < 0) { //ace low straight
                assert(hand->cards[i]->value == VALUE_ACE &&
                    (fs == NUM_SUITS || hand->cards[i]->suit == fs));
                ans->cards[4] = hand->cards[i];
                size_t cpind = i+1;
                while(hand->cards[cpind]->value != 5 || 
                    !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
                    cpind++;
                    assert(cpind < hand->n_cards);
                }
                copy_straight(ans->cards, hand, cpind, fs,4) ;
            } else {
                copy_straight(ans->cards, hand, i, fs,5);
            }
            return 1;
        }
    }
    return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
    suit_t fs = flush_suit(hand);
    hand_eval_t ans;
    if (fs != NUM_SUITS) {
        if(find_straight(hand, fs, &ans)) {
            ans.ranking = STRAIGHT_FLUSH;
            return ans;
        }
    }
    unsigned * match_counts = get_match_counts(hand);
    unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
    assert(n_of_a_kind <= 4);
    size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
    ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
    free(match_counts);
    if (n_of_a_kind == 4) { //4 of a kind
        return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
    } else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
        ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
        ans.cards[3] = hand->cards[other_pair_idx];
        ans.cards[4] = hand->cards[other_pair_idx+1];
        return ans;
    } else if(fs != NUM_SUITS) { //flush
        ans.ranking = FLUSH;
        size_t copy_idx = 0;
        for(size_t i = 0; i < hand->n_cards;i++) {
            if (hand->cards[i]->suit == fs) {
                ans.cards[copy_idx] = hand->cards[i];
                copy_idx++;
                if (copy_idx >=5){
                    break;
                }
            }
        }
        return ans;
    } else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
        ans.ranking = STRAIGHT;
        return ans;
    } else if (n_of_a_kind == 3) { //3 of a kind
        return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
    } else if (other_pair_idx >=0) {     //two pair
        assert(n_of_a_kind ==2);
        ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
        ans.cards[2] = hand->cards[other_pair_idx];
        ans.cards[3] = hand->cards[other_pair_idx + 1];
        if (match_idx > 0) {
            ans.cards[4] = hand->cards[0];
        } else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
            //if other_pair_idx > 2, then, e.g. A A K Q Q
            ans.cards[4] = hand->cards[2];
        } else {       //e.g., A A K K Q
            ans.cards[4] = hand->cards[4];
        }
        return ans;
    } else if (n_of_a_kind == 2) {
        return build_hand_from_match(hand, 2, PAIR, match_idx);
    }
    return build_hand_from_match(hand, 0, NOTHING, 0);
}
