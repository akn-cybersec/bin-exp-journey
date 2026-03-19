# Integer Overflow

**Platform:** picoCTF  
**Technique:** Integer Overflow  
**Difficulty:** Easy  

## Challenge Description

A simple integer overflow challenge. The program asks for two positive numbers and performs a check that can be bypassed by exploiting how integers wrap around at their maximum value.

## Vulnerability

In C, a signed 32-bit integer can only store values from `-2,147,483,648` to `2,147,483,647`. When you add `1` to the maximum value `2,147,483,647`, it overflows and wraps around to `-2,147,483,648`.

The program likely checks something like:
```c
if (n1 > n1 + n2 || n2 > n1 + n2) {
    // print flag
}
```
Normally this condition would never be true for positive numbers — adding two positives always gives a larger number. But with integer overflow, it becomes possible.

Exploitation
Step 1: Understand the Overflow
text
2,147,483,647 + 1 = -2,147,483,648 (overflow)
Now:

n1 = 2147483647

n2 = 1

n1 + n2 = -2147483648

The condition n1 > n1 + n2 becomes 2147483647 > -2147483648 → true

Step 2: Send the Numbers
Send the maximum 32-bit signed integer and 1 to trigger the overflow.

Step 3: Get the Flag
The condition passes, and the program prints the flag.
