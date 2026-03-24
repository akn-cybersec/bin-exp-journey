# Controlled Clutter — Local Variable Overwrite

**Platform:** picoCTF  
**Technique:** Buffer Overflow / Local Variable Overwrite  
**Difficulty:** Easy  

## Challenge Description

A simple buffer overflow where we need to overwrite a local variable (`code`) to a specific value. No return address hijacking — just changing data on the stack.

## Vulnerability

The program has a buffer (`clutter`) and a local variable (`code`) on the stack. By writing past the buffer, we can overwrite `code`.

## Exploitation

### Step 1: Find the Offset

The buffer is 256 bytes. The `code` variable is immediately after it, so 256 bytes to reach the start of `code`, then 8 bytes to overwrite it.

Offset = 256 + 8 = **264 bytes**

### Step 2: Craft the Payload

```python
beef = b"\xef\xbe\xad\xde\x00\x00\x00\x00"  # 0xdeadbeef in little-endian
payload = b"A" * 264 + beef
```
b"A" * 264 — padding to reach code

beef — the value to write (0xdeadbeef)

Step 3: Trigger
Send the payload. The code variable is overwritten, and the program prints the flag.

