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

    deck_instance.top_card = 52; // ensure the last card is the top card

    return 0;
}