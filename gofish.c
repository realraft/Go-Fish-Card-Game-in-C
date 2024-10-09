#include "gofish.h"

int main(int args, char *argv[])
{
    int round_num; // tracker for the number of rounds played in a game
    char selected_rank; // user selected rank
    struct card *newest_card; // used to get the info of cards drawn from deck
    char play_again[2]; // storage for user prompt to play again

    while (1) // start program while loop
    {
        shuffle();
        deal_player_cards(&user);
        deal_player_cards(&computer);
        round_num = 0;
        
        while (1) // start game loop
        {
            print_hand_books(&user, &computer);

            // check if it is player 1 or 2 turn
            if (round_num % 2 == 0) // player 1 turn
            {
                selected_rank = user_play(&user);
                if (search(&computer, selected_rank)) // computer has user selected card
                {
                    // IMPLEMENT PRINT AND TRANSFER
                }
                else // computer does not have user selected card
                {
                    go_fish(&user, selected_rank);
                }

                /*
                check add book needs to be moved into the go fish and search portions of the if statement
                so that the logic for a player going again if they guess correctly 
                */
                check_add_book(&user);

                if (game_over(&user)) // check if player 1 won
                {
                    printf("Player 1 Wins! %d-%d", get_book_count(&user), get_book_count(&computer));
                    break; // break game loop
                }
            }
            else // player 2 turn
            {
                selected_rank = computer_play(&computer);
                if (search(&user, selected_rank)) // computer has user selected card
                {
                    // IMPLEMENT PRINT AND TRANSFER
                }
                else // computer does not have user selected card
                {
                    go_fish(&computer, selected_rank);
                }

                check_add_book(&computer);

                if (game_over(&computer)) // check if player 2 won
                {
                    printf("Player 2 Wins! %d-%d", get_book_count(&computer), get_book_count(&user));
                    break; // break game loop
                }
            }

            round_num++;
        }

        // prompt user to play again
        printf("Do you want to play again [Y/N]: ");
        scanf("%2c", play_again);
        if (to_lower(play_again[0]) != 'y')
        {
            break;
        }
    }
    printf("Exiting.");
    /*
    Things to think about in psuedo code:
    when a player correctly asks if another player has a certain card they get to go again
    check if there are any cards left when you go to pick up, play accordingly from there
    memory needs to be freed after a game
    if a player has no cards they must draw and skip the asking turn
    if you run out of cards to draw then just prompt asking until someone wins
    check to make sure that a card is in the players hand when they choose a rank

    */

    /*
    COMMENT PSUEDOCODE BEGINS

    start program while loop
    shuffle deck
    deal cards to player and robot
    set round_num to 0

    start current game while loop
    print hand and books
    use a variable called round_num or something and check if it is even or odd. even means human picks card odd means robot picks

    EVEN:
    prompt human player for rank
    check valid rank
    check robot hand for card and transfer cards to human player if robot possesses one, otherwise draw card
    print this process
    check for books in human, if they exist remove the 4 cards from hand and update books
    check win condition and exit current while loop if true and declare winner

    ODD:
    randomly pick a rank in robot hand
    check if human hand has card and transfer if needed, otherwise draw card
    print this process
    check for books in robot, if they exist remove the 4 cards from hand and update books
    check win condition and exit current while loop if true and declare winner

    exit game while loop
    prompt user to want to play again
    if yes then continue
    if no then break from loop and exit program
    */
}

int print_hand_books(struct player *one, struct player *two)
{
    struct hand *iterator = one->card_list;

    // print player 1 hand
    printf("Player 1's Hand - ");
    while (iterator != NULL)
    {
        printf("%c%c ", iterator->top.suit, iterator->top.rank);
    }

    // print player 1 book
    printf("Player 1's Book - ");
    for (int i = 0; i < 7; i++)
    {
        if (one->book[i] == '\0')
        {
            break;
        }
        else
        {
            printf(" %c", one->book[i]);
        }
    }

    // print player 2 book
    printf("Player 2's Book - ");
    for (int i = 0; i < 7; i++)
    {
        if (two->book[i] == '\0')
        {
            break;
        }
        else
        {
            printf(" %c", two->book[i]);
        }
    }

    return 0;
}

