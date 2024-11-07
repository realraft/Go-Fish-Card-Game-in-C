# ECE322 Assignment 2
## GoFish in C

### Author
[Owen Raftery](https://github.com/realraft)

### Description
The classic Go Fish card game, but against a computer and in C!

### Tutorial
1. Run `Makefile`
2. Run `./gofish`
3. Upon running, human player is presented with something like:
```
Player 1's Hand - 5S 3H JC 9D 9H AS QC
Player 1's Book -
Player 2's Book -
Player 1's turn, enter a Rank: 
```
Human player must now enter a rank of card that is in their hand. From there, play Go Fish as normal!
```
Player 1's turn, enter a Rank: 5
    - Player 2 has no 5's    
    - Go Fish, Player 1 draws 7D    
    - Player 2's turn    

Player 1's Hand - 5S 3H JC 9D 9H AS QC 7D
Player 1's Book -
Player 2's Book -
Player 2's turn, enter a Rank: 9
    - Player 1 has 9D, 9H    
    - Player 2 has 9C, 9S    
    - Player 2 books 9    
    - Player 2 gets another turn    

Player 1's Hand - 5S 3H JC AS QC 7D
Player 1's Book -
Player 2's Book - 9
Player 2's turn, enter a Rank: 4
    - Player 1 has no 4's    
    - Go Fish, Player 2 draws a card    
    - Player 1's turn    

Player 1's Hand - 5S 3H JC AS QC 7D
Player 1's Book -
Player 2's Book - 9
Player 1's turn, enter a Rank: 
```
Computer will play automatically. Play will continue until a player has 7 books.
```
Player 1's Hand - 8D
Player 1's Book - 3 2 J A 6 Q
Player 2's Book - 9 5 10 4 5 K
Player 1's turn, enter a Rank: 8
    - Player 2 has 8H, 8S, 8C
    - Player 1 has 8D
    - Player 1 books 8
    - Player 1 gets another turn

Player 1's Hand -
Player 1's Book - 3 2 J A 6 Q 8
Player 2's Book - 9 5 10 4 5 K
Player 1 Wins! 7-6

Do you want to play again [Y/N]: 
```
Upon a winner the user will be prompted to play again. 'Y/y' will start a new game and 'N/n' will exit the program.

### Project in Retrospect
There are some things I would change about the project if I could go back and do it again. First, I would have avoided using T on the backend because printing 10 on the frontend was a requirement. This added a lot of unneeded fluff. Second, I wouldn't have used an if statement to diverge between two large sections of code depending on if it was the human or computers turn. Instead, I would write one function and simply provide the items that will change between players in the arguments of the function. Third, I would have planned better for the formatting of the output, specifically the printing of new line characters and included them in the regular print statements to save on lines of code. Altogether, I am proud of the working finished product for my first project in a new coding language to me, and I am also happy with the lessons I learned with pointers and memory allocation.
