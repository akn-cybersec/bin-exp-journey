# Echo Escape 1

**Platform:** picoCTF  
**Technique:** Buffer Overflow / ret2win  
**Difficulty:** Easy  

## Challenge Description

A simple buffer overflow with a clear `win` function. No protections, no leaks, no complications. Just overflow, overwrite the return address, and win.

## Vulnerability

The program uses an unsafe function like `gets()` or `fgets()` without proper bounds checking. The buffer is too small for the input we send, so we can overwrite the return address on the stack.

## Exploitation

### Step 1: Find the Offset

Through fuzzing, I found that **40 bytes** of padding reach the return address.

### Step 2: Find the Win Address

Using `elf.symbols['win']`, I got the exact address of the `win` function.

### Step 3: Craft the Payload

```python
payload = b"A" * 40 + p64(win_addr)
```
b"A" * 40 — padding to the return address

p64(win_addr) — win function address (64-bit packing)

Step 4: Send and Win
Send the payload when prompted for the name. The function returns to win instead of its normal flow, printing the flag.
