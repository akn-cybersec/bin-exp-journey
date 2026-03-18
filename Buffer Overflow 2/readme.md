# buffer overflow 3

**Platform:** picoCTF  
**Technique:** 32-bit ret2win with Arguments  
**Difficulty:** Easy-Medium  

## Challenge Description

A 32-bit buffer overflow where the win function requires two specific arguments. Unlike 64-bit where arguments are passed in registers, 32-bit programs expect arguments on the stack **after** the return address. A suggestion: For buffer overflow especially with partial relro, the best tool is: ```nm <binary> | grep <funtion>``` to get the address of funtion, and then overwrite. 

## Vulnerability

The program uses an unsafe read into a buffer without bounds checking, allowing us to overwrite the return address and control the stack layout.

## Exploitation

### Step 1: Find the Win Address

Using `nm` or `readelf` on the binary:

```bash
$ nm ./vuln | grep win
08049296 T win
```
The win function is at 0x08049296.

Step 2: Identify Required Arguments
From the source or reverse engineering, the win function expects:

First argument: 0xCAFEF00D

Second argument: 0xF00DF00D

Step 3: Determine the Offset
Through fuzzing with cyclic patterns, I found that 112 bytes of padding reach the return address.

Step 4: Understand 32-bit Stack Layout
In 32-bit x86 architecture:

Arguments are pushed to the stack before the function call

The call instruction pushes the return address

The called function finds its arguments at [ebp+8], [ebp+12], etc.

When we overwrite the return address, we must also provide the arguments after it in the correct positions.
