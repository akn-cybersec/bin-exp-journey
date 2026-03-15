# Buffer Overflow 0

**Platform:** picoCTF  
**Technique:** Simple Buffer Overflow  
**Difficulty:** Easy  

## Challenge Description

A basic buffer overflow vulnerability where the program asks for input and likely copies it into a small buffer without bounds checking. An overflow causes a segmentation fault, which prints the flag. To be very honest, it was easy, and you must be thinking why easy? Cuz, I'd say, every solve matter, not in a flashy way, but in reality, every step is actually us moving toward the goal, no matter how small the step is, it takes us closer to the destination even if 0.1%.

## Vulnerability

The program uses an unsafe function like `gets()` or `strcpy()` to read input into a fixed-size buffer. Writing beyond the buffer size corrupts the stack and triggers a crash that reveals the flag.

## Exploitation

### Step 1: Identify Overflow Point

Through simple fuzzing, sending long strings of `"A"` characters causes the program to crash. The crash handler prints the flag.

### Step 2: Craft the Payload

```python
payload = "AAAA" * 32
```
This creates a string of 128 `'A'` characters — enough to overflow the buffer and trigger the crash.

Step 3: Trigger the Overflow
Send the payload when prompted for input. The program crashes and prints the flag.

