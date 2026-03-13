# Username to Shell

**Platform:** picoCTF  
**Technique:** Buffer Overflow / Command Injection  
**Difficulty:** Easy  

## Challenge Description

A buffer overflow vulnerability where the program asks for a username and passes the input to `system()` or a similar function. The goal is to overflow the buffer and inject a command to read the flag.

## Vulnerability

The program uses an unsafe function to read the username into a fixed-size buffer, then passes that buffer to `system()`. By overflowing, we control the argument passed to `system()` and can execute arbitrary commands.

## Exploitation

### Step 1: Finding the Offset

Through fuzzing, I determined that **48 bytes** of padding reach the point where the input becomes the argument to `system()`. This was found by testing different lengths until the program executed part of my input as a command.

### Step 2: Crafting the Command

Instead of using spaces (which can cause issues in buffer overflows), I used shell redirection:
cat<flag.txt

text

The `<` character feeds the file directly to `cat` without needing a space, avoiding null byte problems and making the payload cleaner.

### Step 3: Building the Payload

```python
payload = b"A" * offset + command
```
b"A" * 48 – padding to reach the command argument

b"cat<flag.txt" – the command with shell redirection

Step 4: Triggering the Overflow
Send the payload when prompted for username. The program reads our input, overflows the buffer, and passes our command to system().
