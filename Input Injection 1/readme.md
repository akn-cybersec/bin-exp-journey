# Input Injection/Buffer Overflow

**Platform:** picoCTF  
**Technique:** Buffer Overflow / Command Injection  
**Difficulty:** Easy  

## Challenge Description

A simple buffer overflow where the program takes a name input and likely passes it directly to `system()` or a similar function. The goal is to overflow the buffer and inject a command that reads the flag.

## Vulnerability

The program uses `gets()` or an unsafe read into a small buffer, then passes that buffer to `system()`. By overflowing, we can control the argument passed to `system()`.

## Exploitation

### Step 1: Finding the Offset

Through fuzzing, I determined that **10 bytes** of padding reach the point where the input becomes the argument to `system()`.

### Step 2: Crafting the Command

Instead of trying to call a separate function, we can directly inject:
cat flag.txt

text

This will be executed when the program calls `system()` on our overflowed input.

### Step 3: Building the Payload

```python
payload = b"A" * offset + command
```
b"A" * 10 – padding to reach the command argument

b"cat flag.txt" – the command to execute

Step 4: Triggering
Send the payload when prompted for name. The program executes our command and prints the flag.

