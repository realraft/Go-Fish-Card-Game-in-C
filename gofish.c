#include <stdio.h>

int main(int args, char *argv[])
{
  fprintf(stdout, "Put your code here.");

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