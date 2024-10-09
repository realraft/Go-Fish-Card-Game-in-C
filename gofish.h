#ifndef GOFISH_H
#define GOFISH_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "player.h"
#include "deck.h"

int print_hand_books(struct player *one, struct player *two);

int go_fish(struct player *target, char rank);

int get_book_count(struct player *target);

int correct_guess(struct player *src, struct player *dest, char rank, int round_num);

#endif
