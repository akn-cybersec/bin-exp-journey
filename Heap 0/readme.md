# First Heap Overflow

**Platform:** picoCTF  
**Technique:** Heap Overflow  
**Difficulty:** Easy  

## Challenge Description

A simple heap-based buffer overflow challenge. The program allows us to allocate a buffer, write data to it, and then print something. The goal is to overwrite specific data to get the flag.

## Vulnerability

The program allocates a buffer but doesn't check input size when writing. This allows us to write beyond the buffer bounds and overwrite adjacent heap metadata or data.

## Exploitation

### Step 1: Finding the Offset

I started by fuzzing the input length to find the exact offset where overwrite happens:
- Sent increasing lengths of padding
- At 32 bytes + "X", the program behavior changed
- This indicated the offset was 32 bytes

### Step 2: Crafting the Payload

```python
payload = b"A" * offset + b"X"
```
# This payload:

b"A" * 32 – padding to reach the target location

b"X" – the value to overwrite with (could be anything, just needed to trigger)

# Step 3: Triggering the Vulnerability
The exploit follows this sequence:

Send choice 2 to allocate buffer

Send the payload to overflow the buffer

Send choice 4 to trigger the print function

When the program tries to use the corrupted heap data, it prints the flag.