int go_fish(struct player *target, char rank)
{
    printf("    - Player 2 has no %c's", rank);
    struct card *newest_card = next_card(); // get next card from deck
    add_card(&user, newest_card); // add card to user hand
    printf("    - Go Fish, Player 1 draws %c%c", newest_card->suit, newest_card->rank);
}

int get_book_count(struct player *target)
{
    char current_book = target->book[0];
    int count = 0;

    for (int i = 0; i < 7; i++)
    {
        if (target->book[i] != '\0')
        {
            count++;
        }
    }

    return count;
}

int correct_guess(struct player *src, struct player *dest, char rank, int round_num)
{
    char src_cards[3][2]; // cards to be transfered
    char dest_cards[3][2]; // cards of rank that destination owns

    // initialize the card arrays with default '00'
    for (int i = 0; i < 3; i++) {
        src_cards[i][0] = '0';
        src_cards[i][1] = '0';
        dest_cards[i][0] = '0';
        dest_cards[i][1] = '0';
    }

    struct hand *iterator = src->card_list;
    int index = 0;

    // loop and store all cards to transfer
    while (iterator != NULL)
    {
        if (iterator->top.rank == rank)
        {
            src_cards[index][0] = iterator->top.rank;
            src_cards[index][1] = iterator->top.suit;
            index++;
        }
    }

    iterator = dest->card_list; // reset iterator
    index = 0; // reset index

    // loop and store all cards destination owns of rank
    while (iterator != NULL)
    {
        if (iterator->top.rank == rank)
        {
            dest_cards[index][0] = iterator->top.rank;
            dest_cards[index][1] = iterator->top.suit;
            index++;
            index++;
        }
    }

    if (round_num % 2 == 0) // user turn so player 2 printed first
    {
        // print for cards to be transferred
        printf("    - Player 2 has ");
        for (int i = 0; i < 3; i++)
        {
            if (src_cards[i][0] != '0' && src_cards[i][1] != '0')
            {
                if (i == 0)
                {
                    printf("%c%c", src_cards[i][0], src_cards[i][1]);
                }
                else
                {
                    printf(", %c%c", src_cards[i][0], src_cards[i][1]);
                }
            }
        }

        // print for cards owned
        printf("    - Player 1 has ");
        for (int i = 0; i < 3; i++)
        {
            if (dest_cards[i][0] != '0' && dest_cards[i][1] != '0')
            {
                if (i == 0)
                {
                    printf("%c%c", dest_cards[i][0], dest_cards[i][1]);
                }
                else
                {
                    printf(", %c%c", dest_cards[i][0], dest_cards[i][1]);
                }
            }
        }
    }
    else // computer turn so player 1 printed first
    {
        // print for cards to be transferred
        printf("    - Player 1 has ");
        for (int i = 0; i < 3; i++)
        {
            if (src_cards[i][0] != '0' && src_cards[i][1] != '0')
            {
                if (i == 0)
                {
                    printf("%c%c", src_cards[i][0], src_cards[i][1]);
                }
                else
                {
                    printf(", %c%c", src_cards[i][0], src_cards[i][1]);
                }
            }
        }

        // print for cards owned
        printf("    - Player 2 has ");
        for (int i = 0; i < 3; i++)
        {
            if (dest_cards[i][0] != '0' && dest_cards[i][1] != '0')
            {
                if (i == 0)
                {
                    printf("%c%c", dest_cards[i][0], dest_cards[i][1]);
                }
                else
                {
                    printf(", %c%c", dest_cards[i][0], dest_cards[i][1]);
                }
            }
        }
    }

    // transfer cards
    transfer_cards(src, dest, rank);

    return 0;
}