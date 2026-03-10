# Heap Overflow with Free First

**Platform:** picoCTF  
**Technique:** Heap Overflow / Use-After-Free Pattern  
**Difficulty:** Medium  

## Challenge Description

A heap-based buffer overflow challenge with multiple steps: allocation, writing, freeing, and printing. The vulnerability requires understanding the correct sequence of operations to trigger the overflow.

## Vulnerability

The program allows heap operations in a specific order:
1. Allocate object
2. Write to buffer
3. Free object
4. Print flag

The critical insight: **you must free the object first, then use it** — a use-after-free pattern combined with heap overflow.

## Exploitation

### Step 1: Finding the Correct Flow

Initially, I tried a simple allocate → write → print sequence, but it failed. After getting a hint, I realized the correct flow requires freeing before using:

- Choice `5` – Initialize/setup
- Choice `2` – Allocate buffer
- Specify size (32 bytes)
- Write payload to buffer
- Choice `3` – Free the object
- Choice `4` – Print flag (trigger vulnerability)

### Step 2: Determining the Offset

Through fuzzing, I found:
- With 32 bytes of padding, the output showed `x = AApico`
- This meant 2 bytes of my padding were being truncated
- Reducing to 30 bytes (`offset = 30`) gave clean control

The observation: `x = AApico` indicated that 2 A's were being interpreted as part of the heap metadata, so removing them put the "pico" string exactly where needed.

### Step 3: Crafting the Payload

```python
payload = b"A" * offset + b"pico"
```
# This payload:

b"A" * 30 – padding to reach the target location

b"pico" – the value to overwrite with

# Step 4: Triggering the Vulnerability
The exploit follows this exact sequence:

Send choice 5 – setup/initialize

Send choice 2 – allocate buffer

Send size 32 – allocation size

Send payload – overflow the buffer

Send choice 3 – free the object (critical step)

Send choice 4 – print flag (use after free)
