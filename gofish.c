#include "gofish.h"

int main(int args, char *argv[])
{
    int round_num;        // tracker for the number of rounds played in a game
    char selected_rank;   // user selected rank
    char play_again[2];   // storage for user prompt to play again
    char lower_response;  // storage for lowercase of user prompt
    int continue_playing; // bool for if user would like to play again
    char book_added;      // storage for the book added char

    while (1) // start program while loop
    {
        printf("Shuffling deck...\n");
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
                while (1) // start turn loop
                {
                    selected_rank = user_play(&user);
                    if (search(&computer, selected_rank)) // computer has user selected card
                    {
                        correct_guess(&computer, &user, selected_rank, round_num);
                        book_added = check_add_book(&user);
                        if (book_added != '0')
                        {
                            printf("    - Player 1 books %c\n", book_added);
                        }

                        if (game_over(&user)) // check if player 1 won
                        {
                            break; // break turn loop if player 1 won
                        }

                        printf("    - Player 1 gets another turn\n");
                        print_hand_books(&user, &computer);
                    }
                    else // computer does not have user selected card
                    {
                        go_fish(&user, selected_rank, round_num);
                        book_added = check_add_book(&user);
                        if (book_added != '0')
                        {
                            printf("    - Player 1 books %c\n", book_added);
                        }
                        break; // break turn loop
                    }
                }

                if (game_over(&user)) // check if player 1 won
                {
                    printf("Player 1 Wins! %d-%d\n", get_book_count(&user), get_book_count(&computer));
                    break; // break game loop
                }
            }
            else // player 2 turn
            {
                while (1) // start turn loop
                {
                    selected_rank = computer_play(&computer);
                    if (search(&user, selected_rank)) // user has computer selected card
                    {
                        correct_guess(&user, &computer, selected_rank, round_num);
                        book_added = check_add_book(&computer);
                        if (book_added != '0')
                        {
                            printf("    - Player 2 books %c", book_added);
                        }

                        if (game_over(&computer)) // check if player 2 won
                        {
                            break; // break turn loop if player 2 won
                        }

                        printf("    - Player 2 gets another turn\n");
                        print_hand_books(&user, &computer);
                    }
                    else // user does not have computer selected card
                    {
                        go_fish(&computer, selected_rank, round_num);
                        book_added = check_add_book(&computer);
                        if (book_added != '0')
                        {
                            printf("    - Player 2 books %c\n", book_added);
                        }
                        break; // break turn loop
                    }
                }

                if (game_over(&computer)) // check if player 2 won
                {
                    printf("Player 2 Wins! %d-%d\n", get_book_count(&computer), get_book_count(&user));
                    break; // break game loop
                }
            }

            round_num++;
        }

        while (1)
        {
            // prompt user to play again
            printf("Do you want to play again [Y/N]: ");
            scanf("%1s", play_again);
            // convert to lowercase for comparison
            lower_response = tolower(play_again[0]);

            // check for valid input
            if (lower_response == 'y' || lower_response == 'n')
            {
                if (lower_response != 'y') // assign continue playing boolean
                {
                    continue_playing = 0;
                }
                else
                {
                    continue_playing = 1;
                }
                break;
            }
            else
            {
                printf("Invalid input. Please enter 'Y' or 'N'.\n");
            }
        }

        if (continue_playing == 0) // if user said N then break program loop
        {
            break;
        }

        // reset the game back to play again
        round_num = 0;
        reset_player(&user);
        reset_player(&computer);
        printf("\n");
    }
    printf("Exiting.");
    return 0;
}

int print_hand_books(struct player *one, struct player *two)
{
    printf("\n");
    struct hand *iterator = one->card_list;

    //  print player 1 hand
    printf("Player 1's Hand - ");
    while (iterator != NULL)
    {
        printf("%c%c ", iterator->top.rank, iterator->top.suit);
        iterator = iterator->next;
    }

    printf("\n");

    //  print player 2 hand (for testing)
    /*iterator = two->card_list;
    printf("Player 2's Hand - ");
    while (iterator != NULL)
    {
        printf("%c%c ", iterator->top.rank, iterator->top.suit);
        iterator = iterator->next;
    }
    printf("\n");*/

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

    printf("\n");

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

    printf("\n");

    // printf("p1 hand %d\n", one->hand_size);
    // printf("p2 hand %d\n", two->hand_size);

    return 0;
}

int go_fish(struct player *target, char rank, int round_num)
{
    if (round_num % 2 == 0)
    {
        printf("    - Player 2 has no %c's", rank);
        printf("\n");

        struct card *newest_card = next_card(); // get next card from deck
        add_card(target, newest_card);          // add card to target hand

        printf("    - Go Fish, Player 1 draws %c%c", newest_card->rank, newest_card->suit);
        printf("\n");
    }
    else
    {
        printf("    - Player 1 has no %c's", rank);
        printf("\n");

        struct card *newest_card = next_card(); // get next card from deck
        add_card(target, newest_card);          // add card to target hand

        printf("    - Go Fish, Player 2 draws %c%c", newest_card->rank, newest_card->suit);
        printf("\n");
    }
    return 0;
}

int get_book_count(struct player *target)
{
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
    char src_cards[3][2];  // cards to be transfered
    char dest_cards[3][2]; // cards of rank that destination owns

    // initialize the card arrays with default '00'
    for (int i = 0; i < 3; i++)
    {
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
        iterator = iterator->next;
    }

    iterator = dest->card_list; // reset iterator
    index = 0;                  // reset index

    // loop and store all cards destination owns of rank
    while (iterator != NULL)
    {
        if (iterator->top.rank == rank)
        {
            dest_cards[index][0] = iterator->top.rank;
            dest_cards[index][1] = iterator->top.suit;
            index++;
        }
        iterator = iterator->next;
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
        printf("\n");
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
        printf("\n");
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
        printf("\n");
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
        printf("\n");
    }

    // transfer cards
    transfer_cards(src, dest, rank);

    return 0;
}