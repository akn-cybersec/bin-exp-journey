# Jump to Win

**Platform:** picoCTF  
**Technique:** Direct ret2win  
**Difficulty:** Trivial  

## Challenge Description

A program that directly asks for an address to jump to. No overflow. No format string. Just enter the right address and win.

## Vulnerability

The program takes user input and jumps to it. The challenge is literally "enter the win function address."

## Exploitation

### Step 1: Find the Win Address

```bash
nm ./picker-IV | grep win
```
Output: 

```text
000000000040129e T win
```
The win function is at 0x40129e.

Step 2: Enter the Address
The program asks:

text
Enter the address in hex to jump to, excluding '0x':
Send 40129e.

Step 3: Get the Flag
The program jumps to win and prints the flag.
