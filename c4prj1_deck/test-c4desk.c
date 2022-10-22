#include "cards.h"
#include "deck.h"
#include "eval.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  deck_t *d1 = malloc(sizeof(deck_t));
  d1->cards = malloc(sizeof(card_t *));
  d1->cards[0] = malloc(sizeof(card_t));
  d1->cards[0]->value = 2;
  d1->cards[0]->suit = SPADES;
  d1->n_cards = 1;
  card_t test = {.value = 3, .suit = HEARTS};
  add_card_to(d1, test);
  assert(deck_contains(d1, test));
  print_hand(d1);
  printf("\n");
  // add_empty_card(d1);
  // card_t empty = {.value = 0, .suit = 0};
  // assert(deck_contains(d1, empty));

  // deck_t *d2 = make_deck_exclude(d1);
  // print_hand(d2);
  // assert(!deck_contains(d2, test));
  deck_t *d2 = malloc(sizeof(deck_t));
  d2->cards = malloc(sizeof(card_t *));
  d2->cards[0] = malloc(sizeof(card_t));
  d2->cards[0]->value = 3;
  d2->cards[0]->suit = CLUBS;
  d2->n_cards = 1;

  deck_t **hands = malloc(2 * sizeof(deck_t *));
  size_t n_hands = 2;
  hands[0] = d1;
  hands[1] = d2;
  print_hand(d1);
  printf("\n");
  print_hand(d2);
  printf("\n");
  deck_t *d3 = build_remaining_deck(hands, n_hands);
  print_hand(d3);
  assert(!deck_contains(d3, test));
  printf("\n");

  unsigned *counts = get_match_counts(d3);
  for (int i = 0; i < d3->n_cards; ++i) {
    printf("%d ", counts[i]);
  }
  printf("\n");

  free(counts);
  free(hands);
  free_deck(d1);
  free_deck(d2);
  free_deck(d3);
  return 0;
}
