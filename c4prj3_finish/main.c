#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
    // check command line arguments/report errors
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: ./porke inputfileName [num_trials]\n");
        return EXIT_FAILURE;
    }

    // open the inputfile
    int num_trials = 10000;
    if (argc == 3) num_trials = atoi(argv[2]);
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Can not open the file.\n");
        return EXIT_FAILURE;
    }
    size_t n_hands = 0;
    future_cards_t *fc = malloc(sizeof(future_cards_t));
    fc->n_decks = 0;
    fc->decks = NULL;

    // read the hands in it by read_input
    deck_t ** hands = read_input(f, &n_hands, fc);
    deck_t * remainings = build_remaining_deck(hands, n_hands);

    // an array to count how many times each hand wins.
    // + 1 for the tie condition
    int count_win_each_hand[n_hands + 1];
    for (size_t i = 0; i < n_hands + 1; ++i) {
        count_win_each_hand[i] = 0;
    }

    // shuffle the remainings for num_trials times
    for (int times = 0; times < num_trials; ++times) {
        shuffle(remainings);
        // assign unknown cards from the shuffled deck
        future_cards_from_deck(remainings, fc);

        size_t index = 0;
        // for the tie condition but should continue compare
        size_t inc_index_fin = 0;
        for (size_t i = 1; i < n_hands; ++i) {
            int result = compare_hands(hands[index], hands[i]);
            // result > 0 should do nothing
            /*
              ex: hand1 hand2 hand3
              hand1 == hand2 > hand3 should result tie
              hand1 == hand2 < hand3 should hand3 win
            */
            if (result < 0) {
                index = i;
                inc_index_fin = i;
            }
            else if(result == 0) {
                inc_index_fin = n_hands;
            }
        }
        count_win_each_hand[inc_index_fin]++;
    }

    for (size_t i = 0; i < n_hands; ++i) {
        double ratio = (double)count_win_each_hand[i] / (double)num_trials * 100;
        fprintf(stdout, "Hand %zu won %u / %u times (%.2f%%)\n", i, count_win_each_hand[i], num_trials, ratio);
    }
    fprintf(stdout, "And there were %u ties\n", count_win_each_hand[n_hands]);

    if (fclose(f) != 0) {
        fprintf(stderr, "Close file failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n_hands; ++i) {
        free_deck(hands[i]);
    }
    free(hands);
    free_deck(remainings);

    for (size_t i = 0; i < fc->n_decks; ++i) {
        free(fc->decks[i].cards);
    }
    free(fc->decks);
    free(fc);

    return EXIT_SUCCESS;
}
