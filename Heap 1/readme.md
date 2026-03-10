# Heap 1

**Platform:** picoCTF  
**Technique:** Heap Overflow  
**Difficulty:** Easy  

## Challenge Description

A heap-based buffer overflow challenge where we need to overwrite specific data to get the flag. The program allows us to allocate a buffer, write data to it, and then print it.

## Vulnerability

The program doesn't properly check the size of input when writing to the allocated buffer. This allows us to write beyond the bounds of the buffer and overwrite adjacent heap metadata or data.

## Exploitation

### Step 1: Finding the Offset

I started by fuzzing the input length. The pattern I noticed:
- With 32 bytes of padding + "pico", the output showed `x = AApico`
- This indicated that 2 bytes of my padding were being truncated or modified
- Removing 2 bytes (offset 30) gave me clean control

### Step 2: Understanding the Flow

The program has a menu system:
1. Allocate buffer (choice 2)
2. Write data to buffer
3. Print flag (choice 4)

The vulnerability is triggered when writing more data than the allocated buffer size.

### Step 3: Crafting the Payload

```python
payload = b"A" * offset + b"pico"
