#include "cards.h"
#include "deck.h"
#include "future.h"
#include <stdlib.h>

int main() {
  deck_t *d = malloc(sizeof(deck_t));
  d->n_cards = 0;
  // card_t first = {.value = 0, .suit = 0};
  // d->cards = malloc(sizeof(card_t *));
  // d->cards[0] = malloc(sizeof(card_t));
  // *(d->cards[0]) = first;
  d->cards = NULL;
  for (int i = 0; i < 4; ++i) {
    add_empty_card(d);
  }
  future_cards_t *fc = malloc(sizeof(future_cards_t));
  fc->n_decks = 0;
  fc->decks = NULL;
  for (int i = 3; i >= 0; --i) {
    add_future_card(fc, i, d->cards[i]);
  }

  deck_t *d1 = malloc(sizeof(deck_t));
  card_t c1 = {.value = VALUE_ACE, .suit = SPADES};
  card_t c2 = {.value = VALUE_KING, .suit = HEARTS};
  card_t c3 = {.value = 8, .suit = CLUBS};
  card_t c4 = {.value = 7, .suit = DIAMONDS};
  add_card_to(d1, c1);
  add_card_to(d1, c2);
  add_card_to(d1, c3);
  add_card_to(d1, c4);

  future_cards_from_deck(d1, fc);
  return 0;
}
