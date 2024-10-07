#include "deck.h"
#include "string.h"

/*
 * Variable: deck_instance
 * -----------------------
 *  
 * Go Fish uses a single deck
 */
struct deck deck_instance;

/*
 * Function: shuffle
 * --------------------
 *  Initializes deck_instance and shuffles it.
 *  Resets the deck if a prior game has been played.
 * 
 *  returns: 0 if no error, and non-zero on error
 */ 
int shuffle() {
    // initialize variables for deck creation
    char suits[4] = {'S', 'H', 'D', 'C'};
    char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'};
    int deck_index = 0;

    // fill deck with cards
    for(int i=0; i<4; i++) {
        for(int j=0; j<13; j++) {
            struct card to_add;
            to_add.suit = suits[i];
            strcpy(to_add.rank, ranks[j]); // strcpy needed here because the rank can he 1 OR 2 characters long

            deck_instance.list[deck_index] = to_add;
            deck_index++;
        }
    }

    // initialize variables for deck creation
    int random_index;
    struct card temp_card;

    // shuffle deck using Fisher-Yates shuffle (I googled this algo)
    for(int i=0; i<=50; i++) {
        random_index = (rand() % (51 - i + 1)) + i;
        temp_card = deck_instance.list[i];
        deck_instance.list[i] = deck_instance.list[random_index];
        deck_instance.list[random_index] = temp_card;
    }

    deck_instance.top_card = 51; // index of the top card after shuffle

    return 0;
}

/*
 * Function: deal_player_cards
 * ---------------------------
 *  Deal 7 random cards to the player specified in the function.
 *  Remove the dealt cards from the deck. 
 *
 *  target: pointer to the player to be dealt cards
 *
 *  returns: 0 if no error, and non-zero on error
 */
int deal_player_cards(struct player* target) {
    // initialize the card pointer
    struct card *to_deal;

    for(int i=0; i<7; i++) {
        to_deal = next_card();
        add_card(target, to_deal); // call add_card for the player
    }

    return 0;
}

/*
 * Function: next_card
 * -------------------
 *  Return a pointer to the top card on the deck.
 *  Removes that card from the deck. 
 *
 *  returns: pointer to the top card on the deck.
 */
struct card* next_card() {
    if(deck_instance.top_card < 0) {
        return NULL; // if there are no more cards left return null
    }
    else {
        int current_top_card = deck_instance.top_card;
        deck_instance.top_card--; // decerement the top card index because we just removed one
        return &deck_instance.list[current_top_card];
    }
}

/*
 * Function: size
 * --------------
 *  Return the number of cards left in the current deck.
 *
 *  returns: number of cards left in the deck.
 */
size_t deck_size() {
    if(deck_instance.top_card<0) { // if top card index if less than 0 then we have no more cards left
        return 0;
    }
    else {
        return deck_instance.top_card + 1; // there is always one more card than the index of the current top card
    }
}