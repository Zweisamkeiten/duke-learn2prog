#include "deck.h"
#include "future.h"
#include "cards.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    deck_t * d = malloc(sizeof(deck_t));
    d->n_cards = 0;
    d->cards = NULL;

    char * index = NULL;
    const char * curr = str;
    while ((index=strchr(curr, ' ')) != NULL || (index=strchr(curr, '\n')) != NULL) {
        // get the card str
        // +1 for '\0'
        char * card_str = calloc(1, index - curr + 1);
        strncpy(card_str, curr, index - curr);
        curr = index + 1;

        // letter to card
        if (card_str[0] == '?') {
            card_t * empty = add_empty_card(d);
            size_t index_future = atoi(card_str + 1);
            add_future_card(fc, index_future, empty);
        }
        else {
            card_t c = card_from_letters(card_str[0], card_str[1]);
            add_card_to(d, c);
        }
        free(card_str);
    }
    if (d->n_cards < 5) {
        fprintf(stderr, "a poker hand should have at least 5 cards.\n");
        exit(EXIT_FAILURE);
    }
    return d;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    *n_hands = 0;
    deck_t ** ds = NULL;

    char * line = NULL;
    size_t sz = 0;

    while (getline(&line, &sz, f) >= 0) {
        ds = realloc(ds, (*n_hands + 1) * sizeof(deck_t *));
        ds[*n_hands] = hand_from_string(line, fc);

        free(line);
        line = NULL;
        *n_hands = *n_hands + 1;
    }
    free(line);

    return ds;
}
