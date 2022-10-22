#include "deck.h"
#include "future.h"
#include "input.h"
#include <stddef.h>
#include <stdio.h>

int main() {
  FILE *f = fopen("test-input.txt", "r");
  size_t n_hands = 0;
  future_cards_t *fc = malloc(sizeof(future_cards_t));
  fc->n_decks = 0;
  fc->decks = NULL;
  deck_t **ds = read_input(f, &n_hands, fc);

  for (size_t i = 0; i < n_hands; ++i) {
    print_hand(ds[i]);
    free_deck(ds[i]);
    printf("\n");
  }
  free(ds);

  for (size_t i = 0; i < fc->n_decks; ++i) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
  if (fclose(f) != 0) {
    return EXIT_FAILURE;
  }
  return 0;
}
