#include "cards.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void assert_card_valid(card_t c) {
  assert(2 <= c.value && c.value <= VALUE_ACE);
  assert(SPADES <= c.suit && c.suit <= CLUBS);
}

const char *ranking_to_string(hand_ranking_t r) {
  switch (r) {
  case STRAIGHT_FLUSH:
    return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
  case FULL_HOUSE:
    return "FULL_HOUSE";
  case FLUSH:
    return "FLUSH";
  case STRAIGHT:
    return "STRAIGHT";
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
  case TWO_PAIR:
    return "TWO_PAIR";
  case PAIR:
    return "PAIR";
  case NOTHING:
    return "NOTHING";
  default:
    return "";
  };
}

char value_letter(card_t c) {
  switch (c.value) {
  case 2:
    return '2';
  case 3:
    return '3';
  case 4:
    return '4';
  case 5:
    return '5';
  case 6:
    return '6';
  case 7:
    return '7';
  case 8:
    return '8';
  case 9:
    return '9';
  case 10:
    return '0';
  case 11:
    return 'J';
  case 12:
    return 'Q';
  case 13:
    return 'K';
  case 14:
    return 'A';
  default:
    return 'x';
  };
}

char suit_letter(card_t c) {
  switch (c.suit) {
  case SPADES:
    return 's';
  case HEARTS:
    return 'h';
  case DIAMONDS:
    return 'd';
  case CLUBS:
    return 'c';
  default:
    return 'x';
  };
}

void print_card(card_t c) { printf("%c%c", value_letter(c), suit_letter(c)); }

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp = {0, 0};
  assert(value_let < 2 || value_let > VALUE_ACE);
  assert(suit_let < SPADES || suit_let > CLUBS);
  if ('2' <= value_let && value_let <= '9')
    temp.value = value_let - '0';
  else {
    switch (value_let) {
    case '0':
      temp.value = 10;
      break;
    case 'J':
      temp.value = VALUE_JACK;
      break;
    case 'Q':
      temp.value = VALUE_QUEEN;
      break;
    case 'K':
      temp.value = VALUE_KING;
      break;
    case 'A':
      temp.value = VALUE_ACE;
      break;
    }
  }

  switch (suit_let) {
  case 's':
    temp.suit = SPADES;
    break;
  case 'h':
    temp.suit = HEARTS;
    break;
  case 'd':
    temp.suit = DIAMONDS;
    break;
  case 'c':
    temp.suit = CLUBS;
    break;
  }

  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp = {0, 0};
  temp.value = c % 13 + 2;
  temp.suit = c / 13;
  return temp;
}
