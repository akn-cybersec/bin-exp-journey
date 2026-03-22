# Rock, Paper, Scissors

**Platform:** picoCTF  
**Technique:** Logic Exploitation / String Substring  
**Difficulty:** Easy  

## Challenge Description

A simple rock-paper-scissors game. Beat the computer five times in a row to get the flag. The computer's moves are random, but the input validation has a flaw.

## Vulnerability

The program likely uses `strstr()` to check if the player's input contains the computer's move:

```c
if (strstr(player_input, computer_move) != NULL) {
    // player wins
}
```
By entering a string that contains all possible moves (rock, paper, scissors), the player wins every round regardless of the computer's choice.

Exploitation
Step 1: Find the Edge Case
I noticed that entering "rockpaperscissors" caused a win, even when the computer played different moves.

Step 2: Understand the Logic
```strstr("rockpaperscissors", "rock") → match
strstr("rockpaperscissors", "paper") → match
strstr("rockpaperscissors", "scissors") → match
```

One input covers all possibilities.

Step 3: Play Five Rounds
Enter rockpaperscissors each time. Win five times in a row. Get the flag.

Interaction
```text
Type '1' to play a game
1

Please make your selection (rock/paper/scissors):
rockpaperscissors
You played: rockpaperscissors
The computer played: paper
You win!

[repeat four more times]

Congrats, here's the flag!
picoCTF{50M3_3X7R3M3_1UCK_58F0F41B}
```
