#include "cards.h"
#include <stdio.h>

int main(void) {
  card_t c1 = {2, SPADES};
  card_t c2 = {3, CLUBS};
  card_t c3 = {14, CLUBS};
  assert_card_valid(c1);
  assert_card_valid(c2);
  assert_card_valid(c3);
  printf("%s\n", ranking_to_string(STRAIGHT_FLUSH));
  printf("%s\n", ranking_to_string(FOUR_OF_A_KIND));
  printf("%s\n", ranking_to_string(FULL_HOUSE));
  printf("%s\n", ranking_to_string(FLUSH));
  printf("%s\n", ranking_to_string(STRAIGHT));
  printf("%s\n", ranking_to_string(THREE_OF_A_KIND));
  printf("%s\n", ranking_to_string(TWO_PAIR));
  printf("%s\n", ranking_to_string(PAIR));
  printf("%s\n", ranking_to_string(NOTHING));

  printf("%c\n", value_letter(c1));
  printf("%c\n", value_letter(c2));
  printf("%c\n", value_letter(c3));

  print_card(c1);
  printf("\n");
  print_card(c2);
  printf("\n");
  print_card(c3);
  printf("\n");

  print_card(card_from_letters('A', 's'));
  printf("\n");
  print_card(card_from_letters('K', 'c'));
  printf("\n");
  print_card(card_from_letters('3', 'd'));
  printf("\n");

  for (int i = 0; i < 52; i++) {
    print_card(card_from_num(i));
    printf("\n");
  }
}
