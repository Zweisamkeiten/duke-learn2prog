#include <stddef.h>
#include <stdio.h>
#include "future.h"
#include "deck.h"
#include "input.h"

int main()
{
    FILE *f = fopen("test-input.txt", "r");
    size_t n_hands = 0;
    future_cards_t *fc = malloc(sizeof(future_cards_t));
    fc->n_decks = 0;
    fc->decks = NULL;
    deck_t ** ds = read_input(f, &n_hands, fc);

    for (size_t i = 0; i < n_hands; ++i) {
        print_hand(ds[i]);
        printf("\n");
    }

    return 0;
}
