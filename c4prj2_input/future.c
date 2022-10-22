#include "future.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * adds ptr into the future cards for the given index
 * (that is which ?n it is)
 */
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
    if (fc->n_decks == 0 || index > fc->n_decks - 1) {
        fc->decks = realloc(fc->decks, (index + 1) * sizeof(deck_t));

        for (size_t i = fc->n_decks; i <= index; ++i) {
            fc->decks[i].n_cards = 0;
            fc->decks[i].cards = NULL;
        }
        fc->n_decks = index + 1;
    }
    fc->decks[index].n_cards++;
    fc->decks[index].cards = realloc(fc->decks[index].cards, fc->decks[index].n_cards * sizeof(card_t *));
    fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
    if (deck->n_cards < fc->n_decks){
        fprintf(stderr, "The numbers of deck and future_cards do not match\n");
        return;
    }

    for (int i=0; i<fc->n_decks;i++){
        if (fc->decks[i].n_cards==0){
            continue;
        }
        for (int x=0; x<fc->decks[i].n_cards; x++){
            *(fc->decks[i].cards[x]) = *(deck->cards[i]);
        }
      }
}
