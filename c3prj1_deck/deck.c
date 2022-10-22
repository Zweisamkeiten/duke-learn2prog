#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"
void print_hand(deck_t * hand){
    for (int i = 0; i < hand->n_cards; ++i) {
        print_card(**(hand->cards + i));
        printf(" ");
    }
    return;
}

int deck_contains(deck_t * d, card_t c) {
    for (int i = 0; i < d->n_cards; ++i) {
        if ((*(d->cards+i))->value == c.value && (*(d->cards+i))->suit == c.suit) {
            return 1;
        }
    }
  return 0;
}

void shuffle(deck_t * d){
    for (int i = 0; i < d->n_cards; ++i) {
        int random_pos = random() % d->n_cards;
        card_t * p = *(d->cards+i);
        *(d->cards+i) = *(d->cards+random_pos);
        *(d->cards+random_pos) = p;
    }
}

void assert_full_deck(deck_t * d) {
    for (int i = 0; i < d->n_cards; ++i) {
        assert_card_valid(*(*(d->cards+i)));
    }
}

void add_card_to(deck_t * deck, card_t c) {
    deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(card_t *));
    deck->cards[deck->n_cards] = malloc(sizeof(card_t));
    deck->cards[deck->n_cards]->value = c.value, deck->cards[deck->n_cards]->suit = c.suit;
    deck->n_cards = deck->n_cards + 1;
}

card_t * add_empty_card(deck_t * deck) {
    card_t empty = {.value = 0, .suit=0};
    add_card_to(deck, empty);
    return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
    deck_t * d = malloc(sizeof(deck_t));
    d->cards = NULL;
    d->n_cards = 0;
    for (size_t i = 0; i < 52; ++i) {
        card_t c = card_from_num(i);
        if (!deck_contains(excluded_cards, c)) {
            add_card_to(d, c);
        }
    }
    return d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
    deck_t * excluded_cards = malloc(sizeof(deck_t));
    excluded_cards->cards = NULL;
    excluded_cards->n_cards = 0;
    for (size_t i = 0; i < n_hands; ++i) {
        for (size_t j = 0; j < hands[i]->n_cards; ++j) {
            add_card_to(excluded_cards, *(hands[i]->cards[j]));
        }
    }

    deck_t * remaining_deck = make_deck_exclude(excluded_cards);
    free_deck(excluded_cards);
    return remaining_deck;
}

void free_deck(deck_t * deck) {
    for (size_t i = 0; i < deck->n_cards; ++i) {
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
}
