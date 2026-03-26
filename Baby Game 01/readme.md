# Game Exploit — Maze Solver

**Platform:** picoCTF  
**Technique:** Input Injection / Game Exploitation  
**Difficulty:** Easy  

## Challenge Description

A game where you control a character in a maze. The goal is to reach the flag by sending a sequence of moves. No buffer overflow, no memory corruption — just playing the game with a script.

## Vulnerability

The program accepts user input as movement commands. By sending the right sequence of moves, we can navigate the maze to the flag.

## Exploitation

### Step 1: Understand the Game

I decompiled the program to see how the maze works. It's a simple grid. The flag is at a specific location.

### Step 2: Find the Path

Through analysis, I found:
- 4 up moves (`w`) and 4 left moves (`a`) to reach a starting point
- 4 left moves (`a`) to leak something (maybe position)
- 29 down moves (`s`) and 93 right moves (`d`) to reach the flag

### Step 3: Craft the Payload

```python
init_move = b'w' * 4 + b'a' * 4   # 4 up, 4 left
leak_move = b'a' * 4              # 4 left (leak)
win_move = b's' * 29 + b'd' * 93  # 29 down, 93 right
payload = init_move + leak_move + win_move
```
Step 4: Send and Win
Send the payload. The character moves to the flag and prints it.
