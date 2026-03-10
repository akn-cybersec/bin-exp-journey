# Return to Win

**Platform:** picoCTF  
**Technique:** Heap Overflow / Return Address Overwrite  
**Difficulty:** Easy-Medium  

## Challenge Description

A heap-based buffer overflow challenge that allows us to overwrite a return address and redirect program execution to a win function.

## Vulnerability

The program allocates a buffer on the heap but doesn't bounds-check input. Writing beyond the buffer size allows us to overwrite adjacent heap metadata and eventually control a return address stored nearby.

## Exploitation

### Step 1: Finding the Win Address

First, I needed to find the address of the function that prints the flag:

```bash
nm ./challenge | grep win
```
# This revealed:

0x4011a0 – the win function address

# Step 2: Determining the Offset
Through fuzzing, I found that:

32 bytes of padding reaches the return address

The program is 64-bit, so addresses need to be packed with p64()

# Step 3: Crafting the Payload
python
payload = b"A" * 32 + p64(win_addr)
This payload:

b"A" * 32 – padding to reach the return address

p64(win_addr) – the win function address, packed for 64-bit architecture

# Step 4: Triggering the Overflow
The exploit follows this sequence:

Send choice 2 to allocate buffer

Send the payload to overflow the buffer and overwrite the return address

Send choice 4 to trigger the function return

When the function returns, it jumps to 0x4011a0 instead of its original return address, executing the win function.
